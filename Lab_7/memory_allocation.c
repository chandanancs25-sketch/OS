#include <stdio.h>

int main()
{
    int nb, np, i, j, choice;
    int block[20], process[20];
    int temp[20], allocation[20];

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);

    printf("Enter number of processes: ");
    scanf("%d", &np);

    printf("Enter sizes of memory blocks:\n");
    for(i = 0; i < nb; i++)
        scanf("%d", &block[i]);

    printf("Enter sizes of processes:\n");
    for(i = 0; i < np; i++)
        scanf("%d", &process[i]);

    printf("\n1. First Fit\n");
    printf("2. Best Fit\n");
    printf("3. Worst Fit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    for(i = 0; i < nb; i++)
        temp[i] = block[i];

    for(i = 0; i < np; i++)
        allocation[i] = -1;

    switch(choice)
    {
        case 1: // First Fit
            for(i = 0; i < np; i++)
            {
                for(j = 0; j < nb; j++)
                {
                    if(temp[j] >= process[i])
                    {
                        allocation[i] = j;
                        temp[j] -= process[i];
                        break;
                    }
                }
            }
            break;

        case 2: // Best Fit
            for(i = 0; i < np; i++)
            {
                int best = -1;

                for(j = 0; j < nb; j++)
                {
                    if(temp[j] >= process[i])
                    {
                        if(best == -1 || temp[j] < temp[best])
                            best = j;
                    }
                }

                if(best != -1)
                {
                    allocation[i] = best;
                    temp[best] -= process[i];
                }
            }
            break;

        case 3: // Worst Fit
            for(i = 0; i < np; i++)
            {
                int worst = -1;

                for(j = 0; j < nb; j++)
                {
                    if(temp[j] >= process[i])
                    {
                        if(worst == -1 || temp[j] > temp[worst])
                            worst = j;
                    }
                }

                if(worst != -1)
                {
                    allocation[i] = worst;
                    temp[worst] -= process[i];
                }
            }
            break;

        default:
            printf("Invalid Choice\n");
            return 0;
    }

    printf("\nProcess No\tProcess Size\tBlock No\n");

    for(i = 0; i < np; i++)
    {
        if(allocation[i] != -1)
            printf("%d\t\t%d\t\t%d\n",
                   i + 1, process[i], allocation[i] + 1);
        else
            printf("%d\t\t%d\t\tNot Allocated\n",
                   i + 1, process[i]);
    }

    return 0;
}