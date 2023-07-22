
#include<stdio.h>
#define V 4
#define E 5
void initgraph(int graph[V][V])
{
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
            graph[i][j]=0;
    }
}

void addedge(int graph[V][V],int i,int j)
{
    graph[i][j] = 1;
}

void print(int graph[V][V])
{
    for(int i=0;i<V;i++)
    {
        printf("%d: ",i);
        for(int j=0;j<V;j++)
            printf("%d ",graph[i][j]);
        printf("\n");
    }
}

int main()
{
    int graph[V][V];

    initgraph(graph);
    addedge(graph,0,1);
    addedge(graph,0,2);
    addedge(graph,0,3);
    addedge(graph,3,2);
    addedge(graph,3,1);

    print(graph);
}
