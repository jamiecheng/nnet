//
// Created by jamie on 6/28/17.
//

#ifndef NET_NODE_HPP
#define NET_NODE_HPP

#include <utility>
#include <vector>
#include <random>
#include <map>

class Neuron {
public:
    explicit Neuron(int val) : value_(val) {}

    explicit Neuron(std::vector<double> weights) : weights_(weights) {}

    void setRandomWeights(unsigned long n_weights) {
        weights_ = std::vector<double>(n_weights);

        for(auto &weight : weights_) {
            weight = randomWeight();
        }
    }

    std::vector<double> weights() const { return weights_; }

    void setValue(double val) {
        value_ = val;
    }

    double value() const { return value_; }

    static double randomWeight() {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_real_distribution<double> uni(0, 1);

        return uni(rng);
    }

private:
    double value_{};
    std::vector<double> weights_;
};

#endif //NET_NODE_HPP
