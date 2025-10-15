17
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child running\n");
    } else {
        wait(NULL);
        printf("Parent resumed\n");
    }
    return 0;
}
#include <stdio.h>
int main() {
    int n;
    printf("Enter processes: ");
    scanf("%d", &n);
    int at[10], bt[10], rt[10];
    for (int i=0;i<n;i++) {
        printf("Arrival & Burst: ");
        scanf("%d%d",&at[i],&bt[i]);
        rt[i]=bt[i];
    }
    int complete=0,t=0;
    float twt=0,ttat=0;
    while(complete<n){
        int smallest=-1;
        for(int i=0;i<n;i++)
            if(at[i]<=t && rt[i]>0 && (smallest==-1||rt[i]<rt[smallest]))smallest=i;
        if(smallest==-1){t++;continue;}
        rt[smallest]--;t++;
        if(rt[smallest]==0){
            complete++;
            int finish=t;
            twt+=finish-at[smallest]-bt[smallest];
            ttat+=finish-at[smallest];
        }
    }
    printf("Avg WT=%.2f\nAvg TAT=%.2f\n",twt/n,ttat/n);
    return 0;
}
#include <stdio.h>
int main() {
    int pages[]={7,0,1,2,0,3,0,4,2,3,0,3,2},n=3,frame[10],count[10],pf=0,t=0;
    for(int i=0;i<n;i++)frame[i]=-1;
    for(int i=0;i<13;i++){
        int found=0;
        for(int j=0;j<n;j++)
            if(frame[j]==pages[i]){found=1;count[j]=++t;}
        if(!found){
            int lru=0;
            for(int j=1;j<n;j++)if(count[j]<count[lru])lru=j;
            frame[lru]=pages[i];
            count[lru]=++t;
            pf++;
        }
    }
    printf("Page Faults=%d\n",pf);
    return 0;
}
