#include <stdio.h>
#include <string.h>

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
    char bookName[100], authorName[20], language[10], date[10];
    char finalInputValue[200];

    //ERROR : program skips the first fgets automatically
    char s[2];
    fgets(s, sizeof(s), stdin);

    //ask for details
    //using fgets instead of gets as fgets is safe to use in comparison to gets since it checks for character array str bounds
    printf("\n\tEnter the name of the book (max : 100) : ");
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

void displayBooks()
{
    printf("\n************************************");

    FILE *filePointer;

    char readLine[1000];

    //open the file in read mode
    filePointer = fopen("BookData.csv", "r");

    //clear the console
    printf("\e[1;1H\e[2J");

    if (filePointer == NULL)
        printf("\n\nFile not present.\n");
    else
    {
        printf("\n\nFile opened.\n\n");

        while (fgets(readLine, 1000, filePointer) != NULL)
        {
            printf("\t%s", readLine);
        }

        //close the file
        fclose(filePointer);
    }

    printf("\n***End of file***\n");
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
        printf("\n 4. Exit. \n \t : ");

        //take input and process.
        scanf(" %c", &choice);

        //check if the user wants to QUIT
        if (choice == '4')
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
            break;
        case '3':
            printf("\n Option 3 selected.");
            displayBooks();
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