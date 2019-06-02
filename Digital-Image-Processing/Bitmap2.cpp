#include "Bitmap.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <malloc.h>
using namespace std;
// O(1)
int SetPixel(const Bitmap &bmp, int row, int col, Color color)
{
	if(row < 0 || row >= bmp.height
		 || col < 0 || col >= bmp.width)
		return 0;
	
	// color: B, G, R
	int offset = (bmp.height - 1 - row)*bmp.rowSize + col*3;
	bmp.pixels[offset] = color.B;
	bmp.pixels[offset + 1] = color.G;
	bmp.pixels[offset + 2] = color.R;
	return 1;
}

int GetPixel(const Bitmap &bmp, int row, int col, Color &color)
{
	if(row < 0 || row >= bmp.height
		 || col < 0 || col >= bmp.width)
		return 0;
	
	// color: B, G, R
	int offset = (bmp.height - 1 - row)*bmp.rowSize + col*3;
	color.B = bmp.pixels[offset];
	color.G = bmp.pixels[offset + 1];
	color.R = bmp.pixels[offset + 2];
}

void Enlarge(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = 2 * inbmp.width;
	outbmp.height = 2 * inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3)/4)*4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for(int row = 0; row < inbmp.height; row++)
		for(int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, 2*row, 2*col, color);
			SetPixel(outbmp, 2*row, 2*col + 1, color);
			SetPixel(outbmp, 2*row + 1, 2*col, color);
			SetPixel(outbmp, 2*row + 1, 2*col + 1, color);
		}
}

void BlackWhite(const Bitmap& bmp)
{
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			double r = color.R * 1.0 / 255;
			double b = color.B * 1.0 / 255;
			double g = color.G * 1.0 / 255;
			double CLinear = 0.2126 * r + 0.7152 * g + 0.0722 * b;
			if (CLinear <= 0.0031308)
				color.R = color.G = color.B = 12.92 * CLinear * 255;
			else
				color.R = color.G = color.B = (1.055 * pow(CLinear, 1.0/2.4) - 0.055)*255;
			/*if (color.R < 128)
				color.R = color.G = color.B = 0;
			else
				color.R = color.G = color.B = 255;*/
			SetPixel(bmp, row, col, color);
		}
}
void reverse_image(const Bitmap &bmp,int k)
{
	switch (k)
	{
	case 1:
		for (int row = 0; row < bmp.height; row++)
			for (int col = 0; col < bmp.width / 2; col++)
			{
				Color color1, color2;
				GetPixel(bmp, row, col, color1);
				GetPixel(bmp, row, bmp.width - col - 1, color2);
				Color temp = color1;
				color1 = color2;
				color2 = temp;
				SetPixel(bmp, row, col, color1);
				SetPixel(bmp, row, bmp.width - col - 1, color2);
			}
		break;
	default:
		for (int row = 0; row < bmp.height/2; row++)
			for (int col = 0; col < bmp.width; col++)
			{
				Color color1, color2;
				GetPixel(bmp, row, col, color1);
				GetPixel(bmp, bmp.height-row-1, col, color2);
				Color temp = color1;
				color1 = color2;
				color2 = temp;
				SetPixel(bmp, row, col, color1);
				SetPixel(bmp, bmp.height - row - 1, col, color2);
			}
		break;
	}

}

void AdjustBrightness(const Bitmap &bmp, double factor)
{
	for(int row = 0; row < bmp.height; row++)
		for(int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			if(color.R*factor > 255)
				color.R = 255;
			else
				color.R = color.R*factor;
			
			if(color.G*factor > 255)
				color.G = 255;
			else
				color.G = color.G*factor;
			
			if(color.B*factor > 255)
				color.B = 255;
			else
				color.B = color.B*factor;
			
			SetPixel(bmp, row, col, color);
		}
}

void Resize(const Bitmap& inbmp, Bitmap& outbmp, int width, int height)
{
	outbmp.width = width;
	outbmp.height = height;
	outbmp.rowSize = ((3 * outbmp.width + 3) / 4) * 4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for (int row = 0; row < inbmp.height; row++)
		for (int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, 2 * row, 2 * col, color);
			SetPixel(outbmp, 2 * row, 2 * col + 1, color);
			SetPixel(outbmp, 2 * row + 1, 2 * col, color);
			SetPixel(outbmp, 2 * row + 1, 2 * col + 1, color);
		}
}

void zoomimage(const Bitmap &inbmp, Bitmap &outbmp, int k)
{
	outbmp.width = k * inbmp.width;
	outbmp.height = k * inbmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3) / 4) * 4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for (int row = 0; row < inbmp.height; row++)
		for (int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, k*row, k*col, color);
			SetPixel(outbmp, k*row, k*col + 1, color);
			SetPixel(outbmp, k*row + 1, k*col, color);
			SetPixel(outbmp, k*row + 1, k*col + 1, color);
		}


	for (int row = 0; row < inbmp.height; row++)
		for (int col = 0; col < inbmp.width; col++)
		{
			Color color3;
			Color color4;

			GetPixel(inbmp, row, col, color3);
			GetPixel(outbmp, row + (outbmp.height * (k - 1)) / (2 * k), col + (outbmp.width * (k - 1)) / (2 * k), color4);
			color3 = color4;

			SetPixel(inbmp, row, col, color3);
		}
}



