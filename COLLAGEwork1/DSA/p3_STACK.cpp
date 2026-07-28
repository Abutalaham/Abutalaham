#include <stackdio.h>
#define MAX 5

int stack[MAX], top = -1;

void push() {
    int x;
    if (top == MAX - 1)
        printf("Overflow\n");
    else {
        printf("Enter element: ");
        scanf("%d", &x);
        stack[++top] = x;
    }
}

int pop() {
    if (top == -1) {
        printf("Underflow\n");
        return -1;
    }
    return stack[top--];
}

void display() {
    if (top == -1)
        printf("stack empty\n");
    else
        for (int i = top; i >= 0; i--)
            printf("%d\n", stack[i]);
}

void palin() {
    char s[20], r[20];
    int i, t = -1, found = 1;

    printf("Enter string: ");
    scanf("%s", s);

    for (i = 0; s[i]; i++)
        r[++t] = s[i];

    for (i = 0; s[i]; i++)
        if (s[i] != r[t--]) { found = 0; break; }

    printf(found ? "Palindrome\n" : "Not Palindrome\n");
}

int main() {
    int choice, x;
    while (1) {
        printf("\n1.Push 2.Pop 3.Display 4.Palindrome 5.Exit\n");
        scanf("%d", &choice);
        if (choice == 1) push();
        else if (choice == 2 && (x = pop()) != -1) printf("Popped: %d\n", x);
        else if (choice == 3) display();
        else if (choice == 4) palin();
        else if (choice == 5) break;
        else printf("Invalid choice\n");
    }
    return 0;
}

