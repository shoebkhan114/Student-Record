#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUBJECTS 5
#define FILE_NAME "students_data.dat"

struct Student {
    int roll;
    char name[50];
    char branch[30];
    int semester;
    float marks[SUBJECTS];
};

// Calculate CGPA (out of 10)
float calculateCGPA(float marks[]) {
    float total = 0;
    for (int i = 0; i < SUBJECTS; i++) {
        total += marks[i];
    }
    return (total / SUBJECTS) / 10;
}

// Add student record
void addStudent() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Roll No: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Branch: ");
    scanf(" %[^\n]", s.branch);
    printf("Enter Semester: ");
    scanf("%d", &s.semester);

    printf("Enter marks (out of 100) for %d subjects:\n", SUBJECTS);
    for (int i = 0; i < SUBJECTS; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%f", &s.marks[i]);
    }

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

// Display student
void displayStudent(struct Student s) {
    printf("\n--------------------------\n");
    printf("Roll No: %d\n", s.roll);
    printf("Name   : %s\n", s.name);
    printf("Branch : %s\n", s.branch);
    printf("Semester: %d\n", s.semester);
    printf("Marks:\n");
    for (int i = 0; i < SUBJECTS; i++) {
        printf("  Subject %d: %.2f\n", i + 1, s.marks[i]);
    }
    printf("CGPA: %.2f\n", calculateCGPA(s.marks));
    printf("--------------------------\n");
}

// Search student by roll
void searchStudent() {
    int roll, found = 0;
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll No to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll == roll) {
            displayStudent(s);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with Roll No %d not found.\n", roll);
    }

    fclose(fp);
}

// List all students
void listAllStudents() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    printf("\n All Student Records:\n");
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        displayStudent(s);
    }

    fclose(fp);
}

// Update student
void updateStudent() {
    int roll, found = 0;
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll No to update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.roll == roll) {
            found = 1;

            printf("Enter new details:\n");
            printf("Name: ");
            scanf(" %[^\n]", s.name);
            printf("Branch: ");
            scanf(" %[^\n]", s.branch);
            printf("Semester: ");
            scanf("%d", &s.semester);
            printf("Enter new marks:\n");
            for (int i = 0; i < SUBJECTS; i++) {
                printf("Subject %d: ", i + 1);
                scanf("%f", &s.marks[i]);
            }

            fseek(fp, -sizeof(s), SEEK_CUR);  // move back to correct position
            fwrite(&s, sizeof(s), 1, fp);
            printf("Student updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Student with Roll No %d not found.\n", roll);
    }

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Portal Menu =====\n");
        printf("1. Add Student\n");
        printf("2. Search Student by Roll\n");
        printf("3. List All Students\n");
        printf("4. Update Student\n");
        printf("5. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: searchStudent(); break;
            case 3: listAllStudents(); break;
            case 4: updateStudent(); break;
            case 5: exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
