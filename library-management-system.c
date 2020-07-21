
//   _      _ _                          __  __                                                   _    _____           _
//  | |    (_) |                        |  \/  |                                                 | |  / ____|         | |
//  | |     _| |__  _ __ __ _ _ __ _   _| \  / | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_| (___  _   _ ___| |_ ___ _ __ ___
//  | |    | | '_ \| '__/ _` | '__| | | | |\/| |/ _` | '_ \ / _` |/ _` |/ _ \ '_ ` _ \ / _ \ '_ \| __|\___ \| | | / __| __/ _ \ '_ ` _ \ 
//  | |____| | |_) | | | (_| | |  | |_| | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_ ____) | |_| \__ \ ||  __/ | | | | |
//  |______|_|_.__/|_|  \__,_|_|   \__, |_|  |_|\__,_|_| |_|\__,_|\__, |\___|_| |_| |_|\___|_| |_|\__|_____/ \__, |___/\__\___|_| |_| |_|
//                                  __/ |                          __/ |                                      __/ |
//                                 |___/                          |___/                                      |___/
//
//
//  Submitted by:
//  - Debashish Gogoi, 190710007017
//  - Rishparn Gogoi, 190710007045
//
//  Jorhat Engineering Colege, AS, IN
//
//  Date: 12/12/1212
//
//  Github: https://github.com/Devzard/LibraryManagmentSystem
//
//  Build Successful on gcc 9.3.0
//  Tested on Ubuntu 18.04 and Kubuntu 20.04

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//Using in Login amd Register
struct person
{
    char uname[12];
    char pass[12];
};

//UTILS
int initFile();
int credential_checks();
int signup(char *uname, char *pass);
int signin(char *uname, char *pass);
int removeNewline(char *buf);
char *concatString(char *book, char *author, char *lang, char *date);
int newEntry(char *data);
void endCell(int total);
void copyFiles(char firstFile[], char secondFile[]);

//CLI FUNCTIONS
int register_prompt();
int login_prompt();
void newBookEntry();
void displayBooks();
void deleteBook();
void createBackUp();

int main()
{
    char choice;

    int auth_status = credential_checks();

    int isLoggedin = 0, temp_status;

    if (auth_status == 33)
    {
        //Registration Required
        temp_status = register_prompt();
        isLoggedin = (temp_status == 22) ? 1 : 0;
    }
    else if (auth_status == 44)
    {
        //Login Required
        temp_status = login_prompt();
        if(temp_status == 22)
        {
            isLoggedin = 1;
            printf("\n\nACCESS GRANTED\n\n");
            sleep(2);
            printf("\e[1;1H\e[2J");
            printf(" _      _ _                          __  __                                                   _    _____           _\n");
            printf("| |    (_) |                        |  \\/  |                                                 | |  / ____|         | |\n");
            printf("| |     _| |__  _ __ __ _ _ __ _   _| \\  / | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_| (___  _   _ ___| |_ ___ _ __ ___  \n");
            printf("| |    | | '_ \\| '__/ _` | '__| | | | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __|\\___ \\| | | / __| __/ _ \\ '_ ` _ \\ \n");
            printf("| |____| | |_) | | | (_| | |  | |_| | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_ ____) | |_| \\__ \\ ||  __/ | | | | |\n");
            printf("|______|_|_.__/|_|  \\__,_|_|   \\__, |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__|_____/ \\__, |___/\\__\\___|_| |_| |_|\n");
            printf("                                __/ |                          __/ |                                      __/ | \n");
            printf("                               |___/                          |___/                                      |___/   \n\n");

        }
        else
        {
            printf("ACCESS DENIED");
        }
        
    }

    //create a file if it doesn't exists
    initFile();

    //main loop for the program
    while (isLoggedin == 1)
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

        // take input and process.
        scanf(" %c", &choice);

        //clears input buffer
        while ((getchar()) != '\n');

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

        printf("\n____________________________________");
    }
    return 0;
}

//FUNCTION DECLARATIONS
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
    return 0;
}

// Registration Required code: 33
// Login Required code: 44
int credential_checks()
{
    int status;
    FILE *credFile;
    credFile = fopen("cred.dat", "r");
    if (credFile == NULL)
    {
        FILE *newFile;
        newFile = fopen("cred.dat", "w");
        fclose(newFile);
        return 33;
    }
    return 44;
}

