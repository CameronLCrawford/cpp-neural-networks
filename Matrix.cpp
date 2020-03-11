#include "Matrix.h"
#include <stdexcept>
#include <string>

Matrix::Matrix(char rows, char columns, std::vector<float> data)
	: matrixData(data)
{
	matrixDimensions = { rows, columns };
}

Matrix::Matrix()
{

}

Matrix::~Matrix()
{
}

Dimensions Matrix::getDimensions()
{
	return matrixDimensions;
}

void Matrix::setData(char row, char column, float data)
{
	matrixData[row * matrixDimensions.columns + column] = data;
}

float Matrix::operator()(char row, char column)
{
	return matrixData[row * matrixDimensions.columns + column];
}

Matrix Matrix::operator*(Matrix &otherMatrix)
{
	if (matrixDimensions.columns != otherMatrix.getDimensions().rows)
		throw std::invalid_argument("matrices are of invalid dimensions to be multiplied");
	char thisRows = matrixDimensions.rows;
	char thisColumns = matrixDimensions.columns;
	char otherRows = otherMatrix.getDimensions().rows;
	char otherColumns = otherMatrix.getDimensions().columns;
	std::vector<float> resultData;
	float *currentRow = new float[thisColumns];
	float *currentColumn = new float[otherRows];
	for (char row = 0; row < thisRows; row++)
	{
		for (char column = 0; column < otherColumns; column++)
		{
			for (char k = 0; k < thisColumns; k++)
			{
				currentRow[k] = matrixData[row * thisColumns + k];
			}
			for (char k = 0; k < otherRows; k++)
			{
				currentColumn[k] = otherMatrix.matrixData[column + otherColumns * k];
			}
			resultData.push_back(dotProduct(currentRow, currentColumn, thisColumns));
		}
	}
	delete currentRow;
	delete currentColumn;
	return Matrix(thisRows, otherColumns, resultData);
}

Matrix Matrix::operator+(Matrix &otherMatrix)
{
	std::vector<float> resultData;
	for (int row = 0; row < matrixDimensions.rows; row++)
	{
		for (int column = 0; column < matrixDimensions.columns; column++)
		{
			float thisValue = matrixData[row * matrixDimensions.columns + column];
			float otherValue = otherMatrix(row, column);
			resultData.push_back(thisValue + otherValue);
		}
	}
	return Matrix(matrixDimensions.rows, matrixDimensions.columns, resultData);
}

Matrix Matrix::operator-(Matrix &otherMatrix)
{
	std::vector<float> resultData;
	for (int row = 0; row < matrixDimensions.rows; row++)
	{
		for (int column = 0; column < matrixDimensions.columns; column++)
		{
			float thisValue = matrixData[row * matrixDimensions.columns + column];
			float otherValue = otherMatrix(row, column);
			resultData.push_back(thisValue - otherValue);
		}
	}
	return Matrix(matrixDimensions.rows, matrixDimensions.columns, resultData);
}

std::ostream& operator<<(std::ostream &ostream, Matrix &thisMatrix)
{
	char rowCount = thisMatrix.matrixDimensions.rows;
	char columnCount = thisMatrix.matrixDimensions.columns;
	std::vector<float> matrix = thisMatrix.matrixData;
	int *significantFigures = new int[columnCount] {};
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			int dataSignificantFigures = std::to_string((int)matrix[i * columnCount + j]).length();
			if (dataSignificantFigures > significantFigures[columnCount])
			{
				significantFigures[j] = dataSignificantFigures + 7;
			}
		}
	}
	for (char row = 0; row < rowCount; row++)
	{
		for (char column = 0; column < columnCount; column++)
		{
			std::string data = std::to_string(matrix[row * columnCount + column]);
			if (data.length() < significantFigures[column])
			{
				ostream << data << ' ';
				for (int i = 0; i < significantFigures[column] - data.length(); i++)
				{
					ostream << ' ';
				}
			}
			else
			{
				data.erase(significantFigures[column], std::string::npos);
				ostream << data << ' ';
			}
		}
		ostream << '\n';
	}
	delete significantFigures;
	return ostream;
}

float dotProduct(float *row, float *column, char size)
{
	float result = 0;
	for (int i = 0; i < size; i++)
	{
		result += row[i] * column[i];
	}
	return result;
}