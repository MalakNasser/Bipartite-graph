#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int N,E;

int stack[MAX];
int top = -1;

void push(int num)
{
    if(top != (MAX - 1))
    {
        top = top + 1;
        stack[top] = num;
    }
}

int pop()
{
    int num;
    if(top != -1)
    {
        num = stack[top];
        top = top - 1;
    }
    return num;
}

int isEmpty_stack( )
{
    if(top == -1)
        return 1;
    else
        return 0;
}

void createAdjMatrix(int Adj[N + 1][N + 1], int arr[][2])
{
    for (int i = 0; i < N + 1; i++)
    {
        for (int j = 0; j < N + 1; j++)
        {
            Adj[i][j] = 0;
        }
    }
    for (int i = 0; i < E; i++)
    {
        int x = arr[i][0];
        int y = arr[i][1];

        Adj[x][y] = 1;
        Adj[y][x] = 1;
    }
}

void DFS(int Adj[N + 1][N + 1], int v, int visited[], int color[])
{
    int neighbours[N];
    int counter;
    push(v);
    while(!isEmpty_stack())
    {
        v = pop();
        counter = 0;
        for(int i = 1; i <= N; i++)
        {
            if(Adj[v][i] == 1)
            {
                neighbours[counter++] = i;
            }
        }
        if(visited[v] == 0)
        {
            visited[v] = 1;
            if(color[v] == 0)
            {
                for(int j = 0; j < counter; j++)
                {
                    if(color[neighbours[j]] != 0)
                    {
                        if(color[neighbours[j]] == 1)
                        {
                            color[v] = 2;
                        }
                        else
                        {
                            color[v] = 1;
                        }
                    }
                }
            }
        }
        for(int i = counter - 1; i >= 0; i--)
        {
            if(visited[neighbours[i]] == 0)
                push(neighbours[i]);
        }
    }
}

int isBipartite(int arr[E][2], int color[N + 1])
{
    for(int i = 0; i < E; i++)
    {
        if(color[arr[i][0]] == color[arr[i][1]])
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    scanf("%d %d", &N, &E);
    int arr[E][2];
    for(int i = 0; i < E ; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            scanf("%d",&arr[i][j]);
        }
    }
    int Adj[N + 1][N + 1];
    createAdjMatrix(Adj, arr);

    int visited[N + 1];
    memset(visited, 0, (N + 1) * sizeof(int));

    int color[N + 1];
    memset(color, 0, (N + 1) * sizeof(int));

    color[1] = 1;

    DFS(Adj, 1, visited, color);


    if (isBipartite(arr, color))
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
    return 0;
}
