/******************************************************************************
This is to certify that this project is my own work, based on my personal 
efforts in studying and applying the concepts learned. I have constructed  
the functions and their respective algorithms and corresponding code by  
myself. The program was run, tested, and debugged by my own efforts.  
I further certify that I have not copied in part or whole or otherwise  
plagiarized the work of other students and/or persons. 

<Ye> - <12223452> - <S26>
******************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_ENTRIES 50
#define MAX_ITEMS 5

typedef struct {
    char name[50];
    char location[100];
    char contact[12]; 
    char servingMode[50];
    char paymentOptions[50];
    char category[30];
    char priceRange[20];
    char popularItems[MAX_ITEMS][50];
} FoodEstablishment;


FoodEstablishment directory[MAX_ENTRIES];
int totalEntries = 0;

//mga prototype palang
void showMainMenu();
void adminMode();
void userMode();

//for admin mode
void addEstablishment();
void editEstablishment();
void deleteEstablishment();
void listAllEstablishments();

// user mode
void searchByCategory();
void searchByLocation();
void searchByMultipleCriteria();


void displayEstablishment(FoodEstablishment f);


int main() {
    int choice;

    do {
        showMainMenu();
        printf ("Enter your mode (1-Admin, 2-User, 0-Exit): ");
        scanf ("%d", &choice);
      

        switch (choice) {
            case 1: adminMode(); break;
            case 2: userMode(); break;
            case 0: printf("Exiting program.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}

void showMainMenu() {
    printf("\n===== Greenie Food Directory!!! =====\n");
    printf("1. Admin Mode\n");
    printf("2. User Mode\n");
    printf("0. Exit\n");
    printf("==================================\n");
}

void adminMode() {
    int choice;
    do {
        printf("\n--- Admin Mode ---\n");
        printf("1. Add Establishment\n");
        printf("2. Edit Establishment\n");
        printf("3. Delete Establishment\n");
        printf("4. List All Establishments\n");
        printf("0. Return to Main Menu\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: addEstablishment(); break;
            case 2: editEstablishment(); break;
            case 3: deleteEstablishment(); break;
            case 4: listAllEstablishments(); break;
            case 0: break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 0);
}

void userMode() {
    int choice;
    do {
        printf("\n--- User Mode ---\n");
        printf("1. Search by Category\n");
        printf("2. Search by Location\n");
        printf("3. Search by Multiple Criteria\n");
        printf("0. Return to Main Menu\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: searchByCategory(); break;
            case 2: searchByLocation(); break;
            case 3: searchByMultipleCriteria(); break;
            case 0: break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 0);
}

 // adding logic na here, sending the full specs din after this
void addEstablishment() {
 
}

void editEstablishment() {
  
}

void deleteEstablishment() {
   
}

void listAllEstablishments() {

}

void searchByCategory() {
 
}

void searchByLocation() {
 
}

void searchByMultipleCriteria() {
  
}

void displayEstablishment(FoodEstablishment f) {
   
}


/*
===============================================================================
Function Specifications (place below main, as instructed in project specs)
===============================================================================

/* addEstablishment adds a new food entry to the directory
 * @param none
 * @return void
 * Pre-condition: totalEntries < MAX_ENTRIES
 */

/* editEstablishment modifies an existing entry based on index or name
 * @param none
 * @return void
 */

/* deleteEstablishment removes an entry from the directory
 * @param none
 * @return void
 */

/* searchByCategory searches for entries matching the specified category
 * @param none
 * @return void
 */

/* etc...
 */

