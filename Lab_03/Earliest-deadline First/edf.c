#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int id;
    int arrival;    // arrival time
    int burst;      // total execution time (Ci)
    int deadline;   // absolute deadline (Di)
    int remaining;  // remaining execution time
    int completed;  // 0 = not done, 1 = done
} Process;

int main() {
    int n;
    Process p[MAX_PROCESSES];


    printf("   Earliest Deadline First (EDF)\n");


    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        p[i].completed = 0;
        printf("\nProcess P%d:\n", i + 1);
        printf("  Arrival time  : ");
        scanf("%d", &p[i].arrival);
        printf("  Burst time C%d : ", i + 1);
        scanf("%d", &p[i].burst);
        printf("  Deadline   D%d : ", i + 1);
        scanf("%d", &p[i].deadline);
        p[i].remaining = p[i].burst;
    }

    // ── Step 1: CPU Utilization ───────────────────
    printf("\n--- Step 1: CPU Utilization ---\n");
    double U = 0.0;
    for (int i = 0; i < n; i++) {
        double ui = (double)p[i].burst / p[i].deadline;
        printf("  U%d = C%d/D%d = %d/%d = %.4f\n",
               i + 1, i + 1, i + 1,
               p[i].burst, p[i].deadline, ui);
        U += ui;
    }
    printf("  Total U = %.4f\n", U);

    // ── Step 2: Feasibility Check ─────────────────
    printf("\n--- Step 2: Feasibility Check ---\n");
    if (U > 1.0)
        printf("  U (%.4f) > 1.0\n  => Scheduling not feasible (deadlines may be missed)\n", U);
    else
        printf("  U (%.4f) <= 1.0\n  => Scheduling feasible\n", U);

    // ── Step 3 & 4: EDF Simulation ────────────────
    printf("\n--- Step 3 & 4: EDF Scheduling Simulation ---\n");
    printf("%-6s %-12s %-10s %-10s\n", "Time", "Running", "Deadline", "Remaining");


    int t = 0;
    int done = 0;

    // find max time limit to avoid infinite loop
    int maxTime = 0;
    for (int i = 0; i < n; i++)
        maxTime += p[i].burst;

    while (done < n && t <= maxTime) {

        // Build ready list — arrived and not completed
        int ready[MAX_PROCESSES];
        int readyCount = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= t && !p[i].completed)
                ready[readyCount++] = i;
        }

        // No process ready — CPU idle
        if (readyCount == 0) {
            printf("t=%-4d %-12s\n", t, "Idle");
            t++;
            continue;
        }

        // Select process with earliest deadline
        int sel = ready[0];
        for (int i = 1; i < readyCount; i++) {
            if (p[ready[i]].deadline < p[sel].deadline)
                sel = ready[i];
        }

        // Execute for 1 time unit
        printf("t=%-4d P%-11d %-10d %-10d\n",
               t,
               p[sel].id,
               p[sel].deadline,
               p[sel].remaining - 1);

        p[sel].remaining--;

        // Check if completed
        if (p[sel].remaining == 0) {
            p[sel].completed = 1;
            done++;
            int missed = (t + 1 > p[sel].deadline) ? 1 : 0;
            printf("       >> P%d completed at t=%d | Deadline: %d | %s\n",
                   p[sel].id,
                   t + 1,
                   p[sel].deadline,
                   missed ? "DEADLINE MISSED!" : "Deadline met");
        }

        t++;
    }

    // ── Summary ───────────────────────────────────
    printf("\n--- Summary ---\n");
    printf("%-10s %-10s %-10s %-15s\n", "Process", "Deadline", "Completed", "Status");

    for (int i = 0; i < n; i++) {
        int finishTime = p[i].burst + p[i].arrival; // approximate
        printf("  P%-8d %-10d %-10s\n",
               p[i].id,
               p[i].deadline,
               p[i].completed ? "Yes" : "No");
    }

    return 0;
}
