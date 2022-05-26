#define  _GNU_SOURCE
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#define PARSE_INTERVAL 86400
#define MAX_ACCOUNTS 100

struct Account {
    char username[50];
    int password;
    int social_security_number;
    int currentBalance;
};
struct FuturePayments {
    char fromAccount[50];
    char toAccount[50];
    int balance;
}; 

struct FuturePayments futurePayments[MAX_ACCOUNTS];
int amountOfPayments = 0;

struct Account account[MAX_ACCOUNTS];
int usedAccounts = 0;

void write_to_accounts() {
    FILE *fp;
    fp = fopen ("accounts.txt", "w+");
    for(int i = 0; i < usedAccounts; i++) {
        fprintf(fp,"%s,%d,%d,%d\n",account[i].username,account[i].password,account[i].social_security_number, account[i].currentBalance); // printing to file
    }
    fflush(fp); /* <== here */
}



// DO NOT USE RIGHT NOW.
void schedulepayment(int fromAccount, int toAccount, int amount) {
    // account[fromAccount] -> account[toAccount]
    // account[fromAccount].username, account[toAccount].username, amount

    FILE *fp;
    fp = fopen ("scheduled_payments.txt", "w");

    fflush(fp); /* <== here */

}

int main() {
    // Read current stored accounts
    FILE* filePointer;
    const int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen("accounts.txt", "ab+");

    int currentIndex = 0;
    while(fgets(buffer, bufferLength, filePointer)) {
  
        char * token = strtok(buffer, ",");

         if( token != NULL ) {
            strcpy(account[currentIndex].username, token);
            token = strtok(NULL, ",");
            account[currentIndex].password = atoi(token);
            token = strtok(NULL, ",");
            account[currentIndex].social_security_number = atoi(token);
            token = strtok(NULL, ",");
            account[currentIndex].currentBalance = atoi(token);
        }
        currentIndex++;

    }
    usedAccounts = currentIndex;

    // 2. Read all future payments
    
    char bufferPayments[bufferLength];
    

    filePointer = fopen("scheduled_payments.txt", "ab+");

    currentIndex = 0;
    while(fgets(bufferPayments, bufferLength, filePointer)) {
  
        char * token = strtok(bufferPayments, ",");

         if( token != NULL ) {
            strcpy(futurePayments[currentIndex].fromAccount, token);
            token = strtok(NULL, ",");
            strcpy(futurePayments[currentIndex].toAccount, token);
            token = strtok(NULL, ",");
            
            futurePayments[currentIndex].balance = atoi(token);
        }
        currentIndex++;

    }
    amountOfPayments = currentIndex;
    // 3. Process all payments
    for(int i = 0; i < amountOfPayments; i++){

        int fromAccountIndex = -1;
        int toAccountIndex = -1;
        for(int j = 0; j < usedAccounts; j++) {
            if(strcmp(account[j].username, futurePayments[i].fromAccount) == 0) {
                fromAccountIndex = j;
            }
            
            if(strcmp(account[j].username, futurePayments[i].toAccount) == 0) {
                toAccountIndex = j;
            }
        }

        if(fromAccountIndex != -1 && toAccountIndex != -1 && account[fromAccountIndex].currentBalance > futurePayments[i].balance) {
            // Perform the transfer of money
            
            account[fromAccountIndex].currentBalance = account[fromAccountIndex].currentBalance - futurePayments[i].balance  ;
            account[toAccountIndex].currentBalance = account[toAccountIndex].currentBalance + futurePayments[i].balance ;
            printf("Money has been successfully transferred from %s to %s", account[fromAccountIndex].username, account[toAccountIndex].username);
            write_to_accounts();
        }
       // futurePayments[i].fromAccount;
       // accounts[futurePayments[i].fromAccount].currentBalance 

    }
    // 4. For every interval, repeat.

    return 0;

}