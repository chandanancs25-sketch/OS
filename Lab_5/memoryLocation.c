#include <stdio.h>

void firstFit(int blocks[], int n, int proc[], int m) {
    int alloc[m];
    for (int i = 0; i < m; i++) alloc[i] = -1;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (blocks[j] >= proc[i]) { alloc[i] = j+1; blocks[j] -= proc[i]; break; }
    printf("\n--- First Fit ---\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < m; i++)
        alloc[i] == -1 ? printf("%d\t\t%d\t\tNot Allocated\n", i+1, proc[i])
                       : printf("%d\t\t%d\t\t%d\n", i+1, proc[i], alloc[i]);
}

void bestFit(int blocks[], int n, int proc[], int m) {
    int alloc[m], b[n];
    for (int i = 0; i < n; i++) b[i] = blocks[i];
    for (int i = 0; i < m; i++) alloc[i] = -1;
    for (int i = 0; i < m; i++) {
        int best = -1;
        for (int j = 0; j < n; j++)
            if (b[j] >= proc[i] && (best == -1 || b[j] < b[best])) best = j;
        if (best != -1) { alloc[i] = best+1; b[best] -= proc[i]; }
    }
    printf("\n--- Best Fit ---\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < m; i++)
        alloc[i] == -1 ? printf("%d\t\t%d\t\tNot Allocated\n", i+1, proc[i])
                       : printf("%d\t\t%d\t\t%d\n", i+1, proc[i], alloc[i]);
}

void worstFit(int blocks[], int n, int proc[], int m) {
    int alloc[m], b[n];
    for (int i = 0; i < n; i++) b[i] = blocks[i];
    for (int i = 0; i < m; i++) alloc[i] = -1;
    for (int i = 0; i < m; i++) {
        int worst = -1;
        for (int j = 0; j < n; j++)
            if (b[j] >= proc[i] && (worst == -1 || b[j] > b[worst])) worst = j;
        if (worst != -1) { alloc[i] = worst+1; b[worst] -= proc[i]; }
    }
    printf("\n--- Worst Fit ---\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < m; i++)
        alloc[i] == -1 ? printf("%d\t\t%d\t\tNot Allocated\n", i+1, proc[i])
                       : printf("%d\t\t%d\t\t%d\n", i+1, proc[i], alloc[i]);
}

int main() {
    int n, m;
    printf("Enter number of memory blocks: "); scanf("%d", &n);
    int blocks[n], orig[n];
    printf("Enter sizes of %d memory blocks:\n", n);
    for (int i = 0; i < n; i++) { scanf("%d", &blocks[i]); orig[i] = blocks[i]; }
    printf("Enter number of processes: "); scanf("%d", &m);
    int proc[m];
    printf("Enter sizes of %d processes:\n", m);
    for (int i = 0; i < m; i++) scanf("%d", &proc[i]);

    firstFit(orig, n, proc, m);   // pass copy for first fit
    bestFit(orig, n, proc, m);
    worstFit(orig, n, proc, m);
    return 0;
}
