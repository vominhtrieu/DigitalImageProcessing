#include "Color.h"

void EffectOption(Bitmap &bmp);
void FilterSummer(Bitmap &bmp, float percent);
void FilterWinter(Bitmap &bmp, float pt1, float pt2);
void SnowEffect(Bitmap &bmp);
void SaltPepperNoise(Bitmap &bmp);
void Pastel(Bitmap &bmp);
void PictureFrames(Bitmap &bmp, int thickness, unsigned char COLOR);
void BunchImage(const Bitmap &bmp, int new_level);
void FindBoundary(Bitmap &bmp, double boundary, int R);
void ConvertToPencilSketch(Bitmap &bmp);
void Sharpen(const Bitmap &inbmp, double k);
void MixImage(Bitmap bmp1, Bitmap bmp2);
void BlurImage(const Bitmap &inbmp, Toado TamElip, float ngang, float doc, double sigma);
