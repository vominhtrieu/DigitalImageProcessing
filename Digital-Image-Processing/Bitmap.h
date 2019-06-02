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
void reverse_image(const Bitmap &bmp,int k);
void AdjustBrightness(const Bitmap &bmp, double factor);
void Enlarge(const Bitmap &inbmp, Bitmap &outbmp);
void zoomimage(const Bitmap &inbmp, Bitmap &outbmp, int k);

void CutImage(Bitmap &inbmp, int x, int y, int X, int Y);
void BalanceHistogram(const Bitmap &bmp);
int* Arrayconvertcolor(Bitmap bmp, int new_level);
unsigned char Convertcolor(int *a, unsigned char A);
void BunchImage(const Bitmap &bmp, int new_level);
void PictureFrames(Bitmap &bmp, int thickness, unsigned char COLOR);
void FindBoundary(Bitmap &bmp, double boundary);


#endif
