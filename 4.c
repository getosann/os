4
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pid=fork();
    if(pid<0) exit(1);
    if(pid==0){
        sleep(2);
        printf("Child: my PID=%d my parent PID=%d\n",getpid(),getppid());
        exit(0);
    }else{
        printf("Parent PID=%d exiting\n",getpid());
        exit(0);
    }
    return 0;
}





#include <stdio.h>
#include <stdlib.h>

int main(){
    int n,i,j;
    scanf("%d",&n);
    int at[n],bt[n],pr[n],ct[n],wt[n],tat[n],done[n];
    for(i=0;i<n;i++) scanf("%d %d %d",&at[i],&bt[i],&pr[i]);
    for(i=0;i<n;i++) done[i]=0;
    int t=0,completed=0;
    while(completed<n){
        int idx=-1;
        for(i=0;i<n;i++) if(!done[i] && at[i]<=t){
            if(idx==-1 || pr[i]<pr[idx]) idx=i;
        }
        if(idx==-1){ t++; continue;}
        ct[idx]=t+bt[idx];
        tat[idx]=ct[idx]-at[idx];
        wt[idx]=tat[idx]-bt[idx];
        t=ct[idx];
        done[idx]=1;
        completed++;
    }
    double aw=0,atime=0;
    for(i=0;i<n;i++){ printf("P%d AT=%d BT=%d PR=%d CT=%d TAT=%d WT=%d\n",i,at[i],bt[i],pr[i],ct[i],tat[i],wt[i]); aw+=wt[i]; atime+=tat[i];}
    printf("Average WT=%.2f\nAverage TAT=%.2f\n",aw/n,atime/n);
    return 0;
}






#include <stdio.h>
#include <stdlib.h>

int safe_state(int n,int m,int avail[],int alloc[][10],int max[][10],int need[][10],int seq[]){
    int finish[20]={0};
    int work[10],i,j;
    for(i=0;i<m;i++) work[i]=avail[i];
    int count=0;
    while(count<n){
        int found=0;
        for(i=0;i<n;i++){
            if(!finish[i]){
                int ok=1;
                for(j=0;j<m;j++) if(need[i][j]>work[j]) {ok=0;break;}
                if(ok){
                    for(j=0;j<m;j++) work[j]+=alloc[i][j];
                    seq[count++]=i;
                    finish[i]=1;
                    found=1;
                }
            }
        }
        if(!found) break;
    }
    return (count==n);
}

int main(){
    int n,m,i,j;
    scanf("%d %d",&n,&m);
    int alloc[20][10],max[20][10],need[20][10],avail[10],seq[20];
    for(i=0;i<n;i++) for(j=0;j<m;j++) scanf("%d",&alloc[i][j]);
    for(i=0;i<n;i++) for(j=0;j<m;j++) scanf("%d",&max[i][j]);
    for(i=0;i<m;i++) scanf("%d",&avail[i]);
    for(i=0;i<n;i++) for(j=0;j<m;j++) need[i][j]=max[i][j]-alloc[i][j];
    for(i=0;i<n;i++){
        for(j=0;j<m;j++) printf("%d ",need[i][j]);
        printf("\n");
    }
    if(safe_state(n,m,avail,alloc,max,need,seq)){
        printf("Safe\n");
        for(i=0;i<n;i++) printf("P%d ",seq[i]);
        printf("\n");
    }else printf("Not Safe\n");
    return 0;
}
