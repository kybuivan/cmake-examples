#include "stdafx.h"
#include "HeightMap.h"
#include <vector>
#include <iostream>
#include <fstream>

HeightMap::HeightMap()
{
}

HeightMap::HeightMap(int m, int n)
{
	recreate(m, n);
}

HeightMap::HeightMap(int m, int n, const string& filename, float heightScale, float heightOffset)
{
	loadRAW(m, n, filename, heightScale, heightOffset);
}

void HeightMap::recreate(int m, int n)
{
	mHeightScale = 1.0f;
	mHeightOffset = 0.0f;
	mHeightMap.resize(m, n, 0.0f);
}

void HeightMap::loadRAW(int m, int n, const string& filename, float heightScale, float heightOffset)
{
	mHeightMapFilename = filename;
	mHeightScale = heightScale;
	mHeightOffset = heightOffset;

	// A height for each vertex
	std::vector<unsigned char> in(m * n);

	// Open the file.
	std::ifstream inFile;
	inFile.open(filename.c_str(), ios_base::binary);
	//if (!inFile) HR(E_FAIL);

	// Read all the RAW bytes in one go.
	inFile.read((char*)&in[0], (streamsize)in.size());

	// Done with file.
	inFile.close();

	// Copy the array data into a float table format, and scale
	// and offset the heights.
	mHeightMap.resize(m, n, 0);
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int k = i * n + j;
			mHeightMap(i, j) = (float)in[k] * heightScale + heightOffset;
		}
	}

	filter3x3();
}

float HeightMap::sampleHeight3x3(int i, int j)
{
	float avg = 0.0f;
	float num = 0.0f;

	for (int m = i - 1; m <= i + 1; ++m)
	{
		for (int n = j - 1; n <= j + 1; ++n)
		{
			if (inBounds(m, n))
			{
				avg += mHeightMap(m, n);
				num += 1.0f;
			}
		}
	}

	return avg / num;
}

int	HeightMap::numRows()const
{
	return mHeightMap.numRows();
}

int	HeightMap::numCols()const
{
	return mHeightMap.numCols();
}

float& HeightMap::operator()(int i, int j)
{
	return mHeightMap(i, j);
}

bool HeightMap::inBounds(int i, int j)
{
	return
		i >= 0 &&
		i < (int)mHeightMap.numRows() &&
		j >= 0 &&
		j < (int)mHeightMap.numCols();
}

void HeightMap::filter3x3()
{
	Table<float> temp(mHeightMap.numRows(), mHeightMap.numCols());

	for (int i = 0; i < mHeightMap.numRows(); ++i)
		for (int j = 0; j < mHeightMap.numCols(); ++j)
			temp(i, j) = sampleHeight3x3(i, j);

	mHeightMap = temp;
}

HeightMap::~HeightMap()
{
}
