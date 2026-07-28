#include<stdio.h>
#define MAX_QUEUE_SIZE 5

char queue[MAX_QUEUE_SIZE];
int front = 0, rear = 0;

void insert()
{
    char item;

    if ((rear + 1) % MAX_QUEUE_SIZE == front)
    {
        printf("Queue Full (Overflow)\n");
        return;
    }

    printf("Enter element: ");
    scanf(" %c", &item);

    rear = (rear + 1) % MAX_QUEUE_SIZE;
    queue[rear] = item;
}

void qdelete()
{
    if (front == rear)
    {
        printf("Queue Empty (Underflow)\n");
        return;
    }

    front = (front + 1) % MAX_QUEUE_SIZE;
    printf("Deleted element: %c\n", queue[front]);
}

void display()
{
    int i;

    if (front == rear)
    {
        printf("Queue Empty\n");
        return;
    }

    printf("Queue elements: ");

    i = (front + 1) % MAX_QUEUE_SIZE;

    while (i != (rear + 1) % MAX_QUEUE_SIZE)
    {
        printf("%c ", queue[i]);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }

    printf("\n");
}

int main()
{
    int ch;

    while (1)
    {
        printf("\n1 Insert\n2 Delete\n3 Display\n4 Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1: insert(); break;
            case 2: qdelete(); break;
            case 3: display(); break;
            case 4: return 0;
            default: printf("Invalid Choice\n");
        }
    }
}

