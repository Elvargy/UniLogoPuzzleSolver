#pragma once

class Matrix
{
public: 
	
	Matrix();

	Matrix(int sizeR, int sizeC, double* input_data);
	Matrix(int sizeR, int sizeC);
	Matrix(const Matrix& m);
	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator*(const Matrix& other);
	Matrix operator/(const Matrix& other);
	Matrix operator=(const Matrix& other);
	double operator()(int i, int j);
	void Matrix::setBlock(int rowS, int colS, Matrix& toSet);
	int getM();
	int getN();
	Matrix getBlock(int startRow, int endRow, int startColumn, int endColumn);
	double Matrix::Add();
	double* getData();
	int _M, _N;
	double* _data;
	
	~Matrix();

	
};