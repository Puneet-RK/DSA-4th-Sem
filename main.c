#include <stdio.h>
#include <stdlib.h>
FILE *ip,*stk,*poped,*pushed,*op;
int data,array[100],top=-1,k;

void push()
{
    if(top>=99)
    {
        printf("\nStack Overflow:");
        return;
    }
    fscanf(ip,"%d",&data);
    stk=fopen("stack.txt","a");
    fprintf(stk,"%d\n",data);
    fprintf(pushed,"%d\n",data);
    fprintf(op,"push\n");
    fclose(stk);
    top++;
    array[top]=data;
}

void pop()
{
    if(top<0)
    {
        printf("\nStack underflow:");
    }
    stk=fopen("stack.txt","w");
    fprintf(poped,"%d\n",array[top]);
    top--;
    fprintf(op,"pop\n");
    k=0;
    for(k=0;k<=top;k++)
    {
        fprintf(stk,"%d\n",array[k]);
    }
    fclose(stk);
}

void flushfile()
{
    poped=fopen("poped.txt","w");
    pushed=fopen("pushed.txt","w");
    op=fopen("op.txt","w");
    fclose(pushed);
    fclose(poped);
    fclose(op);
}

int main()
{
    int choice,i;
    ip=fopen("input.txt","w");
    flushfile();                        //clear previous log files
    poped=fopen("poped.txt","a");
    pushed=fopen("pushed.txt","a");
    op=fopen("op.txt","a");

    if(ip==NULL||poped==NULL||pushed==NULL||op==NULL)
    {
        printf("\n\nFile not opened!");
        goto label;
    }

    for(i=0;i<100;i++)
    {
        fprintf(ip,"%d\n",rand()%100);            //generate random numbers in input file
    }
    fclose(ip);

    ip=fopen("input.txt","r");
    while(1){
    printf("Enter choice: 1-push,2-pop,3-end");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:push();break;
        case 2:pop();break;
        case 3:goto label;break;
        default:printf("Invalid choice");
    }
    }
    label:
        printf("\nfinished");
    fclose(ip);
    fclose(stk);
    fclose(pushed);
    fclose(poped);
    fclose(op);
    return 0;
}
