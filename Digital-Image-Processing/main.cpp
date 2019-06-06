#include "Effect.h"
#include "Transform.h"
using namespace std;
//Test
int main()
{
	char *inFileName = (char*)malloc(100 * sizeof(char));
	const char *outFileName = "out.bmp";
	Bitmap bmp;
	printf("Enter file path:");
	scanf("%s", inFileName);
	int option;
	char next = 'Y';
	if (LoadBitmap(inFileName, bmp))
	{
		printf("Image Size: %dx%d\n", bmp.width, bmp.height);
		while (next == 'Y' || next == 'y')
		{
			cout << "Choose an option:\n"
				<< "\n1. Cut Image"
				<< "\n2. Balance Histogram"
				<< "\n3. Bunch Image"
				<< "\n4. Picture Frames"
				<< "\n5. Create Drawing"
				<< endl;
			scanf("%d", &option);
			switch (option)
			{
			case 1:
				int x, y, X, Y;
				printf("Nhập tọa độ đầu (x,y): \n");
				scanf("%d%d", &x, &y);
				printf("Nhập tọa độ sau (X,Y): \n");
				scanf("%d%d", &X, &Y);
				CutImage(bmp, x, y, X, Y);
				break;
			case 2:
				BalanceHistogram(bmp);
				break;
			case 3:
				int new_level;
				printf("Nhập độ độ bó cụm của ảnh: \n");
				scanf("%d", &new_level);
				BunchImage(bmp, new_level);
				break;
			case 4:
				int thickness, COLOR;
				printf("Nhập độ dày khung: \n");
				scanf("%d", &thickness);
				printf("Nhập màu sắc khung: \n");
				scanf("%d", &COLOR);
				PictureFrames(bmp, thickness, COLOR);
			case 5:
				int boundary;
				printf("Nhập độ nét của tranh vẽ: \n");
				scanf("%d", &boundary);
				FindBoundary(bmp, boundary);
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
