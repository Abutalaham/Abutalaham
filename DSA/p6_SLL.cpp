#include <stdio.h>
#include <stdlib.h>

/* Student Structure */
struct student
{
    char usn[15];
    char name[50];
    char programme[50];
    int sem;
    char phno[15];

    struct student *next;
};

struct student *head = NULL;

/* Create New Node */
struct student* createNode()
{
    struct student *newNode;

    newNode = (struct student*)malloc(sizeof(struct student));

    printf("Enter USN: ");
    scanf("%s", newNode->usn);

    printf("Enter Name: ");
    scanf(" %[^\n]", newNode->name);

    printf("Enter Programme: ");
    scanf(" %[^\n]", newNode->programme);

    printf("Enter Semester: ");
    scanf("%d", &newNode->sem);

    printf("Enter Phone No: ");
    scanf("%s", newNode->phno);

    newNode->next = NULL;

    return newNode;
}

/* Insert at Front */
void insertFront()
{
    struct student *newNode = createNode();

    newNode->next = head;
    head = newNode;

    printf("Inserted at Front\n");
}

/* Insert at End */
void insertEnd()
{
    struct student *newNode = createNode();
    struct student *temp;

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;

    printf("Inserted at End\n");
}

/* Delete from Front */
void deleteFront()
{
    struct student *temp;

    if (head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    temp = head;
    head = head->next;
    free(temp);

    printf("Deleted from Front\n");
}

/* Delete from End */
void deleteEnd()
{
    struct student *temp, *prev;

    if (head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    if (head->next == NULL)
    {
        free(head);
        head = NULL;
        printf("Deleted from End\n");
        return;
    }

    temp = head;
    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }

    prev->next = NULL;
    free(temp);

    printf("Deleted from End\n");
}

/* Display List */
void display()
{
    struct student *temp = head;

    if (head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    printf("\nStudent Details:\n");

    while (temp != NULL)
    {
        printf("\nUSN: %s", temp->usn);
        printf("\nName: %s", temp->name);
        printf("\nProgramme: %s", temp->programme);
        printf("\nSemester: %d", temp->sem);
        printf("\nPhone: %s\n", temp->phno);

        temp = temp->next;
    }
}

/* Main Function */
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
            case 6: return 0;
            default: printf("Invalid Choice\n");
        }
    }
}

