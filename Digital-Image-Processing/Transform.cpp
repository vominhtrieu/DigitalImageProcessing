#include "Transform.h"

void TransfromOption(Bitmap &bmp)
{
	int option;
	cout << "\nChoose an option:"
		<< "\n1. Resize"
		<< "\n2. Flip"
		<< "\n3. Rotate"
		<< endl;
	cin >> option;
	switch (option)
	{
	case 1:
		int width, height;
		cout << "\nEnter new width:";
		cin >> width;
		cout << "Enter new height:";
		cin >> height;
		Resize(bmp, width, height);
		break;
	case 2:
		cout << "\nChoose an option:"
			<< "\n1. Horizontal"
			<< "\n2. Vertical"
			<< endl;
		cin >> option;
		if (option >= 1 && option <= 2)
			Flip(bmp, option);
		break;
	case 3:
		cout << " How many degrees do you want to rotate? Choose your option: " << endl;
		cout << "\n1.90 \n2.180 \n3.270" << endl;
		int k;
		cin >> k;
		k /= 90;
		for (int q = 0; q < k; q++)
			Rotate(bmp);
		break;

	default:
		cout << "\nWrong option!\n";
		break;
	}
}

void Resize(Bitmap& inbmp, int width, int height)
{
	double sx1, sx2, sy1, sy2, dx, dy;
	double desR, desG, desB;
	Bitmap outbmp;
	outbmp.width = width;
	outbmp.height = height;
	outbmp.rowSize = ((3 * outbmp.width + 3) / 4) * 4;
	outbmp.pixels = new unsigned char[outbmp.rowSize * outbmp.height];
	double fx = inbmp.width*1.0 / width;
	double fy = inbmp.height*1.0 / height;
	for (int y = 0; y < height; y++)
	{
		sy1 = fy * y;
		sy2 = sy1 + fy;
		for (int x = 0; x < width; x++)
		{
			sx1 = fx * x;
			sx2 = sx1 + fx;
			desR = desG = desB = 0;
			for (int i = floor(sy1); i < ceil(sy2); i++)
			{
				/*
					5x6
					1 2 3 4 5 5
					2 3 4 4 3 4
					2 4 5 5 5 1
					2 3 4 3 3 4
					2 4 5 5 5 1
						 |
						 V
					3x4
					fx = 4/6
					fy = 3/5
				*/
				dy = 1;
				if (sy1 > i)
				{
					dy -= sy1 - i;
				}
				if (sy2 < i + 1)
				{
					dy -= (i + 1 - sy2);
				}
				for (int j = floor(sx1); j < ceil(sx2); j++)
				{
					dx = 1;
					if (sx1 > j)
					{
						dx -= sx1 - j;
					}
					if (sx2 < j + 1)
					{
						dx -= (j + 1 - sx2);
					}
					Color color;
					GetPixel(inbmp, i, j, color);
					double PC = dx * dy*(1.0 / (fx))*(1.0 / (fy));
					desR += color.R*PC;
					desG += color.G*PC;
					desB += color.B*PC;
				}
			}
			SetPixel(outbmp, y, x, { (unsigned char)desR,(unsigned char)desG,(unsigned char)desB });
		}
	}
	delete[]inbmp.pixels;
	inbmp.width = outbmp.width;
	inbmp.height = outbmp.height;
	inbmp.rowSize = outbmp.rowSize;
	inbmp.pixels = outbmp.pixels;
}

void Flip(const Bitmap &bmp, int k)
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

void CutImage(Bitmap &inbmp, int x, int y, int X, int Y)
{
	if (X > inbmp.width || Y > inbmp.height)
	{
		//printf("ERROR");
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