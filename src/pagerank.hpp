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
    float get(Eigen::Index id);

    Eigen::SparseMatrix<float> linkMatrix;
    PageRank() {
        linkMatrix.conservativeResize(1,1);
        linkMatrix.insert(0,0) = 0;
    }
    
private: 
    Eigen::Index curr= 1;

    Eigen::VectorX<float> powerMethod(int n=1000);
    
    Eigen::VectorX<float> pagerank;
};

#endif
