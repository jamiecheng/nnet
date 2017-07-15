#ifndef ACTIVATIONS_H
#define ACTIVATIONS_H

#include "array.h"

//Array sigmoid(const Array &x, bool deriv = false) {
//  if (deriv) return (1.0 - x) * x;
//
//  return x.unaryExpr(&sigmoid2);//1 / (Array::exp(x * -1.0) + 1.0);
//}

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoidDer(double x) {
    return (1.0 - x) * x;
}

#endif // ACTIVATIONS_H
