#include "hms.h"

void reception_menu() {
    int choice;
    while(1) {
        clear_screen();
        printf("=== RECEPTION PORTAL ===\n");
        printf("1. Register New Patient\n");
        printf("2. View All Patients\n");
        printf("3. Book Appointment (Assign Doctor)\n");
        printf("4. Back to Main Menu\n");
        choice = get_int("Enter Choice: ");

        switch(choice) {
            case 1: add_patient(); break;
            case 2: view_patients(); break;
            case 3: book_appointment(); break;
            case 4: return;
            default: printf("Invalid Choice!\n");
        }
    }
}

void add_patient() {
    Patient p;
    FILE *file = fopen(PATIENT_FILE, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    p.id = get_next_id(PATIENT_FILE);
    printf("Registering Patient ID: %d\n", p.id);
    
    get_string("Enter Name: ", p.name, MAX_NAME);
    p.age = get_int("Enter Age: ");
    get_string("Enter Gender: ", p.gender, 10);
    get_string("Enter Contact: ", p.contact, 20);
    get_string("Enter Address: ", p.address, 100);
    get_string("Enter Disease/Symptoms: ", p.disease, MAX_DISEASE);
    p.assigned_doctor_id = 0; // Initially no doctor assigned

    fprintf(file, "%d|%s|%d|%s|%s|%s|%d|%s\n", p.id, p.name, p.age, p.gender, p.contact, p.address, p.assigned_doctor_id, p.disease);
    fclose(file);
    
    printf("Patient Registered Successfully!\n");
    pause_exec();
}

void view_patients() {
    FILE *file = fopen(PATIENT_FILE, "r");
    if (!file) {
        printf("No patients found.\n");
        pause_exec();
        return;
    }

    Patient p;
    char buffer[MAX_BUFFER];
    clear_screen();
    printf("=== ALL PATIENTS ===\n");
    printf("%-5s %-20s %-5s %-10s %-15s\n", "ID", "Name", "Age", "Gender", "Disease");
    printf("------------------------------------------------------------\n");

    while (fgets(buffer, sizeof(buffer), file)) {
        // Parsing the pipe-delimited format
        // Note: sscanf with %[^|] reads until pipe.
        sscanf(buffer, "%d|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^\n]", 
            &p.id, p.name, &p.age, p.gender, p.contact, p.address, &p.assigned_doctor_id, p.disease);
        
        printf("%-5d %-20s %-5d %-10s %-15s\n", p.id, p.name, p.age, p.gender, p.disease);
    }
    fclose(file);
    pause_exec();
}

void book_appointment() {

    int p_id, d_id;
    int found = 0;

    printf("Enter Patient ID to assign doctor: ");
    scanf("%d", &p_id);
    getchar();   // clear newline

    FILE *file = fopen(PATIENT_FILE, "r");
    if (!file) {
        printf("No patients found.\n");
        pause_exec();
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("File error.\n");
        fclose(file);
        return;
    }

    char buffer[MAX_BUFFER];
    Patient p;

    while (fgets(buffer, sizeof(buffer), file)) {

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
            if (p.id == p_id) {
                found = 1;

                printf("Current Doctor ID: %d\n", p.assigned_doctor_id);
                display_doctor_list();

                d_id = get_int("Enter New Doctor ID to assign: ");
                p.assigned_doctor_id = d_id;

                printf("Doctor assigned successfully!\n");
            }

            /* write updated or unchanged record */
            fprintf(temp, "%d|%s|%d|%s|%s|%s|%d|%s\n",
                    p.id,
                    p.name,
                    p.age,
                    p.gender,
                    p.contact,
                    p.address,
                    p.assigned_doctor_id,
                    p.disease);
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove(PATIENT_FILE);
        rename("temp.txt", PATIENT_FILE);
    } else {
        remove("temp.txt");
        printf("Patient not found.\n");
    }

    pause_exec();
}
