#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>

#include "array.h"
#include "activations.h"

struct Weights {
  Array weights;
  Array (*aCallback)(const Array&, bool);
};

class NN {
public:
  NN(int n_inputs) {
    weights_.push_back({Array(n_inputs, 1), sigmoid});
  }

  void addLayer(int nodes, Array(*aCallback)(const Array&, bool)) {
    weights_.back().weights = (Array::randomize(Array(weights_.back().weights.rows(), nodes), 0, 1) * 2) + -1;
    weights_.push_back({Array(nodes, 1), aCallback});
  }

  void train(const Array &inputs, const Array &correctOutputs, int epochs) {
    using namespace std;

    layerValues_ = std::vector<Array>(weights_.size(), Array(0, 0));

    for(int i = 0; i < epochs; i++) {
        // propagate
        Array output = __forward(inputs);

        if (i % 10000 == 0) cout << Array::mean(correctOutputs - output) << endl;

        __backpropagate(correctOutputs);
      }
  }

  Array predict(const Array &input) {
    return __forward(input);
  }

private:
  std::vector<Weights> weights_;
  std::vector<Array> layerValues_;

  Array __forward(const Array &inputs) {
    // input of the network
    layerValues_[0] = inputs;

    for(unsigned long i = 1; i < weights_.size(); i++) {
        layerValues_[i] = weights_.at(i).aCallback(layerValues_[i - 1].dot(weights_.at(i - 1).weights), false);
      }

    return layerValues_.back();
  }

  void __backpropagate(const Array &target) {
    std::vector<Array> deltas(weights_.size(), Array(0, 0));

    // output layer
    deltas.back() = (target - layerValues_.back()) * weights_.back().aCallback(layerValues_.back(), true);

    for(int i = deltas.size() - 2; i >= 0; i--) {
        auto error = deltas[i + 1].dot(weights_.at(i).weights.transpons());
        deltas[i] = error * weights_[i].aCallback(layerValues_[i], true);
      }

    // adjust weights
    for(int i = 0; i < weights_.size() - 1; i++) {
        weights_[i].weights = weights_[i].weights + layerValues_[i].transpons().dot(deltas[i + 1]);
      }
  }
};

#endif // NETWORK_H
