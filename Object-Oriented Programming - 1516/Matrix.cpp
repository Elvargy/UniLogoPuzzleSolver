#include <sstream> 
#include <iostream> 
#include <fstream> 
#include <istream>
#include <cmath>
#include "Matrix.h"

using namespace std;

Matrix::Matrix()
{
	_M = 1;
	_N = 1;

	_data = new double[_M*_N];
	
	for (int x = 0; x < _M*_N; x++)
	{
		_data[x] = 0;
	}

}

Matrix::Matrix(int sizeR, int sizeC, double* input_data)
{
	_M = sizeR;
	_N = sizeC;

	_data = new double[_M*_N];

	for (int x = 0; x < _M*_N; x++)
	{
		_data[x] = input_data[x];
	}
}

Matrix::Matrix(int sizeR, int sizeC)
{
	_M = sizeR;
	_N = sizeC;
	_data = new double[(_M*_N)];

	for (int ii = 0; ii < _M*_N; ii++)
	{
		*(_data + ii) = 0;
	}
}
//copy constructor
Matrix::Matrix(const Matrix& m)
{	
	_M = m._M;
	_N = m._N;

	_data = new double[_M*_N];

	for (int i = 0; i < _M*_N; i++)
	{
		_data[i] = m._data[i];
	}
}

//operator overloads
Matrix Matrix::operator+(const Matrix& other)
{
	Matrix temp;
	temp._M = other._M;
	temp._N = other._N;

	temp._data = new double[temp._M*temp._N];

	for (int x = 0; x < (temp._M*temp._N); x++)
	{
		temp._data[x] = this->_data[x] + other._data[x];
	}

	return temp;
}

Matrix Matrix::operator-(const Matrix& other)
{
	Matrix temp;
	temp._M = other._M;
	temp._N = other._N;

	temp._data = new double[temp._M*temp._N];

	for (int x = 0; x < (temp._M*temp._N); x++)
	{
		temp._data[x] = this->_data[x] - other._data[x];
	}

	return temp;
}

Matrix Matrix::operator*(const Matrix& other)
{
	Matrix temp;
	temp._M = other._M;
	temp._N = other._N;

	temp._data = new double[temp._M*temp._N];

	for (int x = 0; x < (temp._M*temp._N); x++)
	{
		temp._data[x] = this->_data[x] * other._data[x];
	}

	return temp;
}

Matrix Matrix::operator/(const Matrix& other)
{
	Matrix temp;
	temp._M = other._M;
	temp._N = other._N;

	temp._data = new double[temp._M*temp._N];

	for (int x = 0; x < (temp._M*temp._N); x++)
	{
		temp._data[x] = this->_data[x] / other._data[x];
	}

	return temp;
}

Matrix Matrix::operator=(const Matrix& other)
{
	delete[] _data;
	_M = other._M;
	_N = other._N;

	//Memory allocated for new array
	_data = new double[_M*_N];

	//'this' pointer refers to the current object
	for (int x = 0; x < (_M*_N); x++)
	{
		this->_data[x] = other._data[x];
	}
	return *this;
}

double Matrix::operator()(int i, int j)
{
	return _data[(i*_N) + j];
}

void Matrix::setBlock(int rowS, int colS, Matrix& toSet)
{
	for (int i = 0; i < toSet._M; i++)
	{
		for (int j = 0; j < toSet._N; j++)
		{
			_data[((rowS + i) *_N) + (colS + j)] = toSet(i, j);
		}
	}
}
//Functions
int Matrix::getM()
{
	return _M;
}

int Matrix::getN()
{
	return _N;
}

Matrix Matrix::getBlock(int start_row, int end_row, int start_column, int end_column)
{
	
	int rows = (end_row - start_row);
	int columns = (end_column - start_column);

	double* tempData = new double[rows * columns];

	int index = 0;
	
	for (int x = start_row; x < end_row; x++)
	{
		for (int y = start_column; y < end_column; y++)
		{
			tempData[index] = _data[x*_N + y];
			index++;
		}
	}
	
	Matrix temp(rows, columns, tempData);
	delete[] tempData;
	return temp;
}

double Matrix::Add()
{
	double add = 0;
	for (int x = 0; x < (_M*_N); x++)
	{
		add = add + _data[x];
	}
	return add;
}


double* Matrix::getData()
{
	return _data;
}


Matrix::~Matrix()
{
	delete[] _data;
}
//git test