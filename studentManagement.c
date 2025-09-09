#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int ID;


typedef struct Student {
    int id;
    char name[20];
    float grade;
    struct Student *left;
    struct Student *right;
} Student;

//check if id is unique
int idExists(Student *head, int id){
    if (head == NULL) return 0;
    if (head->id == id) return 1;
    if (id < head->id) return idExists(head->left, id);
    else return idExists(head->right, id);
}
//creating Student
Student *createStudent(char *name, float grade){
    Student *student = (Student *)malloc(sizeof(Student));
    if (student != NULL){
        student->id = ID;
        strcpy(student->name, name);
        student->grade = grade;
        student->left = student->right = NULL;
    }
    return student;
}
//adding student to BST
void addStudent(Student **head, char *name, float grade){
    if (*head == NULL){
        *head = createStudent(name, grade);
        printf("student added succesfuly!!\n");
        return;
    }
    if (ID < (*head)->id){
        addStudent(&((*head)->left), name, grade);
    }
    else{
        addStudent(&((*head)->right), name, grade);
    }
}
//
//Display all student in prefix order
void inorder(Student *head){
    if (head == NULL) return;
    inorder(head->left);
    printf("id: %d : %s -> %.2f\n", head->id, head->name, head->grade);
    inorder(head->right);
}
//find smallest student
Student *findMinID(Student *head){
    Student *current = head;
    while(current->left != NULL){
        current = current->left;
    }
    return current;
}
//remove student by id
Student *deleteStudent(Student *head, int id){
    if (head == NULL){
        return head;
    }
    //if student in the left
    if (id < head->id){
        head->left = deleteStudent(head->left, id);
    }
    //if student in the right
    else if (id > head->id){
        head->right = deleteStudent(head->right, id);
    } 
    //if student found
    else{
        //if student have no children
        if(head->left == NULL && head->right == NULL){
            free(head);
            head = NULL;
        }
        //if student have one child
        else{
            if (head->right == NULL){
                Student *temp = head;
                head = head->left;
                free(temp);
            }
            else if (head->left == NULL){
                Student *temp = head;
                head = head->right;
                free(temp);
            }
            //if student have two childs
            else{
                Student *temp = findMinID(head->right);
                head->id = temp->id;
                strcpy(head->name, temp->name);
                head->grade = temp->grade;
                head->right = deleteStudent(head->right, temp->id);
            }
        }
    }
    return head;
}
//search for student by id;
void searchStudent(Student *head, int id){
    if (head == NULL){
        printf("Student Not Found!!\n");
        return;
    }
    if (id > head->id){
        searchStudent(head->right, id);
    }
    else if (id < head->id){
        searchStudent(head->left, id);
    }
    else {
        printf("%d: %s -> %f\n", head->id, head->name, head->grade);
        return;
    }
}
//count Student
int countStudents(Student *head){
    if (head == NULL) return 0;
    return 1 + countStudents(head->right) + countStudents(head->left);
}

int main(){
    Student *head = NULL;
    int id;
    char name[20];
    float grade;
    int option;
    printf("===== Student Management System =====\n");
    printf("1. Add Student\n2. Search Student\n3. Display All Students\n4. Delete Student\n5. Count Students\n0. Exit\n");
    printf("====================================\n");
    while (1){
        printf("insert youre option: ");
        scanf("%d", &option);
        switch (option){
            case 1:
                int randID;
                do{
                    randID = rand() % 100 + 1;
                } while (idExists(head, randID));
                ID = randID;
                printf("insert Student name: ");
                scanf("%s", name);
                printf("Student Grade: ");
                scanf("%f", &grade);
                addStudent(&head, name, grade);
                break;
            case 2:
                printf("insert Student id: ");
                scanf("%d", &id);
                searchStudent(head, id);
                break;
            case 3:
                inorder(head);
                break;
            case 4:
                printf("insert Student Id: ");
                scanf("%d", &id);
                deleteStudent(head, id);
                printf("student deleted!!\n");
                break;
            case 5:
                int count = countStudents(head);
                printf("there's %d student in the system!\n", count);
                break;
            case 0:
                return 0;
        }
    }
    return 0;
}