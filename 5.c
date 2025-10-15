5
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdlib.h>

int main(){
    pid_t pid=fork();
    if(pid<0) exit(1);
    if(pid==0){
        setpriority(PRIO_PROCESS,0,5);
        printf("Child PID=%d nice=%d\n",getpid(),getpriority(PRIO_PROCESS,0));
        exit(0);
    }else{
        wait(NULL);
        printf("Parent PID=%d nice=%d\n",getpid(),getpriority(PRIO_PROCESS,0));
    }
    return 0;
}



#include <stdio.h>
#include <stdlib.h>

int main(){
    int frames;
    scanf("%d",&frames);
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

int main(){
    int n=3,m=3,i,j;
    int alloc[10][10]={{0,1,0},{2,0,0},{3,0,2}};
    int max[10][10]={{7,5,3},{3,2,2},{9,0,2}};
    int avail[10]={3,3,2};
    int need[10][10];
    for(i=0;i<n;i++) for(j=0;j<m;j++) need[i][j]=max[i][j]-alloc[i][j];
    int choice;
    while(scanf("%d",&choice)==1){
        if(choice==1) for(i=0;i<m;i++) scanf("%d",&avail[i]);
        else if(choice==2){
            for(i=0;i<n;i++){ for(j=0;j<m;j++) printf("%d ",alloc[i][j]); printf("\n");}
            for(i=0;i<n;i++){ for(j=0;j<m;j++) printf("%d ",max[i][j]); printf("\n");}
        }else if(choice==3){
            for(i=0;i<n;i++){ for(j=0;j<m;j++) printf("%d ",need[i][j]); printf("\n");}
        }else if(choice==4){
            for(i=0;i<m;i++) printf("%d ",avail[i]); printf("\n");
        }else break;
    }
    return 0;
}