void CutImage(Bitmap &inbmp, int x, int y, int X, int Y)
{
	if (X > inbmp.width || Y > inbmp.height)
	{
		printf("ERORR");
		return;
	}
	Bitmap outbmp;
	outbmp.width = X - x;
	outbmp.height = Y - y;
	outbmp.rowSize = ((3 * outbmp.width + 3) / 4) * 4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];


	for (int col = 0; col < outbmp.width; col++)
		for (int row = 0; row < outbmp.height; row++)
		{
			Color color3;
			GetPixel(inbmp, row + y, col + x, color3);
			SetPixel(outbmp, row, col, color3);
		}

	inbmp.width = outbmp.width;
	inbmp.height = outbmp.height;
	inbmp.pixels = outbmp.pixels;
	inbmp.rowSize = outbmp.rowSize;
}


void BunchImage(const Bitmap &bmp, int new_level)
{

	for (int row = 0; row < bmp.height-1; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color1, color2;
			GetPixel(bmp, row, col, color1);
			GetPixel(bmp, row + 1, col, color2);
			
			SetPixel(bmp, row, col, { (unsigned char)abs(color2.R-color1.R), (unsigned char)abs(color2.G - color1.G), (unsigned char)abs(color2.B - color1.B) });
		}
}


void BalanceHistogram(const Bitmap &bmp)
{
	int new_level = 256;
	BlackWhite(bmp);
	int *Array = Arrayconvertcolor(bmp, new_level);

	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			color.R = Convertcolor(Array, color.R);
			color.B = color.R;
			color.G = color.R;
			SetPixel(bmp, row, col, color);
		}
}



int* Arrayconvertcolor(Bitmap bmp, int new_level)
{
	int *a = (int *)calloc(256, sizeof(int));

	for (int i = 0; i < 256; i++)
		for (int col = 0; col <= bmp.width; col++)
			for (int row = 0; row <= bmp.height; row++)
			{
				Color color;
				GetPixel(bmp, row, col, color);
				if (color.R == i)
					a[i]++;
			}
	int S = 0;
	for (int i = 0; i < 256; i++)
	{
		S += a[i];
		a[i] = S;
	}

	int TB = (bmp.height*bmp.width) / new_level;

	for (int i = 0; i < 256; i++)
	{
		a[i] = int(round(float(a[i] / TB)) - 1);
		if (a[i] > 255)
			a[i] = 255;
		else if (a[i] < 0)
			a[i] = 0;

	}
	return a;
}

unsigned char Convertcolor(int *a, unsigned char A)
{
	for (int i = 0; i < 256; i++)
		if (A == i)
			return  a[i];
}


void PictureFrames(Bitmap &bmp, int thickness, unsigned char COLOR)  
{
	Bitmap outbmp;
	outbmp.width = bmp.width + thickness * 2;
	outbmp.height = bmp.height + thickness * 2;
	outbmp.rowSize = ((3 * outbmp.width + 3) / 4) * 4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];

	for (int row = 0; row < outbmp.height; row++)
		for (int col = 0; col < outbmp.width; col++)
			SetPixel(outbmp, row, col, { COLOR,COLOR,COLOR });

	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color1;
			GetPixel(bmp, row, col, color1);
			SetPixel(outbmp, row + thickness, col + thickness, color1);
		}
	bmp.width = outbmp.width;
	bmp.height = outbmp.height;
	bmp.pixels = outbmp.pixels;
	bmp.rowSize = outbmp.rowSize;
	if (thickness == 15)
		return;
	PictureFrames(bmp, 15, 0);
}



void FindBoundary(Bitmap &bmp, double boundary)//tạo ảnh tranh vẽ
{
	int R = 2;
	BlackWhite(bmp);
	Bitmap outbmp;
	outbmp.width = bmp.width;
	outbmp.height = bmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3) / 4) * 4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	Color color1, color2;

	for (int row = 0; row < outbmp.height; row++)
		for (int col = 0; col < outbmp.width; col++)
			SetPixel(outbmp, row, col, { 255,255,255});
		

	for (int row = R; row < bmp.height - R; row++)
		for (int col = R; col < bmp.width - R; col++)
		{
			int tong = 0;

			for (int i = row - R; i <= row + R; i++)
				for (int j = col - R; j <= col + R; j++)
				{
					GetPixel(bmp, i, j, color2);
					tong += color2.R;
				}
			GetPixel(bmp, row, col, color1);
			if (tong > (2 * R + 1) * (2 * R + 1) * color1.R + boundary)
			{
				SetPixel(outbmp, row, col, { 0,0,0});
			}
		}
	bmp.width = outbmp.width;
	bmp.height = outbmp.height;
	bmp.pixels = outbmp.pixels;
	bmp.rowSize = outbmp.rowSize;
}
