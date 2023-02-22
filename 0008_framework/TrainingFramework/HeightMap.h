#pragma once
#include <string>
#include "Table.h"

using namespace std;

class HeightMap
{
public:
	HeightMap();
	HeightMap(int m, int n);
	HeightMap(int m, int n, const string& filename, float heightScale, float heightOffset);

	void	recreate(int m, int n);

	void	loadRAW(int m, int n, const string& filename, float heightScale, float heighOffset);

	int		numRows()const;
	int		numCols()const;

	//For non-const object
	float&	operator()(int i, int j);

	//For const object
	//const float& operator()(int i, int j)const;
	~HeightMap();

private:
	bool	inBounds(int i, int j);
	float	sampleHeight3x3(int i, int j);
	void	filter3x3();
private:
	string		mHeightMapFilename;
	Table<float>		mHeightMap;
	float		mHeightScale;
	float		mHeightOffset;
};
