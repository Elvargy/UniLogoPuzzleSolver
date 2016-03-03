#include <sstream> 
#include <iostream> 
#include <fstream> 
#include <istream>
#include <cmath>
#include <math.h>
#include "Matrix.h"

using namespace std;

//Prototyping for NSS algorithm 
Matrix NNS(Matrix& noisy, Matrix& shuffle);

//Variable Declarations
double* readTXT(char *fileName, int sizeR, int sizeC);
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q);

//Main
int main()
{
	
	int row = 512;
	int column = 512;
	
	double* dataShuffled = 0;
    double*  dataNoisy = 0;

	cout << endl;
	cout << "..........Processing data from text file.........." << endl;
		
	char* logoShuffled = "shuffled_logo.txt";
    char* logoNoisy = "unshuffled_logo_noisy.txt";

	dataShuffled = readTXT("shuffled_logo.txt", row, column);
	dataNoisy = readTXT("unshuffled_logo_noisy.txt", row, column);

	Matrix matrixShuffled(row, column, dataShuffled);
	Matrix matrixNoisy(row, column, dataNoisy);
	Matrix matrixCompared(512, 512);
	
	//Denoise Algorithm
	for (int i = 0; i < 511; i++)
	{
		for (int j = 0; j < 511; j++)
		{
			if (i >= 0 && i < 512 && j >= 0 && j < 512)
			{
				double pixel = matrixNoisy(i, j);
				double pixelx = matrixNoisy(i + 1, j);
				if (pixel == 255 && pixelx == 0)
				{
					matrixNoisy._data[i*matrixNoisy._N+j]=0;
				}
			}
		}
	}

	matrixCompared = NNS(matrixNoisy, matrixShuffled);

	char* fileName = "unshuffled_logo.pgm";
	WritePGM(fileName, matrixCompared.getData(), 512, 512, 255);

	// Delete Data
	delete[] dataNoisy;
	delete[] dataShuffled;
	//system("PAUSE");
	return 0;
}


// Read .txt file with image of size RxC, and convert to an array of doubles
	double* readTXT(char *fileName, int sizeR, int sizeC)
{
	double* data = new double[sizeR*sizeC];
	int i = 0;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{

		while (myfile.good())
		{
			if (i>sizeR*sizeC - 1) break;
			myfile >> *(data + i);
			// cout << *(data+i) << ' '; // This line display the converted data on the screen, you may comment it out. 
			i++;
		}
		myfile.close();
	}

	else cout << "Unable to open file";
	//cout << i;

	return data;
}

// convert data from double to .pgm stored in filename
void WritePGM(char *filename, double *data, int sizeR, int sizeC, int Q)
{

	int i;
	int	j;
	unsigned char *image;
	ofstream myfile;

	image = (unsigned char *) new unsigned char[sizeR*sizeC];
		
	// convert the integer values to unsigned char

	for (i = 0; i<sizeR*sizeC; i++)
		image[i] = (unsigned char)data[i];

	myfile.open(filename, ios::out | ios::binary | ios::trunc);

	if (!myfile) {
		cout << "Can't open file: " << filename << endl;
		exit(1);
	}

	myfile << "P5" << endl;
	myfile << sizeC << " " << sizeR << endl;
	myfile << Q << endl;

	myfile.write(reinterpret_cast<char *>(image), (sizeR*sizeC)*sizeof(unsigned char));

	if (myfile.fail()) {
		cout << "Can't write image " << filename << endl;
		exit(0);
	}

	myfile.close();

	delete[] image;

}

//My NNS using SSD
Matrix NNS(Matrix& noisy, Matrix& shuffle)
{
	double norm = 999999999999;
	int bestCaseX = 0;
	int bestCaseY = 0;

	Matrix toReturn(512, 512);

	for (int i = 0; i < 512; i += 32)
	{
		for (int j = 0; j < 512; j += 32)
		{
			Matrix noisyBlock = noisy.getBlock(i, i + 32, j, j + 32);

			for (int t = 0; t < 512; t += 32)
			{
				for (int s = 0; s < 512; s += 32)
				{
					Matrix shuffledBlock = shuffle.getBlock(t, t + 32, s, s + 32);
					
					Matrix SSD = noisyBlock - shuffledBlock;
					SSD = SSD*SSD;
					double normalisedC = 0;
					for (int x = 0; x < SSD._M*SSD._N; x++)
					{
						normalisedC += SSD._data[x];
					}
					if (normalisedC < norm)
					{
						norm = normalisedC;
						bestCaseX = t;
						bestCaseY = s;
					}
				}
			}
			
			Matrix swapBlock = shuffle.getBlock(bestCaseX, bestCaseX + 32, bestCaseY, bestCaseY + 32);

			toReturn.setBlock(i, j, swapBlock);

			norm = 999999999999;
			bestCaseX = 0;
			bestCaseY = 0;
		}
	}
	return toReturn;
}