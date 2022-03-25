// Other people's headers
#include <iostream>
#include <algorithm>
#include <ostream>
#include <vector>

// Our Headers
#include "src/pagerank.hpp"

int main() {
    PageRank pr;

    // Create vectors encoding the links of every object
    std::vector<Eigen::Index> a;
    a.push_back(4);
    a.push_back(3);
    a.push_back(2);

    std::vector<Eigen::Index> b;
    b.push_back(1);
    b.push_back(3);

    std::vector<Eigen::Index> c;
    c.push_back(2);
    c.push_back(1);

    std::vector<Eigen::Index> d;
    c.push_back(2);
    
    // Push the links to the pagerank calculator
    pr.insert(a);
    pr.insert(b);
    pr.insert(c);

    // Get the page rank of each page
    std::cout << pr.get(1) << std::endl;
    std::cout << pr.get(2) << std::endl;
    std::cout << pr.get(3) << std::endl;
    std::cout << pr.get(4) << std::endl;

    return 0;
}

