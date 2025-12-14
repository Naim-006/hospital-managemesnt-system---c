#include "hms.h"

// Clear the console screen
void clear_screen() {
    system("cls");
}

// Pause execution until user presses a key
void pause_exec() {
    printf("\nPress any key to continue...");
    getch();
}

// Safe string input
void get_string(char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    fflush(stdin); // Be careful with this, but for simple C project it's often used. better: while(getchar()!='\n'); if needed.
    // For this level of project, gets or scanf with %[^\n] is common but fgets is safer.
    // We will use fgets and remove newline.
    
    // Quick flush implementation if previous input left newline
    // int c; while ((c = getchar()) != '\n' && c != EOF); // This might block if buffer is empty
    
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove trailing newline
}

// Safe integer input
int get_int(char *prompt) {
    int value;
    printf("%s", prompt);
    scanf("%d", &value);
    
    // Clear input buffer after number read to prevent skipping next string input
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    return value;
}

// generate simple auto-increment ID based on lines or specific logic
// For simplicity, we can read the last ID from file or count lines.
// Here is a simple implementation: reads file, finds max ID.
int get_next_id(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return 1;

    int max_id = 0;
    int id;
    char buffer[MAX_BUFFER];

    // Assuming format: ID|Name|... 
    // We scan just the ID.
    // This depends on how we store data. Let's assume ID is first int.
    
    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%d", &id);
        if (id > max_id) max_id = id;
    }

    fclose(file);
    return max_id + 1;
}
