#include "hms.h"

// Main Menu
int main() {
    int choice;
    
    while(1) {
        clear_screen();
        printf("==========================================\n");
        printf("   HOSPITAL MANAGEMENT SYSTEM (HMS)       \n");
        printf("        Team: UpSideDown                  \n");
        printf("==========================================\n");
        printf("1. Reception Portal\n");
        printf("2. Doctor Portal\n");
        printf("3. Patient Portal\n");
        printf("4. Lab Portal\n");
        printf("5. Admin Portal\n");
        printf("6. Find Doctor\n");
        printf("7. Give Feedback\n");
        printf("8. Exit\n");
        printf("==========================================\n");
        
        choice = get_int("Enter Choice: ");

        switch(choice) {
            case 1: reception_menu(); break;
            case 2: doctor_menu(); break; // Needs implementation of login inside
            case 3: patient_menu(); break;
            case 4: lab_menu(); break;
            case 5: admin_login(); break;
            case 6: find_doctor_menu(); break;
            case 7: give_feedback(); break;
            case 8: 
                printf("Thank you for using HMS.\n");
                printf("Credits:\n");
                printf("Ajmine - Reception\nNaim - Doctor/Patient\nZihad - Lab/Feedback\nSadman - Admin\nLimon - Find Doctor\n");
                return 0;
            default: printf("Invalid Choice. Try again.\n");
        }
    }
    return 0;
}
