#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(double *xp, double *yp);
void arrayBubbleSort(double array[], int n);
void randomArrayGenerator(double array[], int n);
int isValidQuantity (int n);
void isValidElements (double manualArray[], int n);
void arrayPrint (double array[], int n, const char *message);

int main() {
    int n = 0, choice = 0;
    char again[2];
    double *manualArray = NULL;
    double *randomArray = NULL;

    printf("===NUMBER SORTER===\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("DISCLAIMER: The program reads numbers with precision to 5 decimal places. It may output equal values if you enter too much zeros after point.\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");

    do {
        fflush(stdin);
        printf("Choose an option:\n");
        printf("1. Generate a random array\n");
        printf("2. Enter the array manually\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                n = isValidQuantity (n);
                randomArray = (double *) malloc(n * sizeof (double));
                if (randomArray == NULL) {
                    printf("Memory allocation failed. Exiting...\n");
                    return 1;
                }
                randomArrayGenerator(randomArray, n);
                arrayPrint(randomArray, n, "Unsorted array:");
                arrayBubbleSort(randomArray, n);
                arrayPrint(randomArray, n, "Your sorted array:");
                break;
            case 2:
                n = isValidQuantity(n);
                manualArray = (double *) malloc(n * sizeof (double));
                if (manualArray == NULL) {
                    printf("Memory allocation failed. Exiting...\n");
                    return 1;
                }
                isValidElements(manualArray, n);
                arrayPrint(manualArray, n, "Unsorted array:");
                arrayBubbleSort(manualArray, n);
                arrayPrint(manualArray, n, "Your sorted array:");
                break;
            default:
                printf("Invalid choice. Please, press 1 or 2.\n");
        }
        printf("\nCompleted successfully!\n");
        printf("Press Enter to continue or any other not system key + Enter to exit.\n");
        fgets(again, sizeof(again), stdin);
        fflush(stdin);
    } while (again[0] == '\n');
    free(randomArray);
    free(manualArray);
    return 0;
}
void swap (double *xp, double *yp) {
    double tempPlace = *xp;
    *xp = *yp;
    *yp = tempPlace;
}
void arrayBubbleSort(double array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}
void randomArrayGenerator(double array[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int randVal = rand() % 6;
        if (randVal == 0) {
            array[i] = rand() % 10001 - 5000;
        } else if (randVal == 1) {
            array[i] = -5000. + ((double)rand() / RAND_MAX) * 10000.;
        } else if (randVal == 2) {
            array[i] = -500. + ((double)rand() / RAND_MAX) * 1000.;
        } else if (randVal == 3) {
            array[i] = -100. + ((double)rand() / RAND_MAX) * 200.;
        } else if (randVal == 4) {
            array[i] = -0.5 + ((double)rand() / RAND_MAX) * 1.;
        } else {
            array[i] = -0.005 + ((double)rand() / RAND_MAX) * 0.01;
        }
    }
}
int isValidQuantity (int n) {
    int inputValid = 0;
    while (!inputValid) {
        printf("Enter the number of elements in the array to be sorted in ascending order:\n");
        if (scanf("%d", &n) != 1 || getchar() != '\n') {
            printf("Invalid input. Please, enter a whole number.\n");
            fflush(stdin);
            continue;
        } else if (n < 0 || n == 0) {
            printf("Quantity of numbers cannot be less than zero or equal to zero. Enter a positive number.\n");
            fflush(stdin);
            continue;
        } else {
            inputValid = 1;
        }
    }
    return n;
}
void isValidElements (double manualArray[], int n) {
    int inputValid = 0;
    while (!inputValid) {
        printf("Enter the elements of the array up to 5 decimal places:\n");
        for (int i = 0; i < n; i++) {
            if (scanf("%lf", &manualArray[i]) != 1 || getchar() != '\n') {
                printf("Invalid input. Please, enter a number.\n");
                fflush(stdin);
                i--;
                continue;
            } else if ((int) (manualArray[i] * 100000.) != manualArray[i] * 100000.) {
                printf("Please enter a valid number with accuracy to 5 decimal places.\n");
                fflush(stdin);
                i--;
                continue;
            } else {
                inputValid = 1;
            }
        }
    }
}
void arrayPrint (double array[], int n, const char *message) {
    printf("\n%s\n", message);
    for (int i = 0; i < n; i++) {
        printf("|  %g  |", array[i]);
    }
}