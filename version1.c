#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//UTILITIES

int removeNewline(char *buf)
{
    char *ptr = strchr(buf, '\n');
    if (ptr)
    {
        //if new line found replace with null character
        *ptr = '\0';
        return 0;
    }
    else
    {
        return -1;
    }
}

char *concatString(char *book, char *author, char *lang, char *date)
{
    int reqsize = sizeof(book) + sizeof(author) + sizeof(lang) + sizeof(date) + 8;
    char *target = malloc(sizeof(char) * 256);
    removeNewline(book);
    removeNewline(author);
    removeNewline(lang);
    removeNewline(lang);
    snprintf(target, 256, "%s,%s,%s,%s", book, author, lang, date);
    return target;
}

int newEntry(char *data)
{
    //input the data into the file
    FILE *filePointer;

    //open the file in append mode
    filePointer = fopen("BookData.csv", "a");

    if (filePointer == NULL)
    {
        printf("\n\nInvalid\n");
        return -1;
    }
    else
    {
        //write into the file
        fputs(data, filePointer);

        //close the file
        fclose(filePointer);

        printf("\n\tSuccessfully written\n");
        return 0;
    }
}

//TAKE USER INPUT

void newBookEntry()
{
    printf("\n************************************");

    //values to ask
    char bookName[100], authorName[20], language[10], date[10];

    //ask for details
    //using fgets instead of gets as fgets is safe to use in comparison to gets since it checks for character array str bounds
    printf("\n\tEnter the name of the book (max : 100) : ");
    fgets(bookName, sizeof(bookName), stdin);
    printf("\n\tEnter the author's name (max : 20) : ");
    fgets(authorName, sizeof(authorName), stdin);
    printf("\n\tEnter the language in which it's written (max : 10) : ");
    fgets(language, sizeof(language), stdin);
    printf("\n\tEnter the date (DD/MM/YYYY) : ");
    fgets(date, sizeof(date), stdin);

    //clear input buffer
    fflush(stdin);

    printf("%s", concatString(bookName, authorName, language, date));

    newEntry(concatString(bookName, authorName, language, date));
}

void displayBooks()
{
    printf("\n************************************");

    FILE *filePointer;

    char readLine[1024];

    //open the file in read mode
    filePointer = fopen("BookData.csv", "r");

    //clear the console
    printf("\e[1;1H\e[2J");

    if (filePointer == NULL)
        printf("\n\nFile not present.\n");
    else
    {
        printf("\n\nFile opened.\n\n");
        int row_count = 0;
        int field_count = 0;
        while (fgets(readLine, 1000, filePointer) != NULL)
        {
            printf("%s", readLine);
        }

        //close the file
        fclose(filePointer);
    }

    printf("\n***End of file***\n");
}
