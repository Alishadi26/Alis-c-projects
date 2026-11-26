#include <stdio.h>

/* Exchange rates are constants, so they live in #defines.
   Update them here if the market moves. */
#define RATE_EURO_TO_EGP    55.0
#define RATE_DOLLAR_TO_EGP  47.5
#define RATE_EURO_TO_DOLLAR 1.16

/* Clears leftover characters after bad input so scanf doesn't loop forever. */
static void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

static int read_int(const char *prompt, int *out) {
    printf("%s", prompt);
    while (scanf("%d", out) != 1) {
        clear_input();
        printf("Please enter a whole number: ");
    }
    return *out;
}

static float read_float(const char *prompt) {
    float value;
    printf("%s", prompt);
    while (scanf("%f", &value) != 1) {
        clear_input();
        printf("Please enter a number: ");
    }
    return value;
}

static void currency_menu(void) {
    int subchoice;
    float amount;

    printf("\n-- Currency Conversion Menu --\n");
    printf("1. EGP to Euro\n");
    printf("2. EGP to Dollar\n");
    printf("3. Euro to Dollar\n");
    printf("4. Dollar to Euro\n");
    printf("5. Euro to EGP\n");
    printf("6. Dollar to EGP\n");
    read_int("Enter your choice: ", &subchoice);

    if (subchoice < 1 || subchoice > 6) {
        printf("Invalid choice\n");
        return;
    }

    amount = read_float("Enter the amount: ");
    while (amount < 0) {                      /* negative money makes no sense */
        amount = read_float("The amount can't be negative, try again: ");
    }

    switch (subchoice) {
        case 1: printf("Result: %.2f Euro\n",    amount / RATE_EURO_TO_EGP);    break;
        case 2: printf("Result: %.2f Dollars\n", amount / RATE_DOLLAR_TO_EGP);  break;
        case 3: printf("Result: %.2f Dollars\n", amount * RATE_EURO_TO_DOLLAR); break;
        case 4: printf("Result: %.2f Euro\n",    amount / RATE_EURO_TO_DOLLAR); break;
        case 5: printf("Result: %.2f EGP\n",     amount * RATE_EURO_TO_EGP);    break;
        case 6: printf("Result: %.2f EGP\n",     amount * RATE_DOLLAR_TO_EGP);  break;
    }
}

static void calculator_menu(void) {
    int subchoice;
    float num1, num2;

    printf("\n---- Calculator Menu ----\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    read_int("Enter your choice: ", &subchoice);

    if (subchoice < 1 || subchoice > 4) {
        printf("Invalid choice\n");
        return;
    }

    num1 = read_float("Enter the first number: ");
    num2 = read_float("Enter the second number: ");

    switch (subchoice) {
        case 1: printf("Result is %.2f\n", num1 + num2); break;
        case 2: printf("Result is %.2f\n", num1 - num2); break;
        case 3: printf("Result is %.2f\n", num1 * num2); break;
        case 4:
            if (num2 == 0) printf("Error: can't divide by zero\n");
            else           printf("Result is %.2f\n", num1 / num2);
            break;
    }
}

int main(void) {
    int choice;

    do {
        printf("\n-- Main Menu --\n");
        printf("1. Currency conversion\n");
        printf("2. Calculator\n");
        printf("3. Exit\n");
        read_int("Enter choice: ", &choice);

        switch (choice) {
            case 1: currency_menu();   break;
            case 2: calculator_menu(); break;
            case 3: printf("Goodbye!\n"); break;
            default: printf("Invalid choice\n");
        }
    } while (choice != 3);   /* option 3 ends the loop */

    return 0;
}
