#include "Effect.h"
#include "Transform.h"
#include <string>
using namespace std;
//Test
int main()
{
	char *inFileName = (char*)malloc(100 * sizeof(char));
	char *outFileName = (char*)malloc(100 * sizeof(char));
	Bitmap bmp;
	int option;
	char next = 'Y';
	while (next == 'Y' || next == 'y')
	{
		system("cls");
		cout << "Enter input image's path:";
		cin >> inFileName;
		if (LoadBitmap(inFileName, bmp))
		{
			cout << "Choose an option:\n"
				<< "\n1. Transform"
				<< "\n2. Color"
				<< "\n3. Effect"
				<< endl;
			cin >> option;
			switch (option)
			{
			case 1:
				TransformOption(bmp);
				break;
			case 2:
				ColorOption(bmp);
				break;
			case 3:
				EffectOption(bmp);
				break;
			default:
				cout << "Wrong command!\n";
				break;
			}
			cout << "Enter output image's path:";
			cin >> outFileName;
			if (!SaveBitmap(outFileName, bmp))
				cout << "Can not save the bitmap file!!!\n";
			else
			{
				system(outFileName);
				cout << "\nIf the image does not automatically show, please open it in your OS's file explorer\n";
			}
		}
		else
			cout << "Can not load the bitmap file!!!\n";
		cout << "\nWould you like to continue?(Y/N)\n";
		cin >> next;
	}
	cout << "Bye!\n";

	return 0;
}
