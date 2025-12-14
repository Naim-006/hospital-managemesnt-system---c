#include "hms.h"

void patient_menu() {
    int id;
    clear_screen();
    printf("=== PATIENT PORTAL ===\n");
    printf("Enter Your Patient ID: ");
    scanf("%d", &id);

    // Verify ID
    FILE *file = fopen(PATIENT_FILE, "r");
    if (!file) {
        printf("No patients found.\n");
        return;
    }
    
    Patient p;
    char buffer[MAX_BUFFER];
    int found = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^\n]", 
             &p.id, p.name, &p.age, p.gender, p.contact, p.address, &p.assigned_doctor_id, p.disease);
        if (p.id == id) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("Patient ID not found!\n");
        pause_exec();
        return;
    }

    int choice;
    while(1) {
        clear_screen();
        printf("=== Welcome %s ===\n", p.name);
        printf("1. View My Details\n");
        printf("2. View My Lab Reports\n");
        printf("3. View My Prescriptions\n"); 
        printf("4. Logout\n");
        choice = get_int("Enter Choice: ");

        switch(choice) {
            case 1: view_my_details(id); break;
            case 2: view_my_report(id); break;
            case 3: 
                // Simple implementation inline or new function
                // Let's just do inline read for simplicity as it wasn't strictly in header prototype list but implied
                {
                    FILE *fp = fopen("prescriptions.txt", "r");
                    if (fp) {
                        char buf[MAX_BUFFER];
                        int pat_id, doc_id;
                        char med[MAX_BUFFER];
                        printf("\n--- Prescriptions ---\n");
                        while(fgets(buf, sizeof(buf), fp)) {
                            sscanf(buf, "%d|%d|%[^\n]", &pat_id, &doc_id, med);
                            if (pat_id == id) {
                                printf("Doctor %d: %s\n", doc_id, med);
                            }
                        }
                        fclose(fp);
                    } else {
                        printf("No prescriptions found.\n");
                    }
                    pause_exec();
                }
                break;
            case 4: return;
            default: printf("Invalid Choice!\n");
        }
    }
}

void view_my_details(int patient_id) {
    FILE *file = fopen(PATIENT_FILE, "r");
    Patient p;
    char buffer[MAX_BUFFER];
    
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^\n]", 
             &p.id, p.name, &p.age, p.gender, p.contact, p.address, &p.assigned_doctor_id, p.disease);
        if (p.id == patient_id) {
            printf("\nName: %s\nAge: %d\nGender: %s\nContact: %s\nAddress: %s\nAssigned Doc ID: %d\nDisease: %s\n",
                p.name, p.age, p.gender, p.contact, p.address, p.assigned_doctor_id, p.disease);
            break;
        }
    }
    fclose(file);
    pause_exec();
}

void view_my_report(int patient_id) {
    FILE *file = fopen(LAB_FILE, "r");
    if (!file) {
        printf("No lab reports found.\n");
        pause_exec();
        return;
    }
    
    char buffer[MAX_BUFFER];
    int p_id;
    char report[MAX_BUFFER], date[20];
    int found = 0;

    printf("\n--- Lab Reports ---\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d|%[^|]|%[^\n]", &p_id, report, date);
        if (p_id == patient_id) {
            printf("Date: %s | Report: %s\n", date, report);
            found = 1;
        }
    }
    fclose(file);
    
    if (!found) printf("No reports for you.\n");
    pause_exec();
}
