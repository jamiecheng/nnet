#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>

#include "array.h"
#include "activations.h"

namespace nnet {
    struct Layer {
        Array weights;

        double (*aCallback)(double);

        double (*aCallbackDer)(double);
    };

    class NN {
    public:
        NN(unsigned long n_inputs) {
            layers_.push_back({Array(n_inputs, 1), sigmoid, sigmoidDer});
        }

        void addLayer(unsigned long nodes, double(*aCallback)(double), double(*aCallbackDer)(double)) {
            layers_.back().weights = (Array::randomize(Array(layers_.back().weights.rows(), nodes), 0, 1) * 2) + -1;
            layers_.push_back({Array(nodes, 1), aCallback, aCallbackDer});
        }

        void train(const Array &inputs, const Array &correctOutputs, int epochs) {
            using namespace std;

            layerValues_ = std::vector<Array>(layers_.size(), Array(0, 0));

            for (int i = 0; i < epochs; i++) {
                // propagate
                Array output = __forward(inputs);

                if (i % 10000 == 0) cout << "error: " << Array::mean(correctOutputs - output) << endl;

                __backpropagate(correctOutputs);
            }
        }

        Array predict(const Array &input) {
            return __forward(input);
        }

    private:
        std::vector<Layer> layers_;
        std::vector<Array> layerValues_;

        Array __forward(const Array &inputs) {
            // input of the network
            layerValues_[0] = inputs;

            for (unsigned long i = 1; i < layers_.size(); i++) {
                layerValues_[i] = layerValues_[i - 1].dot(layers_.at(i - 1).weights).unaryExpr(layers_.at(i).aCallback);
            }

            return layerValues_.back();
        }

        void __backpropagate(const Array &target) {
            std::vector<Array> deltas(layers_.size(), Array(0, 0));

            // output layer
            deltas.back() = (target - layerValues_.back()) * layerValues_.back().unaryExpr(layers_.back().aCallbackDer);

            for (int i = deltas.size() - 2; i >= 0; i--) {
                auto error = deltas[i + 1].dot(layers_.at(i).weights.transponse());
                deltas[i] = error * layerValues_[i].unaryExpr(layers_[i].aCallbackDer);
            }

            // adjust weights
            for (int i = 0; i < layers_.size() - 1; i++) {
                layers_[i].weights = layers_[i].weights + layerValues_[i].transponse().dot(deltas[i + 1]);
            }
        }
    };

}

#endif // NETWORK_H
