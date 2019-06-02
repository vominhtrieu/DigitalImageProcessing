#include <stdio.h>
#include <iostream>
#include "Bitmap.h"
using namespace std;
//Test
int main()
{
	char *inFileName = (char*)malloc(100*sizeof(char));
	const char *outFileName= "out.bmp";
	Bitmap bmp,bmpout;
	printf("Enter file path:");
	scanf("%s", inFileName);
	int option;
	char next = 'Y';
	if(LoadBitmap(inFileName, bmp))
	{
		printf("Image Size: %dx%d\n", bmp.width, bmp.height);
		while (next == 'Y' || next == 'y')
		{
			printf("Choose an option:\n1.Black White\n2.AdjustBrightess\n3.reverse.\n4.Blur.\n5.FilterWinter.\n6.Sow Effect.\n7.Salt and Pepper Noise.\n8.Pastel.\n9.Rotate.\n");
			scanf("%d", &option);
			switch (option)
			{
			case 1:
				
				BlackWhite(bmp);
				break;
			case 2:
				float a;
				cout << "nhap do tang sang: ";
				cin >> a;
				AdjustBrightness(bmp, a);
				break;
			case 3:
				int k;
				printf("1.Dao nguoc theo be doc.\n2.Dao nguoc theo be ngang\n");
				scanf("%d", &k);
				reverse_image(bmp,k);
				break;
			default:
				printf("Wrong command!");
				break;
			case 4:
				Toado tam;
				float ax, b,zigma;
				
				cout << "nhap toa do tam: "<<endl;
				cin >> tam.x >> tam.y;
				cout << "Nhap be ngang, doc cau elip: "<<endl;
				cin >> ax; cin >> b;

				cout << "Nhap muc do lam nhoe anh (1-10): ";
				cin >> zigma;
				zigma*= 2.5;
			
				BlurImage(bmp, tam, ax, b, zigma);

				break;
			case 5:
				float percent;
				cout << "Nhap muc do ban muon: (0% - 100%): ";
				cin >> percent;
				percent = (100 - percent) / 100;
				FilterWinter(bmp, percent, 0.9);
				break;
			case 6:
				SnowEffect(bmp);
				break;
			case 7:
				SaltPepperNoise(bmp);
				break;
			case 8:
				Pastel(bmp);
				break;
			case 9:
				Rotate(bmp, 100);
				break;
			}
			if (!SaveBitmap(outFileName, bmp))
				printf("Can not save the bitmap file!!!\n");
			#ifdef _WIN32
				system("start out.bmp");
			#else
				system("open out.bmp");
			#endif
			printf("Would you like to continue?(Y/N)");
			scanf("\n%c", &next);
			#ifdef _WIN32
				system("cls");
			#else
				system("clear");
			#endif
		}
		DisposeBitmap(bmp);
	}
	else
		printf("Can not load the bitmap file!!!\n");
	
	printf("Bye!\n");
	
	return 0;
}
