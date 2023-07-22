#include<stdio.h>
#include<stdlib.h>

struct node
{
    int vertex;
    struct node *next;
};
typedef struct node *NODE;

struct Graph
{
    int numver;
    struct Graph **adjlist;
};
typedef struct Graph *GRAPH;

GRAPH creategraph(int n)
{
    GRAPH graph=malloc(sizeof(struct Graph));
    graph->numver=n;

    graph->adjlist=malloc(n*sizeof(NODE));

    for(int i=0;i<n;i++)
    {
        graph->adjlist[i] = NULL;
        //printf("%d->",g->adjlist[i]);
    }

    return graph;
};

NODE createnode(int x)
{
    NODE newnode=malloc(sizeof(struct node));
    newnode->vertex=x;
    newnode->next=NULL;

    return newnode;
}

void addedge(GRAPH graph,int s,int d)
{
    //source
    NODE newnode=createnode(s);
    newnode->next=graph->adjlist[d];
    graph->adjlist[d]=newnode;

    //destination
    newnode=createnode(d);
    newnode->next=graph->adjlist[s];
    graph->adjlist[s]=newnode;
}

void print(GRAPH graph)
{
    for(int i=0 ; i<graph->numver ; i++){
        NODE temp=graph->adjlist[i];
        printf("Vertex %d : ",i);
        while(temp){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

main()
{
    //printf(".");
    GRAPH g=creategraph(5);
    //printf(".");
    addedge(g,0,1);
    //printf(".");
    addedge(g,0,2);
    addedge(g,1,3);
    addedge(g,3,2);

    print(g);
}
