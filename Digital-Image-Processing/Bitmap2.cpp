#include "Bitmap.h"
#include <math.h>

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

void Negative(const Bitmap& bmp)
{
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			color.R = 255-color.R;
			color.G = 255-color.G;
			color.B = 255-color.B;
			
			
			SetPixel(bmp, row, col, color);
		}
}
void Flip(const Bitmap &bmp,int k)
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
double Truncate(double R)
{
	if (R < 0)
		return 0;
	if (R > 255) return 255;
	return R;
}
void FilterSummer(const Bitmap &bmp,int percent)
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

/*void AutoContrastAdjustment(const Bitmap &bmp)
{
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			if (color.R > 255 - 20) color.R = 255;
			else if (color.R >= 100 && color.R <= 255 - 20) color.R += 20;
			else if (color.R < 100 && color.R >70) color.R += 10;
			else if (color.R < 60 && color.R >= 40) color.R -= 10;
			else if (color.R < 40 && color.R >= 20) color.R -= 20;
			else if (color.R < 20) color.R = 0;

			if (color.G > 255 - 20) color.G = 255;
			else if (color.G >= 100 && color.G <= 255 - 20) color.G += 20;
			else if (color.G < 100 && color.G >70) color.G += 10;
			else if (color.G < 60 && color.G >= 40) color.G -= 10;
			else if (color.G < 40 && color.G >= 20) color.G -= 20;
			else if (color.G < 20) color.G = 0;

			if (color.B > 255 - 20) color.B = 255;
			else if (color.B >= 100 && color.B <= 255 - 20) color.B += 20;
			else if (color.B < 100 && color.B >70) color.B += 10;
			else if (color.B < 60 && color.B >= 40) color.B -= 10;
			else if (color.B < 40 && color.B >= 20) color.B -= 20;
			else if (color.B < 20) color.B = 0;

			SetPixel(bmp, row, col, color);
		}
}*/

