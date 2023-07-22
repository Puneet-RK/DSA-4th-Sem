// Binary Search Tree operations in C
#include <stdio.h>
#include <stdlib.h>
FILE *inp,*indr,*predr,*posdr;
struct Node {
  int key;
  struct Node *left, *right;
};
typedef struct Node *node;

// Create a node
node newNode(int item)
{
  node temp = (node)malloc(sizeof(struct Node));
  if(temp==NULL)
  {
      printf("\nnode not created!\n");
      return temp;
  }
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}

// Inorder Traversal
void inorder(node root)
{
    if (root!=NULL)
    {
        // Traverse left
        inorder(root->left);

        // Traverse root
        fprintf(indr,"%d\n",root->key);
        printf("%d -> ", root->key);

        // Traverse right
        inorder(root->right);
    }
}
//Preorder Traversal
void preorder(node root)
{
    if (root!=NULL)
    {
        // Traverse root
        fprintf(predr,"%d\n",root->key);
        printf("%d -> ", root->key);

        // Traverse left
        preorder(root->left);

        // Traverse right
        preorder(root->right);
    }
}

//Postorder Traversal
void postorder(node root)
{
    if (root!=NULL)
    {
        // Traverse left
        postorder(root->left);

        // Traverse right
        postorder(root->right);

        // Traverse root
        fprintf(posdr,"%d\n",root->key);
        printf("%d -> ", root->key);
    }
}


// Insert a node
node insert(node nodee, int num)
{
  // Return a new node if the tree is empty
  if (nodee == NULL)
    return newNode(num);

  // Traverse to the right place and insert the node
  if (num < nodee->key)
    nodee->left = insert(nodee->left, num);
  else
    nodee->right = insert(nodee->right, num);

  return nodee;
}

// Find the inorder successor
node minValueNode(node nodee)
{
    node current;
    current = nodee;

  // Find the leftmost leaf
    while (current && current->left != NULL)
    current = current->left;

  return current;
}

// Deleting a node
node deleteNode(node root, int num) {
  // Return if the tree is empty
  if (root == NULL) return root;

  // Find the node to be deleted
  if (num < root->key)
    root->left = deleteNode(root->left, num);
  else if (num > root->key)
    root->right = deleteNode(root->right, num);

  else
{
    // If the node is with only one child or no child
    if (root->left == NULL)
    {
      node temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL)
    {
      node temp = root->left;
      free(root);
      return temp;
    }

    // If the node has two children
    node temp = minValueNode(root->right);

    // Place the inorder successor in position of the node to be deleted
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

void flushfile()
{
    indr=fopen("Inorder.txt","w");
    predr=fopen("Preorder.txt","w");
    posdr=fopen("Postorder.txt","w");

    fclose(indr);
    fclose(predr);
    fclose(posdr);
}
void random()
{
    for(int i=0;i<100;i++)
    {
        fprintf(inp,"%d\n",rand()%100);
    }
}
// Driver code
int main() {
    node root = NULL;
    int choice,n,dnk;
    flushfile();
    inp=fopen("Input.txt","w");
    random();
    fclose(inp);
    inp=fopen("Input.txt","r");

    printf("Enter choice: \n");
    while(1)
    {
        printf("\n1-Insert, 2-Inorder, 3-Preorder, 4-Postorder, 5-delete, 6-Exit:\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:fscanf(inp,"%d",&n);root=insert(root,n);break;
            case 2:indr=fopen("Inorder.txt","w");inorder(root);fclose(indr);break;
            case 3:predr=fopen("Preorder.txt","w");preorder(root);fclose(predr);break;
            case 4:posdr=fopen("Postorder.txt","w");postorder(root);fclose(posdr);break;
            case 5:printf("Enter data to be deleted");scanf("%d",&dnk);root=deleteNode(root,dnk);break;
            case 6:goto finished;break;
            default: printf("\nInvalid choice!\n");
        }
    }
    finished:
        printf("\nFinished!\n");
        fclose(inp);
}
