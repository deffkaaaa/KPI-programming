#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.c"

typedef struct
{
    int id;
    char brand[MAX_CAR_NAME];
    char model[MAX_CAR_NAME];
    int speed;
    double engine;
    double price;
} CarRecord;

typedef struct
{
    int sortAttributeChoice;
    int sortOrderChoice;
} SortContext;

enum mainMenu
{
    fileMenu = 1,
    recordMenu = 2,
    exitWholeProgram = 0
};
enum sortingMenuAttributes
{
    carBrand = 1,
    carModel = 2,
    maxSpeed = 3,
    engineCapacity = 4,
    carPrice = 5,
    exitMenu = 0,
    exitProgram = -1
};

enum sortingMenuOrder
{
    ascendingSort = 1,
    descendingSort = 2,
};

void createFile();
void readFile();
void deleteFile();
void addRecord(int *maxID);
void readRecord();
void editRecord();
void swapRecords(CarRecord *record1, CarRecord *record2);
int bubbleSort(CarRecord records[], int numRecords, int sortAttributeChoice, int sortOrderChoice, int *maxID);
void readRecordsFromFile(CarRecord records[], int *numRecords);
void displayRecords(CarRecord records[], int numRecords);
void sortRecords();
void insertRecord(int *maxID);
void deleteRecord();
void displayMainMenu(int *mainMenuChoice);
void fileMenuOption(int *fileMenuChoice);
void recordMenuOption(int *recordMenuChoice);

int lastRecordID = 0;
int maxID = 0;

