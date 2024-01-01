#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main() {
    double a = 0, b = 0, c = 0;
    char again[3];
    printf("Enter the sides of the triangle (accuracy to 6 decimal places)\n");
    do {
        int inputValid = 0;
        while(!inputValid) {
            printf("Enter the length of the first side (0.01 < a < 9999): (then press Enter)\n");
            if (scanf("%.6lf", &a) != 1 || getchar() != '\n' || a < 0.01 || a > 9999) {
                printf("Please enter a number between 0.01 and 9999.\n");
                while (getchar() != '\n'); // Очистить буфер ввода
            } else if (a <= 0) {
                printf("Sorry, but the side of the triangle must be greater than 0.\n");
            } else {
                inputValid = 1;
            }
        }

        inputValid = 0;
        while(!inputValid) {
            printf("Enter the length of the second side (0.01 < b < 9999): (then press Enter)\n");
            if (scanf("%.6lf", &b) != 1 || getchar() != '\n' || b < 0.01 || b > 9999) {
                printf("Please enter a number between 0.01 and 9999.\n");
                while (getchar() != '\n'); // Очистить буфер ввода
            } else if (b <= 0) {
                printf("Sorry, but the side of the triangle must be greater than 0.\n");
            } else {
                inputValid = 1;
            }
        }

        inputValid = 0;
        while(!inputValid) {
            printf("Enter the length of the third side (0.01 < c < 9999): (then press Enter)\n");
            if (scanf("%.6lf", &c) != 1 || getchar() != '\n' || c < 0.01 || c > 9999) {
                printf("Please enter a number between 0.01 and 9999.\n");
                while (getchar() != '\n'); // Очистить буфер ввода
            } else if (c <= 0) {
                printf("Sorry, but the side of the triangle must be greater than 0.\n");
            } else {
                inputValid = 1;
            }
        }

        if (a + b <= c || a + c <= b || b + c <= a) {
            printf("This triangle does not exist.\n");
            return 1;
        }
        double P = a + b + c;
        double p = (a + b + c) / 2;
        double S = sqrt(p * (p - a) * (p - b) * (p - c));

        double ha = (2 * sqrt(p * (p - a) * (p - b) * (p - c))) / a;
        double hb = (2 * sqrt(p * (p - a) * (p - b) * (p - c))) / b;
        double hc = (2 * sqrt(p * (p - a) * (p - b) * (p - c))) / c;

        double ma = 0.5 * sqrt(2 * b * b + 2 * c * c - a * a);
        double mb = 0.5 * sqrt(2 * a * a + 2 * c * c - b * b);
        double mc = 0.5 * sqrt(2 * a * a + 2 * b * b - c * c);

        double la = 2 * sqrt(b * c * p * (p - a)) / (b + c);
        double lb = 2 * sqrt(a * c * p * (p - b)) / (a + c);
        double lc = 2 * sqrt(a * b * p * (p - c)) / (a + b);

        printf("Perimeter: %.6lf\n", P);
        printf("Area: %.6lf\n", S);
        printf("Length of altitude to side a: %.6lf;\t Length of altitude to side b: %.6lf;\t Length of altitude to side c: %.6lf;\n", ha, hb, hc);
        printf("Length of median to side a: %.6lf;\t     Length of median to side b: %.6lf;\t     Length of bisector to side c: %.6lf;\n", ma, mb, mc);
        printf("Length of bisector to side a: %.6lf;\t Length of bisector to side b: %.6lf;\t Length of bisector to side c: %.6lf;\n", la, lb, lc);

        printf("Completed successfully!\n");

        do {
            printf("Do you want to continue? (Enter yes or no). If 'no' - close the program.\n");
            scanf("%s", again);
            for (int i = 0; again[i]; i++) {
                again[i] = tolower(again[i]);
            }
        } while(strcmp(again, "yes") != 0 && strcmp(again, "no") != 0);
    } while (strcmp(again, "yes") == 0);

    printf("Exiting the program...\n");
    return 0;
}
