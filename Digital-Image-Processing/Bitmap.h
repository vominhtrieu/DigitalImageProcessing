#ifndef _BITMAP_
#define _BITMAP_

#pragma warning(disable:4996)
struct Bitmap
{
	int width;
	int height;
	int rowSize;
	unsigned char *pixels;
};

struct Color
{
	unsigned char R, G, B;
};

int LoadBitmap(const char *fname, Bitmap &bmp);
int SaveBitmap(const char *fname, const Bitmap &bmp);
void DisposeBitmap(Bitmap &bmp);

int SetPixel(const Bitmap &bmp, int row, int col, Color color);
int GetPixel(const Bitmap &bmp, int row, int col, Color &color);

void BlackWhite(const Bitmap& bmp);
void Negative(const Bitmap& bmp);
void reverse_image(const Bitmap &bmp,int k);
void AdjustBrightness(const Bitmap &bmp, double factor);
double Truncate(double R);
double max(double a, double b);
void AutoContrastAdjustment(const Bitmap &bmp);
void FilterSummer(const Bitmap &bmp, int percent);
void ContrastAdjustment(const Bitmap &bmp, int C);
void Enlarge(const Bitmap &inbmp, Bitmap &outbmp);

#endif
