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

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
char calculateGrade(float marks);

int main()
{
    int choice = 0;

    while (choice != 6)
    {
        printf("\n=====================================");
        printf("\n   STUDENT MANAGEMENT SYSTEM");
        printf("\n=====================================");

        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");

        printf("\n\nEnter Your Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            printf("\nProgram Closed Successfully.\n");
            break;

        default:
            printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}

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

void addStudent()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");

    if (fp == NULL)
    {
        printf("\nFile Error!\n");
        return;
    }

    printf("\nEnter Roll Number : ");
    scanf("%d", &s.roll);

    printf("Enter Student Name : ");
    scanf(" %[^\n]", s.name);

    printf("Enter Student Marks : ");
    scanf("%f", &s.marks);

    s.grade = calculateGrade(s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);

    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

void displayStudents()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n=====================================");
    printf("\n        STUDENT RECORDS");
    printf("\n=====================================");

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        printf("\nRoll Number : %d", s.roll);
        printf("\nName        : %s", s.name);
        printf("\nMarks       : %.2f", s.marks);
        printf("\nGrade       : %c", s.grade);
        printf("\n-------------------------------------");
    }

    fclose(fp);
}

void searchStudent()
{
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Search : ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.roll == roll)
        {
            printf("\nStudent Found!\n");

            printf("Roll Number : %d\n", s.roll);
            printf("Name        : %s\n", s.name);
            printf("Marks       : %.2f\n", s.marks);
            printf("Grade       : %c\n", s.grade);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nStudent Not Found!\n");
    }

    fclose(fp);
}

void updateStudent()
{
    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Update : ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.roll == roll)
        {
            printf("\nEnter New Name : ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks : ");
            scanf("%f", &s.marks);

            s.grade = calculateGrade(s.marks);

            found = 1;
        }

        fwrite(&s, sizeof(struct Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nRecord Updated Successfully!\n");
    else
        printf("\nStudent Not Found!\n");
}

void deleteStudent()
{
    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Delete : ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.roll != roll)
        {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nRecord Deleted Successfully!\n");
    else
        printf("\nStudent Not Found!\n");
}