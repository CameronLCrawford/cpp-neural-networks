#include "NeuralNetwork.h"
#include <math.h>

NeuralNetwork::NeuralNetwork(char layers, char neurons[]) : layers(layers)
{
	std::vector<float> weightData;
	nodeOutputs.push_back(Matrix(1, neurons[0], {}));
	for (int currentWeights = 0; currentWeights < layers - 1; currentWeights++)
	{
		weightData = {};
		char rows = neurons[currentWeights];
		char columns = neurons[currentWeights + 1];
		int currentWeightsSize = rows * columns;
		for (int randomWeight = 0; randomWeight < currentWeightsSize; randomWeight++)
		{
			weightData.push_back(((float)rand() / (RAND_MAX)) * 2 - 1);
		}
		weights.push_back(Matrix(rows, columns, weightData));
		weightDeltas.push_back(Matrix(rows, columns, std::vector<float>(currentWeightsSize, 0)));
		nodeOutputs.push_back(Matrix(1, neurons[currentWeights + 1], std::vector<float>(neurons[currentWeights + 1], 0.0f)));
		if (currentWeights != layers - 2)
		{
			nodeErrorTerms.push_back(std::vector<float>(neurons[currentWeights + 1], 0.0f));
		}
	}
}

NeuralNetwork::~NeuralNetwork()
{
}

Matrix NeuralNetwork::feedForward(Matrix inputLayer)
{
	float nodePreActivation;
	float nodeValue;
	Matrix result = inputLayer;
	nodeOutputs[0] = result;
	for (char currentLayer = 0; currentLayer < layers - 1; currentLayer++)
	{
		result = result * weights[currentLayer];
		for (char node = 0; node < result.getDimensions().columns; node++)
		{
			nodePreActivation = result(0, node);
			nodeValue = sigmoid(nodePreActivation);
			result.setData(0, node, nodeValue);
			nodeOutputs[currentLayer + 1].setData(0, node, nodeValue);
		}
	}
	return result;
}

void NeuralNetwork::backpropagate(Matrix expectedOutput)
{
	/*
	The backpropagation algorithm works on each weight instead of blindly
	mulitplying matrices by the transpose of other matrices in order to
	demonstrate the calculus at work instead of black-boxing it
	*/
	Matrix currentWeights;
	char rows, columns;
	float previousActivation;
	float currentWeight;
	float nodeOutput;
	float nodeError;
	float errorTerm;
	float weightDelta, updatedDelta;
	for (char currentLayer = layers - 2; currentLayer >= 0; currentLayer--)
	{
		currentWeights = weights[currentLayer];
		rows = currentWeights.getDimensions().rows;
		columns = currentWeights.getDimensions().columns;
		for (char row = 0; row < rows; row++)
		{
			previousActivation = nodeOutputs[currentLayer](0, row);
			for (char column = 0; column < columns; column++)
			{
				currentWeight = currentWeights(row, column);
				nodeOutput = nodeOutputs[currentLayer + 1](0, column);
				//Output layer
				if (currentLayer == layers - 2)
				{
					nodeError = expectedOutput(0, column) - nodeOutput;
					errorTerm = nodeError * sigmoidPrime(nodeOutput);
					nodeErrorTerms[currentLayer - 1][row] += errorTerm * currentWeight;
					weightDelta = learningRate * errorTerm * previousActivation;
					updatedDelta = weightDeltas[currentLayer](row, column) + weightDelta;
					weightDeltas[currentLayer].setData(row, column, updatedDelta);
				}
				else //Hidden layer
				{
					errorTerm = nodeErrorTerms[currentLayer][column] * sigmoidPrime(nodeOutput);
					if (currentLayer > 0)
					{
						nodeErrorTerms[currentLayer - 1][row] += errorTerm * currentWeight;
					}
					weightDelta = learningRate * errorTerm * previousActivation;
					updatedDelta = weightDeltas[currentLayer](row, column) + weightDelta;
					weightDeltas[currentLayer].setData(row, column, updatedDelta);
				}
			}
		}
		if (currentLayer < layers - 2)
		{
			nodeErrorTerms[currentLayer] = std::vector<float>(columns, 0.0f);
		}
	}
}

void NeuralNetwork::updateWeights()
{
	for (char currentLayer = 0; currentLayer < layers - 1; currentLayer++)
	{
		weights[currentLayer] = weights[currentLayer] + weightDeltas[currentLayer];
		weightDeltas[currentLayer] = weightDeltas[currentLayer] - weightDeltas[currentLayer];
	}
}

float sigmoid(float x)
{
	return 1 / (1 + exp(-x));
}

float sigmoidPrime(float x)
{
	return x * (1 - x);
}