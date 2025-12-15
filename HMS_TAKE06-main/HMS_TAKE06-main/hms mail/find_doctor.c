#include "hms.h"

void find_doctor_menu() {
    int choice;
    while(1) {
        clear_screen();
        printf("=== FIND DOCTOR ===\n");
        printf("1. View All Doctors\n");
        printf("2. Search by Specialty\n");
        printf("3. Back\n");
        choice = get_int("Enter Choice: ");
        
        switch(choice) {
            case 1: display_doctor_list(); pause_exec(); break;
            case 2: search_doctor(); break;
            case 3: return;
            default: printf("Invalid Choice!\n");
        }
    }
}

// Help to show doctor list
void display_doctor_list() {
    FILE *file = fopen(DOCTOR_FILE, "r");
    if (!file) {
        printf("No doctors available.\n");
        return;
    }
    
    char buffer[MAX_BUFFER];
    Doctor d;
    
    printf("\n--- Available Doctors ---\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d|%[^|]|%[^|]|%d|%[^\n]", &d.id, d.name, d.specialty, &d.years_experience, d.contact);
        printf("[%d] Dr. %s (%s, %d yrs exp)\n", d.id, d.name, d.specialty, d.years_experience);
    }
    fclose(file);
}

void search_doctor() {
    char keyword[MAX_NAME];
    get_string("Enter Specialty to search: ", keyword, MAX_NAME);
    
    FILE *file = fopen(DOCTOR_FILE, "r");
    if (!file) {
        printf("No doctors available.\n");
        return;
    }
    
    char buffer[MAX_BUFFER];
    Doctor d;
    int found = 0;
    
    printf("\n--- Search Results ---\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d|%[^|]|%[^|]|%d|%[^\n]", &d.id, d.name, d.specialty, &d.years_experience, d.contact);
        
        if (strstr(d.specialty, keyword) != NULL) {
             printf("[%d] Dr. %s (%s)\n", d.id, d.name, d.specialty);
             found = 1;
        }
    }
    fclose(file);
    
    if (!found) printf("No doctors found with that specialty.\n");
    pause_exec();
}


