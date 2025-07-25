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
#include <ctype.h>

#define MAX_ENTRIES 50
#define MAX_ITEMS 5
#define MAX_NAME 50
#define MAX_LOCATION 100
#define MAX_CONTACT 12
#define MAX_SERVING 50
#define MAX_PAYMENT 50
#define MAX_CATEGORY 30
#define MAX_PRICERANGE 20

// Structure for food establishment
typedef struct {
    char name[MAX_NAME];
    char location[MAX_LOCATION];
    char contact[MAX_CONTACT]; // 8 or 11 digits
    char servingMode[MAX_SERVING];
    char paymentOptions[MAX_PAYMENT];
    char category[MAX_CATEGORY];
    char priceRange[MAX_PRICERANGE];
    char popularItems[MAX_ITEMS][MAX_NAME];
} FoodEstablishment;

// Directory array and entry count
FoodEstablishment directory[MAX_ENTRIES];
int totalEntries = 0;

// Function prototypes
void showMainMenu();
void adminMode();
void userMode();

//admin functions
void addEstablishment();
void editEstablishment();
void deleteEstablishment();
void listAllEstablishments();

//user funtions
void searchByCategory();
void searchByLocation();
void searchByMultipleCriteria();

void displayEstablishment(const FoodEstablishment *f, int index);
void clearInputBuffer();
void getStringInput(const char *prompt, char *buffer, int size);
int getIntInput(const char *prompt, int min, int max);
int validateContact(const char *contact);
int findEstablishmentByName(const char *name);
void saveToFile();
void loadFromFile();

int main() {
	int choice;
    do {
        showMainMenu();
        choice = getIntInput("Enter your mode (1-Admin, 2-User, 0-Exit): ", 0, 2);
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
        printf("5. Save Directory to File\n");
		printf("6. Load Directory from File\n");

        printf("0. Return to Main Menu\n");
        choice = getIntInput("Choose an option: ", 0, 6);
        switch (choice) {
            case 1: addEstablishment(); break;
            case 2: editEstablishment(); break;
            case 3: deleteEstablishment(); break;
            case 4: listAllEstablishments(); break;
            case 5: saveToFile(); break;
			case 6: loadFromFile(); break;
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
        choice = getIntInput("Choose an option: ", 0, 3);
        switch (choice) {
            case 1: searchByCategory(); break;
            case 2: searchByLocation(); break;
            case 3: searchByMultipleCriteria(); break;
            case 0: break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 0);
}
/*
 * trimNewline removes the trailing newline character from a string, if present.
 * @param str A pointer to the string to be modified.
 * @return void
 * Pre-condition: str is a valid null-terminated string.
 */
void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

// Add a new food establishment
/*
 * addEstablishment adds a new food entry to the directory
 * @param none
 * @return void
 * Pre-condition: totalEntries < MAX_ENTRIES
 */
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

// Edit an existing establishment
/*
 * editEstablishment modifies an existing entry based on name
 * @param none
 * @return void
 * Pre-condition: Establishment with given name exists
 */
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

// Delete an establishment
/*
 * deleteEstablishment removes an entry from the directory
 * @param none
 * @return void
 * Pre-condition: Establishment with given name exists
 */
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

// List all establishments
/*
 * listAllEstablishments displays all entries in the directory
 * @param none
 * @return void
 * Pre-condition: totalEntries > 0
 */
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

// Search by category
/*
 * searchByCategory searches for entries matching the specified category
 * @param none
 * @return void
 * Pre-condition: totalEntries > 0
 */
void searchByCategory() {
    if (totalEntries == 0) {
        printf("No establishments in the directory.\n");
        return;
    }
    printf("\n--- Available Categories ---\n");
    for (int i = 0; i < totalEntries; i++) {
        int alreadyPrinted = 0;
        // Check if category appeared before
        for (int j = 0; j < i; j++) {
            if (strcmp(directory[i].category, directory[j].category) == 0) {
                alreadyPrinted = 1;
            }
        }
        if (!alreadyPrinted) {
            printf("- %s\n", directory[i].category);
        }
    }

    char category[MAX_CATEGORY];
    printf("\n--- Search by Category ---\n");
    getStringInput("Enter category to search: ", category, MAX_CATEGORY);
    int found = 0;
    for (int i = 0; i < totalEntries; i++) {
        if (strcmp(directory[i].category, category) == 0) {
            displayEstablishment(&directory[i], i + 1);
            found = 1;
        }
    }
    if (!found) {
        printf("No establishments found for category '%s'.\n", category);
    }
}

// Search by location
/*
 * searchByLocation searches for entries matching the specified location
 * @param none
 * @return void
 * Pre-condition: totalEntries > 0
 */
void searchByLocation() {
    if (totalEntries == 0) {
        printf("No establishments in the directory.\n");
        return;
    }
    printf("\n--- Available Locations ---\n");
    for (int i = 0; i < totalEntries; i++) {
        int alreadyPrinted = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(directory[i].location, directory[j].location) == 0) {
                alreadyPrinted = 1;
            }
        }
        if (!alreadyPrinted) {
            printf("- %s\n", directory[i].location);
        }
    }
    char location[MAX_LOCATION];
    printf("\n--- Search by Location ---\n");
    getStringInput("Enter location to search (case-sensitive): ", location, MAX_LOCATION);
    int found = 0;
    for (int i = 0; i < totalEntries; i++) {
        if (strcmp(directory[i].location, location) == 0) {
            displayEstablishment(&directory[i], i + 1);
            found = 1;
        }
    }
    if (!found) {
        printf("No establishments found for location '%s'.\n", location);
    }
}

