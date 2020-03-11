#pragma once
#include <iostream>
#include <vector>
#include <memory>

struct Dimensions
{
	char rows;
	char columns;
};

float dotProduct(float *, float *, char);

class Matrix
{
public:
	Matrix(char, char, std::vector<float>);

	Matrix();

	~Matrix();

	Dimensions getDimensions();

	void setData(char, char, float);

	float operator()(char row, char column);

	Matrix operator*(Matrix &);

	Matrix operator+(Matrix &);

	Matrix operator-(Matrix &);

	friend std::ostream& operator<<(std::ostream &, Matrix &);

private:
	std::vector<float> matrixData;
	Dimensions matrixDimensions;
};