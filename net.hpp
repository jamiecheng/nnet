//
// Created by jamie on 6/28/17.
//

#ifndef NET_NET_HPP
#define NET_NET_HPP

#include <algorithm>
#include "layer.hpp"

class NN {
public:
    using vector1d = std::vector<double>;
    using vector2d = std::vector<std::vector<double>>;

    explicit NN(unsigned long n_inputs) {
        layers_.push_back(Layer(n_inputs));
    }

    void addLayer(unsigned long n_neurons, activation_t act) {
        layers_.push_back(Layer(layers_.back(), n_neurons, act));
    }

    vector1d predict(vector1d input) {
        layers_.at(0).setNeuronValues(input);

        for (int i = 1; i < layers_.size(); i++) {
            if (i == layers_.size() - 1) return layers_[i].propagate(layers_[i - 1].forward());
            else layers_[i].propagate(layers_[i - 1].forward());
        }

        return vector1d();
    }

    void train(vector2d inputs, vector1d targets, int iterations) {
        for (int i = 0; i < iterations; i++) {
            for (int k = 0; k < inputs.size(); k++) {
                auto output = predict(inputs[k]).at(0);
                auto error = targets[k] - output;

                auto deltaOut = error * output * (1 - output);

                auto l2_error = std::transform(layers_[1].valueMatrix().begin(), layers_[1].valueMatrix().end(),
                                               layers_[1].valueMatrix().begin(),
                                               std::bind1st(std::multiplies<double>(), deltaOut));

//                std::cout << l2_error. << std::endl;
            }
        }
    }

private:
    std::vector<Layer> layers_;
};

#endif //NET_NET_HPP
