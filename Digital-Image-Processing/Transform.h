#include "Bitmap.h"

void TransfromOption(Bitmap &bmp);
void Resize(Bitmap& inbmp, int width, int height);
void Flip(const Bitmap &bmp, int k);
void Rotate(Bitmap &inbmp);
void CutImage(Bitmap &inbmp, int x, int y, int X, int Y);