#include "Bitmap.h"
#include <math.h>

Color operator + (Color color1, Color color2)
{
	Color color;
	color.R = (color1.R + color2.R) > 255 ? 255 : (color1.R + color2.R);
	color.G = (color1.G + color2.G) > 255 ? 255 : (color1.G + color2.G);
	color.B = (color1.B + color2.B) > 255 ? 255 : (color1.B + color2.B);
	return color;
}

Color operator / (Color color, int n)
{
	color.R /= n;
	color.G /= n;
	color.B /= n;
	return color;
}

// O(1)
int SetPixel(const Bitmap &bmp, int row, int col, Color color)
{
	if (row < 0 || row >= bmp.height
		|| col < 0 || col >= bmp.width)
		return 0;

	// color: B, G, R
	int offset = (bmp.height - 1 - row)*bmp.rowSize + col * 3;
	bmp.pixels[offset] = color.B;
	bmp.pixels[offset + 1] = color.G;
	bmp.pixels[offset + 2] = color.R;
	return 1;
}

int GetPixel(const Bitmap &bmp, int row, int col, Color &color)
{
	if (row < 0 || row >= bmp.height
		|| col < 0 || col >= bmp.width)
		return 0;

	// color: B, G, R
	int offset = (bmp.height - 1 - row)*bmp.rowSize + col * 3;
	color.B = bmp.pixels[offset];
	color.G = bmp.pixels[offset + 1];
	color.R = bmp.pixels[offset + 2];
}

void AdjustBrightness(const Bitmap &bmp, double factor)
{
	Color color;
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			GetPixel(bmp, row, col, color);

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

			SetPixel(bmp, row, col, color);
		}
}

void BlurImage(const Bitmap &inbmp, Toado TamElip, float ngang, float doc, double sigma)
{
	int i, j, h, w, gx = 10, gy = 10, x;

	Color color1, color2;
	const int k = sigma / 2.5;
	float d = 5, doc1, ngang1;
	double gauss[10][10][10], pi = 3.14159, sum[20];
	for (x = 0; x < 20; x++) sum[x] = 0;

	if (ngang < 0)
	{
		//Gaussian
		for (i = 0; i < gx; i++)
			for (j = 0; j < gy; j++)
			{
				gauss[0][i][j] = exp(-(i*i + j * j)*1.0 / (2 * sigma)) / (2 * pi*sigma*sigma);
				sum[0] += gauss[0][i][j];
			}
		for (i = 0; i < gx; i++) {
			for (j = 0; j < gy; j++) {
				gauss[0][i][j] /= sum[0];
			}
		}

		//Blur All Image
		for (i = 0; i < inbmp.height; i++)
			for (j = 0; j < inbmp.width; j++)
			{
				color2.B = 0;
				color2.G = 0;
				color2.R = 0;
				for (h = i; h < i + gx; h++)
					for (w = j; w < j + gy; w++)
					{

						GetPixel(inbmp, h, w, color1);

						color2.B += gauss[0][h - i][w - j] * color1.B;
						color2.R += gauss[0][h - i][w - j] * color1.R;
						color2.G += gauss[0][h - i][w - j] * color1.G;
					}


				SetPixel(inbmp, i, j, color2);
			}

	}
	else
	{
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

					if ((i - TamElip.y)*(i - TamElip.y) / ((doc + k * d)*(doc + k * d)) +
						((j - TamElip.x)*(j - TamElip.x) / ((ngang + d * k)*(ngang + d * k))) > 1)
					{
						color2.B = 0;
						color2.G = 0;
						color2.R = 0;
						for (h = i; h < i + gx; h++)
							for (w = j; w < j + gy; w++)
							{

								GetPixel(inbmp, h, w, color1);

								color2.B += gauss[k - 1][h - i][w - j] * color1.B;
								color2.R += gauss[k - 1][h - i][w - j] * color1.R;
								color2.G += gauss[k - 1][h - i][w - j] * color1.G;
							}


						SetPixel(inbmp, i, j, color2);
					}
					else

						if ((((i - TamElip.y)*(i - TamElip.y) / (doc1*doc1)) +
							((j - TamElip.x)*(j - TamElip.x) / (ngang1*ngang1)) > 1)
							&& (((i - TamElip.y)*(i - TamElip.y) / ((doc1 + d)*(doc1 + d))) +
							((j - TamElip.x)*(j - TamElip.x) / ((ngang1 + d)*(ngang1 + d))) < 1))
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