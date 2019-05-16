#include "Bitmap.h"

struct Images
{
	Bitmap bitmap;
	Images *next;
};

struct Position
{
	int X,Y;
};

double similarThreshold1 = 30, similarThreshold2 = 20, threshold1 = 250, threshold2 = 50;

double SimilarFeatures(Bitmap bmp1, Bitmap bmp2, double similarThreshold)
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
			if (abs((double)color1.R - (double)color2.R) < similarThreshold
				&& abs((double)color1.G - (double)color2.G) < similarThreshold
				&& abs((double)color1.B - (double)color2.B) < similarThreshold)
			{
				dem++;
			}
		}
	}
	return dem;
}

void FixColor(unsigned char &color)
{
	if (color == 13 || color == 0 || color == 27 || color == 32)
		color++;
	else if (color == 7 || color == 8)
		color = 6;
	else if (color == 9 || color == 10)
		color = 11;
	else if (color == 255 || color == 26)
		color--;
}

int Classifier(Bitmap &bmp, Images* images, double Threshold, double similarThreshold, int showProperties = 1)
{
	Bitmap image;
	double max = -INFINITY;
	int indexMax = 0, indexMin = 0;
	int similarCount = 0;
	//BlackWhite(bmp);
	
	int i;
	for (i = 1; ; i++)
	{
		//BlackWhite(image);
		image = images->bitmap;
		double m = SimilarFeatures(image, bmp, similarThreshold);
		if (m > max)
		{
			max = m;
			indexMax = i;
		}
		if (m > threshold2*0.6)
			similarCount++;
		if (images->next == NULL)
			break;
		else
			images = images->next;
	}
	if (max > Threshold)
	{
		if(showProperties)
			cout << max << " " << indexMax << "\n";
		return ((int)max - 200) / 50;
	}
	else
		return -1;
}

void DrawRect(Bitmap bmp, int y, int x, int height, int width)
{
	Color yellow;
	yellow.R = yellow.G = 255;
	yellow.B = 0;
	for (int i = y; i <= y + height; i++)
	{
		SetPixel(bmp, i, x, yellow);
	}
	for (int i = x; i <= x + width; i++)
	{
		SetPixel(bmp, y, i, yellow);
	}
	for (int i = y; i <= y + height; i++)
	{
		SetPixel(bmp, i, x + width, yellow);
	}
	for (int i = x; i <= x + width; i++)
	{
		SetPixel(bmp, y + height, i, yellow);
	}
}

Bitmap GetImage(Bitmap bmp, int y, int x)
{
	Bitmap image;
	image.width = 28;
	image.height = 28;
	image.rowSize = ((3 * image.width + 3) / 4) * 4;
	image.pixels = new unsigned char[image.rowSize * image.height];
	for (int i = y; i < y+28 && i < bmp.height; i++)
	{
		for (int j = x; j < x + 28 && j < bmp.width; j++)
		{
			Color color;
			GetPixel(bmp, i, j, color);
			SetPixel(image, i - y, j - x, color);
		}
	}
	return image;
}

void BrowseImage(Bitmap bmp, Images* face, Images* noface)
{
	//int max = bmp.height > bmp.width ? bmp.height : bmp.width;
	Bitmap image;
	cout << "Detecting...\n";
	Position maxPos = { 0,0 };
	Position minPos = { bmp.width - 1, bmp.height - 1 };
	cout << "       ";
	for (int i = 0; i < bmp.height - 28; i++)
	{
		printf("\b\b\b\b\b\b%3.2f%%", i*100.0 / (bmp.height - 29));
		for (int j = 0; j < bmp.width - 28; j++)
		{
			image = GetImage(bmp, i, j);
			if (Classifier(image, noface, threshold2, similarThreshold2, 0) == -1)
			{
				if (Classifier(image, face, threshold1, similarThreshold1) != -1)
				{
					//DrawRect(bmp, i, j, 28, 28);
					if (i < minPos.Y)
						minPos.Y = i;
					if (i > maxPos.Y)
						maxPos.Y = i;
					if (j < minPos.X)
						minPos.X = j;
					if (j > maxPos.X)
						maxPos.X = j;
				}
			}
			delete[] image.pixels;
		}
	}
	int width = maxPos.X - minPos.X + 28;
	int height = maxPos.Y - minPos.Y + 28;
	//DrawRect(bmp, minPos.Y, minPos.X, height/2, width/2);
	BlurImage(bmp, { (maxPos.X + minPos.X) / 2, (maxPos.Y + minPos.Y) / 2}, width/2, height/2);
}

void SaveClassifier(const char* firstImage, const char* fileName)
{
	ofstream file;
	file.open(fileName);
	Bitmap image;
	char path[100];
	strcpy(path, firstImage);
	int k = 2;
	while (LoadBitmap(path, image))
	{
		for (int i = 0; i < image.height; i++)
		{
			for (int j = 0; j < image.width; j++)
			{
				Color color;
				GetPixel(image, i, j, color);
				FixColor(color.R);
				FixColor(color.G);
				FixColor(color.B);
				file << color.R << color.G << color.B;
			}
		}
		path[strlen(path) - 7] = k / 100 + '0';
		path[strlen(path) - 6] = (k % 100) / 10 + '0';
		path[strlen(path) - 5] = (k % 10) + '0';
		k++;
	}
	file.close();
}

void LoadClassifier(Images* &images, const char* path)
{
	ifstream file;
	file.open(path, ios::binary | ios::ate);
	int lenght = file.tellg() / (28*28*3) ;
	file.close();
	file.open(path);
	Images* curImage;
	int count;
	for (count = 0; count < lenght; count++)
	{
		Images* im = new Images;
		Bitmap bitmap;
		bitmap.width = 28;
		bitmap.height = 28;
		bitmap.rowSize = ((3 * bitmap.width + 3) / 4) * 4;
		bitmap.pixels = new unsigned char[bitmap.rowSize * bitmap.height];
		for (int i = 0; i < 28; i++)
		{
			for (int j = 0; j < 28; j++)
			{
				Color color;
				char code;
				file.get(code);
				color.R = static_cast<unsigned char>(code);
				file.get(code);
				color.G = static_cast<unsigned char>(code);
				file.get(code);
				color.B = static_cast<unsigned char>(code);
				SetPixel(bitmap, i, j, color);
			}
		}
		im->bitmap = bitmap;
		if (images == NULL)
		{
			images = im;
		}
		else
		{
			curImage->next = im;
		}
		curImage = im;
		curImage->next = NULL;
	}
	cout << count << " images\n";
	file.close();
}

int FaceDetect(Bitmap &bmp)
{
	Images* face = NULL;
	Images* noface = NULL;
	SaveClassifier("train/FACES/YELLOW/train001.bmp", "train1.im");
	LoadClassifier(face, "train1.im");
	SaveClassifier("train/NOFACES/train001.bmp", "train2.im");
	LoadClassifier(noface, "train2.im");
	BrowseImage(bmp, face, noface);
	return 1;
}