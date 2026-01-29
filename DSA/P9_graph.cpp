#include <stdio.h>
int graph[10][10], n;
void createGraph()
{
    int i, j;
    printf("Enter Adjacency Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
}
void DFS(int start)
{
    int stack[10], visited[10] = {0};
    int top = -1, i;
    stack[++top] = start;
    visited[start] = 1;
    printf("DFS Traversal: ");
    while (top != -1)
    {
        start = stack[top--];
        printf("%d ", start);
        for (i = n - 1; i >= 0; i--)
        {
            if (graph[start][i] == 1 && visited[i] == 0)
            {
                stack[++top] = i;
                visited[i] = 1;
            }
        }
    }
}

int main()
{
    int start;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    createGraph();
    printf("Enter starting vertex: ");
    scanf("%d", &start);
    DFS(start);
    return 0;
}

