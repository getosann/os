7

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/ls", "ls", NULL);
    } else {
        sleep(1);
    }
    return 0;
}




#include <stdio.h>
int main() {
    int n, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int at[10], bt[10], wt[10], tat[10];
    for (i = 0; i < n; i++) {
        printf("Arrival and Burst time: ");
        scanf("%d%d", &at[i], &bt[i]);
    }
    wt[0] = 0;
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1] - at[i];
        if (wt[i] < 0) wt[i] = 0;
    }
    for (i = 0; i < n; i++) tat[i] = wt[i] + bt[i];
    float awt = 0, atat = 0;
    for (i = 0; i < n; i++) {
        awt += wt[i];
        atat += tat[i];
    }
    printf("Average Waiting Time: %.2f\n", awt / n);
    printf("Average Turnaround Time: %.2f\n", atat / n);
    return 0;
}


#include <stdio.h>
int main() {
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};
    int n = 3, frame[10], count[10], pf = 0, time = 0;
    for (int i = 0; i < n; i++) frame[i] = -1;
    for (int i = 0; i < 13; i++) {
        int avail = 0;
        for (int j = 0; j < n; j++)
            if (frame[j] == pages[i]) { avail = 1; count[j] = ++time; }
        if (!avail) {
            int lru = 0;
            for (int j = 1; j < n; j++)
                if (count[j] < count[lru]) lru = j;
            frame[lru] = pages[i];
            count[lru] = ++time;
            pf++;
        }
    }
    printf("Total Page Faults = %d\n", pf);
    return 0;
}
