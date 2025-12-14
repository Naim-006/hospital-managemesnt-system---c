#include "hms.h"

void admin_login() {
    char password[20];
    clear_screen();
    printf("=== ADMIN LOGIN ===\n");
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(password, "admin123") == 0) {
        admin_menu();
    } else {
        printf("Invalid Password!\n");
        pause_exec();
    }
}

void admin_menu() {
    int choice;
    while(1) {
        clear_screen();
        printf("=== ADMIN PORTAL ===\n");
        printf("1. Add New Doctor\n");
        printf("2. View All Doctors\n");
        printf("3. View Feedback\n");
        printf("4. Logout\n");
        choice = get_int("Enter Choice: ");

        switch(choice) {
            case 1: add_doctor(); break;
            case 2: view_all_doctors(); break;
            case 3: view_feedback(); break;
            case 4: return;
            default: printf("Invalid Choice!\n");
        }
    }
}

void add_doctor() {
    Doctor d;
    FILE *file = fopen(DOCTOR_FILE, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    d.id = get_next_id(DOCTOR_FILE);
    printf("Adding Doctor ID: %d\n", d.id);
    
    get_string("Enter Name: ", d.name, MAX_NAME);
    get_string("Enter Specialty: ", d.specialty, MAX_NAME);
    d.years_experience = get_int("Enter Experience (Years): ");
    get_string("Enter Contact: ", d.contact, 20);

    fprintf(file, "%d|%s|%s|%d|%s\n", d.id, d.name, d.specialty, d.years_experience, d.contact);
    fclose(file);
    
    printf("Doctor Added Successfully!\n");
    pause_exec();
}

void view_all_doctors() {
    FILE *file = fopen(DOCTOR_FILE, "r");
    if (!file) {
        printf("No doctors record found.\n");
        pause_exec();
        return;
    }

    Doctor d;
    char buffer[MAX_BUFFER];
    clear_screen();
    printf("=== ALL DOCTORS ===\n");
    printf("%-5s %-20s %-20s %-10s %-15s\n", "ID", "Name", "Specialty", "Exp", "Contact");
    printf("----------------------------------------------------------------------\n");

    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d|%[^|]|%[^|]|%d|%[^\n]", &d.id, d.name, d.specialty, &d.years_experience, d.contact);
        printf("%-5d %-20s %-20s %-10d %-15s\n", d.id, d.name, d.specialty, d.years_experience, d.contact);
    }
    fclose(file);
    pause_exec();
}
