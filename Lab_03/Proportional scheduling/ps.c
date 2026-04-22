#include <stdio.h>

#define MAX 10
#define TIME_QUANTUM 10

typedef struct {
    int id;
    int burst_time;
    int remaining_time;
    int weight;
    int completed;
} Process;

int main() {
    int n, i;
    Process p[MAX];
    int total_weight = 0;
    int all_done;


    printf("   Proportional Share Scheduling\n");


    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nProcess P%d:\n", i + 1);
        printf("  Enter burst time: ");
        scanf("%d", &p[i].burst_time);

        printf("  Enter weight: ");
        scanf("%d", &p[i].weight);

        p[i].remaining_time = p[i].burst_time;
        p[i].completed = 0;

        total_weight += p[i].weight;
    }


    printf("Scheduling Starts...\n");


    while (1) {
        all_done = 1;

        for (i = 0; i < n; i++) {
            if (!p[i].completed && p[i].remaining_time > 0) {
                all_done = 0;

                int time_slice = (p[i].weight * TIME_QUANTUM) / total_weight;

                if (time_slice == 0)
                    time_slice = 1;

                if (time_slice > p[i].remaining_time)
                    time_slice = p[i].remaining_time;

                printf("Process P%d runs for %d units\n", p[i].id, time_slice);

                p[i].remaining_time -= time_slice;

                if (p[i].remaining_time <= 0) {
                    p[i].completed = 1;
                    total_weight -= p[i].weight;
                    printf("Process P%d completed\n", p[i].id);
                }
            }
        }

        if (all_done)
            break;
    }


    printf("All processes completed.\n");


    return 0;
}
