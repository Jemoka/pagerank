#include "pagerank.hpp"
#include <cstdio>
#include <iostream>

double PageRank::get(Eigen::Index id) {
    // Check that we actually have this page noted
    assert(id < this->linkMatrix.cols());

    // Get its cached PageRank
    return this->pagerank[id];
}

double PageRank::sum() {
    // Get its cached PageRank
    return (this->pagerank).sum();
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
    double linkWeight = (double) 1/(targets.size()+1);

    // Set additional values
    for (Eigen::Index &i : targets)
        (this->linkMatrix).coeffRef(i,newIndex) += linkWeight;

    // Set supernode
    linkMatrix.coeffRef(0,newIndex) = linkWeight;

    // Update the supernode
    for (int i = 1; i<maxIndex+1; i++) 
        // discounting supernode, we add 1/(num_items-1) to each link
        linkMatrix.coeffRef(i,0) = (double) 1/((this->linkMatrix).cols()-1);

    // Calculate principle eigenvector a.k.a pagerank
    this->pagerank = this->powerMethod();

    return newIndex;
}

Eigen::VectorX<double> PageRank::powerMethod(int n) {
    using namespace Eigen;

    // Calculate the incoming dimention
    int inDim = this->linkMatrix.cols();

    // Create the seed vector
    VectorX<double> xk = VectorX<double>();
    xk.resize(inDim);
    xk.fill((float) 1/(inDim));

    // Go Ham
    for (int i=0; i<n; i++) {
        // Set damping
        double DAMP = 0.85;
        // Calculate the damping vector
        VectorX<double> damp = VectorX<double>();
        damp.resize(inDim);
        damp.fill((1-DAMP));
        // We first apply the matrix upon xk
        xk = damp+DAMP*(this->linkMatrix)*xk;
    }

    return xk;
}

