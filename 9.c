9
#include <stdio.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) execl("/bin/ls", "ls", NULL);
    else sleep(1);
    return 0;
}

#include <stdio.h>
int main() {
    int p, r;
    printf("Enter processes and resources: ");
    scanf("%d%d", &p, &r);
    int alloc[10][10], max[10][10], avail[10], need[10][10];
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);
    for (int i = 0; i < r; i++) scanf("%d", &avail[i]);
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    printf("Need Matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) printf("%d ", need[i][j]);
        printf("\n");
    }
    printf("Available: ");
    for (int i = 0; i < r; i++) printf("%d ", avail[i]);
    printf("\n");
    return 0;
}

#include <stdio.h>
int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &tq);
    int bt[10], rt[10];
    for (int i = 0; i < n; i++) {
        printf("Burst time: ");
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }
    int t = 0, done;
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {
                done = 0;
                if (rt[i] > tq) {
                    t += tq;
                    rt[i] -= tq;
                } else {
                    t += rt[i];
                    rt[i] = 0;
                    printf("P%d finishes at %d\n", i + 1, t);
                }
            }
        }
    } while (!done);
    return 0;
}
