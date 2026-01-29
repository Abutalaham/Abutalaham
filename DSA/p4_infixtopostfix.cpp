#include <stdio.h>
#include <ctype.h>
char stack[50];
int top = -1;
void push(char x)
{
    stack[++top] = x;
}
char pop()
{
    return stack[top--];
}
int priority(char x)
{
    if (x == '^') return 3;
    if (x == '*' || x == '/' || x == '%') return 2;
    if (x == '+' || x == '-') return 1;
    return 0;
}
int main()
{
    char infix[50], postfix[50];
    int i, j = 0;
    printf("Enter infix expression: ");
    scanf("%s", infix);
    for (i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];
        if (isalnum(ch))
            postfix[j++] = ch;
        else if (ch == '(')
            push(ch);
        else if (ch == ')')
        {
            while (stack[top] != '(')
                postfix[j++] = pop();
            pop();   
        }
        else
        {
            while (top != -1 && priority(stack[top]) >= priority(ch))
                postfix[j++] = pop();
            push(ch);
        }
    }
    while (top != -1)
        postfix[j++] = pop();
    postfix[j] = '\0';
    printf("Postfix expression: %s", postfix);
    return 0;
}

