// Code to read random numbers from file and sort them using linked list and calculate the time taken

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct NODE
{
    int data;
    struct NODE *next;
};

typedef struct NODE *node;

node head=NULL;
node tail=NULL;
node tail1=NULL,curr;

node insert(int c)                                      //Function to insert new node at the end
{
    node newnode=(node)malloc(sizeof(struct NODE));
    if(newnode==NULL)
    {
        printf("\nNode not created");
        exit(0);
    }
    newnode->data=c;
    newnode->next=NULL;
    return newnode;
}

int n;

void read(FILE *fp)                 //function to read from file and store in linked list
{
    int c;
    for(int i=0;i<n;i++)
    {
        fscanf(fp,"%d",&c);
        if(i==0)//first node
        {
            head=insert(c);
            tail=head;
        }
        else
        {
            tail1=insert(c);
            tail->next=tail1;
            tail=tail->next;
        }
    }
}
void random(FILE *fp)                    //generate random numbers
{
    printf("\nEnter range: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        fprintf(fp,"%d ",rand()%1000);
    }
}

void display()
{
    if(head==NULL)
    {
        printf("\nEmpty..");
        return ;
    }
    node temp=head;
    while(temp!=NULL)
    {
        printf("%d  ",temp->data);
        temp=temp->next;
    }
    printf("\n");
}

void sort()                                          // function to sort linked list using bubble sort
{
    node cur=head,temp1=head;
    int temp;
    do
    {
        do
        {
            temp1=temp1->next;
            if(cur->data>temp1->data)
            {
                temp=temp1->data;
                temp1->data=cur->data;        // swap data
                cur->data=temp;
            }

        }while(temp1->next!=NULL);
        cur=cur->next;
        temp1=cur;
    }while(cur->next!=NULL);
}

int main()
{
    FILE *fp;
    time_t t1,t2,t;
    fp=fopen("LL.txt","w");               //write mode
    random(fp);                            //generate random numbers and store in file
    fclose(fp);

    fp=fopen("LL.txt","r");              //read mode

    read(fp);                            //read from file and store in linked list
    fclose(fp);

    t1=time(NULL);
    sort();
    t2=time(NULL);

    //display();
    t=t2-t1;                                //total time taken to sort
    printf("\nTime Taken: %ld",t);
    fp=fopen("LL.txt","w");
    curr=head;
    do
    {
        fprintf(fp,"%d ",curr->data);
        curr=curr->next;
    }while(curr->next!=NULL);
    return 0;
}
