/******************************************************************************
This is to certify that this project is my own work, based on my personal 
efforts in studying and applying the concepts learned. I have constructed  
the functions and their respective algorithms and corresponding code by  
myself. The program was run, tested, and debugged by my own efforts.  
I further certify that I have not copied in part or whole or otherwise  
plagiarized the work of other students and/or persons. 

<Your Full Name> - <12223452, > - <S26>
******************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_ENTRIES 50
#define MAX_ITEMS 5

typedef struct {
    char name[50];
    char location[100];
    char contact[12]; // 8 or 11 digits
    char servingMode[50];
    char paymentOptions[50];
    char category[30];
    char priceRange[20];
    char popularItems[MAX_ITEMS][50];
} FoodEstablishment;


FoodEstablishment directory[MAX_ENTRIES];
int totalEntries = 0;


void showMainMenu();
void adminMode();
void userMode();

// Admin Mode Functions
void addEstablishment();
void editEstablishment();
void deleteEstablishment();
void listAllEstablishments();

// User Mode Functions
void searchByCategory();
void searchByLocation();
void searchByMultipleCriteria();

// Utility Functions
void displayEstablishment(FoodEstablishment f);
void clearInputBuffer();

int main() {
    int choice;

    do {
        showMainMenu();
        printf("Enter mode (1-Admin, 2-User, 0-Exit): ");
        scanf("%d", &choice);
        clearInputBuffer();

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
    printf("\n===== Greenie Food Directory =====\n");
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

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

void addEstablishment() {
    if (totalEntries >= MAX_ENTRIES) {
        printf("Cannot add more establishments. The directory is full rn.\n");
        return;
    }

    FoodEstablishment *f = &directory[totalEntries];

    printf("\n-- Add New Establishment --\n");

    printf ("Enter name of store: ");
    fgets (f->name, sizeof(f->name), stdin);
    trimNewline(f->name);

    printf ("Enter the location: ");
    fgets (f->location, sizeof(f->location), stdin);
    trimNewline (f->location);

    printf ("Enter Contact Number (8 or 11 digits): ");
    fgets (f->contact, sizeof(f->contact), stdin);
    trimNewline (f->contact);

    int len = strlen(f->contact);
    if (!(len == 8 || len == 11)) {
        printf("The contact number is invalid, it should be just be 8 or 11 digits.\n");
        return;
    }

    printf("Enter the serving mode (dine-in, take-out): ");
    fgets(f->servingMode, sizeof(f->servingMode), stdin);
    trimNewline(f->servingMode);

    printf("Enter the payment options (cash, gcash): ");
    fgets(f->paymentOptions, sizeof(f->paymentOptions), stdin);
    trimNewline(f->paymentOptions);

    printf("Enter what food category it is in (Filipino, Chinese): ");
    fgets(f->category, sizeof(f->category), stdin);
    trimNewline(f->category);

    printf("Enter price range (80-250 PHP): ");
    fgets(f->priceRange, sizeof(f->priceRange), stdin);
    trimNewline(f->priceRange);

    printf("Enter up to 5 popular food items:\n");
    for (int i = 0; i < MAX_ITEMS; i++) {
        printf("  Item %d (please leave blank to stop): ", i + 1);
        fgets(f->popularItems[i], sizeof(f->popularItems[i]), stdin);
        trimNewline(f->popularItems[i]);
        if (strlen(f->popularItems[i]) == 0) break;
    }

    totalEntries++;
    printf("Establishment added successfully!\n");

}

void editEstablishment() {
    if (totalEntries == 0) {
        printf("dawg there ain't any establishments to edit lmaoooo.\n");
        return;
    }

    printf("\n-- Edit Establishment --\n");
    for (int i = 0; i < totalEntries; i++) {
        printf("[%d] %s\n", i + 1, directory[i].name);
    }

    int choice;
    printf("Select an establishment to edit (1-%d): ", totalEntries);
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice < 1 || choice > totalEntries) {
        printf("Invalid choice.\n");
        return;
    }

    FoodEstablishment *f = &directory[choice - 1];
    char input[100];

    printf("\nEditing '%s'\n", f->name);

    printf("Edit Name? (current: %s) [Y/N]: ", f->name);
    fgets(input, sizeof(input), stdin); trimNewline(input);
    if (input[0] == 'Y' || input[0] == 'y') {
        printf("Enter new name: ");
        fgets(f->name, sizeof(f->name), stdin);
        trimNewline(f->name);
    }

    printf ("Edit Location? (current: %s) [Y/N]: ", f->location);
    fgets(input, sizeof(input), stdin); trimNewline(input);
    if (input[0] == 'Y' || input[0] == 'y') {
        printf("Enter new location: ");
        fgets(f->location, sizeof(f->location), stdin);
        trimNewline(f->location);
    }

    printf ("Edit Contact Number? (current: %s) [Y/N]: ", f->contact);
    fgets(input, sizeof(input), stdin); trimNewline(input);
    if (input[0] == 'Y' || input[0] == 'y') {
        printf("Enter new contact number (8 or 11 digits): ");
        fgets(f->contact, sizeof(f->contact), stdin);
        trimNewline(f->contact);
    }

    printf ("Edit Serving Mode? (current: %s) [Y/N]: ", f->servingMode);
    fgets(input, sizeof(input), stdin); trimNewline(input);
    if (input[0] == 'Y' || input[0] == 'y') {
        printf("Enter new serving mode: ");
        fgets(f->servingMode, sizeof(f->servingMode), stdin);
        trimNewline(f->servingMode);
    }

    printf ("Edit Payment Options? (current: %s) [Y/N]: ", f->paymentOptions);
    fgets(input, sizeof(input), stdin); trimNewline(input);
    if (input[0] == 'Y' || input[0] == 'y') {
        printf("Enter new payment options: ");
        fgets(f->paymentOptions, sizeof(f->paymentOptions), stdin);
        trimNewline(f->paymentOptions);
    }

    printf ("Edit Food Category? (current: %s) [Y/N]: ", f->category);
    fgets(input, sizeof(input), stdin); trimNewline(input);
    if (input[0] == 'Y' || input[0] == 'y') {
        printf("Enter new food category: ");
        fgets(f->category, sizeof(f->category), stdin);
        trimNewline(f->category);
    }

    printf ("Edit Price Range? (current: %s) [Y/N]: ", f->priceRange);
    fgets(input, sizeof(input), stdin); trimNewline(input);
    if (input[0] == 'Y' || input[0] == 'y') {
        printf("Enter new price range: ");
        fgets(f->priceRange, sizeof(f->priceRange), stdin);
        trimNewline(f->priceRange);
    }

    printf ("Edit Popular Food Items? [Y/N]: ");
    fgets(input, sizeof(input), stdin); trimNewline(input);
    if (input[0] == 'Y' || input[0] == 'y') {
        for (int i = 0; i < MAX_ITEMS; i++) {
            printf("  Enter item %d (pls leave blank to stop): ", i + 1);
            fgets(f->popularItems[i], sizeof(f->popularItems[i]), stdin);
            trimNewline(f->popularItems[i]);
            if (strlen(f->popularItems[i]) == 0) break;
        }
    }
    printf("Establishment updated successfully yea\n");
}

void deleteEstablishment() {
   
    if (totalEntries == 0) {
        printf ("No establishments to delete.\n");
        return;
    }
    printf ("\n-- Delete Establishment --\n");
    for (int i = 0; i < totalEntries; i++) {
        printf("[%d] %s\n", i + 1, directory[i].name);
    }
    int choice;
    printf ("Select the number of the establishment to delete (1-%d): ", totalEntries);
    scanf("%d", &choice);
    clearInputBuffer();
    if (choice < 1 || choice > totalEntries) {
        printf("Invalid choice.\n");
        return;
    }
    printf ("Are you really sure you want to delete '%s'? [Y/N]: ", directory[choice - 1].name);
    char confirm[10];
    fgets(confirm, sizeof(confirm), stdin);
    trimNewline(confirm);

    if (confirm[0] != 'Y' && confirm[0] != 'y') {
        printf("Deletion cancelled.\n");
        return;
    }
    for (int i = choice - 1; i < totalEntries - 1; i++) {
        directory[i] = directory[i + 1];
    }
    totalEntries--;
    printf("Establishment deleted successfully.\n");


}

void listAllEstablishments() {
   
    if (totalEntries == 0) {
        printf("No establishments found in the directory.\n");
        return;
    }
    printf("\n%-5s%-20s%-20s%-15s%-15s%-12s%-12s%-10s\n",
           "No", "Name", "Location", "Contact #", "Serving Mode", "Payment", "Category", "Price");
    printf("-----------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < totalEntries; i++) {
        FoodEstablishment f = directory[i];
        printf("%-5d%-20s%-20s%-15s%-15s%-12s%-12s%-10s\n",
               i + 1,
               f.name,
               f.location,
               f.contact,
               f.servingMode,
               f.paymentOptions,
               f.category,
               f.priceRange);
    }

    printf("\nPopular Items (Max 5 per establishment):\n");
    for (int i = 0; i < totalEntries; i++) {
        printf("%d. %s:\n", i + 1, directory[i].name);
        for (int j = 0; j < MAX_ITEMS; j++) {
            if (strlen(directory[i].popularItems[j]) > 0) {
                printf("   - %s\n", directory[i].popularItems[j]);
            }
        }
    }
}

   




void searchByCategory() {
   
}

void searchByLocation() {
   
}

void searchByMultipleCriteria() {
   
}

void displayEstablishment(FoodEstablishment f) {
  
}

void clearInputBuffer() {
    while (getchar() != '\n');
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

