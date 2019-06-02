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





