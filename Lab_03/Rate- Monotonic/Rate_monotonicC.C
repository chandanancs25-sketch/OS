#include <stdio.h>
#include <math.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int C;        // execution time
    int T;        // period
    int priority; // 1 = highest
} Task;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

void sortByPeriod(Task tasks[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (tasks[j].T > tasks[j + 1].T) {
                Task tmp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = tmp;
            }
        }
    }
    for (int i = 0; i < n; i++)
        tasks[i].priority = i + 1;
}

void simulateRMS(Task tasks[], int n, int simLen) {
    int remaining[MAX_TASKS] = {0};

    printf("\n--- Step 5: Scheduling Simulation ---\n");
    printf("%-6s %-15s %-10s\n", "Time", "Running Task", "Priority");


    for (int t = 0; t < simLen; t++) {
        // Release new jobs at period boundaries
        for (int i = 0; i < n; i++)
            if (t % tasks[i].T == 0)
                remaining[i] += tasks[i].C;

        // Select highest priority ready task (lowest priority number)
        int sel = -1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                if (sel == -1 || tasks[i].priority < tasks[sel].priority)
                    sel = i;
            }
        }

        if (sel != -1) {
            printf("t=%-4d T%-13d %d\n", t, tasks[sel].id, tasks[sel].priority);
            remaining[sel]--;
        } else {
            printf("t=%-4d %-15s\n", t, "Idle");
        }
    }
}

int main() {
    int n;
    Task tasks[MAX_TASKS];


    printf("   Rate Monotonic Scheduling (RMS)\n");


    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nTask T%d:\n", i + 1);
        printf("  Execution time C%d: ", i + 1);
        scanf("%d", &tasks[i].C);
        printf("  Period         T%d: ", i + 1);
        scanf("%d", &tasks[i].T);
    }

    // ── Step 1: CPU Utilization ───────────────────
    printf("\n--- Step 1: CPU Utilization ---\n");
    double U = 0.0;
    for (int i = 0; i < n; i++) {
        double ui = (double)tasks[i].C / tasks[i].T;
        printf("  U%d = C%d/T%d = %d/%d = %.4f\n",
               i + 1, i + 1, i + 1, tasks[i].C, tasks[i].T, ui);
        U += ui;
    }
    printf("  Total U = %.4f\n", U);

    // ── Step 2: RMS Bound ─────────────────────────
    double bound = n * (pow(2.0, 1.0 / n) - 1.0);
    printf("\n--- Step 2: RMS Bound ---\n");
    printf("  Bound = %d * (2^(1/%d) - 1) = %.4f\n", n, n, bound);

    // ── Step 3: Schedulability Check ─────────────
    printf("\n--- Step 3: Schedulability Check ---\n");
    if (U <= bound)
        printf("  U (%.4f) <= Bound (%.4f)\n  => Schedulable using RMS\n", U, bound);
    else if (U <= 1.0)
        printf("  U (%.4f) > Bound (%.4f), but U <= 1.0\n  => Not guaranteed schedulable (need further analysis)\n", U, bound);
    else
        printf("  U (%.4f) > 1.0\n  => Not schedulable (CPU overloaded)\n", U);

    // ── Step 4: Assign Priorities ─────────────────
    sortByPeriod(tasks, n);
    printf("\n--- Step 4: Priority Assignment (smaller period = higher priority) ---\n");
    printf("  %-10s %-8s %-8s %-8s\n", "Priority", "Task", "C", "T");

    for (int i = 0; i < n; i++)
        printf("  %-10d T%-7d %-8d %-8d\n",
               tasks[i].priority, tasks[i].id, tasks[i].C, tasks[i].T);

    // ── Step 5: Simulate over LCM of all periods ──
    int simLen = tasks[0].T;
    for (int i = 1; i < n; i++)
        simLen = lcm(simLen, tasks[i].T);

    printf("\n  Simulation length = LCM of all periods = %d time units\n", simLen);
    if (simLen > 60) {
        simLen = 60;
        printf("  (Capped at 60 for display)\n");
    }

    simulateRMS(tasks, n, simLen);


    return 0;
}
