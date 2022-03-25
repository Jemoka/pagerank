// Other people's headers
#include <iostream>
#include <algorithm>
#include <ostream>
#include <vector>

// Our Headers
#include "src/pagerank.hpp"

int main() {
    PageRank pr;

    std::vector<Eigen::Index> a;
    a.push_back(4);
    a.push_back(3);
    a.push_back(2);

    std::vector<Eigen::Index> b;
    a.push_back(1);
    a.push_back(3);

    std::vector<Eigen::Index> c;
    a.push_back(2);
    a.push_back(1);
    
    pr.insert(a);
    pr.insert(b);
    pr.insert(c);

    return 0;
}

