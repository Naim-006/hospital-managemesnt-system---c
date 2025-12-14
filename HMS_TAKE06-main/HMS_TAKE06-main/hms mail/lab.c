#include "hms.h"

void lab_menu() {
    int choice;
    while(1) {
        clear_screen();
        printf("=== LAB PORTAL ===\n");
        printf("1. Add Lab Report\n");
        printf("2. Back\n");
        choice = get_int("Enter Choice: ");

        switch(choice) {
            case 1: add_lab_report(); break;
            case 2: return;
            default: printf("Invalid Choice!\n");
        }
    }
}

void add_lab_report() {
    FILE *file = fopen(LAB_FILE, "a");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    
    int p_id;
    char report[MAX_BUFFER];
    char date[20];

    printf("Enter Patient ID: ");
    scanf("%d", &p_id);
    
    get_string("Enter Report Details: ", report, MAX_BUFFER);
    get_string("Enter Date (DD/MM/YYYY): ", date, 20);
    
    fprintf(file, "%d|%s|%s\n", p_id, report, date);
    fclose(file);
    
    printf("Report Added!\n");
    pause_exec();
}
