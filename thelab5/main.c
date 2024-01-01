#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define n_str 25
#define str_size 25

char list[n_str][str_size], again[2];
char *addr[n_str];

void arrayBubbleSort (char *addr[], int n);
int isValidNumStr (int n);
int isValidNumChar (int charsPerLine);
void isValidInput (int n, int charsPerLine);
void arrayPrint(char *addr[], int n, const char *message);
void generateRandomStrings (int n, int charsPerLine);

enum MenuOption {
    MANUAL_INPUT = 1,
    RANDOM_ARRAY = 2
};

int main() {
    printf("===STRING SORTER===\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------\n");
    printf("DISCLAIMER: The program doesn`t read spaces and doesn`t consider them as a string character. Please, enter strings without spaces.\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------\n");

    int n, charsPerLine, choice;
    printf("Choose an option:\n");
    printf("1. Enter the array manually\n");
    printf("2. Generate a random array\n");
    scanf("%d", &choice);
    do {
        switch (choice) {
            case MANUAL_INPUT:
                n = isValidNumStr(n);
                charsPerLine = isValidNumChar(charsPerLine);
                isValidInput(n, charsPerLine);
                arrayPrint(addr, n, "Unsorted strings:");
                arrayBubbleSort(addr, n);
                arrayPrint(addr, n, "Your sorted strings:");
                break;
            case RANDOM_ARRAY:
                n = isValidNumStr(n);
                charsPerLine = isValidNumChar(charsPerLine);
                generateRandomStrings(n, charsPerLine);
                arrayPrint(addr, n, "Unsorted random array:");
                arrayBubbleSort(addr, n);
                arrayPrint(addr, n, "Your sorted strings:");
                break;
            default:
                printf("Invalid choice. Please, press 1 or 2.\n");
        }
        printf("\nCompleted successfully!\n");
        printf("Press Enter to continue or any other not system key + Enter to exit.\n");
        fgets(again, sizeof(again), stdin);
        fflush(stdin);
    } while (again[0] == '\n');
    return 0;
}
void arrayBubbleSort (char *addr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(addr[j], addr[j + 1]) > 0) {
                char *tempPlace = addr[j];
                addr[j] = addr[j + 1];
                addr[j + 1] = tempPlace;
            }
        }
    }
}
int isValidNumStr (int n) {
    int inputValid = 0;
    while (!inputValid) {
        printf("Enter the number of the strings from 2 to 25:\n");
        if (scanf("%d", &n) != 1 || getchar() != '\n') {
            printf("Invalid input. Please enter the number of strings you want to sort.\n");
            fflush(stdin);
            continue;
        } else if (n < 2 || n > n_str) {
            printf("It seems you`ve entered an invalid value. Enter the number between 2 and 25 inclusively.\n");
            continue;
        } else {
            inputValid = 1;
        }
    }
    return n;
}
int isValidNumChar (int charsPerLine) {
    int inputValid = 0;
    while (!inputValid) {
        printf("Enter the number of characters per line:\n");
        if (scanf("%d", &charsPerLine) != 1 || getchar() != '\n') {
            printf("Invalid input. Please enter the number of characters in the line you want to sort.\n");
            fflush(stdin);
            continue;
        } else if (charsPerLine < 1 || charsPerLine > str_size) {
            printf("Sorry, but you`ve entered too big or too little value. Enter the number between 1 and 25");
            continue;
        } else {
            inputValid = 1;
        }
    }
    return charsPerLine;
}
void isValidInput (int n, int charsPerLine) {
    for (int i = 0; i < n; i++) {
        int inputValid = 0;
        while (!inputValid) {
            printf("String %d: ", i + 1);
            if (scanf("%s", list[i]) != 1 || strcspn(list[i], "0123456789") != strlen(list[i])) {
                printf("Invalid input. Please enter a string without numbers.\n");
                fflush(stdin);
                continue;
            } else if (strlen(list[i]) > charsPerLine) {
                printf("String length exceeds the specified limit. Enter a shorter string:\n");
                continue;
            } else {
                inputValid = 1;
            }
            fflush(stdin);
        }
        addr[i] = list[i];

    }
}
void arrayPrint (char *addr[], int n, const char *message) {
    printf("%s\n", message);
    for (int i = 0; i < n; i++) {
        printf("|   %s   |\n", addr[i]);
    }
    fflush(stdin);
}
void generateRandomStrings(int n, int charsPerLine) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < charsPerLine; j++) {
            int isUppercase = rand() % 2;
            if (isUppercase) {
                list[i][j] = 'A' + rand() % 26;
            } else {
                list[i][j] = 'a' + rand() % 26;
            }
        }
        list[i][charsPerLine] = '\0';
        addr[i] = list[i];
    }
}