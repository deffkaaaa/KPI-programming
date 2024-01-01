#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define minValue (-1e6)
#define maxValue 1e6

int main() {
    double x = 0, y = 1, delta = 1, final_epsilon = 0;
    int k = 0, epsilon = 0;
    char again [2];

    printf("===ROOT CALCULATOR===\n");

    do {
        int inputValid = 0;
        while(!inputValid) {
            printf("Enter the power of the root (only integer numbers from -100 to 100 without 0):\n");
            if(scanf("%d", &k) != 1 || getchar() != '\n' || k < -100 || k > 100) {
                printf("Invalid value. Please enter a whole number from -100 to 100.\n");
                fflush(stdin);
                continue;
            } else if (k == 0) {
                printf("The root power cannot be equal to 0.\n");
                fflush(stdin);
                continue;
            } else if (k % 2 == 0 && k > 0 && x >= 0) {
                inputValid = 0;
                while(!inputValid) {
                    printf("Enter the number from which you want to extract the root (from 0 to 1e6):\n");
                    if (scanf("%lf", &x) != 1 || getchar() != '\n' || x < 0 || x > maxValue) {
                        printf("Sorry, you`ve entered an invalid value. Enter a number from 0 to 1e6.\n");
                        fflush(stdin);
                        continue;
                    } else if (floor(x * 1000000.) != x * 1000000.) {
                        printf("Oops, there are too many digits after comma. Please enter a number up to 6 decimal places only.\n");
                        fflush(stdin);
                        continue;
                    } else {
                        inputValid = 1;
                    }
                }
            } else if (k % 2 != 0 && k > 0 && x <= 1e10 || x >= -1e10) {
                inputValid = 0;
                while (!inputValid) {
                    printf("Enter the number from which you want to extract the root (from -1e6 to 1e6):\n");
                    if(scanf("%lf", &x) != 1 || getchar() != '\n' || x < minValue|| x > maxValue) {
                        printf("Invalid input. Enter a number from -1e6 to 1e6.\n");
                        fflush(stdin);
                        continue;
                    } else if (floor(x * 1000000.) != x * 1000000.) {
                        printf("Oops, there are too many digits after comma. Please enter a number up to 6 decimal places only.\n");
                        fflush(stdin);
                        continue;
                    } else {
                        inputValid = 1;
                    }
                }
            } else if (k % 2 == 0 && k < 0 && x > 0) {
                inputValid = 0;
                while (!inputValid) {
                    printf("Enter the number from which you want to extract the root (from 0 (not included) to 1e6):\n");
                    if (scanf("%lf", &x) != 1 || getchar() != '\n' || x < 0 || x > maxValue) {
                        printf("Error. Please reenter a value from 0 to 1e6.\n");
                        fflush(stdin);
                        continue;
                    } else if (x == 0) {
                        printf("Sorry, but 0 is not an acceptable value.\n");
                        fflush(stdin);
                        continue;
                    } else if (floor(x * 1000000.) != x * 1000000.) {
                        printf("Oops, there are too many digits after comma. Please enter a number up to 6 decimal places only.\n");
                        fflush(stdin);
                        continue;
                    } else {
                        inputValid = 1;
                    }
                }
            } else if (k % 2 != 0 && k < 0 && x != 0) {
                inputValid = 0;
                while (!inputValid) {
                    printf("Enter the number from which you want to extract the root (from -1e6 to 1e6 (0 is not included)):\n");
                    if (scanf("%lf", &x) != 1 || getchar() != '\n' || x < minValue || x > maxValue) {
                        printf("It seems you`ve entered an invalid number. Please, try again.\n");
                        fflush(stdin);
                        continue;
                    } else if (x == 0) {
                        printf("Zero is not included in the scope of this root.\n");
                        fflush(stdin);
                        continue;
                    } else if (floor(x * 1000000.) != x * 1000000.) {
                        printf("Oops, there are too many digits after comma. Please enter a number up to 6 decimal places only.\n");
                        fflush(stdin);
                        continue;
                    } else {
                        inputValid = 1;
                    }
                }
            } else {
                inputValid = 1;
            }
        }
        inputValid = 0;
        while(!inputValid) {
            printf("Enter the number of decimal places (from 1 to 6):\n");
            if(scanf("%d", &epsilon) != 1 || getchar() != '\n' || epsilon < 1 || epsilon > 6) {
                printf("Invalid input. Enter a whole number from 1 to 6.\n");
                fflush(stdin);
                continue;
            } else {
                inputValid = 1;
            }
        }
        final_epsilon = pow(10, -epsilon);
        do {
            delta = (x / pow(y, abs(k)-1.) - y) / abs(k);
            y += delta;
        } while (fabs(delta) > final_epsilon);
        printf("y = %.*lf", epsilon, (k > 0) ? y: 1. / y);
        printf("\nCompleted successfully!\n");
        printf("Press Enter to continue or any other not system key + Enter to exit.\n");
        fgets(again, 2, stdin);
        fflush(stdin);
    } while (again[0] == '\n');
    return 0;
}