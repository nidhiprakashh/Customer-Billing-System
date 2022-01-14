#include "server.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

int numProd;
float total=0;
float final_total, subTotal, grandTotal;
float complete_total;
int count=0;
FILE *file;
char customer_name[50];
const char pword[]="password";

int checkPass()
{
	int flag=0;
	flag = password();
	//printf("\n%d", flag);

	if(flag==0)
	{
		for(int i=0; i<3; i++)
		{	printf("\nTry Again.\n");
			flag = passWord();
			if(flag==1)
				break;
		}
	}

	return flag;
}

int passWord()
{
 int passSize=8;
    int flag=0; //0 means entry restricted, flag=1 means password correct
    char pw[passSize];
    int i=0;

    printf("\nEnter password: ");

    while((pw[i]=getchar())!='\n')
    {
   	 i++;
   	 putchar('*');
    }

	printf("\n");

	if(1)
	{
	for(i=0; i<passSize; i++)
	{
		if(pw[i]==pword[i])
			{flag=1;}
		else
		{	flag=0;
			break;
		}
	}

	if(flag==1)
		printf("\nPassword is correct. Entering database...\t\n");
	else
		printf("\nIncorrect password.\t\n");

	return flag;
	}

}

int password()
{
    int passSize=8;
    int flag=0; //0 means entry restricted, flag=1 means password correct
    char pw[passSize];
    int i=0;

    printf("\nEnter password: ");

    pw[i]=getchar();

    while((pw[i]=getchar())!='\n')
    {
   	 i++;
   	 putchar('*');
    }

	printf("\n");

	if(1)
	{
	for(i=0; i<passSize; i++)
	{
		if(pw[i]==pword[i])
			{flag=1;}
		else
		{	flag=0;
			break;
		}
	}

	if(flag==1)
		printf("\nPassword is correct. Entering database...\t\n");
	else
		printf("\nIncorrect password.\t\n");

	return flag;
	}

}

float calcTax(float total)//calculates 18% tax
{

    float tax;
    tax=total*0.18;
    return tax;
}


int calcPoints(float total)//calculates points based on purchase total
{
    if(total<350)
   	 return 0;
    else if(350<=total && total<750)
   	 return 50;
    else if(750<=total && total<1250)
   	 return 100;
    else if(1250<=total && total<2000)
   	 return 175;
    else if(total>=2000)
   	 return 300;
}



void billSwitch()//allows user to choose between options in billing operations and accordingly calls the required function
{
    int bC;
    printf("\nEnter:\n1. Enter Products to bill \n2. Print Bill \n3. Exit\n");
    scanf("%d", &bC);

   		 switch(bC)

        {
   			 case 1:

                 printf("\n\nBilling products...\n\n");
   			     finalTotal();

   			     main();
   				 break;

   			 case 2: printf("\n\nGenerating bill...\n\n");
   				 displayBill();
   				 break;

   			 default:
   			      break;
   		 }
}


void finalTotal() //gives final total after calculating tax, discount and adding them
{

final_total=bill_input();
subTotal=final_total-calcPoints(final_total);
grandTotal=subTotal+calcTax(subTotal);

file = fopen(customer_name,"a+"); //opens file for reading and appending


       fprintf(file,"\n\t\t\t\t\t\t\t\tDISCOUNT ON REDEEMING POINTS= Rs.%d ",calcPoints(final_total));
       fprintf(file,"\n\t\t\t\t\t\t\t\t TAX ON PURCHASE=Rs.%.2f \n",calcTax(subTotal));
       fprintf(file,"\n\t\t\t\t\t\t\t\t GRAND TOTAL=Rs.%.2f\n\n ",grandTotal);
fclose(file);


}


void displayBill()//displays final formatted bill
{
char ch;
file = fopen(customer_name,"r");//opens file in read mode
    if(file == NULL)//there is no associated data with file
    {
        printf("Unable to open file.\n");
        printf("Please check whether file exists and you have read privilege.\n");
        exit(EXIT_FAILURE);
    }



    printf("File opened successfully. Reading file contents character by character. \n\n");

    do
    {
        ch = fgetc(file);//obtains input from file single character at a time
        putchar(ch);//displays output single character at a time

    } while(ch != EOF);
    fclose(file);



}