// Search by multiple criteria
/*
 * searchByMultipleCriteria searches for entries matching multiple criteria
 * @param none
 * @return void
 * Pre-condition: totalEntries > 0
 */
void searchByMultipleCriteria() {
    if (totalEntries == 0) {
        printf("No establishments in the directory.\n");
        return;
    }
    printf("\n--- Available Categories ---\n");
    for (int i = 0; i < totalEntries; i++) {
        int alreadyPrinted = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(directory[i].category, directory[j].category) == 0) {
                alreadyPrinted = 1;
            }
        }
        if (!alreadyPrinted) {
            printf("- %s\n", directory[i].category);
        }
    }
    printf("\n--- Available Locations ---\n");
    for (int i = 0; i < totalEntries; i++) {
        int alreadyPrinted = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(directory[i].location, directory[j].location) == 0) {
                alreadyPrinted = 1;
            }                      
        }
        if (!alreadyPrinted) {
            printf("- %s\n", directory[i].location);
        }
    }
    printf("\n--- Available Payment Options ---\n");
    for (int i = 0; i < totalEntries; i++) {
        int alreadyPrinted = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(directory[i].paymentOptions, directory[j].paymentOptions) == 0) {
                alreadyPrinted = 1;
            }                      
        }
        if (!alreadyPrinted) {
            printf("- %s\n", directory[i].paymentOptions);
        }
    }
    char category[MAX_CATEGORY], location[MAX_LOCATION], payment[MAX_PAYMENT];
    printf("\n--- Search by Multiple Criteria ---\n");
    getStringInput("Enter category (leave blank to skip): ", category, MAX_CATEGORY);
    getStringInput("Enter location (leave blank to skip): ", location, MAX_LOCATION);
    getStringInput("Enter payment option (leave blank to skip): ", payment, MAX_PAYMENT);
    int found = 0;
    for (int i = 0; i < totalEntries; i++) {
        int match = 1;
        if (strlen(category) > 0 && strcmp(directory[i].category, category) != 0) match = 0;
        if (strlen(location) > 0 && strcmp(directory[i].location, location) != 0) match = 0;
        if (strlen(payment) > 0 && strstr(directory[i].paymentOptions, payment) == NULL) match = 0;
        if (match) {
            displayEstablishment(&directory[i], i + 1);
            found = 1;
        }
    }
    if (!found) {
        printf("No establishments found matching criteria.\n");
    }
}

