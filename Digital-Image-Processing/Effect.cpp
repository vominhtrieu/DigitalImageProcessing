#include "Effect.h"

void EffectOption(Bitmap &bmp)
{
	int option;
	cout << "\nChoose an option:"
		<< "\n1. Filter Summer"
		<< "\n2. Filter Winter"
		<< "\n3. Sharpenning."
		<< "\n4. Snow Effect."
		<< "\n5. Salt Pepper Noise"
		<< "\n6. Pastel"
		<< "\n7. Convert To Pencil Sketch"
		<< "\n8. Mix Images"
		<< "\n9. Picture Frame"
		<< "\n10. Bunch Image"
		<< "\n11. Create Drawing"
		<< "\n12. Blur Image"
		<< endl;
	cin >> option;
	switch (option)
	{
	case 1:
		float percent;
		cout << "Value from 0.01 to 1.00: ";
		cin >> percent;
		FilterSummer(bmp, percent);
		break;
	case 2:
		float pt1;
		cout << "Value from 0 to 100: ";
		cin >> pt1;
		FilterWinter(bmp, pt1, 0.9);
		break;
	case 3:
		double L;
		cout << " Value sharpen from 0.1 to 1.0: ";
		cin >> L;
		Sharpen(bmp, L);
		break;
	case 4:
		SnowEffect(bmp);
		break;
	case 5:
		SaltPepperNoise(bmp);
		break;
	case 6:
		Pastel(bmp);
		break;
	case 7:
		ConvertToPencilSketch(bmp);
		break;
	case 8:
		cout << "Enter the secondary image's path:";
		char path[100];
		cin >> path;
		Bitmap bmp2;
		if (LoadBitmap(path, bmp2))
			MixImage(bmp, bmp2);
		else
			cout << "The image is not exist\n";
		break;
	case 9:
		int thickness, COLOR;
		cout << "Enter thickness of picture frame: \n";
		cin >> thickness;
		cout << "Enter color of picture frame (0->255): \n";
		cin >> COLOR;
		PictureFrames(bmp, thickness, COLOR);
		break;
	case 10:
		int new_level;
		cout << "Enter bunch level of the image (0->255): \n";
		cin >> new_level;
		BunchImage(bmp, new_level);
		break;
	case 11:
		int boundary;
		cout << "Enter sharp level of the image (0->255): \n";
		cin >> boundary;
		FindBoundary(bmp, boundary, 2);
		break;
	case 12:
		Toado tam;
		float ax, b, zigma, key;

		cout << "Nhap muc do lam nhoe anh (1-10): ";
		cin >> zigma;
		zigma *= 2.5;
		cout << "Nhap 1 neu ban muon lam nhoe toan anh.\nNhap 0 neu ban muon lam nhoe 1 phan anh.\n";
		cin >> key;
		if (key == 1)
		{
			BlurImage(bmp, { 0,0 }, -1, -1, zigma);
		}
		else
		{
			cout << "Nhap toa do tam: " << endl;
			cin >> tam.x >> tam.y;
			cout << "Nhap be ngang, doc cua elip: " << endl;
			cin >> ax; cin >> b;

			BlurImage(bmp, tam, ax, b, zigma);
		}
		break;
	default:
		cout << "\nWrong option!\n";
		break;
	}
}

void FilterSummer(Bitmap &bmp, float percent)
{
	Color color;
	percent = 1.0 - percent;

	for (int row = 0; row < bmp.height; row++)
		for (int col = 0; col < bmp.width; col++)
		{
			GetPixel(bmp, row, col, color);

			color.B = color.B*(percent);
			if (color.B > 255)
				color.B = 255;
			SetPixel(bmp, row, col, color);
		}
}

void FilterWinter(Bitmap &bmp, float pt1, float pt2)
{
	Color color;
	pt1 = (100 - pt1) / 100;

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

void Sharpen(const Bitmap &inbmp, double k)
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
			Color color, color2, color1;
			GetPixel(temp, row, col, color);
			color2.B = 0;
			color2.G = 0;
			color2.R = 0;
			for (h = i; h < i + gx; h++)
				for (w = j; w < j + gy; w++)
				{

					GetPixel(inbmp, h, w, color1);

					color2.B += gauss[h - i][w - j] * color1.B;
					color2.R += gauss[h - i][w - j] * color1.R;
					color2.G += gauss[h - i][w - j] * color1.G;
				}
			double B, R, G;

			B = color.B - k * color2.B;
			G = color.G - k * color2.G;
			R = color.R - k * color2.R;
			color.R = Truncate(R); color.B = Truncate(B); color.G = Truncate(G);
			SetPixel(temp, row, col, color);
		}
}

void MixImage(Bitmap bmp1, Bitmap bmp2)
{
	if (bmp1.height != bmp2.height || bmp1.width != bmp2.width)
	{
		cout << "Two images have different sizes\n";
		return;
	}
	for (int row = 0; row < bmp1.height; row++)
	{
		for (int col = 0; col < bmp1.width; col++)
		{
			Color color1, color2;
			GetPixel(bmp1, row, col, color1);
			GetPixel(bmp2, row, col, color2);
			SetPixel(bmp1, row, col, (color1 + color2) / 2);
		}
	}
}
