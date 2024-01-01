#include <stdio.h>
#include <math.h>
#include <string.h>
#include "defines.h"

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
double isValidDouble(char *message, int min_value, int max_value, int decimal_places)
{
    double num = 0;
    double intPart = 0;
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[33m"
               "\nEnter %s [%d; %d]:\n"
               "\x1B[0m",
               message, min_value, max_value);
        if (scanf("%lf", &num) != 1 || getchar() != '\n')
        {
            printf("\x1B[31m"
                   "Invalid input. Please enter a number.\n"
                   "\x1B[0m");
            fflush(stdin);
            continue;
        }
        if (num < min_value || num > max_value)
        {
            printf("\x1B[31m"
                   "It seems you`ve entered a value that is out of acceptable range. Please enter a number between 0 and %d.\n"
                   "\x1B[0m",
                   max_value);
            continue;
        }
        if (num == 0)
        {
            printf("\x1B[31m"
                   "Sorry, but the input cannot be equal to zero. Please try again.\n"
                   "\x1B[0m");
            continue;
        }
        if (modf(num * pow(10, decimal_places), &intPart) != 0.0)
        {
            printf("\x1B[31m"
                   "Entered value doesn't have the specified precision. Please enter a number with accuracy to %d decimal places.\n"
                   "\x1B[0m",
                   decimal_places);
            continue;
        }
        inputValid = 1;
    }
    return num;
}
int isValidInt(char *message, int min_value, int max_value)
{
    int num = 0;
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[33m"
               "\nEnter %s [%d; %d]:\n"
               "\x1B[0m",
               message, min_value, max_value);
        if (scanf("%d", &num) != 1 || getchar() != '\n')
        {
            printf("\x1B[31m"
                   "Invalid input. Please enter a whole number.\n"
                   "\x1B[0m");
            fflush(stdin);
            continue;
        }
        if (num < min_value || num > max_value)
        {
            printf("\x1B[31m"
                   "Sorry but you`ve entered a value that is out of acceptable range. Please enter a number between %d and %d inclusively.\n"
                   "\x1B[0m",
                   min_value, max_value);
            continue;
        }
        inputValid = 1;
    }
    return num;
}
int isValidChoice(int choice, int min_choice, int max_choice)
{
    int inputValid = 0;
    while (!inputValid)
    {
        if (scanf("%d", &choice) != 1 || getchar() != '\n')
        {
            printf("\x1b[31m"
                   "Ohh, sorry but there`s an error in your input. Please try again by pressing the specified keys.\n"
                   "\x1b[0m");
            fflush(stdin);
            continue;
        }
        if (choice < min_choice || choice > max_choice)
        {
            printf("\x1b[31m"
                   "Ohh, it seems that there`s an error occured. You`ve entered a number that is not specified as an option.\n"
                   "\x1b[0m");
            continue;
        }
        inputValid = 1;
    }

    return choice;
}
void isValidString(char *message, char *string, int charsPerLine)
{
    int inputValid = 0;
    while (!inputValid)
    {
        printf("\x1B[33m"
               "\nEnter %s: \n"
               "\x1B[0m",
               message);
        if (scanf("%s", string) != 1)
        {
            printf("Invalid input. Please enter a string.\n");
            fflush(stdin);
            continue;
        }
        size_t stringLength = strlen(string);
        if (stringLength > charsPerLine || stringLength < 1)
        {
            printf("Oops! It seems that your input is out of acceptable range. Please enter a string between 1 and %d symbols.\n", charsPerLine);
            continue;
        }
        inputValid = 1;
    }
}
int getLastRecordID(FILE *file, int *maxID)
{
    int lastID = 0;
    int currentID;

    rewind(file);

    while (fscanf(file, "ID: %d", &currentID) == 1)
    {
        while (fgetc(file) != '\n')
            ;

        lastID = currentID;
    }

    *maxID = lastID;

    return lastID;
}
int getNumRecords()
{
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return 0;
    }

    int numRecords = 0;
    char line[MAX_FILE_CONTENT];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, "ID:") != NULL)
        {
            numRecords++;
        }
    }

    fclose(file);
    return numRecords;
}
void printfMainMenu()
{

    printf("\x1B[1m"
           "\nMAIN MENU\n");
    printf("Choose a menu you wanna work with:\n");
    printf("\n1. File menu\n");
    printf("2. Record menu\n");
    printf("\n0. Exit\n"
           "\x1B[0m");
}
void printfFileMenu()
{
    printf("\x1B[1m"
           "\nFILE MENU\n");
    printf("\n1. Create file\n");
    printf("2. Read file\n");
    printf("3. Delete file\n");
    printf("\n0. Back to MAIN MENU\n");
    printf("-1. Exit\n"
           "\x1B[0m");
}
void printfRecordMenu()
{
    printf("\x1B[1m"
           "\nRECORD MENU\n");
    printf("\n1. Create record\n");
    printf("2. Read record\n");
    printf("3. Edit record\n");
    printf("4. Sort record\n");
    printf("5. Insert record into the file\n");
    printf("6. Delete record\n");
    printf("\n0. Back to MAIN MENU\n");
    printf("-1. Exit\n"
           "\x1B[0m");
}
void printfSoringMenuAttributes()
{
    printf("\x1B[1m"
           "\nSORTING MENU (attributes)\n");
    printf("Choose a specification by which the records will be sorted:\n");
    printf("\n1. Brand\n");
    printf("2. Model\n");
    printf("3. Max speed\n");
    printf("4. Engine capacity\n");
    printf("5. Price\n");
    printf("\n0. Exit menu\n");
    printf("-1. Exit program\n"
           "\x1B[0m");
}
void printfSortingMenuOrders()
{
    printf("\x1B[1m"
           "\nSORTING MENU (orders)\n");
    printf("Choose an order by which the records will be sorted:\n");
    printf("\n1. Ascending\n");
    printf("2. Descending\n");
    printf("\n0. Exit menu\n");
    printf(
        "-1. Exit program\n"
        "\x1B[0m");
}