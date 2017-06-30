#include <iostream>

//#include "net.hpp"
#include "array.hpp"

using namespace std;

Array nonLin(const Array &x, bool deriv = false) {
    if (deriv) return (1 - x) * x;

    return 1 / (1 + Array::exp(-1 * x));
}

int main() {
    const Array X({{0, 0, 1},
                   {0, 1, 1},
                   {1, 0, 1},
                   {1, 1, 1}});

    const Array Y({{0},
                   {1},
                   {1},
                   {0}});

    auto syn0 = -1 + (2 * Array::randomize(Array(3, 4), 0, 1));
    auto syn1 = -1 + (2 * Array::randomize(Array(4, 1), 0, 1));

    for (int i = 0; i < 10000; i++) {
        auto k0 = X;
        auto k1 = nonLin(Array::dot(k0, syn0));
        auto k2 = nonLin(Array::dot(k1, syn1));

        auto k2_error = Y - k2;

        if (i % 2000 == 0) cout << Array::mean(k2_error) << endl;

        auto k2_delta = k2_error * nonLin(k2, true);

        auto k1_error = Array::dot(k2_delta, syn1.transpons());

        auto k1_delta = k1_error * nonLin(k1, true);

        syn1 = syn1 + Array::dot(k1.transpons(), k2_delta);
        syn0 = syn0 + Array::dot(k0.transpons(), k1_delta);
    }

    // predict
    auto k0 = Array({{1, 0, 1}});
    auto k1 = nonLin(Array::dot(k0, syn0));
    auto k2 = nonLin(Array::dot(k1, syn1));

    cout << "predicted: " << Array::mean(k2) << endl;

    return 0;
}