11
#include <stdio.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child PID: %d\n", getpid());
        printf("Hello World\n");
    } else {
        printf("Parent PID: %d\n", getpid());
        printf("Hi\n");
    }
    return 0;
}

#include <stdio.h>
int main() {
    int pages[] = {0,2,1,6,4,0,1,0,3,1,2,1};
    int n = 3, frame[10], k = 0, pf = 0;
    for (int i = 0; i < n; i++) frame[i] = -1;
    for (int i = 0; i < 12; i++) {
        int found = 0;
        for (int j = 0; j < n; j++)
            if (frame[j] == pages[i]) found = 1;
        if (!found) {
            frame[k] = pages[i];
            k = (k + 1) % n;
            pf++;
        }
    }
    printf("Page Faults = %d\n", pf);
    return 0;
}

#include <stdio.h>
#include <limits.h>
#define N 5
int cost[N][N]={{0,1,4,0,0},{1,0,2,7,0},{4,2,0,3,5},{0,7,3,0,1},{0,0,5,1,0}};
int h[]={7,6,2,1,0};
int main() {
    int g[N], vis[N], cur = 0;
    for(int i=0;i<N;i++){g[i]=INT_MAX;vis[i]=0;}
    g[cur]=0;
    while(cur!=4) {
        vis[cur]=1;
        for(int i=0;i<N;i++)
            if(cost[cur][i] && !vis[i] && g[i]>g[cur]+cost[cur][i])
                g[i]=g[cur]+cost[cur][i];
        int f=INT_MAX, next=-1;
        for(int i=0;i<N;i++)
            if(!vis[i] && g[i]+h[i]<f){f=g[i]+h[i];next=i;}
        cur=next;
    }
    printf("Min Cost: %d\n", g[4]);
    return 0;
}
