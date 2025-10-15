10
#include <stdio.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        sleep(5);
        printf("Child process running, parent dead\n");
    } else {
        printf("Parent exiting\n");
    }
    return 0;
}

#include <stdio.h>
int main() {
    int pages[] = {12,15,12,18,6,8,11,12,19,12,6,8,12,15,19,8};
    int n = 3, frame[10], pf = 0;
    for (int i = 0; i < n; i++) frame[i] = -1;
    for (int i = 0; i < 16; i++) {
        int avail = 0;
        for (int j = 0; j < n; j++)
            if (frame[j] == pages[i]) avail = 1;
        if (!avail) {
            int rep = -1, farthest = -1;
            for (int j = 0; j < n; j++) {
                int k;
                for (k = i + 1; k < 16; k++)
                    if (frame[j] == pages[k]) break;
                if (k > farthest) { farthest = k; rep = j; }
            }
            frame[rep == -1 ? 0 : rep] = pages[i];
            pf++;
        }
    }
    printf("Page Faults = %d\n", pf);
    return 0;
}
#include <stdio.h>
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[10], bt[10], wt[10], tat[10];
    for (int i = 0; i < n; i++) {
        printf("Arrival and Burst: ");
        scanf("%d%d", &at[i], &bt[i]);
    }
    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1] - at[i];
        if (wt[i] < 0) wt[i] = 0;
    }
    for (int i = 0; i < n; i++) tat[i] = wt[i] + bt[i];
    float awt = 0, atat = 0;
    for (int i = 0; i < n; i++) { awt += wt[i]; atat += tat[i]; }
    printf("Average WT = %.2f\nAverage TAT = %.2f\n", awt / n, atat / n);
    return 0;
}
