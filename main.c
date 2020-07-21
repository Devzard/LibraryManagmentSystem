#include "version1.c"

#define KEY_SPACE 32 //Space Bar
#define KEY_x 120    //x key
#define KEY_X 88     //X key
#define KEY_0 48     //0
#define KEY_1 49     //1
#define KEY_2 50     //2
#define KEY_3 51     //3
#define KEY_4 52     //4
#define KEY_5 53     //5
#define KEY_6 54     //6
#define KEY_7 55     //7
#define KEY_8 56     //8
#define KEY_9 57     //9

int initFile()
{
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
        return 0;
    }
    return 1;
}

int main()
{
    char choice;

    //create a file if it doesn't exists
    initFile();

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

        //clears input buffer
        while ((getchar()) != '\n');

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