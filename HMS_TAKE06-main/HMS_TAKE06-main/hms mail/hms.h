#ifndef HMS_H
#define HMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // For getch() on Windows
#include <windows.h> // For Sleep() and system()

// Constants
#define MAX_NAME 50
#define MAX_DISEASE 50
#define MAX_BUFFER 200

// File Names
#define PATIENT_FILE "patients.txt"
#define DOCTOR_FILE "doctors.txt"
#define LAB_FILE "labreports.txt"
#define FEEDBACK_FILE "feedback.txt"

// Data Structures

typedef struct {
    int id;
    char name[MAX_NAME];
    int age;
    char gender[10];
    char contact[20];
    char address[100];
    int assigned_doctor_id; // 0 if not assigned
    char disease[MAX_DISEASE];
} Patient;

typedef struct {
    int id;
    char name[MAX_NAME];
    char specialty[MAX_NAME];
    int years_experience;
    char contact[20];
} Doctor;

typedef struct {
    int patient_id;
    char report_details[MAX_BUFFER];
    char date[20];
} LabReport;

typedef struct {
    int patient_id; // 0 for anonymous
    char message[MAX_BUFFER];
} Feedback;

// --- Function Prototypes ---

// Utils
void clear_screen();
void pause_exec();
void get_string(char *prompt, char *buffer, int size);
int get_int(char *prompt);
int get_next_id(char *filename);
void developer();

// Reception Module (Ajmine)
void reception_menu();
void add_patient();
void view_patients();
void book_appointment();

// Doctor Module (Naim)
void doctor_menu();
void doctor_login();
void view_assigned_patients(int doctor_id);
void write_prescription(int doctor_id);
void doctor_dashboard(int id); 

// Patient Module (Naim)
void patient_menu();
void view_my_details(int patient_id);
void view_my_report(int patient_id);
void view_my_appointments(int patient_id);

// Lab Module (Zihad)
void lab_menu();
void add_lab_report();

// Feedback Module (Zihad)
void give_feedback();
void view_feedback(); // Admin uses this too

// Admin Module (Sadman)
void admin_menu();
void admin_login();
void add_doctor();
void view_all_doctors();

// Find Doctor Module (Limon)
void find_doctor_menu();
void search_doctor();
void display_doctor_list();

#endif
