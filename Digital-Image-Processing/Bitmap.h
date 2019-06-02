#ifndef _BITMAP_
#define _BITMAP_
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>
using namespace std;
#pragma warning(disable:4996)
struct Bitmap
{
	int width;
	int height;
	int rowSize;
	unsigned char *pixels;
};

struct Color
{
	unsigned char R, G, B;
};

struct Toado {
	int x, y;
};

int LoadBitmap(const char *fname, Bitmap &bmp);
int SaveBitmap(const char *fname, const Bitmap &bmp);
void DisposeBitmap(Bitmap &bmp);

int SetPixel(const Bitmap &bmp, int row, int col, Color color);
int GetPixel(const Bitmap &bmp, int row, int col, Color &color);
#endif
