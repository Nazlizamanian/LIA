//Nazli Zamanian Gustavsson Assignment: "Bank managment programme" 2021-05-12
//File: bank2.c
//Summary: A bank managment programme.
//Version: 1.1
// Owner: Nazli Zamanian Gustavsson
// ----------------------------
// Log: 2021-03-02 Created the file.
//BankclearkMENY efter log in 
#define  _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#define MAX_ACCOUNTS 100

struct Account {
    char username[50];
    int password;
    int social_security_number;
    int currentBalance;
};

/**
struct FuturePayments {
    char fromAccount[50];
    char toAccount[50];
    int balance;
}; 
**/

// currentLoggedInAccount = The Logged in account position
int currentLoggedInAccount = 0; 
int usedAccounts = 0;
struct Account account[MAX_ACCOUNTS];

// Declarations
void create_new_account();
void firstpage();
void membership();
void write_to_accounts();
void schedulepayment(int fromAccount, int toAccount, int amount);
void namelogin();

void namelogin(char* username){
    
    printf("\n                                                             Current Logged in as: %s\n", username);
}
 
void write_to_accounts() {
    FILE *fp;
    fp = fopen ("accounts.txt", "w+");
    for(int i = 0; i < usedAccounts; i++) {
        fprintf(fp,"%s,%d,%d,%d\n",account[i].username,account[i].password,account[i].social_security_number, account[i].currentBalance); // printing to file
    }
    fflush(fp); /* <== here */
}

void schedulepayment(int fromAccount, int toAccount, int amount) {
    // account[fromAccount] -> account[toAccount]
    // account[fromAccount].username, account[toAccount].username, amount

    FILE *fp;
    fp = fopen ("scheduled_payments.txt", "a");
    fprintf(fp,"%s,%s,%d\n",account[fromAccount].username,account[toAccount].username,amount); // printing to file
    fflush(fp); /* <== here */

}

