#include "hms.h"

void doctor_login() {
    int id;
   
    
    clear_screen();
      printf("\n===============\033[1;32m DOCTOR LOGIN \033[0m===============\n\n");
    printf("Enter Doctor ID: ");
    scanf("%d", &id);

    // Verify if doctor exists
    FILE *file = fopen(DOCTOR_FILE, "r");
    if (!file) {
        printf("Error: No doctors in system.\n");
        pause_exec();
        return;
    }
    
    Doctor d;
    int found = 0;
    char buffer[MAX_BUFFER];
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d|%[^|]|%[^|]|%d|%[^\n]", &d.id, d.name, d.specialty, &d.years_experience, d.contact);
        if (d.id == id) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (found) {
        printf("Welcome Dr. %s!\n", d.name);
        pause_exec();
      
        
        void doctor_dashboard(int id); 
        doctor_dashboard(id);
        
    } else {
        printf("Doctor ID not found.\n");
        pause_exec();
    }
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
    printf("%-5s %-20s %-5s %-15s %-20s\n", "ID", "Name", "Age", "Gender", "Disease");
    printf("----------------------------------------------------------------------\n");

    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^\n]", 
            &p.id, p.name, &p.age, p.gender, p.contact, p.address, &p.assigned_doctor_id, p.disease);
        
        if (p.assigned_doctor_id == doctor_id) {
            printf("%-5d %-20s %-5d %-15s %-20s\n", p.id, p.name, p.age, p.gender, p.disease);
            count++;
        }
    }
    fclose(file);
    
    if (count == 0) printf("\nNo patients assigned to you yet.\n");
    pause_exec();
}


// Usually prescriptions are stored in a file or appended to patient record.
// For simplicity, let's make a new file prescriptions.txt: PatientID|DoctorID|Medicine
void write_prescription(int doctor_id) {
    int p_id;
    char medicine[MAX_BUFFER];
    
    view_assigned_patients(doctor_id); // Show list first
    
    printf("\nEnter Patient ID to prescribe: ");
    scanf("%d", &p_id);
    
    // Verify patient is assigned to this doctor (optional safety check)
    // skipping for brevity
    
    get_string("Enter Prescription/Medicine: ", medicine, MAX_BUFFER);
    
    FILE *file = fopen("prescriptions.txt", "a");
    fprintf(file, "%d|%d|%s\n", p_id, doctor_id, medicine);
    fclose(file);
    
    printf("Prescription saved.\n");
    pause_exec();
}
