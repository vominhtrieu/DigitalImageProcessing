#include <stdio.h>
#include "Bitmap.h"

int main()
{
	const char *inFileName = "MARBLES.BMP";
	const char *outFileName= "out.bmp";
	Bitmap bmp;
	
	if(LoadBitmap(inFileName, bmp))
	{
		printf("%dx%d\n", bmp.width, bmp.height);
		BlackWhite(bmp);
		//AdjustBrightness(bmp, 2);
		
		if(!SaveBitmap(outFileName, bmp))
			printf("Can not save the bitmap file!!!\n");
		
		DisposeBitmap(bmp);
	}
	else
		printf("Can not load the bitmap file!!!\n");
	
	printf("Bye!\n");
	
	return 0;
}
