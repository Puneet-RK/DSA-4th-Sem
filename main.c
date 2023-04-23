// Code to read numbers from file containing random numbers, sort them and find the time taken to sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void read(FILE *fp,int no,int arr[])       //function to read from file
{
    int i;
    for(i=0;i<no;i++)
    {
        fscanf(fp,"%d",&arr[i]);
    }
}

void sort(FILE *fp,int no,int arr[])       //function to sort the array
{
    int i,j,temp;
    for(i=0;i<no-1;i++)
    {
        for(j=i;j<no;j++)
        {
            if(arr[i]>arr[j])
            {
                temp=arr[i];
                arr[i]=arr[j];            //swap
                arr[j]=temp;
            }
        }
    }
}
void display(int arr[],int no)             //function to display the arrray
{
    int i;
    for(i=0;i<no;i++)
    {
        printf(" %d",arr[i]);
    }
}

int main()
{
    time_t t1,t2,tf;

    int no,i,arr[100000],num;
    FILE *fp=fopen("array1.txt","w");               //write mode

    printf("\nEnter no. of rand nos.:");
    scanf("%d",&num);

    for(i=0;i<num;i++)
    {
        fprintf(fp," %d",rand()%1000);              // generate random numbers
    }
    fclose(fp);


    printf("\nEnter the no. of digits to sort: ");
    scanf("%d",&no);

    fp=fopen("array1.txt","r");                    // read mode
    read(fp,no,arr);
    fclose(fp);


    t1=time(NULL);                               //initial time
    sort(fp,no,arr);
    t2=time(NULL);                               //final time


    display(arr,no);
    tf=t2-t1;
    printf("\n\n Time = %ld",tf);              //total time taken to sort
    return 0;
}
