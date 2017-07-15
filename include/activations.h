#ifndef ACTIVATIONS_H
#define ACTIVATIONS_H

#include "array.h"

namespace nnet {
    double sigmoid(double x) {
        return 1.0 / (1.0 + exp(-x));
    }

    double sigmoidDer(double x) {
        return (1.0 - x) * x;
    }
}

#endif // ACTIVATIONS_H
