#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

struct record {
    char SSN[20];
    char name[20];
    char dept[20];
    char salary[20];
};

struct record *hashTable[SIZE] = {NULL};

int hashFunction(char key[])
{
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++)
        sum = sum + key[i];

    return sum % SIZE;
}

void insert()
{
    struct record temp;
    int index, i;

    printf("Enter SSN Name Dept Salary:\n");
    scanf("%s %s %s %s", temp.SSN, temp.name, temp.dept, temp.salary);

    index = hashFunction(temp.SSN);

    // Linear Probing
    i = index;
    while (hashTable[i] != NULL)
    {
        printf("Collision detected at index %d\n", i);
        i = (i + 1) % SIZE;
    }

    hashTable[i] = (struct record *)malloc(sizeof(struct record));
    *hashTable[i] = temp;

    printf("Record inserted at index %d\n", i);
}

void display()
{
    printf("\nINDEX\tSSN\tNAME\tDEPT\tSALARY\n");

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d\t", i);

        if (hashTable[i] != NULL)
            printf("%s\t%s\t%s\t%s\n",
                   hashTable[i]->SSN,
                   hashTable[i]->name,
                   hashTable[i]->dept,
                   hashTable[i]->salary);
        else
            printf("-\n");
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n1.Insert\n2.Display\n3.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: insert();
                    break;

            case 2: display();
                    break;

            case 3: return 0;

            default: printf("Invalid choice\n");
        }
    }
}


