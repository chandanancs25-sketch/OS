#include <stdio.h>

void fifo(int pages[], int n, int frames) {
    int frame[frames], front = 0, faults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    printf("\nFIFO Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) if (frame[j] == pages[i]) { found = 1; break; }
        if (!found) {
            frame[front] = pages[i];
            front = (front + 1) % frames;
            faults++;
            printf("PF No. %d: ", faults);
            for (int j = 0; j < frames; j++) frame[j] == -1 ? printf("- ") : printf("%d ", frame[j]);
            printf("\n");
        }
    }
    printf("FIFO Page Faults: %d\n", faults);
}

void lru(int pages[], int n, int frames) {
    int frame[frames], recent[frames], faults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    printf("\nLRU Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int found = -1;
        for (int j = 0; j < frames; j++) if (frame[j] == pages[i]) { found = j; break; }
        if (found == -1) {
            int lruIdx = 0;
            // find empty or least recently used
            int empty = -1;
            for (int j = 0; j < frames; j++) if (frame[j] == -1) { empty = j; break; }
            if (empty != -1) lruIdx = empty;
            else {
                int minTime = recent[0]; lruIdx = 0;
                for (int j = 1; j < frames; j++) if (recent[j] < minTime) { minTime = recent[j]; lruIdx = j; }
            }
            frame[lruIdx] = pages[i];
            recent[lruIdx] = i;
            faults++;
            printf("PF No. %d: ", faults);
            for (int j = 0; j < frames; j++) frame[j] == -1 ? printf("- ") : printf("%d ", frame[j]);
            printf("\n");
        } else recent[found] = i;
    }
    printf("LRU Page Faults: %d\n", faults);
}

void optimal(int pages[], int n, int frames) {
    int frame[frames], faults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    printf("\nOptimal Page Replacement Process:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) if (frame[j] == pages[i]) { found = 1; break; }
        if (!found) {
            int replaceIdx = -1, empty = -1;
            for (int j = 0; j < frames; j++) if (frame[j] == -1) { empty = j; break; }
            if (empty != -1) replaceIdx = empty;
            else {
                int farthest = -1;
                for (int j = 0; j < frames; j++) {
                    int k;
                    for (k = i+1; k < n; k++) if (pages[k] == frame[j]) break;
                    if (k > farthest) { farthest = k; replaceIdx = j; }
                }
            }
            frame[replaceIdx] = pages[i];
            faults++;
            printf("PF No. %d: ", faults);
            for (int j = 0; j < frames; j++) frame[j] == -1 ? printf("- ") : printf("%d ", frame[j]);
            printf("\n");
        }
    }
    printf("Optimal Page Faults: %d\n", faults);
}

int main() {
    int frames, n;
    printf("Enter the number of Frames: "); scanf("%d", &frames);
    printf("Enter the length of reference string: "); scanf("%d", &n);
    int pages[n];
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);
    return 0;
}
