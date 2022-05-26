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
    a.push_back(2);
    a.push_back(3);

    std::vector<Eigen::Index> b;
    b.push_back(3);

    std::vector<Eigen::Index> c;
    c.push_back(1);

    std::vector<Eigen::Index> d;
    d.push_back(3);
    
    // Push the links to the pagerank calculator
    pr.insert(a);
    pr.insert(b);
    pr.insert(c);
    pr.insert(d);

    // Get the page rank of each page
    printf("Page 1 Rank: %.2f\n", pr.get(1)); 
    printf("Page 2 Rank: %.2f\n", pr.get(2)); 
    printf("Page 3 Rank: %.2f\n", pr.get(3)); 
    printf("Page 4 Rank: %.2f\n", pr.get(4)); 

    return 0;
}

