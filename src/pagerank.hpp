#include <Eigen/Sparse>
#include <Eigen/Dense>

#include <sys/syslimits.h>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstddef>
#include <limits>
#include <vector>

#ifndef __pagerank__hpp
#define __pagerank__hpp

class PageRank {
public:
    Eigen::Index insert(std::vector<Eigen::Index> targets);

    PageRank() {
        linkMatrix.conservativeResize(1,1);
        linkMatrix.insert(0,0) = 1;
    }
    
private: 
    Eigen::SparseMatrix<float> linkMatrix;

    Eigen::VectorX<float> shiftedInverseTransform(float alpha, float loss);
    Eigen::VectorX<float> shiftedInverseTransform(float loss=0.0001);
    
    Eigen::VectorX<float> pagerank;
};

#endif
