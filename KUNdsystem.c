//KUNdsystem Kund loggar in
//Kan skapa konto
//Kan göra överföring
//Kan lägga upp framtida betalning

#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
  

int main()
{
    char username[50]; //Defintion of the variables. 
    int password;

    printf("1.Login or 2. create new account\n"); 
    printf("Please enter log information \n");
    scanf("%s",&username); //Customer enter his/hers log in information. 

    printf("Please enter your 4-digit password pincode\n"); //Customer enter his/hers 4 digit pincode password.
    scanf("%d",&password); //scans

    if (strcmp(username,"name")==0 && password == 1234){
         printf("Log in succeful!\n"); 
    }//If the input is equal to the right, customer has loged in succefully.
     //Compares the info entered.If the right password is entered, log in succefully. 
   //Goes to next part 
    else{
     printf("Log in unsucceful!Wrong credentials\n");
    }
    //If wrong info is entered, retry. 

    return 0;
}
