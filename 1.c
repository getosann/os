1

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int main(){
    pid_t pid=fork();
    if(pid<0) exit(1);
    if(pid==0){
        setpriority(PRIO_PROCESS,0,-5);
        printf("child pid=%d priority=%d\n",getpid(),getpriority(PRIO_PROCESS,0));
        exit(0);
    }else{
        wait(NULL);
        printf("parent pid=%d priority=%d\n",getpid(),getpriority(PRIO_PROCESS,0));
    }
    return 0;
}













#include <stdio.h>
#include <stdlib.h>

int main(){
    int frames=3;
    int ref[] = {3,4,5,6,3,4,7,3,4,5,6,7,2,4,6};
    int n = sizeof(ref)/sizeof(ref[0]);
    int *f = malloc(frames*sizeof(int));
    int i,j;
    for(i=0;i<frames;i++) f[i]=-1;
    int next=0, faults=0;
    for(i=0;i<n;i++){
        int present=0;
        for(j=0;j<frames;j++) if(f[j]==ref[i]) present=1;
        if(!present){
            f[next]=ref[i];
            next=(next+1)%frames;
            faults++;
        }
        for(j=0;j<frames;j++){
            if(f[j]==-1) printf("- ");
            else printf("%d ",f[j]);
        }
        printf("\n");
    }
    printf("Total page faults: %d\n",faults);
    free(f);
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
        printf("System is in safe state\nSafe sequence: ");
        for(i=0;i<n;i++) printf("P%d ",seq[i]);
        printf("\n");
    }else{
        printf("System is not in safe state\n");
    }
    int p,req[10];
    if(scanf("%d",&p)==1){
        for(i=0;i<m;i++) scanf("%d",&req[i]);
        int ok=1;
        for(i=0;i<m;i++) if(req[i]>need[p][i] || req[i]>avail[i]) ok=0;
        if(!ok){ printf("Request cannot be granted\n"); return 0;}
        for(i=0;i<m;i++){ avail[i]-=req[i]; alloc[p][i]+=req[i]; need[p][i]-=req[i]; }
        if(safe_state(n,m,avail,alloc,max,need,seq)) printf("Request can be granted\n");
        else printf("Request cannot be granted to keep safe state\n");
    }
    return 0;
}

