#include <iostream>
#include <algorithm>
#include <ostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>

class PageRank {
private: 
    Eigen::SparseMatrix<float> linkMatrix;
};

int main() {
    // Eigen::Matrix<float, 4,4> m;

    // auto eivals = m.eigenvalues();

    // std::cout << eivals << "\n";

    PageRank pr;

    return 0;
}
