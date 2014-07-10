#ifndef BMP_H
#define BMP_H

#define BMP_TEST

#include <iostream>
#include <assert.h>
#include "stdafx.h"
#define checkborder(x,y) (x>=0 && x<W && y>=0 && y<H)
using namespace std;

class TBMP{
private:
	char **bitmap;
	FILE *fp;
public:
	int W, H;
	int MODE;
	//int R, G, B;
	int Grey;
	TBMP(char *filename, int w, int h, int mode);
	~TBMP();
	int setcolor(int grey);
	int drawpoint(int x, int y);
	int drawline(int x0, int y0, int x1, int y1);
	int drawrect(int x0, int y0, int x1, int y1);
};

#endif
