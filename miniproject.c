#include <stdio.h>
#include <stdlib.h>
int main(){
#define RATE_EURO_TO_EGP  55.0            //So here I made a define because those are constant values 
#define RATE_DOLLAR_TO_EGP  47.5
#define RATE_EURO_TO_DOLLAR  1.16
float amount , num1 , num2;
int subchoice;
int choice;
do {                                       // Here is the menu 
    printf("\n--Main Menu--\n");
    printf("1. Currency converstion\n");
    printf("2. Calculator\n");
    printf("3. Exit the program\n");
    printf("Enter choice:");
    scanf("%d", &choice);
    switch(choice){                     //After I finshied the menu I made a switch case for every choice now this for the currency 
    case 1:
    printf("You chose Currency conversion\n");
    printf("\n-- Currency Conversion Menu --\n");
    printf("1.EGP to EURO\n");
    printf("2.EGP to Dollar\n");
    printf("3.EURO to Dollar\n");
    printf("4.Dollar to EURO\n");
    printf("5.EURO to EGP\n");
    printf("6.Dollar to EGP\n");
    printf("7.Percentage Euro to Dollar\n");
    printf("Enter your choice: ");
    scanf("%d", &subchoice);
    if (subchoice >=1 && subchoice <=7){
    printf("Enter the amount: ");
    scanf("%f", &amount);
while (amount < 0){
    printf("The amount can not be negative soryy just try again");
    scanf("%f", &amount);

}
if (subchoice == 7){
    printf("Enter Euro Amount:");
    scanf("%f", &num1);                    
    printf("Enter Dollar Amount: ");
    scanf("%f",&num2);
    printf("Result %.2f Dollar", num1 / num2);
}
if (subchoice == 1){
    printf("Result: %.2f Euro\n", amount / RATE_EURO_TO_EGP);
}else if (subchoice ==2){
    printf("Result: %.2f Dollars\n", amount / RATE_DOLLAR_TO_EGP);
}else if (subchoice ==3){
    printf("Resukt: %.2f Dollars\n", amount * RATE_EURO_TO_DOLLAR);
}else if (subchoice ==4){
    printf("Result: %.2f Euro\n", amount / RATE_EURO_TO_DOLLAR);
}else if (subchoice ==5){
    printf("Result: %.2f EGP\n", amount * RATE_EURO_TO_EGP);
}else if (subchoice ==6){
    printf("Result: %.2f EGP\n", amount * RATE_DOLLAR_TO_EGP);
}else {
  printf("Invalid choice\n");
}
}
break;

case 2:                                     // The second switch case for the calcultaor
printf("You chose Calculator \n");
printf("\n----Calculator menu---\n");
printf("1. Addidtion\n");
printf("2. Subtraction\n");
printf("3. Multiplcation\n");
printf("4. Division\n");
printf("Enter your choice: ");
scanf("%d", &subchoice);

printf("Enter the first number: ");
scanf("%f", &num1);
printf("Enter the second number: ");
scanf("%f", &num2);

if (subchoice ==1){
   printf("Result is %.2f", num1 + num2);
}else if (subchoice ==2){
    printf("Result is %.2f ", num1 - num2);
}else if (subchoice ==3){
    printf("Result is %.2f", num1 * num2);
}else if (subchoice ==4){
    printf("Result is %.2f", num1 / num2);
}
break;

case 3:       //The third switch case is to exit the program to prevent going to an infint loop
printf("Exit the program\n");
break;

    }

}while (choice !=3);
return 0;
}