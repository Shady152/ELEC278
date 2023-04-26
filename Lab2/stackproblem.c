// stackproblem.c – Lab 02

#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *pnext;
    char ch;
};

struct node *phead = NULL;
struct node *pend = NULL;

// The below creates a new node for every value input
struct node *pnewnode(char c)
{
    struct node *pn = (struct node *)malloc(sizeof(struct node));
    if (pn != NULL)
    {
        pn->ch = c;
        pn->pnext = NULL;
    }
    return pn;
};

// The below inserts the node into the Stack
int insert(char c)
{
    struct node *pn = pnewnode(c);
    if (pn == NULL)
    {
        return -1;
    }
    pn->pnext = phead;
    phead = pn;
    if (pend == NULL)
    {
        pend = pn;
    }
    return 0;
} // insert()

// The below prints the Stack
void printS()
{
    struct node *pcurr = phead;
    if (phead == pend)
    {
        printf("The Stack is empty\n");
        return;
    }
    while (pcurr != NULL)
    {
        printf("%c ", pcurr->ch);
        pcurr = pcurr->pnext;
    }
    return;
} // printS()

int main()
{
    char c;
    int cmd;
    int i = 0;
    int b = 1;
    printf("To insert a character type '1' followed by the character you want to insert\n");
    printf("To print the stack type '2'\n");
    printf("WARNING: This stack has a limit of 80 characters, when 80 characters are reached the stack will print\n");
    // The function below inputs the new line character into the Stack
    insert('\n');
    while (b == 1)
    {
        scanf("%d", &cmd);
        scanf("%c", &c);
        switch (cmd)
        {
        case 1:
            printf("Received %d %c\n", cmd, c);
            insert(c);
            i++;
            if (i >= 80)
            {
                printS();
                b = 0;
                break;
            }
            break;
        case 2:
            printf("Received %d\n", cmd);
            printS();
            b = 0;
            break;
        default:
            fprintf(stderr, "ERROR: Invalid command --%d--\n", cmd);
            break;
        }
    }
    printf("------END------\n");
}
