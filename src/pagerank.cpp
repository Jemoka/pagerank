#include "pagerank.hpp"
#include <cstdio>

float PageRank::get(Eigen::Index id) {
    // Check that we actually have this page noted
    assert(id < this->linkMatrix.cols());

    // Get its cached PageRank
    return this->pagerank[id];
}

Eigen::Index PageRank::insert(std::vector<Eigen::Index> targets) {
    // Procedure to just add a node without subchild
    Eigen::Index newIndex = curr++;

    // Get a tenative max index, which does not include potential targets
    auto tenativeIndex = std::max(newIndex, this->linkMatrix.cols()-1); 

    if (targets.size() == 0) {
        // Expand the size of our sparse matrix to the tenativeindex
        (this->linkMatrix).conservativeResize(tenativeIndex+1, tenativeIndex+1);

        // Update the supernode
        for (int i = 1; i<tenativeIndex+1; i++) {
            // discounting supernode, we add 1/(num_items-1) to each link
            linkMatrix.coeffRef(i, 0) = (float) 1/((this->linkMatrix).cols()-1);
        }

        // And be done
        return newIndex;
    }

    // Get the max of the nodes in list
    auto maxIndex = std::max(*(std::max_element(std::begin(targets), std::end(targets))),
                             tenativeIndex); 

    // Expand the size of our sparse matrix
    (this->linkMatrix).conservativeResize(maxIndex+1, // +1 because 0 indexing
                                          maxIndex+1);

    // Define link weight
    float linkWeight = (float) 1/targets.size();

    // Set additional values
    for (Eigen::Index &i : targets)
        (this->linkMatrix).coeffRef(i, newIndex) += linkWeight;

    // Update the supernode
    for (int i = 1; i<maxIndex+1; i++) {
        // discounting supernode, we add 1/(num_items-1) to each link
        linkMatrix.coeffRef(i, 0) = (float) 1/((this->linkMatrix).cols()-1);
    }

    // Calculate principle eigenvector a.k.a pagerank
    this->pagerank = this->shiftedInverseTransform();

    return newIndex;
}

Eigen::VectorX<float> PageRank::shiftedInverseTransform(float loss) {
    // TODO start transfromation at alpha=0.1
    return this->shiftedInverseTransform(0.01, loss);
}

Eigen::VectorX<float> PageRank::shiftedInverseTransform(float alpha, float loss) {
    using namespace Eigen;

    // Calculate the incoming dimention
    int inDim = this->linkMatrix.cols();

    // Create the seed vector
    VectorX<float> xk = VectorX<float>();
    xk.resize(inDim);
    xk.fill(1);

    // seed previous ck
    float ckm1 = std::numeric_limits<float>::max();
    float ck = 0;

    do {
        // Store previous value 
        ckm1 = ck;

        // Apply shifted inverse transform
        VectorXf yk = (this->linkMatrix - alpha*MatrixXf::Identity(inDim, inDim)).transpose()*xk;

        // Calculate tenative eigenvalue via the Rayleigh quotient
        // https://www.cs.cmu.edu/afs/cs/academic/class/15859n-f16/Handouts/TrefethenBau/RayleighQuotient-27.pdf
        ck = ((yk.transpose()*xk)/(xk.transpose()*xk))[0];

        // Update xk to new value
        xk = (yk/yk.norm());
    } while (abs(ck-ckm1) > loss);

    return xk;
}

