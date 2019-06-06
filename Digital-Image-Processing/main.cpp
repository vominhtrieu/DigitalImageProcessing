#include "Effect.h"
#include "Transform.h"
using namespace std;
//Test
int main()
{
	char *inFileName = (char*)malloc(100*sizeof(char));
	const char *outFileName= "out.bmp";
	Bitmap bmp;
	printf("Enter file path:");
	scanf("%s", inFileName);
	int option;
	char next = 'Y';
	int q = 0;
	if(LoadBitmap(inFileName, bmp))
	{
		printf("Image Size: %dx%d\n", bmp.width, bmp.height);
		while (next == 'Y' || next == 'y')
		{
			cout << "Choose an option:\n"
				<< "\n1. Transform"
				<< "\n2. Color"
				<< "\n3. Effect"
				<< endl;
			scanf("%d", &option);
			switch (option)
			{
			case 1:
				TransfromOption(bmp);
				break;
			case 2:
				ColorOption(bmp);
				break;
			case 3:
				EffectOption(bmp);
				break;
			
			default:
				printf("Wrong command!");
				break;
			}
			if (!SaveBitmap(outFileName, bmp))
				cout << "Can not save the bitmap file!!!\n";
			system("start out.bmp");
			system("cls");
			cout << "Would you like to continue?(Y/N)\n";
			cin >> next;
		}
		DisposeBitmap(bmp);
	}
	else
		printf("Can not load the bitmap file!!!\n");
	
	printf("Bye!\n");
	
	return 0;
}