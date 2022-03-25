#include "pagerank.hpp"

Eigen::Index PageRank::insert(std::vector<Eigen::Index> targets) {
    assert(targets.size() > 0);

    // Get the current size of our sparse matrix
    Eigen::Index newIndex = linkMatrix.rows();

    // Get the max of the nodes in list
    auto maxIndex = std::max(*(std::max_element(std::begin(targets), std::end(targets))),
                             newIndex); 

    // Expand the size of our sparse matrix
    auto linkmatrix = this->linkMatrix;
    linkMatrix.conservativeResize(maxIndex+1, // +1 because 0 indexing
                                  maxIndex+1);

    // Define link weight
    float linkWeight = 1/targets.size();

    // Define a type as Fliplet to create a triplet list
    typedef Eigen::Triplet<float> Fliplet;

    // Create a node insertion
    std::vector<Fliplet> nodes;

    // Create the triplet list
    for (Eigen::Index &i : targets) {
        nodes.push_back(Fliplet(i, newIndex, linkWeight));
    }

    // Add the values
    linkMatrix.setFromTriplets(nodes.begin(), nodes.end());

    // Update the supernode
    for (int i=0; i<newIndex+1; i++) {
        linkMatrix.coeffRef(i, 0) = 1/(newIndex+1);
    }

    // Calculate principle eigenvector a.k.a pagerank
    this->pagerank = this->shiftedInverseTransform();

    return newIndex;
}

Eigen::VectorX<float> PageRank::shiftedInverseTransform(float loss) {
    // TODO start transfromation at alpha=0.1
    return this->shiftedInverseTransform(0.1, loss);
}

Eigen::VectorX<float> PageRank::shiftedInverseTransform(float alpha, float loss) {
    using namespace Eigen;

    // TODO remove
    linkMatrix.conservativeResize(5,5);

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

