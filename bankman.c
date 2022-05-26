//Strucutre
//h-fil som kan anänvadas för båda filerna  
// Program för banktjänstemän där man kan log in först 
//Skapa konto (här behövs information från kunden fyllas i )
//Sätta in pengar på konto 
//Ta ut pengar från konto
//Skapa kund
//Göra överföring mellan konto
//Lägga upp framtida betalning
#include <stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#define MAX_ACCOUNTS 50

struct BankclearkAccounts{
    char username[20];
    int pincode;
};

int currentLoggedInBankclearkAccount = 0;
struct BankclearkAccounts Bankclearkaccounts[MAX_ACCOUNTS];

int main(){
    char username[20];
    int pincode;

    printf("Log in, enter username:\n");
    scanf("%s",username);

    printf("Please enter your PIN-code to complete log in:\n");
    scanf("%d", pincode);
    int foundBankclearkAccount = -1;
    for (int i =0; i<50;i++){
        if (strcmp(username,Bankclearkaccounts[i].username)==0 && pincode == Bankclearkaccounts[i].pincode){
            printf("\nLogin Succeful!Welcome\n");
             foundBankclearkAccount = i;
             currentLoggedInBankclearkAccount = i;
             break;
        }
    }
        else (foundBankclearkAccount==-1){
             printf("\nWrong creditentials entered!\nTry again\n");
             break; 
         }
     

    
                        
                        