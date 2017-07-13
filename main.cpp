#include <iostream>

#include "network.h"
#include "array.h"
#include "tests.h"

using namespace std;

int main() {
  Array X({{0, 0, 1},
           {0, 1, 1},
           {1, 0, 1},
           {1, 1, 1}});

  Array Y({{0},
           {1},
           {1},
           {0}});

  NN neuralNetwork(3);
  neuralNetwork.addLayer(4, sigmoid);
  neuralNetwork.addLayer(1, sigmoid);

  neuralNetwork.train(X, Y, 10000);

  cout << neuralNetwork.predict(Array({{0, 1, 1}}));

//  double error = 100.0;

//  // pre declare layers
//  Array k0(4, 3), k1(4, 4), k2(1, 4);

//  auto syn0 = (Array::randomize(Array(3, 4), 0, 1) * 2) + -1;
//  auto syn1 = (Array::randomize(Array(4, 1), 0, 1) * 2) + -1;

//  for (int i = 0; i < 60000 && error > 0.01; i++) {
//      k0 = X;
//      k1 = sigmoid(k0.dot(syn0));
//      k2 = sigmoid(k1.dot(syn1));

//      auto k2_error = Y - k2;
//      error = Array::mean(k2_error);

//      if (i % 2000 == 0) cout << Array::mean(k2_error) << endl;

//      auto k2_delta = k2_error * sigmoid(k2, true);

//      auto k1_error = k2_delta.dot(syn1.transpons());

//      auto k1_delta = k1_error * sigmoid(k1, true);

//      syn1 = syn1 + k1.transpons().dot(k2_delta);
//      syn0 = syn0 + k0.transpons().dot(k1_delta);
//    }

//  // predict
//  k0 = Array({{1, 0, 1}});
//  k1 = sigmoid(k0.dot(syn0));
//  k2 = sigmoid(k1.dot(syn1));

//  cout << "predicted: " << Array::mean(k2) << endl;

  return 0;
}

//TEST_MAIN
