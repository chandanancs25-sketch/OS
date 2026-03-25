#include <stdio.h>

#define MAX 100

typedef struct
{
    int pid;
    int at;
    int bt;
    int type;   // 0 = System, 1 = User
    int ct;
    int tat;
    int wt;
    int start;
} Process;

void sortByArrival(Process q[], int n)
{
    int i, j;
    Process temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (q[j].at > q[j + 1].at)
            {
                temp = q[j];
                q[j] = q[j + 1];
                q[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n, i;
    Process p[MAX], systemQ[MAX], userQ[MAX];
    int sysCount = 0, userCount = 0;
    int time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("\nEnter details for process %d\n", i + 1);
        printf("PID: ");
        scanf("%d", &p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
        p[i].start = 0;

        if (p[i].type == 0)
            systemQ[sysCount++] = p[i];
        else
            userQ[userCount++] = p[i];
    }

    // Sort both queues by arrival time
    sortByArrival(systemQ, sysCount);
    sortByArrival(userQ, userCount);

    // Execute system processes first
    for (i = 0; i < sysCount; i++)
    {
        if (time < systemQ[i].at)
            time = systemQ[i].at;

        systemQ[i].start = time;
        time += systemQ[i].bt;
        systemQ[i].ct = time;
        systemQ[i].tat = systemQ[i].ct - systemQ[i].at;
        systemQ[i].wt = systemQ[i].tat - systemQ[i].bt;
    }

    // Execute user processes after system queue
    for (i = 0; i < userCount; i++)
    {
        if (time < userQ[i].at)
            time = userQ[i].at;

        userQ[i].start = time;
        time += userQ[i].bt;
        userQ[i].ct = time;
        userQ[i].tat = userQ[i].ct - userQ[i].at;
        userQ[i].wt = userQ[i].tat - userQ[i].bt;
    }

    printf("\nMulti-Level Queue Scheduling (FCFS)\n");
    printf("-----------------------------------------------------------\n");
    printf("PID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");
    printf("-----------------------------------------------------------\n");

    for (i = 0; i < sysCount; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               systemQ[i].pid,
               systemQ[i].at,
               systemQ[i].bt,
               systemQ[i].type,
               systemQ[i].ct,
               systemQ[i].tat,
               systemQ[i].wt);
    }

    for (i = 0; i < userCount; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               userQ[i].pid,
               userQ[i].at,
               userQ[i].bt,
               userQ[i].type,
               userQ[i].ct,
               userQ[i].tat,
               userQ[i].wt);
    }

    return 0;
}