int main()
{
    int mainMenuChoice = 0, fileMenuChoice = 0, recordMenuChoice = 0;

    do
    {
        clearScreen();
        displayMainMenu(&mainMenuChoice);

        switch (mainMenuChoice)
        {
        case fileMenu:
            clearScreen();
            fileMenuOption(&fileMenuChoice);
            break;

        case recordMenu:
            clearScreen();
            recordMenuOption(&recordMenuChoice);
            break;

        case exitWholeProgram:
            clearScreen();
            printf("\nExiting program...\n");
            printf("\nSee you soon! Bye!\n");

            break;
        default:
            printf("\x1b[31m"
                   "Ohh, it seems that there`s an error occured. You`ve entered a number that is not specified as an option.\n"
                   "\x1b[0m");
            break;
        }
    } while (mainMenuChoice != exitWholeProgram);
    return 0;
}
void displayMainMenu(int *mainMenuChoice)
{
    printfMainMenu();

    *mainMenuChoice = isValidChoice(*mainMenuChoice, MIN_CHOICE, MAX_CHOICE_MAIN_MENU);
}
void fileMenuOption(int *fileMenuChoice)
{
    enum fileMenu
    {
        create = 1,
        read = 2,
        delete = 3,
        exitMenu = 0,
        exitProgram = -1
    };

    do
    {
        printfFileMenu();

        *fileMenuChoice = isValidChoice(*fileMenuChoice, MIN_CHOICE, MAX_CHOICE_FILE_MENU);

        switch (*fileMenuChoice)
        {
        case create:
            clearScreen();
            createFile();
            break;
        case read:
            clearScreen();
            readFile();
            break;

        case delete:
            clearScreen();
            deleteFile();
            break;

        case exitMenu:
            clearScreen();
            printf("\x1b[90m"
                   "Returning to MAIN MENU...\n"
                   "\x1b[0m");
            break;

        case exitProgram:
            clearScreen();
            printf("\x1b[90m"
                   "\nExiting program...\n"
                   "\x1b[0m");
            printf("\x1b[32m"
                   "\nSee you soon! Bye!\n"
                   "\x1b[0m");
            exit(0);
            break;

        default:
            printf("\x1b[31m"
                   "Ohh, it seems that there`s an error occured. You`ve entered a number that is not specified as an option.\n"
                   "\x1b[0m");
            break;
        }

    } while (*fileMenuChoice != 0);
}
void recordMenuOption(int *recordMenuChoice)
{
    enum recordMenu
    {
        create = 1,
        read = 2,
        edit = 3,
        sort = 4,
        insert = 5,
        delete = 6,
        exitMenu = 0,
        exitProgram = -1
    };
    CarRecord newRecord;
    do
    {
        printfRecordMenu();

        *recordMenuChoice = isValidChoice(*recordMenuChoice, MIN_CHOICE, MAX_CHOICE_RECORD_MENU);

        switch (*recordMenuChoice)
        {
        case create:
            clearScreen();
            addRecord(&lastRecordID);
            break;
        case read:
            clearScreen();
            readRecord();
            break;

        case edit:
            clearScreen();
            editRecord();
            break;

        case sort:
            clearScreen();
            sortRecords();
            break;

        case insert:
            clearScreen();
            insertRecord(&lastRecordID);
            break;

        case delete:
            clearScreen();
            deleteRecord();
            break;

        case exitMenu:
            clearScreen();
            printf("\x1b[90m"
                   "Returning to MAIN MENU...\n"
                   "\x1b[0m");
            break;

        case exitProgram:
            clearScreen();
            printf("\x1b[90m"
                   "\nExiting program...\n"
                   "\x1b[0m");
            printf("\x1b[32m"
                   "\nSee you soon! Bye!\n"
                   "\x1b[0m");
            exit(0);
            break;

        default:
            printf("\x1b[31m"
                   "Ohh, it seems that there`s an error occured. You`ve entered a number that is not specified as an option.\n"
                   "\x1b[0m");
            break;
        }
    } while (*recordMenuChoice != 0);
}
void createFile()
{
    if (access(FILE_NAME, F_OK) != -1)
    {
        printf("\x1b[31m"
               "\nError: The file %s already exists. Please choose another operation.\n"
               "\x1b[0m",
               FILE_NAME);
        printf("\x1b[1m"
               "\nPress Enter to return to FILE MENU\n"
               "\x1b[0m");
        fflush(stdin);
        getchar();
        clearScreen();
        return;
    }

    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL)
    {
        printf("\x1b[31m"
               "\nAn error occurred while creating the file.\n"
               "\x1b[0m");
    }

    lastRecordID = getLastRecordID(file, &maxID);

    printf("\x1b[1m"
           "\nDo you want to enter car information now?\n"
           "\x1b[0m");
    printf("\x1b[90m"
           "If you want to create a record now - press Enter. In case you want to exit the menu - press any other key + Enter.\n"
           "\x1b[0m");
    if (getchar() == '\n')
    {

        CarRecord newRecord;
        newRecord.id = 0;

        fprintf(file, "ID: %d\n", newRecord.id);

        isValidString("the brand of the car", newRecord.brand, MAX_CAR_NAME);
        fprintf(file, "Brand: %s\n", newRecord.brand);

        isValidString("the model of the car", newRecord.model, MAX_CAR_NAME);
        fprintf(file, "Model: %s\n", newRecord.model);

        newRecord.speed = isValidInt("the maximum speed of the car", MIN_CAR_SPEED, MAX_CAR_SPEED);
        fprintf(file, "Maximum speed: %d\n", newRecord.speed);

        newRecord.engine = isValidDouble("the engine capacity of the car", MIN_ENGINE_CAPACITY, MAX_ENGINE_CAPACITY, DECIMAL_PLACES);
        fprintf(file, "Engine capacity: %g\n", newRecord.engine);

        newRecord.price = isValidDouble("the price of the car", MIN_CAR_PRICE, MAX_CAR_PRICE, DECIMAL_PLACES);
        fprintf(file, "Price: %g\n", newRecord.price);

        clearScreen();
        printf("\x1b[32m"
               "Car information was added to %s successfully!\n"
               "\x1b[0m",
               FILE_NAME);
    }
    else
    {
        printf("\x1b[90m"
               "File %s was created without any information.\n"
               "\x1b[0m",
               FILE_NAME);
        fflush(stdin);
    }

    fclose(file);
}
void readFile()
{
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        printf("\x1b[31m"
               "An error occurred while opening the file. The file is empty\n"
               "\x1b[0m");
        return;
    }

    printf("\x1b[1m"
           "\nCAR SPECIFICATIONS\n"
           "\x1b[0m");

    char line[MAX_FILE_CONTENT];
    if (fgets(line, sizeof(line), file) == NULL)
    {
        printf("\x1b[90m"
               "The file is empty.\n"
               "\x1b[0m");
    }
    else
    {
        do
        {
            if (strstr(line, "ID:") == line)
            {
                printf("\n%s", line);
            }
            else
            {
                printf("%s", line);
            }
        } while (fgets(line, sizeof(line), file) != NULL);
    }

    fclose(file);
    printf("\x1b[1m"
           "\nPress Enter to return to FILE MENU\n"
           "\x1b[0m");
    fflush(stdin);
    getchar();
    fflush(stdin);
    clearScreen();
}
void deleteFile()
{
    if (remove(FILE_NAME) == 0)
    {
        printf("\x1b[32m"
               "File %s deleted successfully!\n"
               "\x1b[0m",
               FILE_NAME);
    }
    else
    {
        printf("\x1b[31m"
               "\nAn error occurred while deleting the file %s. Maybe you haven't created the file yet.\n"
               "\x1b[0m",
               FILE_NAME);
    }
    printf("\x1b[1m"
           "\nPress Enter to return to FILE MENU\n"
           "\x1b[0m");
    fflush(stdin);
    getchar();
    fflush(stdin);
    clearScreen();
}
void addRecord(int *maxID)
{
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL)
    {
        printf("\x1b[31m"
               "\nAn error occurred while opening the file.\n"
               "\x1b[0m");
        return;
    }

    CarRecord newRecord;
    int numRecords;
    CarRecord records[MAX_FILE_CONTENT];

    readRecordsFromFile(records, &numRecords);

    *maxID = 0;
    for (int i = 0; i < numRecords; i++)
    {
        if (records[i].id > *maxID)
        {
            *maxID = records[i].id;
        }
    }

    printf("\x1b[1m"
           "\nADDING A NEW RECORD\n"
           "\x1b[0m");
    int newID = *maxID + 1;

    newRecord.id = newID;
    fprintf(file, "ID: %d\n", newRecord.id);

    isValidString("the brand of the car", newRecord.brand, MAX_CAR_NAME);
    fprintf(file, "Brand: %s\n", newRecord.brand);

    isValidString("the model of the car", newRecord.model, MAX_CAR_NAME);
    fprintf(file, "Model: %s\n", newRecord.model);

    newRecord.speed = isValidInt("the maximum speed of the car", MIN_CAR_SPEED, MAX_CAR_SPEED);
    fprintf(file, "Maximum speed: %d\n", newRecord.speed);

    newRecord.engine = isValidDouble("the engine capacity of the car", MIN_ENGINE_CAPACITY, MAX_ENGINE_CAPACITY, DECIMAL_PLACES);
    fprintf(file, "Engine capacity: %g\n", newRecord.engine);

    newRecord.price = isValidDouble("the price of the car", MIN_CAR_PRICE, MAX_CAR_PRICE, DECIMAL_PLACES);
    fprintf(file, "Price: %g\n", newRecord.price);

    *maxID = newRecord.id;

    fclose(file);
    printf("\x1b[32m"
           "Record added to %s successfully!\n"
           "\x1b[0m",
           FILE_NAME);
    printf("\x1b[1m"
           "\nPress Enter to return to RECORD MENU\n"
           "\x1b[0m");
    fflush(stdin);
    getchar();
    fflush(stdin);
    clearScreen();
}

