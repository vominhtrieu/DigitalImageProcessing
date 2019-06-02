#include "Bitmap.h"
#include <math.h>
#include<iostream>

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
	Color color;
	for(int row = 0; row < bmp.height; row++)
		for(int col = 0; col < bmp.width; col++)
		{
			GetPixel(bmp, row, col, color);

			double  min = color.R, 
					max = color.R, 
					light, 
					k;

			if (min > color.G) 
				min = color.G;

			if (min > color.B) 
				min = color.B;

			if (max < color.G) 
				max = color.G;

			if (max < color.B) 
				max = color.B;

			if (color.R*factor > 255)
				color.R = 255;
			else
				color.R = color.R*factor;

			if (color.G*factor > 255)
				color.G = 255;
			else 
				color.G = color.G*factor;

			if (color.B*factor > 255)
				color.B = 255;
			else 
				color.B = color.B*factor;
			
			light = (min + max)/2;
			/*if (light > 200 && light<240) {
				k = 0.9;
				color.R = color.R*k;
				color.B = color.B*k;
				color.G = color.G*k;
			}
			if (light>=240) {
				k = 0.7;
				color.R = color.R*k;
				color.B = color.B*k;
				color.G = color.G*k;
			}*/
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
void BlurImage(const Bitmap &inbmp, Toado TamElip, float ngang, float doc, double sigma)
{
	int i, j, h, w, gx = 10, gy = 10, x;

	Color color, color1, color2;
	const int k = sigma / 2.5;
	float d=5, doc1, ngang1;
	double gauss[10][10][10], pi = 3.14159, sum[20];
	for (x = 0; x < 20; x++) sum[x] = 0;
	
	//Gaussian
	sigma = 0.5;
	for (x = 0; x < k; x++)
	{
		for (i = 0; i < gx; i++)
			for (j = 0; j < gy; j++)
			{
				gauss[x][i][j] = exp(-(i*i + j * j)*1.0 / (2 * sigma)) / (2 * pi*sigma*sigma);
				sum[x] += gauss[x][i][j];
			}
		sigma += 2;
	}
	for (x = 0; x < k; x++)
		for (i = 0; i < gx; i++) {
			for (j = 0; j < gy; j++) {
				gauss[x][i][j] /= sum[x];
			}
		}
	
	
	//Blured Image

	for (i = 0; i < inbmp.height; i++)
		for (j = 0; j < inbmp.width; j++)
		{
			doc1 = doc; ngang1 = ngang;
			for (x = 0; x < k; x++)
			{

				if ((i - TamElip.y)*(i - TamElip.y) / ((doc + k*d)*(doc + k*d)) +
					((j - TamElip.x)*(j - TamElip.x) / ((ngang + d*k)*(ngang + d*k))) > 1)
						{
							color2.B = 0;
							color2.G = 0;
							color2.R = 0;
							for (h = i; h < i + gx; h++)
								for (w = j; w < j + gy; w++)
								{

									GetPixel(inbmp, h, w, color1);

									color2.B += gauss[k-1][h - i][w - j] * color1.B;
									color2.R += gauss[k-1][h - i][w - j] * color1.R;
									color2.G += gauss[k-1][h - i][w - j] * color1.G;
								}


							SetPixel(inbmp, i, j, color2);
						}
				else

					if ((((i - TamElip.y)*(i - TamElip.y) / (doc1*doc1)) +
						((j - TamElip.x)*(j - TamElip.x) / (ngang1*ngang1)) > 1)
						&& ( ((i - TamElip.y)*(i - TamElip.y) / ((doc1 + d)*(doc1 + d)) ) +
						((j - TamElip.x)*(j - TamElip.x) / ((ngang1 + d)*(ngang1 + d)) ) < 1))
					{

						color2.B = 0;
						color2.G = 0;
						color2.R = 0;
						for (h = i; h < i + gx; h++)
							for (w = j; w < j + gy; w++)
							{

								GetPixel(inbmp, h, w, color1);

								color2.B += gauss[x][h - i][w - j] * color1.B;
								color2.R += gauss[x][h - i][w - j] * color1.R;
								color2.G += gauss[x][h - i][w - j] * color1.G;
							}
						

						SetPixel(inbmp, i, j, color2);
						break;
					}
					doc1 += d;
					ngang1 += d;
				}

			}
}
void FilterWinter(Bitmap &bmp, float pt1, float pt2)
{
	Color color;
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			GetPixel(bmp, row, col, color);
			color.R = (color.R * (pt1));
			
			color.G = (color.G * (pt2));
			
			SetPixel(bmp, row, col, color);
		}
}
void SnowEffect(Bitmap &bmp)
{
	Color color;
	int row, col, h, w,x,y; h = 0;
	while (h < bmp.height*bmp.width / 7)
	{
		x = rand() % bmp.height + 1;
		y = rand() % bmp.width + 1;
		color.B = 255; color.R = 255; color.G = 255;
		SetPixel(bmp, x, y, color);
		h++;
	}
}
void SaltPepperNoise(Bitmap &bmp)
{
	Color color;
	int rand1, rand2, row, col;
	for(row=0;row<bmp.height;row++)
		for (col = 0; col < bmp.width; col++)
		{
			rand1 = rand() % 100;
			if (rand1 < 5)
			{
				rand2 = rand() % 2;
				if (rand2 == 0)
				{
					color.B = 0; color.G = 0; color.R = 0;
					SetPixel(bmp, row, col, color);
				}
				else
				{
					color.B = 255; color.R = 255; color.G = 255;
					SetPixel(bmp, row, col, color);
				}
			}
		}
}
void Pastel(Bitmap &bmp)
{
	Color color;
	int row, col;
	for(row=0;row<bmp.height;row++)
		for (col = 0; col < bmp.width; col++)
		{
			GetPixel(bmp, row, col, color);

			color.R = color.R / 2 + 127;
			if (color.R > 255) color.R = 255;

			color.B = color.B / 2 + 127;
			if (color.B > 255) color.B = 255;

			color.G = color.G / 2 + 127;
			if (color.G > 255) color.G = 255;

			SetPixel(bmp, row, col, color);
		}
}

void Rotate(Bitmap bmp, float degree)
{
	Color color;
	int rowcenter = bmp.height, colcenter = bmp.width, row, col,m,n;
	float rowRotation, colRotation;
	for(row=0;row<bmp.height;row++)
		for (col = 0; col < bmp.width; col++)
		{
			rowRotation = (row - rowcenter)*sin(-degree) + (col - colcenter)*sin(-degree);
			colRotation = (row - rowcenter)*cos(-degree) + (col - colcenter)*cos(-degree);
			m = rowRotation + rowcenter;
			n = colRotation + colcenter;
			if(!(m>=bmp.height||m<0||n>=bmp.width||n<0))
				for (int dem = 0; dem < 3; dem++)
				{
					GetPixel(bmp, m + dem, n + dem, color);
					SetPixel(bmp, row + dem, col + dem, color);
				}
		}
}