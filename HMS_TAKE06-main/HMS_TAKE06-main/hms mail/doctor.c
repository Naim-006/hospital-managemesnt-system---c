#include "hms.h"

void doctor_login() {
    int id;
   
    
    clear_screen();
      printf("\n===============\033[1;32m DOCTOR LOGIN \033[0m===============\n\n");
    printf("Enter Doctor ID: ");
    scanf("%d", &id);
    doctor_dashboard(id);

   
}

void doctor_dashboard(int id) {
    int choice;
    while(1) {
        clear_screen();
        printf("\n===============\033[1;32m DOCTOR DASHBOARD \033[0m===============\n\n");
        printf("1. View Assigned Patients\n");
        printf("2. Write Prescription\n");
        printf("3. Logout\n");
        choice = get_int("Enter Choice: ");

        switch(choice) {
            case 1: view_assigned_patients(id); break;
            case 2: write_prescription(id); break;
            case 3: return;
            default: printf("Invalid Choice!\n");
        }
    }
}

void doctor_menu() {
    doctor_login();
}

void view_assigned_patients(int doctor_id) {
    FILE *file = fopen(PATIENT_FILE, "r");
    if (!file) {
        printf("No patients found.\n");
        pause_exec();
        return;
    }

    Patient p;
    char buffer[MAX_BUFFER];
    int count = 0;

    clear_screen();
    printf("=== MY PATIENTS ===\n");
    printf("%-5s %-20s %-5s %-10s %-20s\n",
           "ID", "Name", "Age", "Gender", "Disease");
    printf("---------------------------------------------------------------\n");

    while (fgets(buffer, sizeof(buffer), file)) {

        /* validate sscanf */
        if (sscanf(buffer,
            "%d|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^\n]",
            &p.id,
            p.name,
            &p.age,
            p.gender,
            p.contact,
            p.address,
            &p.assigned_doctor_id,
            p.disease) == 8)
        {
            if (p.assigned_doctor_id == doctor_id) {
                printf("%-5d %-20s %-5d %-10s %-20s\n",
                       p.id, p.name, p.age, p.gender, p.disease);
                count++;
            }
        }
    }

    fclose(file);

    if (count == 0) {
        printf("\nNo patients assigned to you yet.\n");
    }

    pause_exec();
}


void write_prescription(int doctor_id) {
    int p_id;
    char medicine[MAX_BUFFER];
    
    view_assigned_patients(doctor_id); 
    
    printf("\nEnter Patient ID to prescribe: ");
    scanf("%d", &p_id);
    
    get_string("Enter Prescription/Medicine: ", medicine, MAX_BUFFER);
    
    FILE *file = fopen("prescriptions.txt", "a");
    fprintf(file, "%d|%d|%s\n", p_id, doctor_id, medicine);
    fclose(file);
    
    printf("Prescription saved.\n");
    pause_exec();
}
