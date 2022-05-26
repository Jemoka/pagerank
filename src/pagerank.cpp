#include "pagerank.hpp"
#include <cstdio>
#include <iostream>

float PageRank::get(Eigen::Index id) {
    // Check that we actually have this page noted
    assert(id < this->linkMatrix.cols());

    this->pagerank = this->powerMethod();
    // Get its cached PageRank
    return this->pagerank[id];
}

Eigen::Index PageRank::insert(std::vector<Eigen::Index> targets) {
    assert(targets.size() > 0);

    // Get the current size of our sparse matrix
    Eigen::Index newIndex = curr++;

    // Get the max of the nodes in list
    auto maxIndex = std::max(*(std::max_element(std::begin(targets), std::end(targets))),
                             std::max(newIndex, this->linkMatrix.cols()-1)); 

    // Expand the size of our sparse matrix
    (this->linkMatrix).conservativeResize(maxIndex+1, // +1 because supernode
                                          maxIndex+1);

    // Define link weight
    float linkWeight = (float) 1/(targets.size()+1);

    // Set supernode
    linkMatrix.coeffRef(0,newIndex) = linkWeight;

    // Set additional values
    for (Eigen::Index &i : targets)
        (this->linkMatrix).coeffRef(i, newIndex) += linkWeight;

    // Update the supernode
    for (int i = 1; i<maxIndex+1; i++) 
        // discounting supernode, we add 1/(num_items-1) to each link
        linkMatrix.coeffRef(i,0) = (float) 1/((this->linkMatrix).cols()-1);

    // Calculate principle eigenvector a.k.a pagerank
    // this->pagerank = this->powerMethod();

    return newIndex;
}

Eigen::VectorX<float> PageRank::powerMethod(int n) {
    using namespace Eigen;

    // Calculate the incoming dimention
    int inDim = this->linkMatrix.cols();

    // Create the seed vector
    VectorX<float> xk = VectorX<float>();
    xk.resize(inDim);
    xk.fill(1);

    // Go Ham
    for (int i=0; i<n; i++) {
        // Set damping
        float DAMP = 1;
        // Calculate the damping vector
        VectorX<float> damp = VectorX<float>();
        damp.resize(inDim);
        damp.fill((1-DAMP));
        // We first apply the matrix upon xk
        xk = damp+DAMP*(linkMatrix)*xk;
        xk.normalize();
    }

    return xk/(1+0.25*inDim);
}

