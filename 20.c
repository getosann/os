20
#include <stdio.h>
#include <unistd.h>
int main(){
    pid_t pid=fork();
    if(pid==0)execl("/bin/date","date",NULL);
    else sleep(1);
    return 0;
}
#include <stdio.h>
int main(){
    int n,tq;
    printf("Enter processes: ");
    scanf("%d",&n);
    printf("Enter time quantum: ");
    scanf("%d",&tq);
    int bt[10],rt[10];
    for(int i=0;i<n;i++){
        printf("Burst time: ");
        scanf("%d",&bt[i]);
        rt[i]=bt[i];
    }
    int t=0,done;
    do{
        done=1;
        for(int i=0;i<n;i++){
            if(rt[i]>0){
                done=0;
                if(rt[i]>tq){
                    t+=tq;
                    rt[i]-=tq;
                }else{
                    t+=rt[i];
                    rt[i]=0;
                    printf("P%d finishes at %d\n",i+1,t);
                }
            }
        }
    }while(!done);
    return 0;
}
#include <stdio.h>
int main(){
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
