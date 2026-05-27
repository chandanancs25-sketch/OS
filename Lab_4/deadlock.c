#include <stdio.h>
int main() {
    int n, m, i, j, k;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], req[n][m];
    int avail[m], finish[n];

    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &req[i][j]);

    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Finish[i] = true if process has no allocation
    for(i = 0; i < n; i++) {
        finish[i] = 1;
        for(j = 0; j < m; j++) {
            if(alloc[i][j] != 0) {
                finish[i] = 0;
                break;
            }
        }
    }

    // Detection loop (same structure as your Banker's)
    int found = 1;
    while(found) {
        found = 0;
        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                for(j = 0; j < m; j++) {
                    if(req[i][j] > avail[j])
                        break;
                }
                if(j == m) {
                    for(k = 0; k < m; k++)
                        avail[k] += alloc[i][k];
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
    }

    // Check for deadlocked processes
    int deadlock = 0;
    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            if(!deadlock)
                printf("\nDeadlock Detected!\nDeadlocked Processes: ");
            printf("P%d ", i);
            deadlock = 1;
        }
    }
    if(!deadlock)
        printf("\nNo Deadlock. All processes completed.\n");

    return 0;
}
