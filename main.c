#include <stdio.h>
#include <stdlib.h>
FILE *ip,*stk,*poped,*pushed,*op;
int data;
struct Node
{
    int dat;
    struct Node *next,*prev;
};
typedef struct Node *node;
node top=NULL,newnode,temp;
void push()
{
    newnode=malloc(sizeof(struct Node));
    newnode->next=NULL;
    newnode->prev=NULL;
    fscanf(ip,"%d",&data);
    stk=fopen("stack.txt","a");
    fprintf(stk,"%d\n",data);
    fprintf(pushed,"%d\n",data);
    fprintf(op,"push\n");
    fclose(stk);
    newnode->dat=data;
    if(top==NULL)
        top=newnode;
    else
    {
        top->next=newnode;
        newnode->prev=top;
        top=top->next;
    }
}

void pop()
{
    if(top==NULL)
    {
        printf("\nStack underflow:");
        return;
    }
    stk=fopen("stack.txt","w");
    fprintf(poped,"%d\n",top->dat);
    temp=top;
    top=top->prev;
    free(temp);
    top->next=NULL;
    fprintf(op,"pop\n");
    temp=top;
    while(temp->prev!=NULL)
        temp=temp->prev;
    while(temp!=NULL)
    {
        fprintf(stk,"%d\n",temp->dat);
        temp=temp->next;
    }
    fclose(stk);
}

void flushfile()
{
    poped=fopen("poped.txt","w");
    pushed=fopen("pushed.txt","w");
    op=fopen("op.txt","w");
    fclose(pushed);
    stk=fopen("stack.txt","w");
    fclose(stk);
    fclose(poped);
    fclose(op);
}
void random()
{
    for(int i=0;i<100;i++)
    {
        fprintf(ip,"%d\n",rand()%1000);            //generate random numbers in input file
    }
}
void display()
{
    temp=top;
    while(temp->prev!=NULL)
        temp=temp->prev;
    printf("\n\n");
    while(temp!=NULL)
    {
        printf("%d ",temp->dat);
        temp=temp->next;
    }

}
int main()
{
    int choice;
    ip=fopen("input.txt","w");
    flushfile();                        //clear previous log files
    poped=fopen("poped.txt","a");
    pushed=fopen("pushed.txt","a");
    op=fopen("op.txt","a");

    if(ip==NULL||poped==NULL||pushed==NULL||op==NULL)
    {
        printf("\n\nFile not opened!");
        goto finished;
    }
    random();
    fclose(ip);

    ip=fopen("input.txt","r");
    while(1){
    printf("\nEnter choice: 1-push,2-pop,3-display,4-end:\n");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:push();break;
        case 2:pop();break;
        case 3:display();break;
        case 4:goto finished;break;
        default:printf("Invalid choice");
    }
    }
    finished:
    printf("\nfinished");
    fclose(ip);
    fclose(stk);
    fclose(pushed);
    fclose(poped);
    fclose(op);
    return 0;
}


