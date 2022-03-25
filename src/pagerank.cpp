#include "pagerank.hpp"

Eigen::VectorX<float> PageRank::shiftedInverseTransform(float loss) {
    // TODO start transfromation at alpha=0.1
    return this->shiftedInverseTransform(0.1, loss);
}

Eigen::VectorX<float> PageRank::shiftedInverseTransform(float alpha, float loss) {
    using namespace Eigen;

    // TODO remove
    linkMatrix.conservativeResize(5,5);

    // Calculate the incoming dimention
    int inDim = this->linkMatrix.cols();

    // Create the seed vector
    VectorX<float> xk = VectorX<float>();
    xk.resize(inDim);
    xk.fill(1);

    // seed previous ck
    float ckm1 = std::numeric_limits<float>::max();
    float ck = 0;

    do {
        // Store previous value 
        ckm1 = ck;

        // Apply shifted inverse transform
        VectorXf yk = (this->linkMatrix - alpha*MatrixXf::Identity(inDim, inDim)).transpose()*xk;

        // Calculate tenative eigenvalue via the Rayleigh quotient
        // https://www.cs.cmu.edu/afs/cs/academic/class/15859n-f16/Handouts/TrefethenBau/RayleighQuotient-27.pdf
        ck = ((yk.transpose()*xk)/(xk.transpose()*xk))[0];

        // Update xk to new value
        xk = (yk/yk.norm());
    } while (abs(ck-ckm1) > loss);

    return xk;
}

