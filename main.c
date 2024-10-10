// required to enable use of scanf() and printf()
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    /* Constants */
#define car_PRICE 45000.0f
#define DISCOUNT_MULTIBUY_PERCENTAGE 0.20f
#define DISCOUNT_MULTIBUY_AMOUNT 3
#define DISCOUNT_MEMBER_PERCENTAGE 0.25f

    /* Variables */
    // short carsAvailable = 10, carsNeeded;
    // float totalPrice;
    unsigned short carsAvailable = 10, carsNeeded = 0, giveDiscount = 0, discountAmount = 0;
    float totalPrice = 0.0f, discountValue, carsSold = 1.0f, carsAmount = 45000.0f;
    bool discountGiven = false;
    char isMemberOfCarClub; char userChoice;
    /* Rest of the program */
    printf("Welcome to the car Sales office!\n\n");

    printf("Menu:\n");
    printf("a. Buy Ticket\n");
    printf("b. View Sales Stats\n");
    printf("x. Exit\n\n");

    // prompt user for their choice
    printf("Please choose one: ");
    // we use %c to tell scanf() it should be expecting a single character, ideally one found within the above menu
    scanf("%c", &userChoice);

    while (userChoice != 'a' && userChoice != 'b' && userChoice != 'x') {
        printf("Please enter a valid choice: ");

        printf("Menu:\n");
        printf("a. Buy Ticket\n");
        printf("b. View Sales Stats\n");
        printf("x. Exit\n\n");

        // prompt user for their choice
        printf("Please choose one: ");
        // we use %c to tell scanf() it should be expecting a single character, ideally one found within the above menu
        scanf("%c", &userChoice);
        if (userChoice == 'a' || userChoice == 'b' || userChoice == 'x') {
            break;
        }
    }
    // for the user's benefit...
    printf("\n\n");


    switch (userChoice) {
        case 'a':
            printf("There are %hd cars available. Each car costs %f.\n\n", carsAvailable, car_PRICE);

            bool enoughCars = false;
            while (enoughCars == false) {
                if (carsAvailable == 0) {
                    printf("Sorry there are no cars available");
                }
                printf("How many cars do you need? Amount: ");
                // please make sure you add & in front of the variable name, else it won't work
                scanf("%hd", &carsNeeded);

                if (carsNeeded > carsAvailable) {
                    printf("Sorry, we only have %hd cars available\n", carsAvailable);
                } else {
                    enoughCars = true;
                }

            }
            totalPrice = carsNeeded * car_PRICE;
            printf("Total price: £%f", totalPrice);
            // Calculate total price before discounts

            printf("\nAre you a member of the Car Club? Answer (Y/N) = ");
            scanf("\n%c", &isMemberOfCarClub);

            if (isMemberOfCarClub == 'Y') {
                totalPrice = totalPrice / (1 + DISCOUNT_MEMBER_PERCENTAGE);
                // Adjust totalPrice to show discount for car club members
                discountGiven = true;
                // Record that a discount has been given
                discountAmount = 25;
            } else if (carsNeeded >= DISCOUNT_MULTIBUY_AMOUNT) {
                totalPrice = totalPrice / (1 + DISCOUNT_MULTIBUY_PERCENTAGE);
                discountGiven = true;
                discountAmount = 20;
                // Same as for car club discount
            }

            // update number of cars available by subtracting from it the amount of cars needed
            carsAvailable = carsAvailable - carsNeeded;

            // present the outcome
            printf("\nThank you.\n");
            printf("You have bought %hd cars.\n", carsNeeded);
            printf("Total cost is %f GBP.\n", totalPrice);
            carsAmount += totalPrice;
            carsSold += carsNeeded;
            if (discountGiven) {
                printf("This price includes a discount of %hu percent", discountAmount);
            }

            printf("\n\nThere are %hd cars remaining.", carsAvailable);
            printf("\n\nHave a good day!");

        case 'b':
            printf("Cars Sold: %f\n", carsSold);
            printf("Total Value of cars sold: £%f\n", carsAmount);

        case 'x':
            printf("Thank you for using the car sales program. Bye!\n");
            break;
        }

        return 0;
}
