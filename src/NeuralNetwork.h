#pragma once
#include "Matrix.h"

class NeuralNetwork
{
public:
	NeuralNetwork(char, char[]);
	~NeuralNetwork();

	Matrix feedForward(Matrix);

	void backpropagate(Matrix);

	void updateWeights();

private:
	std::vector<Matrix> weights;
	std::vector<Matrix> weightDeltas;
	char layers;
	std::vector<Matrix> nodeOutputs;
	std::vector<std::vector<float>> nodeErrorTerms;
	float learningRate = 0.1;
};

float sigmoid(float);

float sigmoidPrime(float);