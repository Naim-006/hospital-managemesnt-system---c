#include "hms.h"

void give_feedback() {
    FILE *file = fopen(FEEDBACK_FILE, "a");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    char message[MAX_BUFFER];
    int p_id;
    int choice;
    
    printf("Do you want to provide Patient ID? (1=Yes, 0=No/Anonymous): ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter Patient ID: ");
        scanf("%d", &p_id);
    } else {
        p_id = 0;
    }
    
    get_string("Enter your feedback: ", message, MAX_BUFFER);
    
    fprintf(file, "%d|%s\n", p_id, message);
    fclose(file);
    
    printf("Thank you for your feedback!\n");
    pause_exec();
}

void view_feedback() {
    FILE *file = fopen(FEEDBACK_FILE, "r");
    if (!file) {
        printf("No feedback found.\n");
        pause_exec();
        return;
    }
    
    char buffer[MAX_BUFFER];
    int p_id;
    char msg[MAX_BUFFER];
    
    clear_screen();
    printf("=== FEEDBACK ===\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d|%[^\n]", &p_id, msg);
        if (p_id == 0) printf("Anonymous: %s\n", msg);
        else printf("Patient %d: %s\n", p_id, msg);
    }
    fclose(file);
    pause_exec();
}
