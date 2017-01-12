#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

static const int ROWS = 3;
static const int COLS = 3;

using namespace std;

typedef float Matrix[ROWS][COLS];

void ReadMatrixFromFile(ifstream &input, Matrix &matrix);
float CalculateDeterminantOfMatrix(Matrix const &matrix);
float FindDeterminantOfMinor(float a11, float a12, float a21, float a22);
float FindMinor(Matrix const &matrixOfMinors, const int row, const int col);
void CalculateMatrixOfAlgebraicAdditions(const Matrix &matrix, Matrix &matrixOfMinors);
void InvertMatrix(const Matrix &matrixOfMinors, Matrix &inverseMatrix, const float determinant);
void PrintInverseMatrix(const Matrix &inverseMatrix);

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n" << "Usage: invert.exe <input file>\n";
		return 1;
	}

	ifstream input(argv[1]);
	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	Matrix matrix, MatrixOfAlgebraicAdditions, inverseMatrix;
	ReadMatrixFromFile(input, matrix);

	float determinant = CalculateDeterminantOfMatrix(matrix);
	if (determinant == 0)
	{
		cout << "Inverse matrix doesn't exist\n";
		return 1;
	}

	CalculateMatrixOfAlgebraicAdditions(matrix, MatrixOfAlgebraicAdditions);
	InvertMatrix(MatrixOfAlgebraicAdditions, inverseMatrix, determinant);
	PrintInverseMatrix(inverseMatrix);
    return 0;
}

void ReadMatrixFromFile(ifstream &input, Matrix &matrix)
{
	for (int i = 0; i < ROWS; ++i)
		for (int j = 0; j < COLS; ++j)
			input >> matrix[i][j];
}

float CalculateDeterminantOfMatrix(Matrix const &matrix)
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[0][2] * matrix[1][0] * matrix[2][1]
		- matrix[0][0] * matrix[1][2] * matrix[2][1]
		- matrix[0][1] * matrix[1][0] * matrix[2][2]
		- matrix[0][2] * matrix[1][1] * matrix[2][0];
}

float FindDeterminantOfMinor(float a11, float a12, float a21, float a22)
{
	return a11 * a22 - a12 * a21;
}

float FindMinor(Matrix const &matrix, const int row, const int col)
{
	float minor[4];
	int index = 0;
	for (int i = 0; i < ROWS; ++i)
	{
		if (i != row)
		{
			for (int j = 0; j < COLS; ++j)
			{
				if (j != col)
				{
					minor[index] = matrix[i][j];
					++index;
				}
			}
		}
	}
	return FindDeterminantOfMinor(minor[0], minor[1], minor[2], minor[3]);
}

void CalculateMatrixOfAlgebraicAdditions(const Matrix &matrix, Matrix &MatrixOfAlgebraicAdditions)
{
	for (int i = 0; i < ROWS; ++i)
		for (int j = 0; j < COLS; ++j)
			MatrixOfAlgebraicAdditions[j][i] = ((i + j) % 2 != 0 ? FindMinor(matrix, i, j) * (-1) : FindMinor(matrix, i, j));
}

void InvertMatrix(const Matrix &MatrixOfAlgebraicAdditions, Matrix &inverseMatrix, const float determinant)
{
	for (int i = 0; i < ROWS; ++i)
		for (int j = 0; j < COLS; ++j)
			inverseMatrix[i][j] = (1 / determinant) * MatrixOfAlgebraicAdditions[i][j];
}

void PrintInverseMatrix(const Matrix &inverseMatrix)
{
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			cout << fixed << setprecision(3) << inverseMatrix[i][j] << " ";
		}
		cout << "\n";
	}
}