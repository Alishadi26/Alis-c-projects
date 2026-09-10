#include <stdio.h>
#include <stdlib.h>

#define MAX_TRANSACTIONS 50

int main() {
    int choice;
    double balance = 1000.00; // Initial starting balance
    double amount;
    
    // Arrays to store mini-statement transaction history
    double transaction_amounts[MAX_TRANSACTIONS];
    char transaction_types[MAX_TRANSACTIONS]; // 'D' for Deposit, 'W' for Withdrawal
    int transaction_count = 0;

    printf("=========================================\n");
    printf("        WELCOME TO THE C BANK SYSTEM     \n");
    printf("=========================================\n");

    do {
        printf("\n------------- MAIN MENU -------------\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Transaction History (Mini-Statement)\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("\n>>> Current Available Balance: $%.2f\n", balance);
                break;

            case 2:
                printf("\nEnter amount to deposit: $");
                if (scanf("%lf", &amount) != 1 || amount <= 0) {
                    printf("[Error] Invalid deposit amount.\n");
                    while (getchar() != '\n');
                    break;
                }

                balance += amount;
                if (transaction_count < MAX_TRANSACTIONS) {
                    transaction_amounts[transaction_count] = amount;
                    transaction_types[transaction_count] = 'D';
                    transaction_count++;
                }

                printf(">>> Successfully deposited $%.2f\n", amount);
                printf(">>> Updated Balance: $%.2f\n", balance);
                break;

            case 3:
                printf("\nEnter amount to withdraw: $");
                if (scanf("%lf", &amount) != 1 || amount <= 0) {
                    printf("[Error] Invalid withdrawal amount.\n");
                    while (getchar() != '\n');
                    break;
                }

                if (amount > balance) {
                    printf("[Declined] Insufficient funds! Current balance: $%.2f\n", balance);
                } else {
                    balance -= amount;
                    if (transaction_count < MAX_TRANSACTIONS) {
                        transaction_amounts[transaction_count] = amount;
                        transaction_types[transaction_count] = 'W';
                        transaction_count++;
                    }
                    printf(">>> Successfully withdrew $%.2f\n", amount);
                    printf(">>> Remaining Balance: $%.2f\n", balance);
                }
                break;

            case 4:
                printf("\n------- RECENT TRANSACTIONS -------\n");
                if (transaction_count == 0) {
                    printf("No transactions recorded yet.\n");
                } else {
                    for (int i = 0; i < transaction_count; i++) {
                        if (transaction_types[i] == 'D') {
                            printf("%d. [DEPOSIT]    + $%.2f\n", i + 1, transaction_amounts[i]);
                        } else {
                            printf("%d. [WITHDRAW]   - $%.2f\n", i + 1, transaction_amounts[i]);
                        }
                    }
                }
                printf("------------------------------------\n");
                break;

            case 5:
                printf("\nThank you for banking with us. Have a great day!\n");
                break;

            default:
                printf("\n[Error] Invalid option. Please select between 1 and 5.\n");
                break;
        }

    } while (choice != 5);

    return 0;
}