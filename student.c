#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int roll;
    char name[50];
    float marks;
    char grade;
};

struct Student s;

/* Function Declarations */
char calculateGrade(float marks);
void addStudent();
void saveStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

/* Grade Calculation */
char calculateGrade(float marks)
{
    if (marks >= 90)
        return 'A';
    else if (marks >= 75)
        return 'B';
    else if (marks >= 50)
        return 'C';
    else
        return 'F';
}

/* Add Student */
void addStudent()
{
    printf("\nEnter Roll Number : ");
    scanf("%d", &s.roll);

    printf("Enter Student Name : ");
    scanf(" %[^\n]", s.name);

    printf("Enter Student Marks : ");
    scanf("%f", &s.marks);

    s.grade = calculateGrade(s.marks);

    printf("\nStudent Added In Memory!");
    printf("\nNow Select SAVE DATA Option.\n");
}

/* Save Student Data */
void saveStudent()
{
    FILE *fp;

    fp = fopen("students.csv", "a");

    if (fp == NULL)
    {
        printf("\nFile Error!\n");
        return;
    }

    fprintf(fp, "%d,%s,%.2f,%c\n",
            s.roll,
            s.name,
            s.marks,
            s.grade);

    fclose(fp);

    printf("\nData Saved Successfully!\n");
}

/* Display Students */
void displayStudents()
{
    FILE *fp;
    char line[200];

    fp = fopen("students.csv", "r");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);
}

/* Search Student */
void searchStudent()
{
    FILE *fp;
    char line[200];
    int roll;
    int found = 0;

    fp = fopen("students.csv", "r");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Search : ");
    scanf("%d", &roll);

    while (fgets(line, sizeof(line), fp))
    {
        int fileRoll;

        sscanf(line, "%d,", &fileRoll);

        if (fileRoll == roll)
        {
            printf("\nStudent Found:\n");
            printf("%s", line);

            found = 1;
        }
    }

    if (!found)
    {
        printf("\nStudent Not Found!\n");
    }

    fclose(fp);
}

/* Update Student */
void updateStudent()
{
    FILE *fp, *temp;
    char line[200];
    int roll;
    int found = 0;

    fp = fopen("students.csv", "r");
    temp = fopen("temp.csv", "w");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Update : ");
    scanf("%d", &roll);

    while (fgets(line, sizeof(line), fp))
    {
        int fileRoll;
        char name[50];
        float marks;
        char grade;

        sscanf(line, "%d,%[^,],%f,%c",
               &fileRoll,
               name,
               &marks,
               &grade);

        if (fileRoll == roll)
        {
            printf("\nEnter New Name : ");
            scanf(" %[^\n]", name);

            printf("Enter New Marks : ");
            scanf("%f", &marks);

            grade = calculateGrade(marks);

            fprintf(temp, "%d,%s,%.2f,%c\n",
                    fileRoll,
                    name,
                    marks,
                    grade);

            found = 1;
        }
        else
        {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.csv");
    rename("temp.csv", "students.csv");

    if (found)
        printf("\nRecord Updated Successfully!\n");
    else
        printf("\nStudent Not Found!\n");
}

/* Delete Student */
void deleteStudent()
{
    FILE *fp, *temp;
    char line[200];
    int roll;
    int found = 0;

    fp = fopen("students.csv", "r");
    temp = fopen("temp.csv", "w");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Delete : ");
    scanf("%d", &roll);

    while (fgets(line, sizeof(line), fp))
    {
        int fileRoll;

        sscanf(line, "%d,", &fileRoll);

        if (fileRoll != roll)
        {
            fputs(line, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.csv");
    rename("temp.csv", "students.csv");

    if (found)
        printf("\nRecord Deleted Successfully!\n");
    else
        printf("\nStudent Not Found!\n");
}

/* Main Function */
int main()
{
    int choice;

    while (1)
    {
        printf("\n=====================================");
        printf("\n   STUDENT MANAGEMENT SYSTEM");
        printf("\n=====================================");

        printf("\n1. Add Student");
        printf("\n2. Save Data");
        printf("\n3. Display Students");
        printf("\n4. Search Student");
        printf("\n5. Update Student");
        printf("\n6. Delete Student");
        printf("\n7. Exit");

        printf("\n\nEnter Your Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            saveStudent();
            break;

        case 3:
            displayStudents();
            break;

        case 4:
            searchStudent();
            break;

        case 5:
            updateStudent();
            break;

        case 6:
            deleteStudent();
            break;

        case 7:
            printf("\nProgram Closed Successfully.\n");
            exit(0);

        default:
            printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