int tl,sl,ts;
void displayDB() //function for customer database operations
	{
	  //int i,n;
	  char ch;



	  printf("   CUSTOMER BILLING SYSTEM:\n\n");
	  printf("===============================\n");
	  printf("\n1:    to add account on list\n");
	  printf("2:    to search customer account\n");
	  printf("3:    exit\n");
	  printf("\n================================\n");
	  do{
	       printf("\nSelect choice?");
	       ch=getche();//waits for character i/p from user and immediately displays on o/p screen
	  }while(ch<='0' || ch>'3');

	  switch(ch){
		case '1':
				input();
				writefile();
                main();

		case '2':
			printf("\n --- searching by customer name\n");
			search_cust();
			ch=getche();
			main();

		case '3':
            exit(1);
	  }
 }


void input()
	{
	  file=fopen("customer.dat","rb");//.dat file is a data file and is a type of binary file and rb is read mode for binary files
	  fseek (file,0,SEEK_END);//takes cursor to  end of file
	  tl=ftell(file);//returns current file position wrt to start; used  to get total size of file after moving to EOF
	  sl=sizeof(customer);
	  ts=tl/sl;//gives number of customers
	  fseek(file,(ts-1)*sl,SEEK_SET);//moves file through all customers in file,starting from beginning of file
	  fread(&customer,sizeof(customer),1,file);//reads data from the given stream into the array pointed to, by ptr
	  printf("\ncustomer no:%d\n",++customer.number);
	  fclose(file);//closes file
	  printf("         Account number:");
	  scanf("%d",&customer.acct_no);
	  printf("\n       Name:");
	  scanf("%s",customer.name);
	  printf("\n       mobile no:");
	  scanf("%f",&customer.mobile_no);
	  printf("         City:");
	  scanf("%s",customer.city);

	  return;
   }

   void writefile()//writes data obtained via input() into a file
   {

	  file=fopen("customer.dat","ab");
	  fwrite(&customer,sizeof(customer),1,file);
	  fclose(file);
	  return;
   }

   void search_cust()//function to search for customer in database based on name
   {
	 char ch;
	 char nam[100];
	 int n,i,m=1;
	 file=fopen("customer.dat","rb");

		    do{
			printf("\nEnter the name:");
			scanf("%s",nam);
			fseek(file,0,SEEK_SET);//sets cursor distance 0 bytes from beginning
			for(i=1;i<=n;i++)
			{
			     fread(&customer,sizeof(customer),1,file);
			     if(strcmp(customer.name,nam)==0)//strcmp returns 0 if strings compared are equal
			     {
				   output();
                   m=0;
				   break;
			     }
			}
			if(m!=0)
			printf("\n\nCustomer record not found in database.\n");
			printf("\nTry another? (Y/N) ");
			ch=getche();
		    }while(ch=='y');
		    fclose(file);

	      return;
	 }



void output()//displays customer details
	 {
	   printf("\n\n    Customer no    :%d\n",customer.number);
	   printf("    Name 	   :%s\n",customer.name);
	   printf("    Mobile no      :%.f\n",customer.mobile_no);
	   printf("    Account number :%d\n",customer.acct_no);


	 }



