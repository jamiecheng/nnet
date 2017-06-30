#include <iostream>

//#include "net.hpp"
#include "matrix.hpp"

using namespace std;

Matrix nonLin(Matrix x, bool deriv = false) {
    if (deriv) return (1 - x) * x;

    return 1 / (1 + Matrix::exp(-1 * x));
}

int main() {
//    NN neuralNetwork(2);
//
//    neuralNetwork.addLayer(3, SIGMOID);
//    neuralNetwork.addLayer(1, SIGMOID);
//
//    neuralNetwork.train({{1, 1}, {1, 0}},
//                        {1, 0}, 1);
//
//    auto predicted = neuralNetwork.predict({1, 1});

    const Matrix X({{0, 0, 1},
                    {0, 1, 1},
                    {1, 0, 1},
                    {1, 1, 1}});

    const Matrix Y({{0},
                    {1},
                    {1},
                    {0}});

    auto syn0 = -1 + (2 * Matrix::randomize(Matrix(3, 4), 0, 1));
    auto syn1 = -1 + (2 * Matrix::randomize(Matrix(4, 1), 0, 1));

    for (int i = 0; i < 10000; i++) {
        auto k0 = X;
        auto k1 = nonLin(Matrix::dot(k0, syn0));
        auto k2 = nonLin(Matrix::dot(k1, syn1));

        auto k2_error = Y - k2;

        if(i % 2000 == 0) cout << Matrix::mean(k2_error) << endl;

        auto k2_delta = k2_error * nonLin(k2, true);

        auto k1_error = Matrix::dot(k2_delta, syn1.transpons());

        auto k1_delta = k1_error * nonLin(k1, true);

        syn1 = syn1 + Matrix::dot(k1.transpons(), k2_delta);
        syn0 = syn0 + Matrix::dot(k0.transpons(), k1_delta);
    }

    // predict
    auto k0 = Matrix({{0, 1, 1}});
    auto k1 = nonLin(Matrix::dot(k0, syn0));
    auto k2 = nonLin(Matrix::dot(k1, syn1));

    cout << k2 << endl;

    return 0;
}