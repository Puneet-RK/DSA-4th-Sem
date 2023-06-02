#include<stdio.h>
#include<stdlib.h>
FILE *input,*queue,*enqueue,*dq,*logg;
struct Node
{
    int data;
    struct Node *next;
};
typedef struct Node *node;
node head=NULL,tail=NULL;

void enqueuee()
{
    node newNode=malloc(sizeof(struct Node));
    if(newNode==NULL)
    {
        printf("\nNode not created!!\n");
        return;
    }
    int val;
    fscanf(input,"%d",&val);

    newNode->data=val;
    newNode->next = NULL;

    //if it is the first node
    if(head == NULL && tail == NULL)
        //make both head and tail points to the new node
        head = tail = newNode;
    else
    {
        //add newnode in tail->next
        tail->next = newNode;

        //make the new node as the tail node
        tail = newNode;
    }
    queue=fopen("queue.txt","a");
    fprintf(queue,"%d\n",val);
    fclose(queue);
    fprintf(enqueue,"%d\n",val);
    logg=fopen("log.txt","a");
    fprintf(logg,"Enqueue\n");
    fclose(logg);
}

void dequeuee()
{
    //used to free the first node after dequeue
    node temp;

    if(head == NULL){
         printf("Queue is Empty. Unable to perform dequeue\n");return;}
        //take backup
        temp = head;

        //make the head node points to the next node
        //logically removing the head element
        head = head->next;

        //if head == NULL, set tail = NULL
        if(head == NULL)
            {tail = NULL;
            head=NULL;}
       //free the first node
       fprintf(dq,"%d\n",temp->data);
       free(temp);
       queue=fopen("queue.txt","w");
       temp=head;
       while(temp!=NULL)
       {
           fprintf(queue,"%d\n",temp->data);
           temp=temp->next;
       }
       fclose(queue);
        logg=fopen("log.txt","a");
        fprintf(logg,"Dequeue\n");
        fclose(logg);


}

void display()
{
    node temp = head;

    while(temp)
    {
        printf("%d->",temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
void random(int n)
{
    input=fopen("input.txt","w");
    for(int i=0;i<n;i++)
    {
        fprintf(input,"%d\n",rand()%1000);
    }
    fclose(input);
}
 void flush()
{
    queue=fopen("queue.txt","w");
    fclose(queue);
    logg=fopen("log.txt","w");
    fclose(logg);
}
int main()
{
    int choice,n;
    printf("Enter the number of random numbers to be generated: ");
    scanf("%d",&n);
    random(n);
    flush();
    enqueue=fopen("enqueue.txt","w");
    dq=fopen("dequeue.txt","w");
    input=fopen("input.txt","r");
    while(1)
    {
        printf("\nEnter 1:Enqueue 2:Dequeue 3:Display\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:enqueuee(); break;
            case 2:dequeuee(); break;
            case 3:display(); break;
            case 4:goto finish;break;
            default:printf("\nChoice not valid\n");
        }
    }
    finish:
    fclose(input);
    fclose(dq);
    fclose(enqueue);
    return 0;
}