float bill_input()
{
int ch,n;
char rem[50],c,c1;
char rep[30];
char date[30];

    char se[30];
    int changed_quantity,choice,i;
    float changed_price;
    float complete_total=0;
    printf("Enter customer name:\n");
    scanf("%s",customer_name);   //input name of the customer which will also be the name of the file
     printf("enter date in the format dd/mm/yyyy\n");
     scanf("%s",date);
 c='y';
while(c=='y'||c=='Y')
{   printf("\nenter product name\n");
    scanf("%s",prd[count].name);
     printf("enter quantity\n");
    scanf("%d",&prd[count].qty);
    printf("enter price\n");    // price of 1 unit
    scanf("%f",&prd[count].price);
    prd[count].tot=prd[count].qty*prd[count].price; //finding price total for the quantity inputed
    c='\0';
    printf("\nDo you want to  continue? (Y/N) \n");
    scanf("%c",&c);
    c=getchar();
    count+=1;                // keeps the count of the total number of products
}
c1='y';
while(c1=='y'||c1=='Y')
{
printf(("Enter: 1- to Remove Product, 2- to Edit Product, 3- Add Product, 4- Continue with selected Products\n"));
scanf("%d",&ch);
switch(ch)            //customer can make changes in the bill
{
case 1:

    printf("Enter item to remove:\n");
    scanf("%s",rem);
    for(i=0;i<count;i++)
    {
        if((strcmp(rem,prd[i].name))==0)   //compares the product name with the name of the product the customer wants to remove
        {
            n=i;                           //if strcmp returns zero the position is stored
            break;}
}


        for(int j=n;j<count;j++)           //as the product is to be removed all the array members have to shift to take its place
            {strcpy(prd[j].name,prd[j+1].name);
            prd[j].qty=prd[j+1].qty;
            prd[j].price=prd[j+1].price;}
            count=count-1;
            for(i=0;i<count;i++)
            {
                prd[i].tot=prd[i].qty*prd[i].price;
            }
        break;
case 2:
    printf("Enter product to replace:\n");
    scanf("%s",se);                       //ask the customer the product they want to make changes to
   for(i=0;i<count;i++)
    {if((strcmp(se,prd[i].name))==0)       // compares the input from the customer and product name if 0 asks them want changes they want to make
        {printf("enter 1 for changing product and quantity 2 for product 3 for only quantity\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:                             //this case is to change the product and the quantity as well therefore the price also changes
           printf("Product to replace it with:\n");
            scanf("%s",rep);
            printf("Enter changed quantity:\n"); //input the changes in all
            scanf("%d",&changed_quantity);
            printf("Enter changed price:\n");
            scanf("%f",&changed_price);
            strcpy(prd[i].name,rep);
            prd[i].qty=changed_quantity;
            prd[i].price=changed_price;

            prd[i].tot=prd[i].qty*prd[i].price;
            break;
        case 2:                        //this is the case where product is replaced quantity remains the same but the price also changes
            printf("Product to Replace it with:\n");
            scanf("%s",rep);
            printf("Enter changed price:\n");
            scanf("%f",&changed_price);
            strcpy(prd[i].name,rep);
             prd[i].price=changed_price;

            prd[i].tot=prd[i].qty*prd[i].price;

             break;
        case 3:                       //in this case the quantity of the given product changes the price remains the same but product total changes
             printf("Enter changed quantity:\n");
            scanf("%d",&changed_quantity);
            prd[i].qty=changed_quantity;
            prd[i].tot=prd[i].qty*prd[i].price;

            break;
        default:
            printf("Wrong choice.");


            }

        }
        else
        {
            prd[i].tot=prd[i].qty*prd[i].price;
            }

    }
    break;
        case 3:                          //this case is to add product to the already inputed products
             printf("\Enter product name:\n");
    scanf("%s",prd[count].name);          //it is added to the last element of the array as array starts from index zero
       printf("Enter quantity:\n");
    scanf("%d",&prd[count].qty);
     printf("Enter Price:\n");
    scanf("%f",&prd[count].price);

    for(i=0;i<=count;i++)
    {   prd[i].tot=prd[i].qty*prd[i].price;

    }
           count=count+1;          //as an extra item is added the total no. of products increases by 1
            break;
        default:
            printf("You've chosen to continue.\n");}
c1='\0';
printf("Any more changes? (Y/N) \n"); //asks if the customer wants to make any more changes
scanf("%c",&c1);
c1=getchar();}
for(i=0;i<count;i++)                                      //outputs to the terminal the final list of product details
{          printf("The product name is: %s\n", prd[i].name);
            printf("The product quantity is: %d\n", prd[i].qty);
            printf("The product price per unit is: %.2f\n", prd[i].price);
             printf("The total price of the product is: %.2f\n ", prd[i].tot);
             complete_total+=prd[i].tot;  //finds the sum of the total product price to give us a complete total before taxes and discounts

}
printf("your Final Total is %.2f\n",complete_total);
 file = fopen(customer_name,"a+");        //appends to the file with the customer name the details of all the products
 fprintf(file,"\n\n-----------------------------------------------------------------------------------------------------------------\n");
    fprintf(file,"                                              SWAMI'S CONDIMENTS                                                 \n");
    fprintf(file,"-----------------------------------------------------------------------------------------------------------------\n");
    fprintf(file,"\n");
    fprintf(file,"__________________________________________________________________________________________________________________\n");
    fprintf(file,"                                              CUSTOMER BILL                                                       \n");
    fprintf(file,"__________________________________________________________________________________________________________________\n");
    fprintf(file,"\nDATE:%s\n",date);
    fprintf(file,"\nCUSTOMER NAME:%s\n",customer_name);
 fprintf(file,"\nSL.NO.\t\tPRODUCT NAME\t\tPRODUCT PRICE\t\tPRODUCT QUANTITY\t\tPRODUCT TOTAL\n");

for(int i=0;i<count;i++)
{
    fprintf(file, "%d\t%15s\t\t\t%.2f\t\t\t%d\t\t\t\t%.2f\n",i+1,prd[i].name,prd[i].price,prd[i].qty,prd[i].tot);
   }
    fprintf(file,"\n\t\t\t\t\t\t\t\t TOTAL IS:Rs%.2f",complete_total); //appends the complete total to the file
fclose(file);

return complete_total; //returns complete_total which is later called in the grandTotal function

}
