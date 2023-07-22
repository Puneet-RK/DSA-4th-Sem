#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
FILE *inp,*indr,*predr;
bool flag;

struct tree
{
    int data,height,balance;
    struct tree *left,*right;
};
//Pointer to tree
typedef struct tree *ptree ;

//Function to generate 100 random numbers
void random()
{
    inp=fopen("Input.txt","w");
    for(int i=0;i<100;i++)
    {
       fprintf(inp,"%d ",rand()%100);
    }
    fclose(inp);
}
//Return the height of given node
int getHeight(ptree node)
{
    if(node==NULL)return 0;
    return node->height;
}
//Find the balance factor of a given node --> (height of left subtree)-(height of right subtree)
int getBalance(ptree node)
{
    if(node==NULL)return 0;
    return (getHeight(node->left))-(getHeight(node->right));
}
//Find maximum of heights of left and right sub tree
int max(int l,int r)
{
    return l>r?l:r;
}


//***Function to rotate left***
ptree rotateLeft(ptree l)
{
    ptree y=l->right;
    ptree t=y->left;

    y->left=l;
    l->right=t;

    //Assign new height after rotating
    l->height=max(getHeight(l->right),getHeight(l->left))+1;
    y->height=max(getHeight(y->right),getHeight(y->left))+1;
    l->balance=getBalance(l);
    y->balance=getBalance(y);
    return y;
}
//***Function to rotate right***
ptree rotateRight(ptree r)
{
    ptree y=r->left;
    ptree t=y->right;

    y->right=r;
    r->left=t;

    //Assign new height after rotating
    r->height=max(getHeight(r->left),getHeight(r->right))+1;
    y->height=max(getHeight(y->left),getHeight(y->right))+1;
    r->balance=getBalance(r);
    y->balance=getBalance(y);
    return y;
}


//***Function to check AVL and balance the tree if not balanced:***
ptree treeAvl(ptree node)
{
    node->height=1+max(getHeight(node->left),getHeight(node->right));
    node->balance=getBalance(node);

    if(node->balance>1&&getBalance(node->left)>=0)
        return rotateRight(node);

    if(node->balance<-1&&getBalance(node->right)<=0)
        return rotateLeft(node);

    if(node->balance>1&&getBalance(node->left)<0)
    {
        node->left=rotateLeft(node->left);
        return rotateRight(node);
    }
    if(node->balance<-1&&getBalance(node->right)>0)
    {
        node->right=rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}


//Create new node
ptree getNode(int key)
{
    ptree newnode=(ptree)malloc(sizeof(struct tree));
    if(newnode==NULL){printf("\nNode not created!\n");return newnode;}
    newnode->data=key;
    newnode->right=NULL;
    newnode->left=NULL;
    newnode->height=1;
    newnode->balance=0;
    return newnode;
}
//***Insert a new node to Tree***
ptree insertNode(ptree node,int key)
{
    if(node==NULL)return getNode(key);
    if(key<node->data)
        node->left=insertNode(node->left,key);
    else if(key>=node->data)
        node->right=insertNode(node->right,key);
    else return node;

    return treeAvl(node);
}


//Find Max value Predecessor of a node
ptree minvalue(ptree node)
{
    ptree temp=node;
    while(temp->right!=NULL)
    {
        temp=temp->right;
    }
    return temp;
}
//***Delete a given node based on key***
ptree delete_(ptree node,int key)
{
    if(node==NULL){printf("\n            Node not Found!\n");return node;}

    if(key<node->data)
        node->left=delete_(node->left,key);

    else if(key>node->data)
        node->right=delete_(node->right,key);

    else if(key==node->data)
    {
        ptree temp;
        if(node->right==NULL||node->left==NULL)           //At most one child is NULL
        {
            temp=node->right?node->right:node->left;

            if(temp==NULL)   //Both are null
            {
                temp=node;
                node=NULL;
            }
            else             //has only one child
            {
                *node=*temp;
            }
            free(temp);
        }
        else
        {
            printf("                    %d is Deleted\n",node->data);
            temp=minvalue(node->left);
            printf("\nThe successor of %d is %d\n",key,temp->data);
            node->data=temp->data;
            node->left=delete_(node->left,temp->data);
        }
        if(node==NULL) return node;
    }
    return treeAvl(node);
}


//Traverse Inorder
void inorder(ptree node)
{
    if(node==NULL)return;
    //Left
    inorder(node->left);
    //Root
    printf(" %d    ->    %d    ->    %d\n",node->data,node->balance,node->height);
    fprintf(indr," %d    ->    %d    ->    %d\n",node->data,node->balance,node->height);
    //Right
    inorder(node->right);
}
//Traverse Preorder
void preorder(ptree node)
{
    if(node==NULL)return;
    //Root
    printf(" %d    ->    %d    ->    %d\n",node->data,node->balance,node->height);
    fprintf(predr," %d    ->    %d    ->    %d\n",node->data,node->balance,node->height);
    //Left
    preorder(node->left);
    //Right
    preorder(node->right);
}
//Clears the output file before starting
void flushfile()
{
    indr=fopen("Inorder.txt","w");
    fclose(indr);
    predr=fopen("Preorder.txt","w");
    fclose(predr);
}
void checkBal(ptree node)
{
    if(node==NULL)return;
    //Left
    checkBal(node->left);
    //Root
    if(node->balance<-1||node->balance>1)flag=true;
    //Right
    checkBal(node->right);
}
//Driver code
int main()
{
    ptree root=NULL;
    int choice,num,del;
    random();
    flushfile();
    inp=fopen("Input.txt","r");
    printf("\nEnter 1-Insert Element, 2-Delete Element, 3-Traverse Inorder, 4-Traverse Postorder, 5-check balance, 6-Exit:\n");
    while(1)
    {
        printf("\nEnter choice: ");
        fflush(stdin);
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:fscanf(inp,"%d",&num);
                   printf("                    %d is Inserted\n",num);
                   root=insertNode(root,num); break;

            case 2:if(root==NULL){printf("                    Tree is empty!!");break;}
                   printf("\nEnter Key: ");
                   scanf("%d",&del);
                   root=delete_(root,del);break;

            case 3:indr=fopen("Inorder.txt","w");
                   printf("\n\n   ***Inorder Traversal***\n\n node     balance    height\n");
                   inorder(root);
                   fclose(indr); break;

            case 4:predr=fopen("Preorder.txt","w");
                   printf("\n\n   ***Preorder Traversal***\n\n node     balance    height\n");
                   preorder(root);
                   fclose(predr); break;

            case 5:flag=false;checkBal(root);
                   if(flag==true){printf("\nTree is not balanced!!\n");}
                   else {printf("The Tree is Completely balanced %c",1);}break;

            case 6:fclose(inp);return 0;
            default:printf("\nInvalid choice!!\n");
        }
    }
    return 0;
}
