#include "Effect.h"
#include "Transform.h"
using namespace std;
//Test
int main()
{
	char *inFileName = (char*)malloc(100 * sizeof(char));
	const char *outFileName = "out.bmp";
	Bitmap bmp;
	int option;
	char next = 'Y';
	while (next == 'Y' || next == 'y')
	{
		printf("Enter file path:");
		cin >> inFileName;
		if (LoadBitmap(inFileName, bmp))
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
			DisposeBitmap(bmp);
			system("start out.bmp");
			system("cls");
		}
		else
			printf("Can not load the bitmap file!!!\n");
		cout << "Would you like to continue?(Y/N)\n";
		cin >> next;
	}
	printf("Bye!\n");

	return 0;
}
