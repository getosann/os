8
#include <stdio.h>
int main() {
    int p, r;
    printf("Enter number of processes and resources: ");
    scanf("%d%d", &p, &r);
    int alloc[10][10], max[10][10], need[10][10];
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);
    printf("Enter Max Matrix:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    return 0;
}

#include <stdio.h>
#include <limits.h>
#define N 5
int main() {
    int cost[N][N]={{0,1,2,0,0},{0,0,0,3,4},{0,0,0,6,0},{0,0,0,0,0},{0,0,0,0,0}};
    int h[N]={7,4,6,0,0};
    int open[N]={0},closed[N]={0},g[N],i,j;
    for(i=0;i<N;i++) g[i]=INT_MAX;
    g[0]=0;
    int cur=0;
    while(cur!=3 && cur!=4){
        closed[cur]=1;
        for(i=0;i<N;i++)
            if(cost[cur][i] && !closed[i] && g[i]>g[cur]+cost[cur][i])
                g[i]=g[cur]+cost[cur][i];
        int f=INT_MAX,next=-1;
        for(i=0;i<N;i++)
            if(!closed[i] && g[i]+h[i]<f){f=g[i]+h[i];next=i;}
        cur=next;
    }
    printf("Minimum cost: %d\n", g[cur]);
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