// Display a single establishment in tabular form
/*
 * displayEstablishment displays a single food establishment in tabular form
 * @param f - pointer to FoodEstablishment
 * @param index - index for display
 * @return void
 * Pre-condition: f is not NULL
 */
void displayEstablishment(const FoodEstablishment *f, int index) {
    printf("%-5d%-20s%-20s%-15s%-15s%-12s%-12s%-10s\n",
           index,
           f->name,
           f->location,
           f->contact,
           f->servingMode,
           f->paymentOptions,
           f->category,
           f->priceRange);

    printf("     Popular Items: ");
    for (int i = 0; i < MAX_ITEMS && strlen(f->popularItems[i]) > 0; i++) {
        printf("%s%s", f->popularItems[i],
               (i < MAX_ITEMS - 1 && strlen(f->popularItems[i + 1]) > 0) ? ", " : "");
    }
    printf("\n");
}

// Helper: Clear input buffer after scanf
/*
 * clearInputBuffer clears the input buffer after scanf
 * @param none
 * @return void
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Helper: Get string input safely
/*
 * getStringInput safely gets a string from user input
 * @param prompt - prompt to display
 * @param buffer - buffer to store input
 * @param size - size of buffer
 * @return void
 */
void getStringInput(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
    }
}

// Helper: Get integer input with range
/*
 * getIntInput gets an integer input within a range
 * @param prompt - prompt to display
 * @param min - minimum value
 * @param max - maximum value
 * @return int - user input
 */
int getIntInput(const char *prompt, int min, int max) {
    int value, valid = 0;
    char line[32];
    do {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin)) {
            if (sscanf(line, "%d", &value) == 1 && value >= min && value <= max) {
                valid = 1;
            } else {
                printf("Invalid input. Try again.\n");
            }
        }
    } while (!valid);
    return value;
}

// Helper: Find establishment by name (case-insensitive)
/*
 * findEstablishmentByName finds the index of an establishment by name
 * @param name - name to search
 * @return int - index if found, -1 otherwise
 */
int findEstablishmentByName(const char *name) {
    for (int i = 0; i < totalEntries; i++) {
        if (strcasecmp(directory[i].name, name) == 0) return i;
    }
    return -1;
}

void saveToFile() {
    FILE *fp = fopen("directory.txt", "w");
    if (!fp) {
        printf("Error saving file.\n");
        return;
    }

    fprintf(fp, "%d\n", totalEntries);
    for (int i = 0; i < totalEntries; i++) {
        FoodEstablishment *f = &directory[i];
        fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n", 
                f->name, f->location, f->contact, f->servingMode, 
                f->paymentOptions, f->category, f->priceRange);
        for (int j = 0; j < MAX_ITEMS; j++) {
            fprintf(fp, "%s\n", f->popularItems[j]);
        }
    }

    fclose(fp);
    printf("Directory saved successfully.\n");
}

void loadFromFile() {
    FILE *fp = fopen("directory.txt", "r");
    if (!fp) {
        printf("Error loading file. File may not exist yet.\n");
        return;
    }

    fscanf(fp, "%d\n", &totalEntries);
    for (int i = 0; i < totalEntries; i++) {
        FoodEstablishment *f = &directory[i];
        fgets(f->name, MAX_NAME, fp); trimNewline(f->name);
        fgets(f->location, MAX_LOCATION, fp); trimNewline(f->location);
        fgets(f->contact, MAX_CONTACT, fp); trimNewline(f->contact);
        fgets(f->servingMode, MAX_SERVING, fp); trimNewline(f->servingMode);
        fgets(f->paymentOptions, MAX_PAYMENT, fp); trimNewline(f->paymentOptions);
        fgets(f->category, MAX_CATEGORY, fp); trimNewline(f->category);
        fgets(f->priceRange, MAX_PRICERANGE, fp); trimNewline(f->priceRange);

        for (int j = 0; j < MAX_ITEMS; j++) {
            fgets(f->popularItems[j], MAX_NAME, fp);
            trimNewline(f->popularItems[j]);
        }
    }

    fclose(fp);
    printf("Directory loaded successfully.\n");
}