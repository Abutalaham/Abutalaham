#include <stdio.h>
#include <stdlib.h>


struct Employee
{
    char socialSecurityNumber[15];
    char fullName[50];
    char department[30];
    char jobDesignation[30];
    float salary;
    char phoneNumber[15];
};


struct Node
{
    struct Employee data;
    struct Node *prev;
    struct Node *next;
};

struct Node *head = NULL;


struct Node* createNode()
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));

    printf("Enter SSN: ");
    scanf("%s", newNode->data.socialSecurityNumber);

    printf("Enter Name: ");
    scanf(" %[^\n]", newNode->data.fullName);

    printf("Enter Department: ");
    scanf(" %[^\n]", newNode->data.department);

    printf("Enter Designation: ");
    scanf(" %[^\n]", newNode->data.jobDesignation);

    printf("Enter Salary: ");
    scanf("%f", &newNode->data.salary);

    printf("Enter Phone: ");
    scanf("%s", newNode->data.phoneNumber);

    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}


void insertFront()
{
    struct Node *newNode = createNode();

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    printf("Inserted at Front\n");
}


void insertEnd()
{
    struct Node *newNode = createNode();
    struct Node *temp;

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;

    printf("Inserted at End\n");
}


void deleteFront()
{
    struct Node *temp;

    if (head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    temp = head;
    head = head->next;

    if (head != NULL)
        head->prev = NULL;

    free(temp);

    printf("Deleted from Front\n");
}


void deleteEnd()
{
    struct Node *temp;

    if (head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    temp = head;

    if (head->next == NULL)
    {
        free(head);
        head = NULL;
        return;
    }

    while (temp->next != NULL)
        temp = temp->next;

    temp->prev->next = NULL;
    free(temp);

    printf("Deleted from End\n");
}


void display()
{
    struct Node *temp = head;

    if (head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    printf("\nEmployee Details:\n");

    while (temp != NULL)
    {
        printf("\nSSN: %s", temp->data.socialSecurityNumber);
        printf("\nName: %s", temp->data.fullName);
        printf("\nDepartment: %s", temp->data.department);
        printf("\nDesignation: %s", temp->data.jobDesignation);
        printf("\nSalary: %.2f", temp->data.salary);
        printf("\nPhone: %s\n", temp->data.phoneNumber);

        temp = temp->next;
    }
}


int main()
{
    int choice;

    while (1)
    {
        printf("\n1.Insert Front");
        printf("\n2.Insert End");
        printf("\n3.Delete Front");
        printf("\n4.Delete End");
        printf("\n5.Display");
        printf("\n6.Exit");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: insertFront(); break;
            case 2: insertEnd(); break;
            case 3: deleteFront(); break;
            case 4: deleteEnd(); break;
            case 5: display(); break;
            case 6: exit(0);
            default: printf("Invalid Choice\n");
        }
    }

    return 0;
}

