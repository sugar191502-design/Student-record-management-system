
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define FILE_NAME "students.dat"
 
typedef struct Student {
    int rollNo;
    char name[50];
    char course[30];
    int semester;
    float marks;
} Student;
 
typedef struct Node {
    Student data;
    struct Node *next;
} Node;
 
Node *head = NULL;
 
Node *searchStudent(int roll) {
    Node *temp = head;
    while (temp != NULL) {
        if (temp->data.rollNo == roll)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
 
void saveToFile(void) {
    FILE *fp = fopen(FILE_NAME, "wb");
    Node *temp = head;
    if (fp == NULL) {
        printf("Error: unable to save records.\\n");
        return;
    }
    while (temp != NULL) {
        fwrite(&temp->data, sizeof(Student), 1, fp);
        temp = temp->next;
    }
    fclose(fp);
}
 
void loadFromFile(void) {
    FILE *fp = fopen(FILE_NAME, "rb");
    Student s;
    if (fp == NULL) return;
 
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("Memory allocation failed.\\n");
            break;
        }
        newNode->data = s;
        newNode->next = NULL;
 
        if (head == NULL) {
            head = newNode;
        } else {
            Node *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }
    fclose(fp);
}
 
void addStudent(void) {
    Node *newNode, *temp;
    newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\\n");
        return;
    }
 
    printf("Enter Roll Number: ");
    scanf("%d", &newNode->data.rollNo);
 
    if (searchStudent(newNode->data.rollNo) != NULL) {
        printf("Roll number already exists!\\n");
        free(newNode);
        return;
    }
 
    printf("Enter Name: ");
    scanf(" %49[^\\n]", newNode->data.name);
    printf("Enter Course: ");
    scanf(" %29[^\\n]", newNode->data.course);
    printf("Enter Semester: ");
    scanf("%d", &newNode->data.semester);
    printf("Enter Marks: ");
    scanf("%f", &newNode->data.marks);
 
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
    saveToFile();
    printf("Student Added Successfully!\\n");
}
 
void displayStudents(void) {
    Node *temp = head;
    if (temp == NULL) {
        printf("No student records available.\\n");
        return;
    }
    printf("\\n------ STUDENT RECORDS ------\\n");
    while (temp != NULL) {
        printf("Roll Number: %d\\n", temp->data.rollNo);
        printf("Name       : %s\\n", temp->data.name);
        printf("Course     : %s\\n", temp->data.course);
        printf("Semester   : %d\\n", temp->data.semester);
        printf("Marks      : %.2f\\n", temp->data.marks);
        printf("-----------------------------\\n");
        temp = temp->next;
    }
}
 
void searchAndDisplay(void) {
    int roll;
    Node *found;
    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);
    found = searchStudent(roll);
 
    if (found == NULL) {
        printf("Student Not Found!\\n");
    } else {
        printf("\\nRecord Found\\n");
        printf("Roll Number: %d\\n", found->data.rollNo);
        printf("Name       : %s\\n", found->data.name);
        printf("Course     : %s\\n", found->data.course);
        printf("Semester   : %d\\n", found->data.semester);
        printf("Marks      : %.2f\\n", found->data.marks);
    }
}
 
void updateStudent(void) {
    int roll;
    Node *found;
    printf("Enter Roll Number to Update: ");
    scanf("%d", &roll);
    found = searchStudent(roll);
 
    if (found == NULL) {
        printf("Student Not Found!\\n");
        return;
    }
    printf("Enter New Name: ");
    scanf(" %49[^\\n]", found->data.name);
    printf("Enter New Course: ");
    scanf(" %29[^\\n]", found->data.course);
    printf("Enter New Semester: ");
    scanf("%d", &found->data.semester);
    printf("Enter New Marks: ");
    scanf("%f", &found->data.marks);
 
    saveToFile();
    printf("Student Record Updated!\\n");
}
 
void deleteStudent(void) {
    int roll;
    Node *temp = head, *prev = NULL;
    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);
 
    while (temp != NULL && temp->data.rollNo != roll) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Student Not Found!\\n");
        return;
    }
 
    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;
 
    free(temp);
    saveToFile();
    printf("Student Record Deleted!\\n");
}
 
void sortStudents(void) {
    Node *i, *j;
    Student swap;
    if (head == NULL || head->next == NULL) {
        printf("Not enough records to sort.\\n");
        return;
    }
 
    for (i = head; i->next != NULL; i = i->next) {
        for (j = head; j->next != NULL; j = j->next) {
            if (j->data.rollNo > j->next->data.rollNo) {
                swap = j->data;
                j->data = j->next->data;
                j->next->data = swap;
            }
        }
    }
    saveToFile();
    printf("Records Sorted by Roll Number!\\n");
}
 
void freeList(void) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
 
int main(void) {
    int choice;
    loadFromFile();
 
    do {
        printf("\\n====================================\\n");
        printf("    STUDENT RECORD MANAGEMENT SYSTEM\\n");
        printf("====================================\\n");
        printf("1. Add Student\\n");
        printf("2. Display Students\\n");
        printf("3. Search Student\\n");
        printf("4. Update Student\\n");
        printf("5. Delete Student\\n");
        printf("6. Sort Students\\n");
        printf("7. Exit\\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
 
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchAndDisplay(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: sortStudents(); break;
            case 7:
                saveToFile();
                printf("Thank You for Using the System!\\n");
                break;
            default:
                printf("Invalid Choice! Please Try Again.\\n");
        }
    } while (choice != 7);
 
    freeList();
    return 0;
}
