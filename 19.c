19
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
int main(){
    pid_t pid=fork();
    if(pid==0){nice(5);printf("Child priority changed\n");}
    else printf("Parent priority default\n");
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
            if(!done[i]&&at[i]<=t&&bt[i]<min){min=bt[i];pos=i;}
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
#include <stdio.h>
int main(){
    int pages[]={1,2,3,4,1,2,5,1,2,3,4,5},n=3,frame[3],k=0,pf=0;
    for(int i=0;i<n;i++)frame[i]=-1;
    for(int i=0;i<12;i++){
        int found=0;
        for(int j=0;j<n;j++)if(frame[j]==pages[i])found=1;
        if(!found){frame[k]=pages[i];k=(k+1)%n;pf++;}
    }
    printf("Page Faults=%d\n",pf);
    return 0;
}
