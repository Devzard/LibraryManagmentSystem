#include <stdio.h>
#include <string.h>

void overWrite()
{
	FILE *filePointer;

	char testingText[100] = "Name,Class,Time,\nDev,D,20";

	filePointer = fopen("Test.csv", "w");

	if (filePointer == NULL)
		printf("\n\nInvalid\n");
	else
	{
		printf("\n\nFile opened.");
		if (strlen(testingText) > 0)
		{
			fputs(testingText, filePointer);
			fputs("\n", filePointer);
		}

		fclose(filePointer);

		printf("\n\nSuccessfully written\n\n");
	}
}

void readFile()
{
	FILE *filePointer;

	char read[100];

	filePointer = fopen("Test.txt", "r");

	if (filePointer == NULL)
		printf("\n\nFile not present.\n");
	else
	{
		printf("\n\nFile opened.\n");

		while (fgets(read, 100, filePointer) != NULL)
		{
			printf("%s", read);
		}
		fclose(filePointer);
	}

	printf("\n\nSuccess\n");
}

int main()
{
	overWrite();
	// readFile();
	return 0;
}
