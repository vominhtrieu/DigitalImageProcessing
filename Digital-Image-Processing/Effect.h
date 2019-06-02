#include "Color.h"

void EffectOption(Bitmap &bmp);
void FilterSummer(const Bitmap &bmp, int percent);
void FilterWinter(Bitmap &bmp, float pt1, float pt2);
void SnowEffect(Bitmap &bmp);
void SaltPepperNoise(Bitmap &bmp);
void Pastel(Bitmap &bmp);
void PictureFrames(Bitmap &bmp, int thickness, unsigned char COLOR);
void BunchImage(const Bitmap &bmp, int new_level);
void FindBoundary(Bitmap &bmp, double boundary, int R);
void ConvertToPencilSketch(Bitmap &bmp);