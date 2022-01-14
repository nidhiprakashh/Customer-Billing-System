#include<stdlib.h>
#include<stdio.h>
#include "server.h"
//#define password "hello"

void main()
{
    const char *password = "hello";

    int umbrellaChoice;
    printf("\n\nEnter:\n 1. Customer Database operations \n 2. Billing Operations \n 3. Exit\n");
    scanf("%d", &umbrellaChoice);

    switch(umbrellaChoice)
    {
   	 case 1: printf("You've chosen to enter the database.\n\n");

   		 int pas;
   		 pas = checkPass();

   		 if(pas)
   		 	displayDB();
   		 //printf("control back in umbrella");
   		 break;

   	 case 2:
         printf("You've chosen to enter the billing process.\n");
   		 billSwitch();
   		 break;

   	 default:
   	     exit(0); //exits entire program
    }
}

