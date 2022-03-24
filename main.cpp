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
    Eigen::SparseMatrix<float> m;
    m.conservativeResize(10, 10);

    m.insert(1,4) = 17;

    std::cout << m.coeffRef(1,4) << "\n";

    // 
    // auto eivals = m.eigenvalues();

    // for (int i=0; i<=1000; i++) {
    // }

    // PageRank pr;

    return 0;
}
