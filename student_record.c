// Assignment #2 by Dylan Phillips T00750910 
// COMP 2131

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Intitalizing defines for max lengths.
#define MAX_ID_LENGTH 15
#define MAX_NAME_LENGTH 60
#define MAX_EMAIL_LENGTH 60
#define MAX_COURSE_LENGTH 30
#define MAX_GRADE_LENGTH 6

// creating a structure for variables. 
struct Record {
    char student_id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char course_id[MAX_COURSE_LENGTH];
    char grade[MAX_GRADE_LENGTH];
};

// creating the binary file to hold records. 
void createRecord(FILE *file) {
    struct Record student;

    // user inputs information. 
    printf("Enter Student ID: ");
    scanf("%s", student.student_id);

    printf("Enter Student Name: ");
    scanf("%s", student.name);

    printf("Enter Email ID: ");
    scanf("%s", student.email);

    printf("Enter Course ID: ");
    scanf("%s", student.course_id);

    printf("Enter Grade: ");
    scanf("%s", student.grade);

    fwrite(&student, sizeof(struct Record), 1, file);

    printf("The Record has been loaded.\n");
}

// Displays records that have been saved in the file. 
void displayRecord(FILE *file) {
    struct Record student;

    rewind(file);

    printf("\nStudent Records:\n");

    while (fread(&student, sizeof(struct Record), 1, file) == 1) {
        printf("Student ID: %s\n", student.student_id);
        printf("Name: %s\n", student.name);
        printf("Email ID: %s\n", student.email);
        printf("Course ID: %s\n", student.course_id);
        printf("Grade: %s\n", student.grade);
        printf("-----------------------------\n");
    }
}

// Searches for a specific file of a record by a given name. 
void specificFile(FILE *file) {
    char findName[MAX_NAME_LENGTH];
    struct Record student;

    printf("Please enter the name of the student you wish to the search for: ");
    scanf("%s", findName);

    rewind(file);

    while (fread(&student, sizeof(struct Record), 1, file) == 1) {
        if (strcmp(student.name, findName) == 0) {
            printf("Record found:\n");
            printf("Student ID: %s\n", student.student_id);
            printf("Name: %s\n", student.name);
            printf("Email ID: %s\n", student.email);
            printf("Course ID: %s\n", student.course_id);
            printf("Grade: %s\n", student.grade);
            return;
        }
    }

    printf("The record has not been found.\n");
}

// Searches for file you wish to update and allows user to change information. 
void updateFile(FILE *file) {
    char findName[MAX_NAME_LENGTH];
    struct Record student;

    printf("Enter Student Name you wish to update: ");
    scanf("%s", findName);

    rewind(file);

    while (fread(&student, sizeof(struct Record), 1, file) == 1) {
        if (strcmp(student.name, findName) == 0) {
            printf(" The record has been found:\n");
            printf("Student ID: %s\n", student.student_id);
            printf("Enter updated information:\n");

            printf("Enter Students name: "); 
            scanf("%s", student.name); 
            
            printf("Enter Email ID: ");
            scanf("%s", student.email);

            printf("Enter Course ID: ");
            scanf("%s", student.course_id);

            printf("Enter Grade: ");
            scanf("%s", student.grade);

            fseek(file, -sizeof(struct Record), SEEK_CUR);
            fwrite(&student, sizeof(struct Record), 1, file);

            printf("Update successful.\n");
            return;
        }
    }

    printf("Record has not been found.\n");
}

// Deletes Records by name. 
void deleteRecord(FILE *file) {
    char findName[MAX_NAME_LENGTH];
    struct Record student;

    printf("Enter Student Name of the record you wish to delete: ");
    scanf("%s", findName);

    FILE *tempFile = fopen("temp.dat", "wb");

    int recordDeleted = 0;  

    rewind(file);

    while (fread(&student, sizeof(struct Record), 1, file) == 1) {
        if (strcmp(student.name, findName) != 0) {
            fwrite(&student, sizeof(struct Record), 1, tempFile);
        } else {
            printf("Record deleted successfully.\n");
            recordDeleted = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("student_records.dat");
    rename("temp.dat", "student_records.dat");

    if (!recordDeleted) {
        printf("Record has not been found to delete.\n");
    }
}

int main() {
    FILE *file;
    int decision;

    // opening file. 
    file = fopen("student_records.dat", "ab+");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Main Menu. 
    while (1) {
        printf("Main Menu\n");
        printf("\n1. Create the Binary File\n");
        printf("2. Display contents of the File\n");
        printf("3. Seek a specific record\n");
        printf("4. Update the contents of a record\n");
        printf("5. Delete a record for a specific name\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &decision);

        // switch case on what you would like to choose from the main menu. 
        switch (decision) {
            case 1:
                createRecord(file);
                break;
            case 2:
                displayRecord(file);
                break;
            case 3:
                specificFile(file);
                break;
            case 4:
                updateFile(file);
                break;
            case 5:
                deleteRecord(file);
                break;
            case 6:
                printf("You are now exiiting the program.\n");
                fclose(file);
                exit(0);
            default:
                printf("Not a valid choice. Please enter either 1,2,3,4,5,6.\n");
        }
    }

    return 0;
}
