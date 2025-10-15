16
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    pid_t pid = fork();
    if (pid > 0) {
        printf("Parent process sleeping\n");
        sleep(10);
        system("ps -l");
    } else {
        printf("Child exiting\n");
        exit(0);
    }
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
#include <stdio.h>
int main() {
    int n, m;
    printf("Enter processes and resources: ");
    scanf("%d%d", &n, &m);
    int alloc[10][10], max[10][10], avail[10], need[10][10], done[10]={0}, safe[10];
    printf("Allocation:\n");
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)scanf("%d",&alloc[i][j]);
    printf("Max:\n");
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)scanf("%d",&max[i][j]);
    printf("Available:\n");
    for(int i=0;i<m;i++)scanf("%d",&avail[i]);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)need[i][j]=max[i][j]-alloc[i][j];
    int count=0;
    while(count<n){
        int found=0;
        for(int p=0;p<n;p++){
            if(!done[p]){
                int j;
                for(j=0;j<m;j++) if(need[p][j]>avail[j]) break;
                if(j==m){
                    for(j=0;j<m;j++)avail[j]+=alloc[p][j];
                    safe[count++]=p;done[p]=1;found=1;
                }
            }
        }
        if(!found)break;
    }
    if(count==n){for(int i=0;i<n;i++)printf("P%d ",safe[i]);}
    else printf("Unsafe state\n");
    return 0;
}
