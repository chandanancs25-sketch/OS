#include <stdio.h>

int main()
{
    int choice, n, start;

    printf("FILE ALLOCATION STRATEGIES\n");
    printf("1. Sequential Allocation\n");
    printf("2. Indexed Allocation\n");
    printf("3. Linked Allocation\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
        {
            printf("\n--- Sequential Allocation ---\n");

            printf("Enter starting block: ");
            scanf("%d", &start);

            printf("Enter number of blocks: ");
            scanf("%d", &n);

            printf("\nAllocated Blocks:\n");

            for(int i = 0; i < n; i++)
            {
                printf("%d ", start + i);
            }

            break;
        }

        case 2:
        {
            int indexBlock;
            int block[20];

            printf("\n--- Indexed Allocation ---\n");

            printf("Enter index block: ");
            scanf("%d", &indexBlock);

            printf("Enter number of file blocks: ");
            scanf("%d", &n);

            printf("Enter block numbers:\n");

            for(int i = 0; i < n; i++)
            {
                scanf("%d", &block[i]);
            }

            printf("\nIndex Block %d contains:\n", indexBlock);

            for(int i = 0; i < n; i++)
            {
                printf("%d ", block[i]);
            }

            break;
        }

        case 3:
        {
            int block[20];

            printf("\n--- Linked Allocation ---\n");

            printf("Enter number of blocks: ");
            scanf("%d", &n);

            printf("Enter block numbers:\n");

            for(int i = 0; i < n; i++)
            {
                scanf("%d", &block[i]);
            }

            printf("\nLinked Blocks:\n");

            for(int i = 0; i < n - 1; i++)
            {
                printf("%d -> ", block[i]);
            }

            printf("%d -> NULL", block[n - 1]);

            break;
        }

        default:
            printf("Invalid Choice");
    }

    return 0;
}