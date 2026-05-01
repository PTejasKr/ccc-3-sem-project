#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <stdbool.h> // For boolean type
// ANSI Colors
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define BOLD "\033[1m"

#define MAX_USERS 3
#define MAX_NOTES 7
#define MAX_LOGIN_ATTEMPTS 3

typedef struct {
    int account_id;
    char name[50];
    int balance;
    int pin;
} Account;

Account accounts[MAX_USERS];
int logged_in_index = -1;
int algo_mode = 0;

int atm_notes[MAX_NOTES] = {10, 20, 50, 60, 100, 200, 500};

// Utility
void clear_buffer() {
    while (getchar() != '\n');
}

void pause() {
    printf("\nPress ENTER to continue...");
    getchar();
}

// Safe integer input
int get_int_input(const char *prompt) {
    int value;
    int result;
    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &value);
        clear_buffer(); // Always clear buffer after scanf

        if (result == 1) {
            return value;
        } else {
            printf(RED "Invalid input. Please enter a number.\n" RESET);
        }
    }
}

// Mask account ID
void print_masked_id(int id) {
    printf("XXXX%d", id % 100);
}

// Init
void init_accounts() {
    accounts[0] = (Account){1001, "Aarav Sharma", 15000, 1234};
    accounts[1] = (Account){1002, "Priya Patel", 8500, 2345};
    accounts[2] = (Account){1003, "Rohan Desai", 20000, 3456};
}

// Find account
int find_account(int id) {
    for (int i = 0; i < MAX_USERS; i++)
        if (accounts[i].account_id == id)
            return i;
    return -1;
}

// Header UI
void header() {
    system("clear || cls");
    printf(CYAN "=========================================\n" RESET);
    printf(BOLD "         ALGO BANK ATM SYSTEM\n" RESET);
    printf(CYAN "=========================================\n\n" RESET);
}

// Login
void login() {
    int attempts = 0;

    while (attempts < MAX_LOGIN_ATTEMPTS) {
        int id, pin;
        header();

        printf(YELLOW "[ LOGIN ]\n\n" RESET);
        id = get_int_input("Enter Account ID: ");
        pin = get_int_input("Enter PIN: ");
        
        int idx = find_account(id);

        if (idx != -1 && accounts[idx].pin == pin) {
            logged_in_index = idx;
            printf(GREEN "\nLogin Successful!\n" RESET);
            pause();
            return;
        }

        printf(RED "\nInvalid credentials.\n" RESET);
        attempts++;
        pause();
    }

    printf(RED "\nToo many failed attempts. Exiting...\n" RESET);
    exit(0);
}

// Greedy Dispenser
// Returns true if the exact amount can be dispensed, false otherwise.
bool greedy_dispense(int amount) {
    printf(GREEN "\n[ GREEDY DISPENSER ]\n" RESET);
    int temp_amount = amount;
    int dispensed_notes[MAX_NOTES] = {0}; // To store count of each note

    for (int i = MAX_NOTES - 1; i >= 0; i--) {
        while (temp_amount >= atm_notes[i]) {
            temp_amount -= atm_notes[i];
            dispensed_notes[i]++;
        }
    }

    if (temp_amount == 0) {
        // Successfully dispensed
        for (int i = MAX_NOTES - 1; i >= 0; i--) {
            for (int j = 0; j < dispensed_notes[i]; j++) {
                printf("₹%d ", atm_notes[i]);
            }
        }
        printf("\n");
        return true;
    } else {
        printf(RED "Cannot dispense exact amount using Greedy algorithm.\n" RESET);
        return false;
    }
}

// DP Dispenser
// Returns true if the exact amount can be dispensed, false otherwise.
bool dp_dispense(int amount) {
    printf(GREEN "\n[ DP DISPENSER ]\n" RESET);

    if (amount == 0) {
        printf("No amount to dispense.\n");
        return true;
    }

    // Use dynamic allocation to avoid stack overflow for large amounts
    int *dp_arr = (int *)malloc((amount + 1) * sizeof(int));
    int *parent_arr = (int *)malloc((amount + 1) * sizeof(int));

    if (dp_arr == NULL || parent_arr == NULL) {
        printf(RED "Memory allocation failed for DP algorithm.\n" RESET);
        free(dp_arr);
        free(parent_arr);
        return false;
    }

    for (int i = 1; i <= amount; i++) dp_arr[i] = INT_MAX;
    dp_arr[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < MAX_NOTES; j++) {
            if (atm_notes[j] <= i && dp_arr[i - atm_notes[j]] != INT_MAX && dp_arr[i - atm_notes[j]] + 1 < dp_arr[i]) {
                dp_arr[i] = dp_arr[i - atm_notes[j]] + 1;
                parent_arr[i] = atm_notes[j];
            }
        }
    }

    if (dp_arr[amount] == INT_MAX) {
        printf(RED "Cannot dispense exact amount using DP algorithm.\n" RESET);
        free(dp_arr);
        free(parent_arr);
        return false;
    }

    int current_amount = amount;
    while (current_amount > 0) {
        printf("₹%d ", parent_arr[current_amount]);
        current_amount -= parent_arr[current_amount];
    }
    printf("\n");

    free(dp_arr);
    free(parent_arr);
    return true;
}

// Dashboard
void dashboard() {
    int choice;

    while (logged_in_index != -1) {
        header();

        Account *user = &accounts[logged_in_index];

        printf(BLUE "Welcome, %s\n" RESET, user->name);
        printf("Account: ");
        print_masked_id(user->account_id);
        printf("\n\n");

        printf(BOLD "1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Toggle Algorithm (%s)\n",
               algo_mode ? "DP" : "Greedy");
        printf("5. Logout\n\n" RESET);

        printf("Select: ");
        choice = get_int_input("");

        int amt;

        switch (choice) {
            case 1:
                printf(GREEN "\nBalance: ₹%d\n" RESET, user->balance);
                pause();
                break;

            case 2:
                amt = get_int_input("Enter amount: ");
                if (amt <= 0) {
                    printf(RED "Amount must be positive.\n" RESET);
                    pause();
                    break;
                }
                if (amt > 0) {
                    user->balance += amt;
                    printf(GREEN "Deposited.\n" RESET);
                }
                pause();
                break;

            case 3:
                amt = get_int_input("Enter amount: ");

                if (amt <= 0) {
                    printf(RED "Amount must be positive.\n" RESET);
                    pause();
                    break;
                }

                if (amt > user->balance) {
                    printf(RED "Insufficient funds.\n" RESET);
                } else {
                    bool dispensed_successfully = false;
                    if (algo_mode == 0) {
                        dispensed_successfully = greedy_dispense(amt);
                    } else {
                        dispensed_successfully = dp_dispense(amt);
                    }

                    if (dispensed_successfully) {
                        user->balance -= amt;
                        printf(GREEN "Amount dispensed successfully.\n" RESET);
                    } else {
                        // Balance is not reduced if dispensing failed
                        printf(RED "Withdrawal failed. Balance not reduced.\n" RESET);
                    }
                }
                pause();
                break;

            case 4:
                algo_mode = !algo_mode;
                break;

            case 5:
                logged_in_index = -1;
                break;
        }
    }
}

// Main
int main() {
    init_accounts();

    while (1) {
        login();
        dashboard();
    }
}