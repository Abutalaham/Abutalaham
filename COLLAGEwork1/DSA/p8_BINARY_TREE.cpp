#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};
struct Node *root = NULL;	
struct Node* createNode(int value)
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
struct Node* insert(struct Node *root, int value)
{
    if (root == NULL)
        return createNode(value);
    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);
    return root;
}
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
void preorder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(struct Node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}
int search(struct Node *root, int key)
{
    if (root == NULL)
        return 0;
    if (key == root->data)
        return 1;
    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}
int main()
{
    int choice, n, value, key;

    while (1)
    {
        printf("\n\n1.Insert");
        printf("\n2.Inorder");
        printf("\n3.Preorder");
        printf("\n4.Postorder");
        printf("\n5.Search");
        printf("\n6.Exit");
        printf("\nEnter Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                printf("How many nodes: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++)
                {
                    printf("Enter value: ");
                    scanf("%d", &value);
                    root = insert(root, value);
                }
                break;
            case 2:
                printf("Inorder Traversal: ");
                inorder(root);
                break;
            case 3:
                printf("Preorder Traversal: ");
                preorder(root);
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorder(root);
                break;
            case 5:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(root, key))
                    printf("Key Found");
                else
                    printf("Key Not Found");
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid Choice");
        }
    }
    return 0;
}

