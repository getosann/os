2
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t pid=fork();
    if(pid<0) exit(1);
    if(pid==0){
        printf("Child PID=%d: Hello World\n",getpid());
        exit(0);
    }else{
        wait(NULL);
        printf("Parent PID=%d: Hi\n",getpid());
    }
    return 0;
}




#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int n,i,j;
    scanf("%d",&n);
    int at[n],bt[n],ct[n],wt[n],tat[n],pid[n],done[n];
    for(i=0;i<n;i++){ scanf("%d %d",&at[i],&bt[i]); pid[i]=i; done[i]=0;}
    int t=0,completed=0;
    while(completed<n){
        int idx=-1;
        for(i=0;i<n;i++) if(!done[i] && at[i]<=t){
            if(idx==-1 || bt[i]<bt[idx]) idx=i;
        }
        if(idx==-1){
            t++;
            continue;
        }
        ct[idx]=t+bt[idx];
        tat[idx]=ct[idx]-at[idx];
        wt[idx]=tat[idx]-bt[idx];
        t=ct[idx];
        done[idx]=1;
        completed++;
    }
    double aw=0,atime=0;
    for(i=0;i<n;i++){ printf("P%d AT=%d BT=%d CT=%d TAT=%d WT=%d\n",pid[i],at[i],bt[i],ct[i],tat[i],wt[i]); aw+=wt[i]; atime+=tat[i];}
    printf("Average WT=%.2f\nAverage TAT=%.2f\n",aw/n,atime/n);
    return 0;
}










#include <stdio.h>
#include <stdlib.h>

int main(){
    int n=5,m=3,i,j;
    int alloc[20][10]={{0,0,1},{1,0,0},{1,3,5},{0,6,3},{0,0,1}};
    int max[20][10]={{0,0,1},{1,7,5},{2,3,5},{0,6,5},{0,6,5}};
    int avail[10]={7,2,6};
    int need[20][10];
    for(i=0;i<n;i++) for(j=0;j<m;j++) need[i][j]=max[i][j]-alloc[i][j];
    int choice;
    while(1){
        scanf("%d",&choice);
        if(choice==1){
            for(i=0;i<m;i++) scanf("%d",&avail[i]);
        }else if(choice==2){
            for(i=0;i<n;i++){ for(j=0;j<m;j++) printf("%d ",alloc[i][j]); printf("\n");}
            for(i=0;i<n;i++){ for(j=0;j<m;j++) printf("%d ",max[i][j]); printf("\n");}
        }else if(choice==3){
            for(i=0;i<n;i++){ for(j=0;j<m;j++) printf("%d ",need[i][j]); printf("\n");}
        }else if(choice==4){
            for(i=0;i<m;i++) printf("%d ",avail[i]);
            printf("\n");
        }else break;
    }
    return 0;
}