void readRecord()
{
    FILE *file = fopen(FILE_NAME, "r");

    if (file == NULL)
    {
        printf("\x1b[31m"
               "\nAn error occurred while opening the file.\n"
               "\x1b[0m");
        return;
    }

    printf("\x1b[1m"
           "\nREADING RECORD\n"
           "\x1b[0m");

    char line[MAX_FILE_CONTENT];
    const char *markers[] = {"Brand:", "Model:", "Maximum speed:", "Engine capacity:", "Price:"};
    int found = 0;
    int targetID = isValidInt("Enter the ID of the record you want to read", MIN_ID, MAX_ID);

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, "ID:") != NULL)
        {
            int id;
            sscanf(line, "ID: %d", &id);

            if (id == targetID)
            {
                found = 1;
                printf("\nRecord with ID %d found:\n", targetID);

                for (int i = 0; i < sizeof(markers) / sizeof(markers[0]); i++)
                {
                    fgets(line, sizeof(line), file);
                    printf("%s %s", markers[i], line + strlen(markers[i]));
                }

                break;
            }
        }
    }

    if (!found)
    {
        printf("\x1b[31m"
               "Error: No information found for the given ID.\n"
               "\x1b[0m");
    }

    fclose(file);
    printf("\x1b[1m"
           "\nPress Enter to return to RECORD MENU\n"
           "\x1b[0m");
    fflush(stdin);
    getchar();
    fflush(stdin);
    clearScreen();
}
void editRecord()
{
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        printf("\x1b[31m"
               "\nAn error occurred while opening the file.\n"
               "\x1b[0m");
        return;
    }

    printf("\x1b[90m"
           "\nEDITING A RECORD\n"
           "\x1b[0m");

    char line[MAX_FILE_CONTENT];
    int found = 0;
    int targetID = isValidInt("Enter the ID of the record you want to edit", MIN_ID, MAX_ID);

    CarRecord currentRecord;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, "ID:") != NULL)
        {
            sscanf(line, "ID: %d", &currentRecord.id);

            if (currentRecord.id == targetID)
            {
                found = 1;
                printf("\x1b[1m"
                       "\nEDITING RECORD WITH ID %d\n"
                       "\x1b[0m",
                       targetID);

                isValidString("Enter the new brand of the car", currentRecord.brand, MAX_CAR_NAME);
                isValidString("Enter the new model of the car", currentRecord.model, MAX_CAR_NAME);
                currentRecord.speed = isValidInt("Enter the new maximum speed of the car", MIN_CAR_SPEED, MAX_CAR_SPEED);
                currentRecord.engine = isValidDouble("Enter the new engine capacity of the car", MIN_ENGINE_CAPACITY, MAX_ENGINE_CAPACITY, DECIMAL_PLACES);
                currentRecord.price = isValidDouble("Enter the new price of the car", MIN_CAR_PRICE, MAX_CAR_PRICE, DECIMAL_PLACES);

                fprintf(tempFile, "ID: %d\n", currentRecord.id);
                fprintf(tempFile, "Brand: %s\n", currentRecord.brand);
                fprintf(tempFile, "Model: %s\n", currentRecord.model);
                fprintf(tempFile, "Maximum speed: %d\n", currentRecord.speed);
                fprintf(tempFile, "Engine capacity: %g\n", currentRecord.engine);
                fprintf(tempFile, "Price: %g\n", currentRecord.price);

                // Consume the rest of the line
                while (fgets(line, sizeof(line), file) != NULL && strcmp(line, "\n") != 0)
                    ;
            }
            else
            {
                fprintf(tempFile, "%s", line);
            }
        }
        else
        {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (remove(FILE_NAME) == 0)
    {
        if (rename("temp.txt", FILE_NAME) == 0 && found)
        {
            printf("\x1b[32m"
                   "\nRecord edited successfully!\n"
                   "\x1b[0m");
        }
        else
        {
            printf("\x1b[31m"
                   "\nError: No information found for the given ID.\n"
                   "\x1b[0m");
        }
    }
    else
    {
        printf("\x1b[31m"
               "\nAn error occurred while deleting the original file.\n"
               "\x1b[0m");
    }

    printf("\x1b[90m"
           "\nPress Enter to return to RECORD MENU\n"
           "\x1b[0m");
    fflush(stdin);
    getchar();
    fflush(stdin);
    clearScreen();
}
void deleteRecord()
{
    FILE *file = fopen(FILE_NAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        printf("\x1b[31m"
               "\nAn error occurred while opening the file.\n"
               "\x1b[0m");
        return;
    }

    printf("\x1b[1m"
           "\nDELETING A RECORD\n"
           "\x1b[0m");

    char line[MAX_FILE_CONTENT];
    int found = 0;
    int targetID = isValidInt("Enter the ID of the record you want to delete: ", MIN_ID, MAX_ID);

    CarRecord currentRecord;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, "ID:") != NULL)
        {
            sscanf(line, "ID: %d", &currentRecord.id);

            if (currentRecord.id == targetID)
            {
                found = 1;
                printf("\x1b[1m"
                       "\nDELETING RECORD WITH ID %d\n"
                       "\x1b[0m",
                       targetID);

                while (fgets(line, sizeof(line), file) != NULL && strcmp(line, "\n") != 0)
                    ;

                while (fgets(line, sizeof(line), file) != NULL && strcmp(line, "\n") != 0)
                    ;

                continue;
            }
        }
        fprintf(tempFile, "%s", line);
    }
    if (!found)
    {
        printf("\x1b[31m"
               "\nError: No record found with ID %d.\n"
               "\x1b[0m",
               targetID);
    }

    fclose(file);
    fclose(tempFile);
    if (remove(FILE_NAME) == 0)
    {
        if (rename("temp.txt", FILE_NAME) == 0 && found)
        {
            printf("\x1b[32m"
                   "\nRecord deleted successfully!\n"
                   "\x1b[0m");
        }
        else
        {
            printf("\x1b[31m"
                   "\nAn error occurred while renaming the temporary file.\n"
                   "\x1b[0m");
        }
    }
    else
    {
        printf("\x1b[31m"
               "\nAn error occurred while deleting the original file.\n"
               "\x1b[0m");
    }

    printf("\x1b[1m"
           "\nPress Enter to return to RECORD MENU\n"
           "\x1b[0m");
    fflush(stdin);
    getchar();
    fflush(stdin);
    clearScreen();
}
void swapRecords(CarRecord *record1, CarRecord *record2)
{
    CarRecord temp = *record1;
    *record1 = *record2;
    *record2 = temp;
}

