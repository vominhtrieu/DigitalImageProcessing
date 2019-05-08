#include "Bitmap.h"
#include <iostream>
#include <math.h>
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

void Resize(const Bitmap& inbmp, int width, int height)
{
	Bitmap outbmp;
	outbmp.width = width;
	outbmp.height = height;
	outbmp.rowSize = ((3 * outbmp.width + 3) / 4) * 4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	for (int row = 0; row < inbmp.height; row++)
	{
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
}

double threshold = 30;

double SimilarFeatures(Bitmap bmp1, Bitmap bmp2)
{
	int dem = 0;
	double S = 0;
	for (int i = 0; i < bmp1.height; i++)
	{
		for (int j = 0; j < bmp1.width; j++)
		{
			Color color1;
			GetPixel(bmp1, i, j, color1);
			Color color2;
			GetPixel(bmp2, i, j, color2);
			//S += ((double)color1.R - (double)color2.R)*((double)color1.R - (double)color2.R);
			if(abs((double)color1.R - (double)color2.R)< threshold 
				&& abs((double)color1.G - (double)color2.G) < threshold 
				&& abs((double)color1.B - (double)color2.B) < threshold)
				dem++;
		}
	}
	return dem;
}

int KNN(Bitmap &bmp)
{
	Bitmap image;
	double max = -INFINITY, min = INFINITY;
	int indexMax = 0, indexMin = 0;
	//BlackWhite(bmp);
	char path[100] = "train/FACES/train01.bmp";
	int i;
	for (i = 2; LoadBitmap(path, image); i++)
	{
		//BlackWhite(image);
		double m = SimilarFeatures(image, bmp);
		if (m > max)
		{
			max = m;
			indexMax = i - 1;
		}
		if (m < min)
		{
			min = m;
			indexMin = i - 1;
		}
		path[strlen(path) - 6] = i / 10 + '0';
		path[strlen(path) - 5] = (i % 10) + '0';
	}
	cout << i - 2 << " images\n";
	cout << max << " " << indexMax << "||" << min << " " << indexMin;
	if (max > 250 || min > 100)
	{
		return ((int)max - 200)/50;
	}
	else
		return -1;
}

int FaceDetect(Bitmap &bmp)
{
	//SVM svm;
	/*fstream file;
	file.open("SVM.model");
	if (!file)
		svm.fit();
	else
	{
		vector<double> w;
		w.resize(2);
		double b;
		file >> w[0] >> w[1] >> b;
		svm.SetValue(w, b);
	}*/
	int result = KNN(bmp);
	if (result == 1)
		cout << "\nV-V Maybe a face\n";
	else if (result == 2)
		cout << "\n0-0 It can be a face\n";
	else if (result > 2)
		cout << "\n^^ It's definitely a face\n";
	else
		cout << "\n-_-No Face's found\n";
	return 0;
}