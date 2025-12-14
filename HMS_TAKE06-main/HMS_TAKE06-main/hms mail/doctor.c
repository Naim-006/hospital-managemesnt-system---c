#include "hms.h"

void doctor_login() {
    int id;
    // For simplicity, we trust the doctor just by ID.
    // In real app, we check password.
    
    clear_screen();
    printf("=== DOCTOR LOGIN ===\n");
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
        // Pass ID to menu so we know who is logged in
        // But doctor_menu signature in hms.h is void(), let's make it use a static variable or change signature?
        // Let's change signature or just ask for ID again inside (simpler for this level). 
        // Actually, let's just make doctor_menu take 'void' and we'll ask ID inside specific functions or use a global.
        // Better: We'll just pass ID implicitly or change design slightly.
        // Let's stick to the plan: doctor_menu calls other things. We can make a static global here or just pass it around if I change header.
        // I will change the logic slightly to be cleaner:
        // view_assigned_patients(id);
        
        // Let's implement doctor_menu that takes ID, but header says void.
        // I will modify doctor_menu implementation to take ID, and Update header later if needed?
        // No, I can't easily update header right now without context switch. 
        // I will make doctor_menu() ask for ID again or better, handle the loop inside doctor_login and call helper functions.
        // Wait, the plan said "doctor_login() & doctor_menu()".
        // Let's do this: doctor_login CALLS the actual menu loop passing the ID.
        // But the prototype for doctor_menu is void.
        // Okay, I will implement a local static helper `doctor_dashboard(int id)` and call it.
        
        void doctor_dashboard(int id); // Forward declaration
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
        printf("=== DOCTOR DASHBOARD (ID: %d) ===\n", id);
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
