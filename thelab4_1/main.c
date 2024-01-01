#include <stdio.h>
#include <math.h>
#define MIN_ANGLE (-360)
#define MAX_ANGLE 360
#define MIN_PRECISION 1
#define MAX_PRECISION 6

double isValidScope (char *name);
double isValidStep (double dx);
int isValidPrecision (int epsilon);

double delta = 1., final_epsilon = 0, x = 0, x1 = 0, x2 = 0, dx = 0, radx = 0, cosx_taylor = 1., cosx_tab = 0, difference = 0;
int epsilon = 0;
char again[2];

int main() {
    printf("===COSINE CALCULATOR===\n");
    printf("--------------------------------------------------------------------------\n");
    printf("DISCLAIMER: The program can round cosine values if precision 1 is entered.\n");
    printf("--------------------------------------------------------------------------\n");
    do {
        x1 = isValidScope("first");
        x2 = isValidScope("last");
        dx = isValidStep(dx);
        epsilon = isValidPrecision(epsilon);

        printf("| %-10s |%20s |%20s |%30s |\n", "x", "cosx(Library)", "cosx(Taylor)", "cosx(Library) - cosx(Taylor)");
        printf("------------------------------------------------------------------------------------------\n");
        x = x1;
        do {
            radx = (x*M_PI)/180.;
            int n = 1;
            delta = 1.;
            cosx_taylor = 1.;
            cosx_tab = cos(radx);
            final_epsilon = pow(10, -epsilon);

            do {
                delta = delta * (-1. * pow(radx,2)/(2. * n * (2. * n - 1)));
                n = n + 1;
                cosx_taylor += delta;
            } while(fabs(delta) > final_epsilon);

            difference = fabs(cosx_tab - cosx_taylor) ;
            printf("| %-10.6lf |%20.*lf |%20.*lf |%30g |\n", x, epsilon, cosx_tab, epsilon, cosx_taylor, difference);
            x += dx;
        } while ((x1 < x2 && x <= x2) || (x1 > x2 && x >= x2));
        printf("\nCompleted successfully!\n");
        printf("Press Enter to continue or any other not system key + Enter to exit.\n");
        fgets(again, sizeof(again), stdin);
        fflush(stdin);
    } while (again[0] == '\n');
    return 0;
}
double isValidScope (char *name) {
    double num = 0;
    int inputValid = 0;
    while (!inputValid) {
        printf("Enter the %s value of the calculated cosine from -360 to 360 up to 6 decimal places:\n", name);
        if (scanf("%lf", &num) != 1 || getchar() != '\n' || num < MIN_ANGLE || num > MAX_ANGLE) {
            printf("It seems you`ve entered an invalid value. Please enter a number between -360 and 360 inclusively.\n");
            fflush(stdin);
            continue;
        } else if ((int) (num * 1000000) != num * 1000000) {
            printf("Entered value is out of range of allowed decimal places. Please enter a number with accuracy to 6 decimal places.\n");
            fflush(stdin);
            continue;
        } else {
            inputValid = 1;
        }
    }
    return num;
}
double isValidStep (double dx) {
    int inputValid = 0;
    while (!inputValid) {
        printf("Enter the change step between the first and the last step of the calculated cosine (from 0 to the value of the last calculated cosine):\n");
        if (scanf("%lf", &dx) != 1 || getchar() != '\n' || fabs(dx) < 0 || fabs(dx) > fabs(x2)) {
            printf("It seems you`ve entered an invalid value of change step. Please enter a number between 0 and the positive value of the last calculated cosine.\n");
            fflush(stdin);
            continue;
        } else if (dx == 0 || dx < 0) {
            printf("Sorry but change step cannot be equal to 0 or less than 0.\n");
            fflush(stdin);
            continue;
        } else {
            inputValid = 1;
        }
    }
    return dx;
}
int isValidPrecision (int epsilon) {
    int inputValid = 0;
    while (!inputValid) {
        printf("Enter the number of digits after comma (from 1 to 6 decimal places):\n");
        if (scanf("%d", &epsilon) != 1 || getchar() != '\n' || epsilon < MIN_PRECISION || epsilon > MAX_PRECISION) {
            printf("Invalid input. Please enter an integer from 1 to 6.\n");
            fflush(stdin);
            continue;
        } else if (epsilon == 0) {
            printf("Sorry but precision cannot be equal to 0.\n");
            fflush(stdin);
            continue;
        } else {
            inputValid = 1;
        }
    }
    return epsilon;
}