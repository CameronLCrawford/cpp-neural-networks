#include <iostream>
#include "NeuralNetwork.h"
#include <memory>
#include <fstream>
#include <string>

int main()
{
	std::vector<Matrix> trainData;
	std::vector<Matrix> trainOutput;
	std::vector<Matrix> testData;
	std::vector<Matrix> testOutput;
	std::ifstream irisFile("iris.data");
	float sepalLength, sepalWidth, petalLength, petalWidth;
	std::string flowerType;
	for (int currentData = 0; currentData < 150; currentData++)
	{
		irisFile >> sepalLength >> sepalWidth >> petalLength >> petalWidth >> flowerType;
		if (50 - currentData % 50 > 10)
		{
			trainData.push_back(Matrix(1, 4, { sepalLength, sepalWidth, petalLength, petalWidth }));
			if (flowerType == "Iris-setosa") trainOutput.push_back(Matrix(1, 3, { 1.0f, 0.0f, 0.0f }));
			if (flowerType == "Iris-versicolor") trainOutput.push_back(Matrix(1, 3, { 0.0f, 1.0f, 0.0f }));
			if (flowerType == "Iris-virginica") trainOutput.push_back(Matrix(1, 3, { 0.0f, 0.0f, 1.0f }));
		}
		else
		{
			testData.push_back(Matrix(1, 4, { sepalLength, sepalWidth, petalLength, petalWidth }));
			if (flowerType == "Iris-setosa") testOutput.push_back(Matrix(1, 3, { 1.0f, 0.0f, 0.0f }));
			if (flowerType == "Iris-versicolor") testOutput.push_back(Matrix(1, 3, { 0.0f, 1.0f, 0.0f }));
			if (flowerType == "Iris-virginica") testOutput.push_back(Matrix(1, 3, { 0.0f, 0.0f, 1.0f }));
		}
	}
	srand(0);
	char networkParamaters[3]{ 4, 5, 3 };
	NeuralNetwork myNN(3, networkParamaters);
	Matrix networkOutput;
	float averageError = 0;
	int epochs = 500;
	std::cout << "Training";
	for (int epoch = 0; epoch < epochs; epoch++)
	{
		for (int inputIndex = 0; inputIndex < 120; inputIndex++)
		{
			myNN.feedForward(trainData[inputIndex]);
			myNN.backpropagate(trainOutput[inputIndex]);
			myNN.updateWeights();
		}
		if (epoch % (epochs / 10) == 0)
		{
			std::cout << ".";
		}
	}
	std::cout << "\nTraining complete.\n \nEvaluating...\n";
	for (int inputIndex = 0; inputIndex < 30; inputIndex++)
	{
		networkOutput = myNN.feedForward(testData[inputIndex]);
		std::cout << networkOutput << '\n';
		averageError += abs(testOutput[inputIndex](0, 0) - networkOutput(0, 0));
		averageError += abs(testOutput[inputIndex](0, 1) - networkOutput(0, 1));
		averageError += abs(testOutput[inputIndex](0, 2) - networkOutput(0, 2));
	}
	std::cout << "Final Cost: " << averageError / 90 << '\n';
	int end;
	std::cin >> end;
	return 0;
}