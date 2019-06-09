#include "Color.h"

void ColorOption(Bitmap&bmp)
{
	int option;
	cout << "\nChoose an option:"
		<< "\n1. Black White"
		<< "\n2. Negative"
		<< "\n3. ContrastAdjustment."
		<< "\n4. AdjustBrightness."
		<< "\n5. BlurImage."
		<< "\n6. BalanceHistogram"
		<< endl;
	cin >> option;
	switch (option)
	{
	case 1:
		BlackWhite(bmp);
		break;
	case 2:
		Negative(bmp);
		break;
	case 3:
		int C;
		cout << "Contrast from 0 to 200: ";
		cin >> C;
		ContrastAdjustment(bmp, C);
		break;
	case 4:
		double factor;
		cin >> factor;
		AdjustBrightness(bmp, factor);
		break;
	case 5:
		Toado TamElip; float ngang; float doc;
		break;
	case 6:
		BalanceHistogram(bmp);
		break;
	default:
		cout << "\nWrong option!\n";
		break;
	}
}


void BlackWhite(const Bitmap& bmp)
{
	for (int row = 0; row < bmp.height; row++)
	{
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			double r = color.R * 1.0 / 255;
			double b = color.B * 1.0 / 255;
			double g = color.G * 1.0 / 255;
			double CLinear = 0.2126 * r + 0.7152 * g + 0.0722 * b;
			if (CLinear <= 0.0031308)
				color.R = color.G = color.B = (char)(12.92 * CLinear * 255);
			else
				color.R = color.G = color.B = (char)((1.055 * pow(CLinear, 1.0 / 2.4) - 0.055) * 255);
			/*if (color.R < 128)
				color.R = color.G = color.B = 0;
			else
				color.R = color.G = color.B = 255;*/
			SetPixel(bmp, row, col, color);
		}
	}
}

char Truncate(double R)
{
	if (R < 0)
		return 0;
	if (R > 255)
		return 255;
	return R;
}

void ContrastAdjustment(const Bitmap &bmp, int C)
{
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			double r, g, b;
			r = (C * (color.R - 128) / 100 + 128);
			g = (C * (color.G - 128) / 100 + 128);
			b = (C * (color.B - 128) / 100 + 128);
			color.R = Truncate(r); color.G = Truncate(g); color.B = Truncate(b);
			SetPixel(bmp, row, col, color);
		}
}

void Negative(const Bitmap& bmp)
{
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			color.R = 255 - color.R;
			color.G = 255 - color.G;
			color.B = 255 - color.B;


			SetPixel(bmp, row, col, color);
		}
}

void AdjustBrightness(const Bitmap &bmp, double factor)
{
	Color color;
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
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

			light = (min + max) / 2;
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

unsigned char ConvertColor(int *a, unsigned char A)
{
	for (int i = 0; i < 256; i++)
		if (A == i)
			return  a[i];
}

int* ArrayConvertColor(Bitmap bmp, int newLevel)
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

	int TB = (bmp.height*bmp.width) / newLevel;

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

void BalanceHistogram(const Bitmap &bmp)
{
	int newLevel = 256;
	BlackWhite(bmp);
	int *Array = ArrayConvertColor(bmp, newLevel);

	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			color.R = ConvertColor(Array, color.R);
			color.B = color.R;
			color.G = color.R;
			SetPixel(bmp, row, col, color);
		}
}

void NormalizeImage(Bitmap &bmp, int newMin, int newMax)
{
	int min = 1000000;
	int max = 0;
	for (int row = 0; row < bmp.height; row++)
	{
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			if (color.R < min)
				min = color.R;
			if (color.R > max)
				max = color.R;
		}
	}

	for (int row = 0; row < bmp.height; row++)
	{
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			int I = color.R;
			color.R = color.G = color.B = (unsigned char)((I - min)*(newMax - newMin)*1.0 / (max - min) + newMin);
			SetPixel(bmp, row, col, color);
		}
	}
}
