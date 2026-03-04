#include <stdio.h>

//SRTF

int main() {
    int n, bt[20], wt[20], tat[20], at[20], ct[20], rt[20];
    int i, time = 0, count = 0, min_index;
    float twt = 0.0, ttat = 0.0, awt, att;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input Arrival Time and Burst Time
    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   // Remaining Time
    }

    while (count < n) {
        int min_rt = 9999;
        min_index = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                if (rt[i] < min_rt) {
                    min_rt = rt[i];
                    min_index = i;
                }
            }
        }

        if (min_index != -1) {
            rt[min_index]--;
            time++;

            if (rt[min_index] == 0) {
                ct[min_index] = time;
                tat[min_index] = ct[min_index] - at[min_index];
                wt[min_index] = tat[min_index] - bt[min_index];
                count++;
            }
        } else {
            time++;   // CPU idle
        }
    }

    // Calculate averages
    for (i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
    }

    awt = twt / n;
    att = ttat / n;

    // Output Table
    printf("\nPROCESS\tAT\tBT\tCT\tWT\tTAT");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", awt);
    printf("\nAverage Turnaround Time = %.2f\n", att);

    return 0;
}
