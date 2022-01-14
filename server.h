#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

float bill_input();

int checkPass();
int password();
//int passWord();


float calcTax(float total);
int calcPoints(float total);

//switch case functions
void dbSwitch();
void billSwitch();


float calcTotal();
void finalTotal();

void displayBill();
void main();

struct account {
	int number;
	char name[100];
	int acct_no;
	float mobile_no;
	char city[100];
	}customer;

struct details
 {
        char name[20];
        int price;
        int qty;
 }item[50];


struct product
{
    float price;
    int qty;
    float tot;
    char name[30];
}prd[100];

 void displayDB();
 void input();
 void writefile();
 void search_cust();
 void output();


#endif // SERVER_H_INCLUDED
