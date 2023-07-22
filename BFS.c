#include<stdio.h>
#include<stdlib.h>
int m[10][10]={{0,1,1,0},{1,0,0,1},{1,0,0,1},{0,1,1,0}};
int visited[10],source=0,size=5;

void bfs(int m[10][10],int size,int source)
{
    int queue[20],front=0,rear=0,u;
    queue[rear]=source;
    visited[source]=1;
    printf("BFS traversal is:\n");
    while(front<=rear)
    {
        u=queue[front];
        printf("%d\t",u);
        front++;

        for(int i=0;i<size;i++)
      {
        if(m[u][i]==1 && visited[i]==0)
        {
            visited[i]=1;
            rear++;
            queue[rear]=i;

        }
     }
    }
}
int main()
{
    int i;
    for(i=0;i<size;i++)
    {
        visited[i]=0;
    }
    bfs(m,size,source);
}
