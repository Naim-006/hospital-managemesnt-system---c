#include "hms.h"

void patient_menu() {

    int id;
    clear_screen();
    printf("\n===============\033[1;32m PATIENT PORTAL \033[0m===============\n\n");
    printf("Enter Your Patient ID: ");
    scanf("%d", &id);

    FILE *file = fopen(PATIENT_FILE, "r");
    if (!file) {
        printf("No patients found.\n");
        pause_exec();
        return;
    }

    Patient p;
    int found = 0;

    while (fscanf(file,
        "%d|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^\n]\n",
        &p.id, p.name, &p.age, p.gender,
        p.contact, p.address,
        &p.assigned_doctor_id, p.disease) == 8)
    {
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
    while (1) {
        clear_screen();
        printf("\n===============\033[1;32m %s, welcome to PATIENT PORTAL!\033[0m===============\n\n", p.name);
        printf("1. View My Details\n");
        printf("2. View My Lab Reports\n");
        printf("3. View My Prescriptions\n");
        printf("4. My Appointments\n");
        printf("5. Logout\n");

        choice = get_int("Enter Choice: ");

        switch (choice) {
            case 1: view_my_details(id); break;
            case 2: view_my_report(id); break;
            case 3: view_my_prescriptions(id); break;
            case 4: view_my_appointments(id); break;
            case 5: return;
            default: printf("Invalid Choice!\n");
        }
    }
}


void view_my_details(int patient_id) {

    FILE *file = fopen(PATIENT_FILE, "r");
    if (!file) return;

    Patient p;

    while (fscanf(file,
        "%d|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^\n]\n",
        &p.id, p.name, &p.age, p.gender,
        p.contact, p.address,
        &p.assigned_doctor_id, p.disease) == 8)
    {
        if (p.id == patient_id) {
            printf("\nName: %s\nAge: %d\nGender: %s\nContact: %s\nAddress: %s\nAssigned Doctor ID: %d\nDisease: %s\n",
                   p.name, p.age, p.gender,
                   p.contact, p.address,
                   p.assigned_doctor_id, p.disease);
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

    int p_id;
    char report[100], date[20];
    int found = 0;

    printf("\n--- Lab Reports ---\n");

    while (fscanf(file, "%d|%[^|]|%[^\n]\n", &p_id, report, date) == 3) {
        if (p_id == patient_id) {
            printf("Date: %s | Report: %s\n", date, report);
            found = 1;
        }
    }

    fclose(file);

    if (!found)
        printf("No reports for you.\n");

    pause_exec();
}


void view_my_prescriptions(int patient_id) {

    FILE *fp = fopen("prescriptions.txt", "r");
    if (!fp) {
        printf("No prescriptions found.\n");
        pause_exec();
        return;
    }

    int p_id, d_id;
    char medicine[200];
    int found = 0;

    printf("\n--- My Prescriptions ---\n");

    while (fscanf(fp, "%d|%d|%[^\n]\n", &p_id, &d_id, medicine) == 3) {
        if (p_id == patient_id) {
            printf("Doctor %d : %s\n", d_id, medicine);
            found = 1;
        }
    }

    fclose(fp);

    if (!found)
        printf("No prescriptions for you.\n");

    pause_exec();
}

void view_my_appointments(int patient_id) {

    FILE *pfile = fopen(PATIENT_FILE, "r");
    if (!pfile) {
        printf("No patient records found.\n");
        pause_exec();
        return;
    }

    Patient p;
    int doctor_id = 0;

    while (fscanf(pfile,
        "%d|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^\n]\n",
        &p.id, p.name, &p.age, p.gender,
        p.contact, p.address,
        &p.assigned_doctor_id, p.disease) == 8)
    {
        if (p.id == patient_id) {
            doctor_id = p.assigned_doctor_id;
            break;
        }
    }
    fclose(pfile);

    if (doctor_id == 0) {
        printf("You have no assigned doctor yet.\n");
        pause_exec();
        return;
    }

    FILE *dfile = fopen(DOCTOR_FILE, "r");
    if (!dfile) {
        pause_exec();
        return;
    }

    Doctor d;
    int found = 0;

    while (fscanf(dfile,
        "%d|%[^|]|%[^|]|%d|%[^\n]\n",
        &d.id, d.name, d.specialty,
        &d.years_experience, d.contact) == 5)
    {
        if (d.id == doctor_id) {
            printf("\n--- My Appointment ---\n");
            printf("Doctor Name: %s\nSpecialty: %s\nExperience: %d years\nContact: %s\n",
                   d.name, d.specialty, d.years_experience, d.contact);
            found = 1;
            break;
        }
    }

    fclose(dfile);

    if (!found)
        printf("Doctor not found.\n");

    pause_exec();
}
