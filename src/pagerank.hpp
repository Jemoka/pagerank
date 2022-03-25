#include <Eigen/Sparse>
#include <Eigen/Dense>

#include <iostream>
#include <limits>

#ifndef __pagerank__hpp
#define __pagerank__hpp

class PageRank {
 private: 
    Eigen::SparseMatrix<float> linkMatrix;
 public:
    Eigen::VectorX<float> shiftedInverseTransform(float alpha, float loss);
    Eigen::VectorX<float> shiftedInverseTransform(float loss=0.0001);
};

#endif
