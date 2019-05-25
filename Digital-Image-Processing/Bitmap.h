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
void Cut_image(Bitmap &inbmp, int x, int y, int X, int Y);
void Balance_Histogram(const Bitmap &bmp, int new_level = 255);
void Bunch_image(const Bitmap &bmp, int new_level);
int* Array_convert_color(Bitmap bmp, int new_level);
unsigned char Convert_color(int *a, unsigned char A);
void Picture_frames(Bitmap &bmp, int thickness = 5, unsigned char COLOR = 255);
void Find_boundary(Bitmap &bmp, double boundary, int R = 2);


#endif