int bubbleSort(CarRecord records[], int numRecords, int sortAttributeChoice, int sortOrderChoice, int *maxID)
{

    for (int i = 0; i < numRecords - 1; i++)
    {
        for (int j = 0; j < numRecords - i - 1; j++)
        {
            int comparisonResult;

            switch (sortAttributeChoice)
            {
            case carBrand:
                comparisonResult = strcmp(records[j].brand, records[j + 1].brand);
                break;
            case carModel:
                comparisonResult = strcmp(records[j].model, records[j + 1].model);
                break;
            case maxSpeed:
                comparisonResult = records[j].speed - records[j + 1].speed;
                break;
            case engineCapacity:
                comparisonResult = (records[j].engine > records[j + 1].engine) - (records[j].engine < records[j + 1].engine);
                break;
            case carPrice:
                comparisonResult = (records[j].price > records[j + 1].price) - (records[j].price < records[j + 1].price);
                break;
            default:
                printf("Invalid sorting attribute.\n");
                return -1; // Indicate error
            }

            if (sortOrderChoice == descendingSort)
            {
                comparisonResult = -comparisonResult;
            }
            if (comparisonResult > 0)
            {
                swapRecords(&records[j], &records[j + 1]);
            }
        }
        if (records[i].id > *maxID)
        {
            *maxID = records[i].id;
        }
    }

    return *maxID;
}

