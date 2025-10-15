13
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
int main() {
    pid_t pid=fork();
    if(pid==0){
        nice(10);
        printf("Child priority increased\n");
    } else {
        printf("Parent running normally\n");
    }
    return 0;
}
#include <stdio.h>
int main() {
    int alloc[5][4]={{0,0,1,2},{1,0,0,0},{1,3,5,4},{0,6,3,2},{0,0,1,4}};
    int max[5][4]={{0,0,1,2},{1,7,5,0},{2,3,5,6},{0,6,5,2},{0,6,5,6}};
    int avail[4]={1,5,2,0},need[5][4],done[5]={0},safe[5],count=0;
    for(int i=0;i<5;i++)
        for(int j=0;j<4;j++)
            need[i][j]=max[i][j]-alloc[i][j];
    while(count<5){
        int found=0;
        for(int p=0;p<5;p++){
            if(!done[p]){
                int j;
                for(j=0;j<4;j++)
                    if(need[p][j]>avail[j]) break;
                if(j==4){
                    for(j=0;j<4;j++) avail[j]+=alloc[p][j];
                    safe[count++]=p;
                    done[p]=1;
                    found=1;
                }
            }
        }
        if(!found) break;
    }
    if(count==5){
        printf("Safe Sequence: ");
        for(int i=0;i<5;i++) printf("P%d ",safe[i]);
    } else printf("System not in safe state\n");
    return 0;
}
#include <stdio.h>
int main(){
    int n;
    printf("Enter processes: ");
    scanf("%d",&n);
    int bt[10],at[10],wt[10],tat[10],done[10]={0},t=0,count=0;
    for(int i=0;i<n;i++){
        printf("Arrival & Burst: ");
        scanf("%d%d",&at[i],&bt[i]);
    }
    while(count<n){
        int min=999,pos=-1;
        for(int i=0;i<n;i++)
            if(!done[i] && at[i]<=t && bt[i]<min){min=bt[i];pos=i;}
        if(pos==-1){t++;continue;}
        t+=bt[pos];
        tat[pos]=t-at[pos];
        wt[pos]=tat[pos]-bt[pos];
        done[pos]=1;count++;
    }
    float awt=0,atat=0;
    for(int i=0;i<n;i++){awt+=wt[i];atat+=tat[i];}
    printf("Avg WT=%.2f\nAvg TAT=%.2f\n",awt/n,atat/n);
    return 0;
}
