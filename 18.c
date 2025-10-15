18
#include <stdio.h>
int main() {
    int n;
    printf("Enter processes: ");
    scanf("%d",&n);
    int bt[10],at[10],wt[10],tat[10];
    for(int i=0;i<n;i++){
        printf("Arrival & Burst: ");
        scanf("%d%d",&at[i],&bt[i]);
    }
    wt[0]=0;
    for(int i=1;i<n;i++){
        wt[i]=wt[i-1]+bt[i-1]-at[i];
        if(wt[i]<0)wt[i]=0;
    }
    for(int i=0;i<n;i++)tat[i]=wt[i]+bt[i];
    float awt=0,atat=0;
    for(int i=0;i<n;i++){awt+=wt[i];atat+=tat[i];}
    printf("Avg WT=%.2f\nAvg TAT=%.2f\n",awt/n,atat/n);
    return 0;
}


#include <stdio.h>
int main() {
    int pages[]={12,15,12,18,6,8,11,12,19,12,6,8,12,15,19,8},n=3,frame[10],pf=0;
    for(int i=0;i<n;i++)frame[i]=-1;
    for(int i=0;i<16;i++){
        int found=0;
        for(int j=0;j<n;j++)if(frame[j]==pages[i])found=1;
        if(!found){
            int rep=-1,far=-1;
            for(int j=0;j<n;j++){
                int k;
                for(k=i+1;k<16;k++)if(frame[j]==pages[k])break;
                if(k>far){far=k;rep=j;}
            }
            frame[rep==-1?0:rep]=pages[i];
            pf++;
        }
    }
    printf("Page Faults=%d\n",pf);
    return 0;
}
#include <stdio.h>
int main(){
    int n,m;
    printf("Processes and resources: ");
    scanf("%d%d",&n,&m);
    int alloc[10][10],max[10][10],avail[10],need[10][10],safe[10],done[10]={0};
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)scanf("%d",&alloc[i][j]);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)scanf("%d",&max[i][j]);
    for(int i=0;i<m;i++)scanf("%d",&avail[i]);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)need[i][j]=max[i][j]-alloc[i][j];
    int count=0;
    while(count<n){
        int found=0;
        for(int i=0;i<n;i++){
            if(!done[i]){
                int j;
                for(j=0;j<m;j++)if(need[i][j]>avail[j])break;
                if(j==m){
                    for(j=0;j<m;j++)avail[j]+=alloc[i][j];
                    safe[count++]=i;done[i]=1;found=1;
                }
            }
        }
        if(!found)break;
    }
    if(count==n){for(int i=0;i<n;i++)printf("P%d ",safe[i]);}
    else printf("Unsafe\n");
    return 0;
}