// Success code: 22
int signup(char *uname, char *pass)
{
    FILE *credFile;

    // open file for appending
    credFile = fopen("cred.dat", "a");
    if (credFile == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit(1);
    }

    struct person input;
    strcpy(input.uname, uname);
    strcpy(input.pass, pass);
    printf("%s, %s", input.uname, input.pass);

    // write struct to file
    fwrite(&input, sizeof(struct person), 1, credFile);

    // close file
    fclose(credFile);
    return 22;
}

// Success code: 22
// Failed code: 99
int signin(char *uname, char *pass)
{

    int found = 0;

    FILE *credFile;
    struct person input;

    credFile = fopen("cred.dat", "r");
    if (credFile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    // read file contents till end of file
    while (fread(&input, sizeof(struct person), 1, credFile))
        if (strcmp(input.uname, uname) == 0 && strcmp(input.pass, pass) == 0)
        {
            found = 1;
            break;
        }

    // close file
    fclose(credFile);
    return found == 1 ? 22 : 99;
}

// Success code: 22
// Failed code: 99
int login_prompt()
{
    char uname[12], pass[12];
    printf("\e[1;1H\e[2J");
    printf("     __          __  _                            ____             _     \n");
    printf("     \\ \\        / / | |                          |  _ \\           | |    \n");
    printf("      \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  | |_) | __ _  ___| | __ \n");
    printf("       \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ |  _ < / _` |/ __| |/ / \n");
    printf("        \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | |_) | (_| | (__|   <  \n");
    printf("         \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___| |____/ \\__,_|\\___|_|\\_\\ \n\n");

    printf("°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸\n\n");
    printf("Username: ");
    scanf("%s", uname);
    printf("\nPassword: ");
    scanf("%s", pass);
    return (signin(uname, pass) == 22) ? 22 : 99;
}

// Success code: 22
int register_prompt()
{
    char uname[12], pass[12], confirm_pass[12];
    printf("\e[1;1H\e[2J");
    printf(" _      _ _                          __  __                                                   _    _____           _\n");
    printf("| |    (_) |                        |  \\/  |                                                 | |  / ____|         | |\n");
    printf("| |     _| |__  _ __ __ _ _ __ _   _| \\  / | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_| (___  _   _ ___| |_ ___ _ __ ___  \n");
    printf("| |    | | '_ \\| '__/ _` | '__| | | | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __|\\___ \\| | | / __| __/ _ \\ '_ ` _ \\ \n");
    printf("| |____| | |_) | | | (_| | |  | |_| | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_ ____) | |_| \\__ \\ ||  __/ | | | | |\n");
    printf("|______|_|_.__/|_|  \\__,_|_|   \\__, |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__|_____/ \\__, |___/\\__\\___|_| |_| |_|\n");
    printf("                                __/ |                          __/ |                                      __/ | \n");
    printf("                               |___/                          |___/                                      |___/   \n\n");

    printf("°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸\n\n");
    printf("Welcome to the project 'LIBRARY MANAGEMENT SYSTEM'\n");
    printf("Created by: Debashish Gogoi (190710007017) and Rishparn Gogoi (190710007045).");
    printf("\n\nCreate new account \n\n");
    while (1)
    {
        printf("Username: ");
        scanf("%s", uname);
        printf("\nPassword: ");
        scanf("%s", pass);
        printf("\nRe-enter password: ");
        scanf("%s", confirm_pass);
        if (strcmp(pass, confirm_pass) == 0)
        {
            signup(uname, pass);
            printf("ACCOUNT CREATED SUCCESSFULLY");
            break;
        }
        else
        {
            printf("Passwords did not match. Re-try.");
        }
    }
    return 22;
}

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

//TAKES USER INPUT

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

    newEntry(concatString(bookName, authorName, language, date));
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
    sleep(1);
}

// function to create backup
void createBackUp()
{
    printf("\n************************************");

    FILE *filePointer;

    //clear the console
    printf("\e[1;1H\e[2J");

    copyFiles("BookData.csv", "Backup.csv");

    printf("\n\nBackup successfull.\n\n");
}
