#include "Bitmap.h"
#include <math.h>

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

void Enlarge(const Bitmap &inbmp, Bitmap &outbmp)
{
	outbmp.width = 2 * inbmp.width;
	outbmp.height = 2 * inbmp.height;
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
				color.R = color.G = color.B = (1.055 * pow(CLinear, 1.0 / 2.4) - 0.055) * 255;
			/*if (color.R < 128)
				color.R = color.G = color.B = 0;
			else
				color.R = color.G = color.B = 255;*/
			SetPixel(bmp, row, col, color);
		}
}
void reverse_image(const Bitmap &bmp, int k)
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
		for (int row = 0; row < bmp.height / 2; row++)
			for (int col = 0; col < bmp.width; col++)
			{
				Color color1, color2;
				GetPixel(bmp, row, col, color1);
				GetPixel(bmp, bmp.height - row - 1, col, color2);
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
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
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

void Rotate(Bitmap &inbmp)
{
	Bitmap outbmp;
	outbmp.width = inbmp.height;
	outbmp.height = inbmp.width;
	outbmp.rowSize = ((3 * outbmp.width + 3) / 4) * 4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	int rowo = 0;
	int colo = outbmp.width - 1;
	for (int row = 0; row < inbmp.height; row++)
	{
		int rowo = 0;
		for (int col = 0; col < inbmp.width; col++)
		{
			Color color;
			GetPixel(inbmp, row, col, color);
			SetPixel(outbmp, rowo, colo, color);
			rowo++;
		}
		colo--;
	}
	inbmp.width = outbmp.width;
	inbmp.height = outbmp.height;
	inbmp.pixels = outbmp.pixels;
	inbmp.rowSize = outbmp.rowSize;
}
void BlurImageforpencilsketch(const Bitmap &inbmp, double sigma)
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

void ConverttoPencilsketch(Bitmap &bmp)
{	
	Bitmap temp;
	BlackWhite(bmp);
	//
	temp.width = bmp.height;
	temp.height = bmp.width;
	temp.rowSize = ((3 * bmp.width + 3) / 4) * 4;
	temp.pixels = new unsigned char[bmp.rowSize * bmp.height];
	//Create negative photo
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			color.B = 255- color.B;
			color.R = 255- color.R;
			color.G = 255- color.G;
			SetPixel(bmp, row, col, color);
		}

	//Blur
	BlurImageforpencilsketch(bmp, 15.0);
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color2,color3;
			GetPixel(bmp, row, col, color2);
			GetPixel(temp, row, col, color3);
			color2.B = color3.B * 255 / (255 - color2.B);
			color2.G = color3.G * 255 / (255 - color2.G);
			color2.R = color3.R * 255 / (255 - color2.R);
			if (color2.G > 255) color2.G = 255;
			if (color2.R > 255) color2.R = 255;
			if (color2.B > 255) color2.B = 255;
			SetPixel(bmp, row, col, color2);
		}



}