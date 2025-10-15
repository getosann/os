6
#include <stdio.h>
#include <time.h>
int main() {
    clock_t start, end;
    double cpu_time;
    start = clock();
    for(long i=0;i<100000000;i++);
    end = clock();
    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", cpu_time);
    return 0;
}


#include <stdio.h>
int main() {
    int pages[] = {3,4,5,6,3,4,7,3,4,5,6,7,2,4,6};
    int n=3, size=15, frame[10], count=0, pf=0;
    for(int i=0;i<n;i++) frame[i]=-1;
    for(int i=0;i<size;i++) {
        int avail=0;
        for(int j=0;j<n;j++) if(frame[j]==pages[i]) avail=1;
        if(avail==0) { frame[count++%n]=pages[i]; pf++; }
    }
    printf("Total Page Faults: %d\n",pf);
    return 0;
}



#include <stdio.h>
#include <limits.h>
#define N 5
int cost[N][N]={{0,1,4,0,0},{1,0,2,7,0},{4,2,0,3,5},{0,7,3,0,1},{0,0,5,1,0}};
int h[]={7,6,2,1,0};
int visited[N];
void astar(int start,int goal){
    int g[N]; for(int i=0;i<N;i++){g[i]=INT_MAX;visited[i]=0;}
    g[start]=0;
    int cur=start;
    while(cur!=goal){
        visited[cur]=1;
        for(int i=0;i<N;i++)
            if(cost[cur][i] && !visited[i] && g[i]>g[cur]+cost[cur][i])
                g[i]=g[cur]+cost[cur][i];
        int fmin=INT_MAX,next=-1;
        for(int i=0;i<N;i++)
            if(!visited[i] && g[i]+h[i]<fmin){fmin=g[i]+h[i];next=i;}
        cur=next;
    }
    printf("Cost from %d to %d: %d\n",start,goal,g[goal]);
}
int main(){
    astar(0,4);
    return 0;
}
