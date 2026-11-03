/*
 * ATM Simulation - C Programming Project
 * Default PIN: 1
 *
 * Features:
 * - PIN authentication (3 attempts)
 * - Balance enquiry
 * - Cash withdrawal and deposit
 * - Mini statement (last 5 successful transactions)
 * - Automatic logout after 5 successful transactions
 */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PIN 1
#define MAX_ATTEMPTS 3
#define MAX_TRANSACTIONS 5

int main(void) {
    const int pin = DEFAULT_PIN;
    int entered_pin;
    float balance = 12500.00f;
    int attempts = MAX_ATTEMPTS;
    int choice;
    int run_atm = 1;
    int total_transactions = 0;
    float history[MAX_TRANSACTIONS] = {0.0f};

    printf("===== WELCOME TO THE TERMINAL ATM =====\n");

    /* PIN authentication */
    while (attempts > 0) {
        printf("Enter PIN: ");

        if (scanf("%d", &entered_pin) != 1) {
            printf("Invalid input. Please enter a numeric PIN.\n");
            return EXIT_FAILURE;
        }

        if (entered_pin == pin) {
            printf("\nAccess Granted!\n");
            break;
        }

        attempts--;
        printf("Wrong PIN. Attempts remaining: %d\n\n", attempts);

        if (attempts == 0) {
            printf("Card blocked! Too many incorrect attempts.\n");
            return EXIT_SUCCESS;
        }
    }

    /* ATM dashboard */
    while (run_atm) {
        printf("\n===================================\n");
        printf("Current Balance:\tINR %.2f\n", balance);
        printf("-----------------------------------\n");
        printf("1. Check Balance\n");
        printf("2. Withdraw Cash\n");
        printf("3. Deposit Cash\n");
        printf("4. Print Mini-Statement (History)\n");
        printf("5. Exit\n");
        printf("===================================\n");
        printf("Enter Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please restart and enter numeric choices.\n");
            return EXIT_FAILURE;
        }

        switch (choice) {
            case 1:
                printf("\n[BALANCE CHECK]\n");
                printf("Available Balance:\tINR %.2f\n", balance);
                break;

            case 2: {
                float amount;

                if (total_transactions >= MAX_TRANSACTIONS) {
                    printf("Transaction limit reached.\n");
                    run_atm = 0;
                    break;
                }

                printf("\nEnter withdrawal amount: INR ");
                if (scanf("%f", &amount) != 1) {
                    printf("Invalid amount. Please restart the program.\n");
                    return EXIT_FAILURE;
                }

                if (amount <= 0.0f || amount > balance) {
                    printf("ERROR: Invalid amount or insufficient funds!\n");
                } else {
                    balance -= amount;
                    history[total_transactions] = -amount;
                    total_transactions++;
                    printf("Success! Cash withdrawn: INR %.2f\n", amount);
                }
                break;
            }

            case 3: {
                float amount;

                if (total_transactions >= MAX_TRANSACTIONS) {
                    printf("Transaction limit reached.\n");
                    run_atm = 0;
                    break;
                }

                printf("\nEnter deposit amount: INR ");
                if (scanf("%f", &amount) != 1) {
                    printf("Invalid amount. Please restart the program.\n");
                    return EXIT_FAILURE;
                }

                if (amount <= 0.0f) {
                    printf("ERROR: Invalid deposit amount!\n");
                } else {
                    balance += amount;
                    history[total_transactions] = amount;
                    total_transactions++;
                    printf("Success! Cash deposited: INR %.2f\n", amount);
                }
                break;
            }

            case 4:
                printf("\n--- MINI STATEMENT ---\n");
                if (total_transactions == 0) {
                    printf("No transactions made yet.\n");
                } else {
                    for (int i = 0; i < total_transactions; i++) {
                        if (history[i] < 0.0f) {
                            printf("Txn %d:\tWithdrew\tINR %.2f\n",
                                   i + 1, -history[i]);
                        } else {
                            printf("Txn %d:\tDeposited\tINR %.2f\n",
                                   i + 1, history[i]);
                        }
                    }
                }
                break;

            case 5:
                printf("\nThank you for visiting! Goodbye.\n");
                run_atm = 0;
                break;

            default:
                printf("ERROR: Please choose a valid menu item (1-5).\n");
                break;
        }

        if (total_transactions >= MAX_TRANSACTIONS && run_atm) {
            printf("\nTransaction limit (5) reached for this session. Safe logout.\n");
            run_atm = 0;
        }
    }

    return EXIT_SUCCESS;
}