void ContrastAdjustment(const Bitmap &bmp, int C)
{
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			double r, g, b;
			r = (C * (color.R - 128)/100 + 128);
			g = (C * (color.G - 128)/100 + 128);
			b = (C * (color.B - 128)/100 + 128);
			color.R = Truncate(r); color.G = Truncate(g); color.B = Truncate(b);
			SetPixel(bmp, row, col, color);
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

void BlurImageforpencilsketch(const Bitmap &inbmp, double sigma)
{
	int i, j, h, w, gx = 5, gy = 5;
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

bool check(int row, int col, const Bitmap bmp)
{
	if (row < 0 || col < 0 || row >= bmp.height || col >= bmp.width)
		return false;
	return true;
}

/*void Sharpen(const Bitmap &inbmp, int k)
{
	//BlurImageforpencilsketch(inbmp, 5.0);
	//Negative(inbmp);
	int i, j, h, w, gx = 5, gy = 5;
	double gauss[10][10], pi = 3.14159, sum = 0;
	double sigma = 10.0;
	//Gaussian
	for (i = 0; i < gx; i++)
		for (j = 0; j < gy; j++)
		{
			gauss[i][j] = exp(-(i*i + j * j)*1.0 / (2 * sigma)) / (2 * pi*sigma*sigma);
			sum += gauss[i][j];
		}
	for (i = 0; i < gx; i++)
	{
		for (j = 0; j < gy; j++) 
		{
			gauss[i][j] /= sum;
		}
	}

	Bitmap temp = inbmp;
	for (int row = 0; row < inbmp.height; row++)
		for (int col = 0; col < inbmp.width; col++)
		{
			Color color, color2,color1;
			GetPixel(temp, row, col, color);
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
			//GetPixel(inbmp, row, col, color1);
			double B, R, G;
			B = color.B + k * (color.B - color2.B);
			G = color.G + k * (color.G - color2.G);
			R = color.R + k * (color.R - color2.R);

			//B = color.B + 0.3 * (color1.B);
			//G = color.G + 0.3* (color1.G);
			//R = color.R + 0.3 * (color1.R);
			color.R = Truncate(R); color.B = Truncate(B); color.G = Truncate(G);
			SetPixel(temp, row, col, color);
		}
	//Negative(temp);

	/*for (int row = 0; row < inbmp.height; row++)
		for (int col = 0; col < inbmp.width; col++)
		{
			Color color, color1, color2, color3, color4;
			GetPixel(inbmp, row, col, color);
			/*if (check(row, col + 1, inbmp))
				GetPixel(inbmp, row, col + 1, color1);
			else
			{
				color1.R = 0; color1.G = 0; color1.B = 0;
			}
			if (check(row, col - 1, inbmp))
				GetPixel(inbmp, row, col - 1, color2);
			else
			{
				color2.R = 0; color2.G = 0; color2.B = 0;
			}
			if (check(row+1, col , inbmp))
				GetPixel(inbmp, row+1, col , color3);
			else
			{
				color3.R = 0; color3.G = 0; color3.B = 0;
			}
			if (check(row-1, col , inbmp))
				GetPixel(inbmp, row-1, col , color4);
			else
			{
				color4.R = 0; color4.G = 0; color4.B = 0;
			}
			*/
		/*	GetPixel(inbmp, row, col + 1, color1);
			GetPixel(inbmp, row, col - 1, color2);
			GetPixel(inbmp, row + 1, col, color3);
			GetPixel(inbmp, row - 1, col, color4);

			double B, R, G;
			B = (k * color.B - (color1.B + color2.B + color3.B + color4.B));
			G = (k * color.G - (color1.G + color2.G + color3.G + color4.G));
			R = (k * color.R - (color1.R + color2.R + color3.R + color4.R));
			color.R = Truncate(R); color.B = Truncate(B); color.G = Truncate(G);

			SetPixel(inbmp, row, col, color);
		}*/
//}

void Sharpen(const Bitmap &inbmp, double k)
{
	int x[8] = { -1,-1,-1,0,0,1,1,1 };
	int y[8] = { -1,0,1,-1,1,-1,0,1 };
	Bitmap bmp;
	for (int row = 0; row < inbmp.height; row++)
		for (int col = 0; col < inbmp.width; col++)
		{
			Color color, color1, color2;
			int size = 1;
			GetPixel(inbmp, row, col, color);
			double B, R, G;
			R = color.R; G = color.G; B = color.B;
			for (int i = 0; i < 8; i++)
			{
				int xM, yM;
				xM = row + x[i];
				yM = row + y[i];
				if (xM >= 0 && yM >= 0 && xM < inbmp.height && yM < inbmp.width)
				{
					GetPixel(inbmp, xM, yM, color1);
					R += color1.R;
					G += color1.G;
					B += color1.B;
					size++;
				}
			}
			R = color.R + k * (color.R - R / size);
			G = color.G + k * (color.G - G / size);
			B = color.B + k * (color.B - B / size);
			//R = R / size; G = G / size; B = B / size;
			color2.R = Truncate(R); color2.B = Truncate(B); color2.G = Truncate(G);
			SetPixel(bmp, row, col, color2);
		}
}

void Quantization(const Bitmap &bmp, int k)
{
	int temp = 256 / k;
	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			Color color;
			GetPixel(bmp, row, col, color);
			double r, g, b;
			r = color.R / temp; 
			g = color.G / temp;
			b = color.B / temp;
			color.R = Truncate(r); color.G = Truncate(g); color.B = Truncate(b);
			SetPixel(bmp, row, col, color);
		}
}



void Ripple(const Bitmap &bmp)
{
	for (int row=0; row<bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
			//for (int c=0; c<3; c++)
			{
				Color color;
				GetPixel(bmp, row, col, color);
				/*double Rdouble = (color.R +  sin((color.R * 2 * 3.14) / 20));
				double Gdouble = (color.G + sin((color.G * 2 * 3.14) / 20));
				double Bdouble = (color.B +  sin((color.B * 2 * 3.14) / 20));
				int temp1 = Rdouble, temp2 = Gdouble, temp3 = Bdouble;
				/*double R, G, B;
				R = (color.R + temp1) * 3 + c;
				G = (color.G + temp2) * 3 + c;
				B = (color.B + temp3) * 3 + c;*/
			    double coldouble = (col + 5 * sin((row * 2 * 3.14) / 20));
				int temp = coldouble;
				/*int temp1 = (row*bmp.width + coldouble) * 3 + c;*/
				color.R = color.R*temp; color.G = color.G*temp; color.B = color.B*temp;
				SetPixel(bmp, row, col, color);
			}

}
/*void Twirl(const Bitmap &bmp)
{
	for (int row=0; row<bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			GetPixel(bmp,row)
		}
}*/

void OilPainting(const Bitmap &bmp, int L)
{

}