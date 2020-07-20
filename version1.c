#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void concatString(char *mainString, char *target)
{
    if (*(target) == '\0')
    {
        *(mainString - 1) = ',';
        *(mainString) = *(target);
    }
    else if (*(mainString) == '\0')
    {
        *(mainString) = *(target);
        *(mainString + 1) = '\0';
        concatString(mainString + 1, target + 1);
    }
    else
    {
        concatString(mainString + 1, target);
    }
}

void newBookEntry()
{
    printf("\n************************************");

    //values to ask
    char bookName[20], authorName[20], language[10], date[10];
    char finalInputValue[200];

    //ERROR : program skips the first fgets automatically
    char s[2];
    fgets(s, sizeof(s), stdin);

    //clear the console
    printf("\e[1;1H\e[2J");

    //ask for details
    //using fgets instead of gets as fgets is safe to use in comparison to gets since it checks for character array str bounds
    printf("\n\tEnter the name of the book (max : 20) : ");
    fgets(bookName, sizeof(bookName), stdin);
    concatString(finalInputValue, bookName);

    printf("\n\tEnter the author's name (max : 20) : ");
    fgets(authorName, sizeof(authorName), stdin);
    concatString(finalInputValue, authorName);

    printf("\n\tEnter the language in which it's written (max : 10) : ");
    fgets(language, sizeof(language), stdin);
    concatString(finalInputValue, language);

    printf("\n\tEnter the date (DD/MM/YYYY) : ");
    fgets(date, sizeof(date), stdin);
    concatString(finalInputValue, date);

    printf("The result is : %s ", finalInputValue);

    //clear the console
    printf("\e[1;1H\e[2J");

    //input the data into the file
    FILE *filePointer;

    //open the file in append mode
    filePointer = fopen("BookData.csv", "a");

    if (filePointer == NULL)
        printf("\n\nInvalid\n");
    else
    {
        //write into the file
        fputs(finalInputValue, filePointer);
        fputs("\n", filePointer);

        //close the file
        fclose(filePointer);

        printf("\n\tSuccessfully written\n");
    }
}

void endCell(int total)
{
    int count;
    count = 20 - total;
    for (int i = 0; i < count; i++)
        printf(" ");
}

void displayBooks()
{
    printf("\n************************************");

    FILE *filePointer;

    int serialNumber = 0;
    char readLine[1000];

    //open the file in read mode
    filePointer = fopen("BookData.csv", "r");

    //clear the console
    printf("\e[1;1H\e[2J");

    if (filePointer == NULL)
        printf("\n\n***File not present.***\n");
    else
    {
        printf("\n\n***File opened.***\n\n");

        while (fgets(readLine, 1000, filePointer) != NULL)
        {
            int wordCount = 0;
            // printf("\t%s", readLine);

            //printing the serial number
            if (serialNumber != 0)
                printf("%d", serialNumber);
            else
                printf("Sl no.");
            serialNumber++;

            printf("\t");

            for (int i = 0; i < strlen(readLine); i++)
            {
                if (readLine[i] == ',')
                {
                    endCell(wordCount);
                    wordCount = 0;
                }
                else
                {
                    wordCount++;
                    printf("%c", readLine[i]);
                }
            }
        }

        //close the file
        fclose(filePointer);
    }

    printf("\n***End of file***\n");
}

// function to copy files that take name of the file to be copied and to the file to be copied
void copyFiles(char firstFile[], char secondFile[])
{
    FILE *firstFilePointer, *secondFilePointer;

    char readLine[1000];

    firstFilePointer = fopen(firstFile, "r");
    secondFilePointer = fopen(secondFile, "w");

    if (firstFilePointer == NULL)
        printf("\nFile to be copied can't be opened\n");
    else
    {
        while (fgets(readLine, 1000, firstFilePointer) != NULL)
        {
            fputs(readLine, secondFilePointer);
        }
        fclose(firstFilePointer);
        fclose(secondFilePointer);
    }
}

//deleting a book
void deleteBook()
{
    printf("\n************************************");

    FILE *filePointer, *tempFilePointer;

    char readLine[1000];
    int deleteRecordSerialNumber = 0, serialNumber = 0;

    filePointer = fopen("BookData.csv", "r");
    tempFilePointer = fopen("TempFile.csv", "w");

    // ask for the record to be deleted
    printf("\nEnter the serial number of the record to be deleted : ");
    scanf("%d", &deleteRecordSerialNumber);
    if (deleteRecordSerialNumber <= 0)
    {
        printf("\n***Invalid Input***\n");
        exit(0);
    }

    //clear the console
    printf("\e[1;1H\e[2J");

    if (filePointer == NULL)
        printf("\n\n***File not present.***\n");
    else
    {
        //write all the data in a temp file without the deleted data
        while (fgets(readLine, 1000, filePointer) != NULL)
        {
            if (serialNumber != deleteRecordSerialNumber)
            {
                fputs(readLine, tempFilePointer);
            }
            serialNumber++;
        }

        if (deleteRecordSerialNumber > serialNumber)
            printf("\n***Invalid Input***\n");
        fclose(filePointer);
        fclose(tempFilePointer);
    }
    copyFiles("TempFile.csv", "BookData.csv");

    //delete the temp file
    int del = remove("TempFile.csv");
    if (del != 0)
        printf("\n***Something went wrong***\n");

    printf("\n\nSuccessfully Deleted.\n\n");
}

// function to create backup
void createBackUp()
{
    printf("\n************************************");

    FILE *filePointer;

    //ERROR : program skips the first fgets automatically
    char s[2];
    fgets(s, sizeof(s), stdin);

    //clear the console
    printf("\e[1;1H\e[2J");

    copyFiles("BookData.csv", "Backup.csv");

    printf("\n\nBackup successfull.\n\n");
}

int main()
{
    char choice;

    //create a file if it doesn't exists
    FILE *file;
    file = fopen("BookData.csv", "r");
    if (file == NULL)
    {
        char text[100] = "Book Name,Author Name,Language,Date,";

        FILE *newFile;
        newFile = fopen("BookData.csv", "w");
        fputs(text, newFile);
        fputs("\n", newFile);

        fclose(newFile);
    }

    //main loop for the program
    while (1)
    {
        printf("\n____________________________________");
        //***

        printf("\n\nSelect :\n");

        //display options of actions
        printf("\n 1. Enter a new book.");
        printf("\n 2. Delete an existing book.");
        printf("\n 3. Display all books.");
        printf("\n 4. Create a backup file.");
        printf("\n 5. Exit. \n \t : ");

        //take input and process.
        scanf(" %c", &choice);

        //check if the user wants to QUIT
        if (choice == '5')
            break;

        //switch cases to operate all funtions conditionally
        switch (choice)
        {
        case '1':
            printf("\n Option 1 selected.");
            newBookEntry();
            break;
        case '2':
            printf("\n Option 2 selected.");
            displayBooks();
            deleteBook();
            break;
        case '3':
            printf("\n Option 3 selected.");
            displayBooks();
            break;
        case '4':
            printf("\n Option 4 selected.");
            createBackUp();
            break;

        default:
            printf("\n Invalid option.");
            break;
        }

        //****
        printf("\n____________________________________");
    }
    return 0;
}