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
				TransfromOption(bmp);
				break;
			case 2:
				ColorOption(bmp);
				break;
			case 3:
				EffectOption(bmp);
				break;
			default:
				cout << "Wrong command!";
				break;
			}
			cout << "Enter output image's path:";
			cin >> outFileName;
			if (!SaveBitmap(outFileName, bmp))
				cout << "Can not save the bitmap file!!!\n";
			system(outFileName);
			system("cls");
		}
		else
			cout << "Can not load the bitmap file!!!\n";
		cout << "Would you like to continue?(Y/N)\n";
		cin >> next;
	}
	cout << "Bye!\n";

	return 0;
}
