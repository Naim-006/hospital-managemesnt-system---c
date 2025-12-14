#include "hms.h"


void developer() {

    clear_screen();
    
      printf("\n|-------------------------------------------------|\n");
printf("|                                                |\n");
printf("|                 \033[1;36mTeam UpSideDown\033[0m                |\n");  
printf("|                                                |\n");
printf("|   Project : \033[1;33mHospital Management System (HMS)\033[0m   |\n"); 
printf("|                                                |\n");
printf("|------------------------------------------------|\n\n\n");

printf(" # Team Members:\n\n");

printf("   - Member 1\033[1;32m: Naim Hossain\033[0m (ID: 252-15-178)\n");  
printf("                           -Project Coordinator and developer\n\n");

printf("   - Member 2\033[1;32m: Md Ajmine Adil Sadik\033[0m (ID: 252-15-172)\n");
printf("                           -Project Structurer and developer\n\n");

printf("   - Member 3\033[1;32m: Sadman Sakib Mahi\033[0m (ID: 252-15-102)\n");
printf("                           - Developer\n\n");

printf("   - Member 4\033[1;32m: Md Zihad Hasan\033[0m (ID: 252-15-436)\n");
printf("                           - Developer\n\n");

printf("   - Member 5\033[1;32m: Shahriar Ahmmed Limon\033[0m (ID: 252-15-351)\n");
printf("                           - Developer\n\n");

printf("\n____________________________Thank You ! ____________________________\n");


       
          pause_exec();
        return ;
  
}

// Main Menu
int main() {
    int choice;
    
    while(1) {
        clear_screen();
        
    printf("\n+------------------------------------------------------------+\n");
    printf("|                                                            |\n");
    printf("| \033[1;33m           WELCOME TO HOSPITAL MANAGEMENT SYSTEM           \033[0m|\n");
    printf("| \033[1;36m                  TEAM: UPSIDEDOWN                         \033[0m|\n");
    printf("|                                                            |\n");
    printf("+------------------------------------------------------------+\n\n");

    printf("+------------------------------------------------------------+\n");
    printf("|                       MAIN MENU                            |\n");
    printf("+------------------------------------------------------------+\n");
    printf("|                                                            |\n");
    printf("| 1. Reception Portal                                        |\n");
    printf("| 2. Patient Portal                                          |\n");
    printf("|                                                            |\n");
    printf("| 3. Doctor Portal                                           |\n");
    printf("| 4. Lab Portal                                              |\n");
    printf("| 5. Admin Portal                                            |\n");
    printf("|                                                            |\n");
    printf("| 6. Find Doctor                                             |\n");
    printf("| 7. Feedback                                                |\n");
    printf("|                                                            |\n");
    printf("| 8. Team Details                                            |\n");
    printf("| 9. Exit System                                             |\n");
    printf("|                                                            |\n");
    printf("+------------------------------------------------------------+\n\n");

        
        choice = get_int("Enter Choice: ");

        switch(choice) {
            case 1: reception_menu(); break;
            case 2: patient_menu(); break;
            case 3: doctor_menu(); break;
            case 4: lab_menu(); break;
            case 5: admin_login(); break;
            case 6: find_doctor_menu(); break;
            case 7: give_feedback(); break;
            case 8: developer();break;
            case 9: 
                clear_screen();
                printf("Thank you for using this system!\n");
                exit(0);
               
            default: printf("Invalid Choice. Try again.\n");
        }
    }
    return 0;
}
