#include <stdio.h>

int main()
{
    int pages[50], frames[10];
    int n, f, i, j, k, choice;
    int faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    printf("\n1. FIFO\n2. LRU\n3. Optimal\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    for(i = 0; i < f; i++)
        frames[i] = -1;

    switch(choice)
    {
        case 1:     // FIFO
        {
            int index = 0;

            for(i = 0; i < n; i++)
            {
                int found = 0;

                for(j = 0; j < f; j++)
                {
                    if(frames[j] == pages[i])
                    {
                        found = 1;
                        break;
                    }
                }

                if(!found)
                {
                    frames[index] = pages[i];
                    index = (index + 1) % f;
                    faults++;
                }
            }
            break;
        }

        case 2:     // LRU
        {
            int time[10], counter = 0;

            for(i = 0; i < f; i++)
                time[i] = 0;

            for(i = 0; i < n; i++)
            {
                int found = 0;

                for(j = 0; j < f; j++)
                {
                    if(frames[j] == pages[i])
                    {
                        counter++;
                        time[j] = counter;
                        found = 1;
                        break;
                    }
                }

                if(!found)
                {
                    int pos = 0;

                    for(j = 1; j < f; j++)
                    {
                        if(time[j] < time[pos])
                            pos = j;
                    }

                    frames[pos] = pages[i];
                    counter++;
                    time[pos] = counter;
                    faults++;
                }
            }
            break;
        }

        case 3:     // Optimal
        {
            for(i = 0; i < n; i++)
            {
                int found = 0;

                for(j = 0; j < f; j++)
                {
                    if(frames[j] == pages[i])
                    {
                        found = 1;
                        break;
                    }
                }

                if(!found)
                {
                    int pos = -1, farthest = i + 1;

                    for(j = 0; j < f; j++)
                    {
                        int next;

                        for(next = i + 1; next < n; next++)
                        {
                            if(frames[j] == pages[next])
                                break;
                        }

                        if(next > farthest)
                        {
                            farthest = next;
                            pos = j;
                        }

                        if(next == n)
                        {
                            pos = j;
                            break;
                        }
                    }

                    if(pos == -1)
                    {
                        for(j = 0; j < f; j++)
                        {
                            if(frames[j] == -1)
                            {
                                pos = j;
                                break;
                            }
                        }

                        if(pos == -1)
                            pos = 0;
                    }

                    frames[pos] = pages[i];
                    faults++;
                }
            }
            break;
        }

        default:
            printf("Invalid Choice\n");
            return 0;
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}