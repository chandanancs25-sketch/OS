#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 5, x = 0;

void wait(int *s)
{
    (*s)--;
}

void signal(int *s)
{
    (*s)++;
}

void producer()
{
    if ((mutex == 1) && (empty != 0))
    {
        wait(&mutex);
        wait(&empty);

        x++;
        printf("Producer produces item %d\n", x);

        signal(&full);
        signal(&mutex);
    }
    else
    {
        printf("Buffer is full!\n");
    }
}

void consumer()
{
    if ((mutex == 1) && (full != 0))
    {
        wait(&mutex);
        wait(&full);

        printf("Consumer consumes item %d\n", x);
        x--;

        signal(&empty);
        signal(&mutex);
    }
    else
    {
        printf("Buffer is empty!\n");
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n1. Producer\n");
        printf("2. Consumer\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                producer();
                break;

            case 2:
                consumer();
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
