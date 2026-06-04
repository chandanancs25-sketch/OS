#include <stdio.h>

#define N 5

int chopstick[N] = {1, 1, 1, 1, 1};

void wait(int *s)
{
    (*s)--;
}

void signal(int *s)
{
    (*s)++;
}

void eat(int i)
{
    if (chopstick[i] == 1 && chopstick[(i + 1) % N] == 1)
    {
        wait(&chopstick[i]);
        wait(&chopstick[(i + 1) % N]);

        printf("Philosopher %d is Eating\n", i);

        signal(&chopstick[i]);
        signal(&chopstick[(i + 1) % N]);
    }
    else
    {
        printf("Philosopher %d is Waiting\n", i);
    }
}

int main()
{
    int i;

    while (1)
    {
        printf("\nEnter philosopher number (0-4) or -1 to exit: ");
        scanf("%d", &i);

        if (i == -1)
            break;

        if (i >= 0 && i < N)
            eat(i);
        else
            printf("Invalid input\n");
    }

    return 0;
}
