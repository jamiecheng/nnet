//
// Created by jamie on 6/28/17.
//

#ifndef NET_LAYER_HPP
#define NET_LAYER_HPP

#include <iostream>

#include "neuron.hpp"

typedef enum {
    NO,
    SIGMOID,
    LINEAR
} activation_t;

class Layer {
public:
    explicit Layer(unsigned long n_inputs) : neurons_(n_inputs, Neuron(0)),
                                             activation_(NO) {}

    explicit Layer(Layer &prevLayer, unsigned long n_neurons, activation_t act) : neurons_(n_neurons, Neuron(0)),
                                                                                  activation_(act) {
        for (auto &neuron : *prevLayer.neurons()) {
            neuron.setRandomWeights(n_neurons);
        }
    }

    void setNeuronValues(const std::vector<double> &values) {
        for (int i = 0; i < values.size(); i++) {
            neurons_[i].setValue(values[i]);
        }
    }

    std::vector<double> propagate(const std::vector<double> &values) {
        std::vector<double> output;

        for (int i = 0; i < values.size(); i++) {
            double finalValue{0.0};

            switch (activation_) {
                case LINEAR:
                    finalValue = values[i];
                    break;

                case SIGMOID:
                    finalValue = 1 / (1 + exp(-values[i]));
                    break;

                default:
                    break;
            }

            neurons_[i].setValue(finalValue);
            output.push_back(neurons_[i].value());
        }

        return output;
    }

    std::vector<double> forward() { return __dot(); }

    void print() {
        for (auto neuron : neurons_) {
            std::cout << "Neuron: (" << neuron.value() << ") [";
            for (const auto &weight : neuron.weights()) {
                std::cout << weight << ',';
            }
            std::cout << ']' << std::endl;
        }
    }

    std::vector<double> valueMatrix() {
        std::vector<double> out;

        for(auto neuron : neurons_) {
            out.push_back(neuron.value());
        }

        return out;
    }

    std::vector<std::vector<double>> weightMatrix() {
        std::vector<std::vector<double>> out;

        for(auto neuron : neurons_) {
            out.push_back(neuron.weights());
        }

        return out;
    }

    std::vector<Neuron> *neurons() { return &neurons_; }

private:
    const activation_t activation_;
    std::vector<Neuron> neurons_{};

    std::vector<double> __dot() {
        std::vector<double> dotProduct(neurons_.at(0).weights().size());

        for (auto neuron : neurons_) {
            std::vector<double> product;

            for (auto weight : neuron.weights()) {
                product.push_back(neuron.value() * weight);
            }

            for (int i = 0; i < product.size(); i++) {
                dotProduct[i] += product[i];
            }
        }

        return dotProduct;
    }
};

#endif //NET_LAYER_HPP
