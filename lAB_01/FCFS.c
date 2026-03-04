#include <stdio.h>

int main() {
int n, bt[20], wt[20], tat[20], at[20], ct[20];
int i;
float twt = 0.0, ttat = 0.0, awt, att;

printf("Enter the number of processes: ");
scanf("%d", &n);

// Input Arrival Time and Burst Time
for (i = 0; i < n; i++) {
printf("Enter Arrival Time for Process %d: ", i + 1);
scanf("%d", &at[i]);
printf("Enter Burst Time for Process %d: ", i + 1);
scanf("%d", &bt[i]);
}

// FCFS Scheduling
ct[0] = at[0] + bt[0]; // Completion time of first process
wt[0] = 0; // Waiting time of first process
tat[0] = bt[0]; // Turnaround time

for (i = 1; i < n; i++) {
if (ct[i - 1] < at[i]) {
ct[i] = at[i] + bt[i]; // CPU idle
wt[i] = 0;
} else {
wt[i] = ct[i - 1] - at[i];
ct[i] = ct[i - 1] + bt[i];
}
tat[i] = wt[i] + bt[i];

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
