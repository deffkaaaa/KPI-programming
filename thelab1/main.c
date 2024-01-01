#include <stdio.h>
#include <ncurses.h>          // Alternative library to conio.h
#include <string.h>          // For strcmp (checks if the again string contains either "yes" or "no")
#include <ctype.h>          // For tolower (lowercasing the input)

short roman (short,short,char);
int main() {
    short userInput;
    char again[3];          // For question "Do you want to continue?"

    do {
        printf("Enter a number (up to 3999):\n");
            for (;;) {
                if ((scanf("%hu", &userInput) != 1) || (getchar() != '\n')) {    //Returns int from the line
                    printf("Enter a whole number.\nPlease, try again:\n");
                    while (getchar() != '\n');       // To clear the buffer (until newline char)
                } else if ((userInput > 3999) || (userInput < 1)) {
                    printf("Oops! It seems you`ve entered a number that is out of range (1-3999).\nPlease, try again:\n");
                } else {
                    break;
                }
            }

        userInput = roman(userInput, 1000, 'M');
        userInput = roman(userInput, 500, 'D');
        userInput = roman(userInput, 100, 'C');
        userInput = roman(userInput, 50, 'L');
        userInput = roman(userInput, 10, 'X');
        userInput = roman(userInput, 5, 'V');
        userInput = roman(userInput, 1, 'I');
        getch();

        printf("\nCompleted successfully!");
        do {
            printf("Do you want to continue? (Enter yes or no). If 'no' - close the program.\n");
            scanf("%s", again);
            for (int i = 0; again[i]; i++) {
                again[i] = tolower(again[i]);
            }
        } while(strcmp(again, "yes") != 0 && strcmp(again, "no") != 0);
    } while (strcmp(again, "yes") == 0);       // Continues until "yes"
    printf("Accomplished!");
    return 0;
}
short roman(short i,short j,char c) {
    while (i >= j) {
        putchar(c);
        i -= j;
    }
    return (i);
}
