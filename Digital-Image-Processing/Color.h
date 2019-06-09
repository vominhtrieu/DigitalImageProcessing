#include "Bitmap.h"

char Truncate(double R);
void ColorOption(Bitmap&bmp);
void BlackWhite(const Bitmap& bmp);
void ContrastAdjustment(const Bitmap &bmp, int C);
void Negative(const Bitmap& bmp);
void AdjustBrightness(const Bitmap &bmp, double factor);
void BalanceHistogram(const Bitmap &bmp, int newLevel);
void NormalizeImage(Bitmap &bmp, int newMin, int newMax);
void BlurImage(const Bitmap &inbmp, Toado TamElip, float ngang, float doc);
