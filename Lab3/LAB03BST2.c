// LAB03BST2.C - Lab 03

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max 13
//--------------------
typedef struct treenode
{
    int key;
    char password[max];
    struct treenode *left;
    struct treenode *right;
} Node;

Node *root = NULL;
Node *newNode(int key, char pw[]);
Node *insert(int k, char pw[], Node *root);
int testOrder(Node *root);
Node *find(int k, Node *root);
int nodeCount(Node *root);
void readDel(Node *root);
void readID(Node *root);
void lookupRead(Node *root);
Node *minVal(Node *root);
Node *delete(Node *root, int key);

Node *newNode(int key, char pw[])
{
    Node *n = (Node *)malloc(sizeof(Node));
    // initialize node if memory obtained
    if (n != NULL)
    {
        n->key = key;
        strcpy(n->password, (char *)pw);
        n->left = NULL;
        n->right = NULL;
    }
    return n;
} // initNode()

Node *insert(int k, char pw[], Node *root)
{
    // this if statement can only be true with first root (root of whole tree)
    if (root == NULL)
    {
        Node *n = newNode(k, pw);
        root = n;
        return n;
    }

    // already exists in tree
    if (root->key == k)
    {
        strcpy(root->password, pw);
        return root;
    }
    else if (k < root->key)
    {
        // key value less than key value in root node - try to insert into left subtree, if it exists.
        if (root->left != NULL)
        {
            // there is a left subtree - insert it
            root->left = (k, pw[max], root->left);
        }
        else
        {
            // new Node becomes the left subtree
            Node *n = newNode(k, pw[max]);
            root->left = n;
            return root;
        }
    }
    else if (k > root->key)
    {
        // key is greater than this nodes key value, so value goes into right subtree, if it exists
        if (root->right != NULL)
            // there is a right subtree - insert new node
            root->right = insert(k, pw[max], root->right);
        else
        {
            // no right subtree - new node becomes right subtree
            Node *n = newNode(k, pw[max]);
            root->right = n;
            return root;
        }
    }
    return root;
} // insert()

// This tests to see is the tree is in order or not
int testOrder(Node *root) // Don't forget to make it print that it is inorder in the main
{
    if (root == NULL)
        return 1;
    // sees if the tree isn't sorted
    if (testOrder(root->left) == 0 || testOrder(root->right == 0))
    {
        return 0;
    }
    // sees if the tree is sorted
    if ((root->left->key < root->key) && (root->right->key > root->key))
    {
        return 1;
    }
    return 0;

} // test()

Node *find(int k, Node *root)
{
    // termination conditions - either true, search is ended
    if ((root == NULL) || (root->key == k))
        return root;
    // Key value sought is larger than current node key, so search right subtree
    if (k > root->key)
        return find(k, root->right);
    // Key value sought is smaller than current node key (the equal case was handled as a termination condition in the first line), so
    // search left subtree
    else
        return find(k, root->left);
} // find()

// This is to count the number of nodes in the tree
int nodeCount(Node *root)
{
    int c;
    if (root == NULL)
        return 0;
    else
    {
        c = 1 + nodeCount(root->left) + nodeCount(root->right);
        return c;
    }
}

// reads what should be deleted
void readDel(Node *root)
{
    int delID;
    FILE *del = fopen("DELETES.txt", "r");
    if (del == NULL)
    {
        printf("ERROR: Delete file not found\n");
        exit(1);
        return;
    }
    while (fscanf(del, "%d", &delID) == 1)
    {
        // printf("%d\n", delID);
        // Sends read data to delete
        delete (root, delID);
    }
}

// reads the IDs and the passwords
void readID(Node *root)
{
    char readPw[max];
    int readKy;
    FILE *id = fopen("IDENTS.txt", "r");
    if (id == NULL)
    {
        printf("ERROR: ID file not found\n");
        exit(1);
        return;
    }
    while (fscanf(id, "%010d   %s\n", &readKy, readPw) == 2)
    {
        // printf("%d  %s\n", readKy, readPw);
        // Inserts read data
        insert(readKy, readPw, root);
    }
    return;
}

// reads the data that needs to be looked up
void lookupRead(Node *root)
{
    int lookR;
    FILE *tr = fopen("LOOKUPS.txt", "r");
    if (tr == NULL)
    {
        printf("ERROR: Lookup file not found\n");
        exit(1);
        return;
    }
    // looks to see if that ID is in the data set
    while (fscanf(tr, "%d", &lookR) == 1)
    {
        // printf("%d\n", lookR);
        Node *n = find(lookR, root);
        if (n->key == NULL)
            printf("<NOT FOUND>");
        else
            printf("ID %d PASSWORD %s\n", n->key, n->password);
    }
}

// finds the min value in the structure
Node *minVal(Node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

// deletes a node
Node *delete(Node *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = delete (root->left, key);
    else if (key > root->key)
        root->right = delete (root->right, key);
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node *temp = minVal(root->right);
        root->key = temp->key;
        root->right = delete (root->right, temp->key);
    }
    return root;
}

int main()
{
    readID(root);
    printf("BST NODES: %d\n", nodeCount(root));
    if (testOrder(root) == 1)
        printf("The tree is in order\n");
    else
        printf("The tree is not in order\n");
    readDel(root);
    printf("NODES AFTER DELETES: %d\n", nodeCount(root));
    if (testOrder(root) == 1)
        printf("The tree is in order\n");
    else
        printf("The tree is not in order\n");
    lookupRead(root);
    return 0;
}
// The print statements in the read commands are there to test
// if the command is reading the txt file, and in this case
// they are I just have absolutly no clue as to why its not
// sending the read data to the spceified commands;