void readRecordsFromFile(CarRecord records[], int *numRecords)
{
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL)
    {
        printf("\x1b[31m"
               "\nAn error occurred while opening the file.\n"
               "\x1b[0m");
        return;
    }

    *numRecords = 0;

    while (fscanf(file, "ID: %d", &records[*numRecords].id) == 1)
    {
        while (fgetc(file) != '\n')
            ;

        fscanf(file, "%*[^:]: %[^\n]", records[*numRecords].brand);
        fscanf(file, "%*[^:]: %[^\n]", records[*numRecords].model);
        fscanf(file, "%*[^:]:%d", &records[*numRecords].speed);
        fscanf(file, "%*[^:]:%lf", &records[*numRecords].engine);
        fscanf(file, "%*[^:]:%lf", &records[*numRecords].price);

        // Consume the rest of the line
        while (fgetc(file) != '\n')
            ;

        (*numRecords)++;
    }

    fclose(file);
}
void displayRecords(CarRecord records[], int numRecords)
{
    printf("\x1b[1m"
           "\nYOUR RECORDS\n"
           "\x1b[0m");

    for (int i = 0; i < numRecords; i++)
    {
        printf("ID: %d\n", records[i].id);
        printf("Brand: %s\n", records[i].brand);
        printf("Model: %s\n", records[i].model);
        printf("Maximum speed: %d\n", records[i].speed);
        printf("Engine capacity: %g\n", records[i].engine);
        printf("Price: %g\n", records[i].price);
        printf("\n");
    }
    printf("\x1b[1m"
           "\nPress Enter to return to FILE MENU\n"
           "\x1b[0m");
    fflush(stdin);
    getchar();
    fflush(stdin);
    clearScreen();
}
void sortRecords()
{
    int sortAttributeChoice = 0;
    int sortOrderChoice = 0;

    CarRecord records[MAX_FILE_CONTENT];
    int numRecords = 0;
    readRecordsFromFile(records, &numRecords);

    printfSoringMenuAttributes();

    sortAttributeChoice = isValidChoice(sortAttributeChoice, MIN_CHOICE, MAX_CHOICE_ATTRIBUTES_SORTING_MENU);
    clearScreen();

    switch (sortAttributeChoice)
    {
    case carBrand:
    case carModel:
    case maxSpeed:
    case engineCapacity:
    case carPrice:

        printfSortingMenuOrders();

        sortOrderChoice = isValidChoice(sortOrderChoice, MIN_CHOICE, MAX_CHOICE_ORDERS_SORTING_MENU);

        switch (sortOrderChoice)
        {
        case ascendingSort:
        case descendingSort:
            clearScreen();
            maxID = bubbleSort(records, numRecords, sortAttributeChoice, sortOrderChoice, &maxID);

            FILE *file = fopen(FILE_NAME, "w");
            if (file == NULL)
            {
                printf("\x1b[31m"
                       "\nAn error occurred while opening the file for reading and writing.\n"
                       "\x1b[0m");
            }

            for (int i = 0; i < numRecords; i++)
            {
                fprintf(file, "ID: %d\n", records[i].id);
                fprintf(file, "Brand: %s\n", records[i].brand);
                fprintf(file, "Model: %s\n", records[i].model);
                fprintf(file, "Maximum speed: %d\n", records[i].speed);
                fprintf(file, "Engine capacity: %g\n", records[i].engine);
                fprintf(file, "Price: %g\n", records[i].price);
            }

            fclose(file);

            displayRecords(records, numRecords);
            lastRecordID = records[numRecords - 1].id;
            break;
        case exitMenu:
            clearScreen();
            printf("\x1b[90m"
                   "Returning to RECORD MENU...\n"
                   "\x1b[0m");
            break;

        case exitProgram:
            clearScreen();
            printf("\x1b[90m"
                   "\nExiting program...\n"
                   "\x1b[0m");
            printf("\x1b[32m"
                   "\nSee you soon! Bye!\n"
                   "\x1b[0m");
            exit(0);
            break;

        default:
            printf("\x1b[31m"
                   "Ohh, it seems that there`s an error occured. You`ve entered a number that is not specified as an option.\n"
                   "\x1b[0m");
            break;
        }

        break;
    case exitMenu:
        clearScreen();
        printf("\x1b[90m"
               "Returning to RECORD MENU...\n"
               "\x1b[0m");
        break;

    case exitProgram:
        clearScreen();
        printf("\x1b[90m"
               "\nExiting program...\n"
               "\x1b[0m");
        printf("\x1b[32m"
               "\nSee you soon! Bye!\n"
               "\x1b[0m");
        exit(0);
        break;

    default:
        printf("\x1b[31m"
               "Ohh, it seems that there`s an error occured. You`ve entered a number that is not specified as an option.\n"
               "\x1b[0m");
        break;
    }
}
void insertRecord(int *maxID)
{
    FILE *file = fopen(FILE_NAME, "r+");
    if (file == NULL)
    {
        printf("\x1b[31m"
               "\nAn error occurred while opening the file.\n"
               "\x1b[0m");
        return;
    }

    int numRecords;
    CarRecord records[MAX_FILE_CONTENT];

    readRecordsFromFile(records, &numRecords);

    *maxID = 0;
    for (int i = 0; i < numRecords; i++)
    {
        if (records[i].id > *maxID)
        {
            *maxID = records[i].id;
        }
    }

    CarRecord newRecord;

    printf("\x1b[1m"
           "\nADDING A NEW RECORD\n"
           "\x1b[0m");

    int newID = *maxID + 1;

    newRecord.id = newID;
    fprintf(file, "ID: %d\n", newRecord.id);

    isValidString("the brand of the car", newRecord.brand, MAX_CAR_NAME);
    fprintf(file, "Brand: %s\n", newRecord.brand);

    isValidString("the model of the car", newRecord.model, MAX_CAR_NAME);
    fprintf(file, "Model: %s\n", newRecord.model);

    newRecord.speed = isValidInt("the maximum speed of the car", MIN_CAR_SPEED, MAX_CAR_SPEED);
    fprintf(file, "Maximum speed: %d\n", newRecord.speed);

    newRecord.engine = isValidDouble("the engine capacity of the car", MIN_ENGINE_CAPACITY, MAX_ENGINE_CAPACITY, DECIMAL_PLACES);
    fprintf(file, "Engine capacity: %g\n", newRecord.engine);

    newRecord.price = isValidDouble("the price of the car", MIN_CAR_PRICE, MAX_CAR_PRICE, DECIMAL_PLACES);
    fprintf(file, "Price: %g\n", newRecord.price);

    fclose(file);

    records[numRecords] = newRecord;
    numRecords++;

    bubbleSort(records, numRecords, carBrand, ascendingSort, maxID);

    file = fopen(FILE_NAME, "w");
    if (file == NULL)
    {
        printf("\x1b[31m"
               "\nAn error occurred while opening the file for writing.\n"
               "\x1b[0m");
        return;
    }
    for (int i = 0; i < numRecords; i++)
    {
        fprintf(file, "ID: %d\n", records[i].id);
        fprintf(file, "Brand: %s\n", records[i].brand);
        fprintf(file, "Model: %s\n", records[i].model);
        fprintf(file, "Maximum speed: %d\n", records[i].speed);
        fprintf(file, "Engine capacity: %g\n", records[i].engine);
        fprintf(file, "Price: %g\n", records[i].price);
    }
    fclose(file);

    *maxID = newID;
    clearScreen();
    printf("\x1b[32m"
           "Record inserted into %s successfully!\n"
           "\x1b[0m",
           FILE_NAME);
    displayRecords(records, numRecords);
    printf("\x1b[1m"
           "\nPress Enter to return to RECORD MENU\n"
           "\x1b[0m");
    fflush(stdin);
    getchar();
    fflush(stdin);
    clearScreen();
}