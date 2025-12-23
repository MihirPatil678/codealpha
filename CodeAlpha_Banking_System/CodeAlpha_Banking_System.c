#include <stdio.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

void createAccount(FILE *file) {
    struct Account account;
    printf("Enter Account Number: ");
    scanf("%d", &account.accNo);
    printf("Enter Account Holder Name: ");
    scanf("%s", account.name);
    account.balance = 0.0;

    fseek(file, 0, SEEK_END);
    fwrite(&account, sizeof(struct Account), 1, file);
    printf("Account created successfully.\n");
}

void displayAccounts(FILE *file) {
    struct Account account;
    rewind(file);
    printf("\nAccNo\tName\tBalance\n");
    while (fread(&account, sizeof(struct Account), 1, file)) {
        printf("%d\t%s\t%.2f\n", account.accNo, account.name, account.balance);
    }
}

void depositMoney(FILE *file) {
    int accNo;
    float amount;
    struct Account account;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    rewind(file);
    FILE *tempFile = fopen("temp.dat", "wb+");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file)) {
        if (account.accNo == accNo) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            if (amount > 0) {
                account.balance += amount;
                printf("Deposited successfully. New balance: %.2f\n", account.balance);
            } else {
                printf("Invalid amount.\n");
            }
            found = 1;
        }
        fwrite(&account, sizeof(struct Account), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (!found) {
        printf("Account not found.\n");
    }
}

void withdrawMoney(FILE *file) {
    int accNo;
    float amount;
    struct Account account;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    rewind(file);
    FILE *tempFile = fopen("temp.dat", "wb+");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file)) {
        if (account.accNo == accNo) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount <= 0) {
                printf("Invalid amount.\n");
            } else if (amount > account.balance) {
                printf("Insufficient balance.\n");
            } else {
                account.balance -= amount;
                printf("Withdrawal successful. New balance: %.2f\n", account.balance);
            }
            found = 1;
        }
        fwrite(&account, sizeof(struct Account), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (!found) {
        printf("Account not found.\n");
    }
}

void balanceEnquiry(FILE *file) {
    int accNo;
    struct Account account;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    rewind(file);
    while (fread(&account, sizeof(struct Account), 1, file)) {
        if (account.accNo == accNo) {
            printf("Account Number: %d\nName: %s\nBalance: %.2f\n", account.accNo, account.name, account.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found.\n");
    }
}

void deleteAccount(FILE *file) {
    int accNo;
    struct Account account;
    int found = 0;

    printf("Enter Account Number to delete: ");
    scanf("%d", &accNo);

    rewind(file);
    FILE *tempFile = fopen("temp.dat", "wb+");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, file)) {
        if (account.accNo != accNo) {
            fwrite(&account, sizeof(struct Account), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (found) {
        printf("Account deleted.\n");
    } else {
        printf("Account not found.\n");
    }
}

int main() {
    FILE *file = fopen("accounts.dat", "rb+");
    if (file == NULL) {
        file = fopen("accounts.dat", "wb+");
        if (file == NULL) {
            printf("Error opening file.\n");
            return 1;
        }
    }

    int choice;
    while (1) {
        printf("\n1. Create Account\n2. Display Accounts\n3. Deposit Money\n4. Withdraw Money\n5. Balance Enquiry\n6. Delete Account\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            createAccount(file);
        } else if (choice == 2) {
            displayAccounts(file);
        } else if (choice == 3) {
            depositMoney(file);
        } else if (choice == 4) {
            withdrawMoney(file);
        } else if (choice == 5) {
            balanceEnquiry(file);
        } else if (choice == 6) {
            deleteAccount(file);
        } else if (choice == 7) {
            printf("Exiting system...\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    fclose(file);
    return 0;
}

