#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 50
#define NAME_LENGTH 50

typedef struct {
    int id;
    char name[NAME_LENGTH];
    float midterm;
    float final_exam;
    float total;
    char grade;
} Student;

char calculate_grade(float score) {
    if (score >= 90.0f) return 'A';
    if (score >= 80.0f) return 'B';
    if (score >= 70.0f) return 'C';
    if (score >= 60.0f) return 'D';
    return 'F';
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    do {
        printf("\n=========================================\n");
        printf("    STUDENT GRADE MANAGEMENT SYSTEM      \n");
        printf("=========================================\n");
        printf("1. Add New Student Record\n");
        printf("2. View All Student Records\n");
        printf("3. View Class Average & Performance\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                if (count >= MAX_STUDENTS) {
                    printf("\n[Error] Student database is full!\n");
                    break;
                }

                printf("\nEnter Student ID: ");
                scanf("%d", &students[count].id);

                printf("Enter Student Name: ");
                scanf(" %[^\n]", students[count].name);

                printf("Enter Midterm Score (0 - 40): ");
                scanf("%f", &students[count].midterm);

                printf("Enter Final Exam Score (0 - 60): ");
                scanf("%f", &students[count].final_exam);

                students[count].total = students[count].midterm + students[count].final_exam;
                students[count].grade = calculate_grade(students[count].total);

                printf("\n>>> Student record added successfully!\n");
                count++;
                break;

            case 2:
                if (count == 0) {
                    printf("\nNo student records available.\n");
                    break;
                }

                printf("\n----------------------------------------------------------------------\n");
                printf("%-8s %-20s %-10s %-10s %-10s %-6s\n", "ID", "Name", "Midterm", "Final", "Total", "Grade");
                printf("----------------------------------------------------------------------\n");
                for (int i = 0; i < count; i++) {
                    printf("%-8d %-20s %-10.2f %-10.2f %-10.2f %-6c\n",
                           students[i].id,
                           students[i].name,
                           students[i].midterm,
                           students[i].final_exam,
                           students[i].total,
                           students[i].grade);
                }
                printf("----------------------------------------------------------------------\n");
                break;

            case 3:
                if (count == 0) {
                    printf("\nNo records available to calculate statistics.\n");
                    break;
                }

                float sum = 0.0f;
                float highest = students[0].total;
                float lowest = students[0].total;

                for (int i = 0; i < count; i++) {
                    sum += students[i].total;
                    if (students[i].total > highest) highest = students[i].total;
                    if (students[i].total < lowest) lowest = students[i].total;
                }

                printf("\n------- CLASS PERFORMANCE REPORT -------\n");
                printf("Total Students Enrolled : %d\n", count);
                printf("Class Average Score     : %.2f / 100\n", sum / count);
                printf("Highest Score           : %.2f\n", highest);
                printf("Lowest Score            : %.2f\n", lowest);
                printf("----------------------------------------\n");
                break;

            case 4:
                printf("\nExiting Student Management System.\n");
                break;

            default:
                printf("\n[Error] Invalid choice! Please select 1 to 4.\n");
                break;
        }

    } while (choice != 4);

    return 0;
}