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
		<< "\n6. Balance histogram."
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
		float a;
		cout << "nhap do tang sang: ";
		cin >> a;
		AdjustBrightness(bmp, a);
		break;
	case 5:
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
			cout << "nhap toa do tam: " << endl;
			cin >> tam.x >> tam.y;
			cout << "Nhap be ngang, doc cua elip: " << endl;
			cin >> ax; cin >> b;

			BlurImage(bmp, tam, ax, b, zigma);
		}
		break;
	case 6:
		BalanceHistogram(bmp, 256);
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

void BalanceHistogram(const Bitmap &bmp, int newLevel)
{
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

