#include <iostream>

#include "network.h"

using namespace std;

int main(int argc, char **argv) {
    int iterations{10000};

    if (argc > 1) iterations = atoi(argv[1]);

    Array X({{0, 0},
             {0, 1},
             {1, 0},
             {1, 1}});

    Array Y({{0},
             {1},
             {1},
             {0}});

    NN neuralNetwork(X.columns());
    neuralNetwork.addLayer(4, sigmoid, sigmoidDer);
    neuralNetwork.addLayer(Y.columns(), sigmoid, sigmoidDer);

    neuralNetwork.train(X, Y, iterations);

    cout << "predicted: " << neuralNetwork.predict(Array({{1, 1}}));

    return 0;
}
