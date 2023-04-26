// queueproblem.c – Lab 02

#include <stdio.h>
#include <stdlib.h>

struct node
{

    struct node *pnext;
    int val;
};

// Below are arrays for the head and end pointers of the list and it's an array for where every element of it is for
// one of the Queues
struct node *head[4] = {NULL, NULL, NULL, NULL};
struct node *end[4] = {NULL, NULL, NULL, NULL};

// The below creates a new node for every value input
struct node *pnewnode(int a)
{
    struct node *pn = (struct node *)malloc(sizeof(struct node));
    if (pn != NULL)
    {
        pn->val = a;
        pn->pnext = NULL;
    }
    return pn;
}; // pnewnode

// Calculates the modulus
int mod(int a)
{
    int m;
    m = a % 4;
    if (m == 0 || m == 1 || m == 2 || m == 3)
    {
        return m;
    }
    else
    {
        return printf("ERROR: Not a valid value\n");
    }
} // mod

// The below checks what Queues are empty
void isempty(int x)
{
    if (head[x] == NULL)
    {
        printf("Q%d is Empty", x + 1);
        return;
    }
    else
    {
        return;
    }
} // isempty

// The below inserts the node into the corresponding Queue
int insert(int a)
{
    int n;
    n = mod(a);
    struct node *pn = pnewnode(a);
    if (pn == NULL)
    {
        return -1;
    }
    pn->pnext = head[n];
    head[n] = pn;
    if (end[n] == NULL)
    {
        end[n] = pn;
    }
    return 0;
} // insert

// The below prints the the Queue
void printQ(struct node *head[], int *pc, int x)
{
    static int i;
    pc = &i;
    if (head[x] == NULL)
    {
        return;
    }
    if (head[x]->pnext == NULL)
    {
        *pc = 0;
    }
    printQ(&head[x]->pnext, pc, x);
    *pc = *pc + 1;
    printf("%5d, %d, %d", head[x]->val, *pc, x);

    if (i >= 12)
    {
        printf("\n");
        i = 0;
    }
    return;
} // printQ

int main()
{
    char c;
    int a, b, i, x;
    i = 0;
    b = 1;
    printf("Use E or e followed by a positive integer number to add a value to the Queue(s)\n");
    printf("Follow E or e by a negative integer to print the Queue(s)\n");
    printf("WARNING: The total capacity of values that can be input are 400 if this number is exceeded then the Queue(s) will print\n");
    while (b == 1)
    {
        scanf("%c", &c);
        scanf("%d", &a);
        // This case is to insert into a Queue
        if (c == 'e' || c == 'E')
        {
            if (a < 0)
            {
                int *pc;
                for (x = 0; x < 4; x++)
                {
                    printf("Q%d:\n", x + 1);
                    isempty(x);
                    printQ(&head[x], pc, x);
                    printf("\n");
                }
                b = 0;
                break;
            }
            else
            {
                insert(a);
                i++;
            }
        }
        // The below is to determine if the maximum number inputs had been reached and if so it prints all the Queues
        if (i >= 400)
        {
            int *pc;
            for (x = 0; x < 4; x++)
            {
                printf("Q%d:\n", x + 1);
                isempty(x);
                printQ(&head[x], pc, x);
                printf("\n");
            }
            b = 0;
        }
    }
    printf("\n");
    printf("------END------\n");
}
