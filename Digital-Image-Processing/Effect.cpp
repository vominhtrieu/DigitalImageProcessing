#include "Effect.h"

void EffectOption(Bitmap &bmp)
{
	int option;
	cout << "\nChoose an option:"
		<< "\n1. Filter Summer"
		<< "\n2. Filter Winter"
		<< endl;
	cin >> option;
	switch (option)
	{
	default:
		cout << "\nWrong option!\n";
		break;
	}
}

void FilterSummer(const Bitmap &bmp, int percent)
{
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);

			color.B = color.R*(percent);
			if (color.B > 255)
				color.B = 255;
			SetPixel(bmp, row, col, color);
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
	int row, col, h, w, x, y; h = 0;
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
	for (row = 0; row < bmp.height; row++)
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
	for (row = 0; row < bmp.height; row++)
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

void BlurImage(const Bitmap &inbmp, Toado TamElip, float ngang, float doc)
{
	int i, j, h, w;
	double gauss[10][10], pi = 3.14159, sigma = 20.0, sum = 0;
	Color color, color1, color2;

	//Gaussian
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
		{
			gauss[i][j] = exp(-(i*i + j * j)*1.0 / (2 * sigma)) / (2 * pi*sigma*sigma);
			sum += gauss[i][j];
		}
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			gauss[i][j] /= sum;
		}
	}
	//Blured Image
	for (i = 0; i < inbmp.height; i++)
	{
		for (j = 0; j < inbmp.width; j++)
		{
			if (((i - TamElip.y)*(i - TamElip.y) / (doc*doc)) + ((j - TamElip.x)*(j - TamElip.x) / (ngang*ngang)) > 1 || (ngang == -1 || doc == -1))
			{
				GetPixel(inbmp, i, j, color);
				color2.B = 0;
				color2.G = 0;
				color2.R = 0;
				for (h = i; h < i + 10; h++)
					for (w = j; w < j + 10; w++) {

						GetPixel(inbmp, h, w, color1);

						color2.B += gauss[h - i][w - j] * color1.B;
						color2.R += gauss[h - i][w - j] * color1.R;
						color2.G += gauss[h - i][w - j] * color1.G;
					}

				SetPixel(inbmp, i, j, color2);
			}
		}
	}
}

void BunchImage(const Bitmap &bmp, int new_level)
{
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			color.R = (color.R / new_level) *new_level;
			color.B = (color.B / new_level) *new_level;
			color.G = (color.G / new_level) *new_level;
			SetPixel(bmp, row, col, color);
		}
}

void FindBoundary(Bitmap &bmp, double boundary, int R)
{
	BlackWhite(bmp);
	Bitmap outbmp;
	outbmp.width = bmp.width;
	outbmp.height = bmp.height;
	outbmp.rowSize = ((3 * outbmp.width + 3) / 4) * 4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	Color color1, color2;

	for (int row = 0; row < outbmp.height; row++)
		for (int col = 0; col < outbmp.width; col++)
			SetPixel(outbmp, row, col, { 255,255,255 });


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
				SetPixel(outbmp, row, col, { 0,0,0 });
			}
		}
	bmp.width = outbmp.width;
	bmp.height = outbmp.height;
	bmp.pixels = outbmp.pixels;
	bmp.rowSize = outbmp.rowSize;
}

void BlurImageForPencilSketch(const Bitmap &inbmp, double sigma)
{
	int i, j, h, w, gx = 10, gy = 10;
	double gauss[10][10], pi = 3.14159, sum = 0;
	Color color, color1, color2;

	//Gaussian
	for (i = 0; i < gx; i++)
		for (j = 0; j < gy; j++)
		{
			gauss[i][j] = exp(-(i*i + j * j)*1.0 / (2 * sigma)) / (2 * pi*sigma*sigma);
			sum += gauss[i][j];
		}
	for (i = 0; i < gx; i++) {
		for (j = 0; j < gy; j++) {
			gauss[i][j] /= sum;
		}
	}

	//Blured Image
	for (i = 0; i < inbmp.height; i++)
		for (j = 0; j < inbmp.width; j++) {
			{
				GetPixel(inbmp, i, j, color);
				color2.B = 0;
				color2.G = 0;
				color2.R = 0;
				for (h = i; h < i + gx; h++)
					for (w = j; w < j + gy; w++) {

						GetPixel(inbmp, h, w, color1);

						color2.B += gauss[h - i][w - j] * color1.B;
						color2.R += gauss[h - i][w - j] * color1.R;
						color2.G += gauss[h - i][w - j] * color1.G;
					}

				SetPixel(inbmp, i, j, color2);
			}
		}
}

void ConvertToPencilSketch(Bitmap &bmp)
{
	Bitmap temp;
	BlackWhite(bmp);
	temp.width = bmp.width;
	temp.height = bmp.height;
	temp.rowSize = ((3 * bmp.width + 3) / 4) * 4;
	temp.pixels = new unsigned char[bmp.rowSize * bmp.height];
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			SetPixel(temp, row, col, color);
		}
	//Create negative photo
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			color.B = 255 - color.B;
			color.R = 255 - color.R;
			color.G = 255 - color.G;
			SetPixel(bmp, row, col, color);
		}

	//Blur
	BlurImageForPencilSketch(bmp, 5.0);
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color2, color3;
			GetPixel(bmp, row, col, color2);
			GetPixel(temp, row, col, color3);
			color2.B = ((int)color3.B * 255 / (255 - (int)color2.B)) > 255 ? 255 : (int)color3.B * 255 / (255 - (int)color2.B);
			color2.G = ((int)color3.G * 255 / (255 - (int)color2.G)) > 255 ? 255 : (int)color3.G * 255 / (255 - (int)color2.G);
			color2.R = ((int)color3.R * 255 / (255 - (int)color2.R)) > 255 ? 255 : (int)color3.R * 255 / (255 - (int)color2.R);
			SetPixel(bmp, row, col, color2);
		}
}