void membership(){
    char username[50]; //List of definded variables. 
    int amount;
    int foundAccount = -1;
    char user_identification[50];  //datatyp,name,max amount of charachters.
    int password;
    int social_security_number;
    int deposit;
    int withdraw;
    int choice;

    do {
        printf("Welcome to the Bank\n");
        printf("Please select what you would like to do today\n");
        printf("n1. Create new customer account\n");
        printf("n2. Transfer money between bank accounts\n");
        printf("n3. Schedule future payments\n");
        printf("n4. Deposit money\n");
        printf("n5. Withdraw money\n");
        printf("n6. Log out\n");
        scanf("%d",&choice);
 
        namelogin(account[currentLoggedInAccount].username);
        switch (choice)
        {
            case 1: //create new customer account
        
            printf("Please enter new log information \n");
            scanf("%s",&user_identification); //Customer enter his/hers log in information. 

            printf("Please enter your 4-digit password pincode\n"); //Customer enter his/hers 4 digit pincode password.
            scanf("%d",&password); //scans

            printf("Please enter you social security number\n");
            scanf("%d",&social_security_number);

            // Lägga till nytt konto, så att man inte kan skriva samma uppgifter.
            strcpy(account[usedAccounts].username, user_identification);
            account[usedAccounts].password = password;
            account[usedAccounts].social_security_number = social_security_number;
            account[usedAccounts].currentBalance = 100;
                
            printf("New account created with the following values:\n");
            printf("Username: %s\n", account[usedAccounts].username);
            printf("social_security_number: %d\n", account[usedAccounts].social_security_number);
            printf("currentBalance: %d\n", account[usedAccounts].currentBalance);

            usedAccounts++;
            write_to_accounts();
            break;

            case 2:
            
            printf("To whom do you want to transfer money?\n");
            scanf("%s",&username);
            printf("Please enter the amount\n");
            scanf("%d",&amount);

            foundAccount = -1;
                for (int i=0;i<MAX_ACCOUNTS;i++){
                    if (strcmp(username,account[i].username)==0){
                        foundAccount = i;
                        break;
                    }
                }

                if(foundAccount != -1 && account[currentLoggedInAccount].currentBalance > amount) {
                    // Vi har hittat ett konto och vi vet att vi har tillräckligt med pengar.
                    // Vi utför överföringen nu.

                    account[currentLoggedInAccount].currentBalance = account[currentLoggedInAccount].currentBalance - amount;
                    account[foundAccount].currentBalance = account[foundAccount].currentBalance + amount;
                    printf("Money has been successfully transferred from %s to %s", account[currentLoggedInAccount].username, account[foundAccount].username);
                    write_to_accounts();
                }
                // else Skriv att det inte gick att överföra pengarna.
                else {
                    printf("Money could not be transferred\n");
                }
            break;

            case 3: 
                printf("To whom do you want to transfer money?\n");
                scanf("%s",&username);
                printf("Please enter the amount\n");
                scanf("%d",&amount);

                foundAccount = -1;
                for (int i=0;i<MAX_ACCOUNTS;i++){
                    if (strcmp(username,account[i].username)==0){
                        foundAccount = i;
                        break;
                    }
                }

                if(foundAccount != -1 && account[currentLoggedInAccount].currentBalance > amount) {
                    // Vi har hittat ett konto och vi vet att vi har tillräckligt med pengar.
                    // Vi utför överföringen senare.
                   
                   // account[currentLoggedInAccount].currentBalance = account[currentLoggedInAccount].currentBalance - amount;
                   // account[foundAccount].currentBalance = account[foundAccount].currentBalance + amount;

                    schedulepayment(currentLoggedInAccount, foundAccount, amount);
                    printf("Money has been  b to be transferred from %s to %s", account[currentLoggedInAccount].username, account[foundAccount].username);
                }
                // Else could not transfer amount that is greater than the current balance.
                else {
                    printf("ERROR! Money could not be transferred\n");

                }

            break;

            case 4: //deposit money
            
            printf("Enter the customers account name that you would like to deposit to\n");
            scanf("%s",&username);
            printf("Please enter how much you would like to deposit to your account?\n"); 
            scanf("%d",&deposit); 
            (foundAccount != -1 && account[currentLoggedInAccount].currentBalance + deposit);
            write_to_accounts();
            printf("Money could succefully be transferred!\n");
            printf("Your new total balance is:%d\n");
            membership();
            break;
           
            case 5: //withdraw money
           
            printf("Enter the customers account name that you would like to withdraw from\n");
            scanf("%s",&username);
            printf("Please enter how much you would like to withdraw from your account?\n"); 
            scanf("%d",&withdraw);
                // Checks that the account balance is greater than the amount that is going to be withdrawn.
             if(foundAccount != -1 && account[currentLoggedInAccount].currentBalance > withdraw){

                 account[currentLoggedInAccount].currentBalance = account[currentLoggedInAccount].currentBalance - amount;
                    account[foundAccount].currentBalance = account[foundAccount].currentBalance + amount;
                    printf("Money has been successfully withdrawn from %s\n", account[currentLoggedInAccount].username, account[foundAccount].username);
                    write_to_accounts();
             }
             else printf("The amount that was given could not be withdrawn from the specific account\n"); //If the amount that wants to be withdran is greater than the balance it will not go through.
            break;
        
            case 6: 
                printf("Signing out..\n");
                firstpage();
            break;
        }
    }
    while(choice!=7); //Exits programme.

}

void firstpage(){
    char user_identification[50]; //Defintion of the variables. 
    int password;
    int social_security_number; //datatyp,namn,maxantal
    int choice;

    while(1) {
        printf("Login\n"); 
        printf("\nPlease enter log in information \n");
        scanf("%s",&user_identification); //Bankstaff enter his/hers log in information. 
        printf("Please enter your 4-digit password pincode\n"); //Bankstaff enter his/hers 4 digit pincode password.
        scanf("%d",&password); //scans
                
        int foundAccount = -1; // foundAccount defines which position the logged in account is found at.
            for (int i=0;i<100;i++){
                    if (strcmp(user_identification,account[i].username)==0 && password == account[i].password){
                        printf("Log in succeful!\n"); 
                        foundAccount = i;
                        currentLoggedInAccount = i;
                        break;
                    }
                }
                // If account is not found the foundAccount should be still at -1
                if( foundAccount == -1 ) {
                    printf("Login unsuccessful!");
                }
                else {
                    membership();
                }

            break;

        }

    }
    //If wrong info is entered, retry. 


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

    fclose(filePointer);
    firstpage();
}

void create_new_account()//Case 1 creates new account. 
{ 
    printf("Creating new account,please fill out the information\n");

}

