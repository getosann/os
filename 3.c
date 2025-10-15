3
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t pid=fork();
    if(pid<0) exit(1);
    if(pid==0){
        execl("/bin/ls","ls","-l",(char*)0);
        exit(0);
    }else{
        wait(NULL);
        printf("Parent PID=%d Child finished\n",getpid());
    }
    return 0;
}





#include <stdio.h>
#include <stdlib.h>

int main(){
    int n,i;
    scanf("%d",&n);
    int at[n],bt[n],ct[n],wt[n],tat[n],pid[n];
    for(i=0;i<n;i++){ scanf("%d %d",&at[i],&bt[i]); pid[i]=i;}
    int t=0,completed=0,idx;
    while(completed<n){
        idx=-1;
        for(i=0;i<n;i++) if(ct[i]==0){
            if(at[i]<=t){
                idx=i; break;
            }
        }
        if(idx==-1){
            t++;
            continue;
        }
        ct[idx]=t+bt[idx];
        tat[idx]=ct[idx]-at[idx];
        wt[idx]=tat[idx]-bt[idx];
        t=ct[idx];
        completed++;
    }
    double aw=0,atime=0;
    for(i=0;i<n;i++){ printf("P%d AT=%d BT=%d CT=%d TAT=%d WT=%d\n",pid[i],at[i],bt[i],ct[i],tat[i],wt[i]); aw+=wt[i]; atime+=tat[i];}
    printf("Average WT=%.2f\nAverage TAT=%.2f\n",aw/n,atime/n);
    return 0;
}








#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int state[9];
    int g,h,f;
    struct Node *parent;
    struct Node *next;
}Node;

int goal[9]={1,2,3,4,5,6,7,8,0};

int heuristic(int s[]){
    int i,mis=0;
    for(i=0;i<9;i++) if(s[i]!=0 && s[i]!=goal[i]) mis++;
    return mis;
}

int equal_state(int a[],int b[]){
    int i;
    for(i=0;i<9;i++) if(a[i]!=b[i]) return 0;
    return 1;
}

Node* pop_lowest(Node **open){
    Node *p=*open,*prev=NULL,*best=p,*bprev=NULL;
    while(p){
        if(p->f < best->f){ best=p; bprev=prev;}
        prev=p;p=p->next;
    }
    if(bprev) bprev->next=best->next; else *open=best->next;
    best->next=NULL;
    return best;
}

int in_list(Node *head,int state[]){
    Node *p=head;
    while(p){ if(equal_state(p->state,state)) return 1; p=p->next;}
    return 0;
}

void push(Node **list,Node *n){
    n->next=*list; *list=n;
}

void print_state(int s[]){
    int i;
    for(i=0;i<9;i++){
        printf("%d ",s[i]);
        if(i%3==2) printf("\n");
    }
    printf("\n");
}

int neighbors(int s[],int out[][9]){
    int i,pos;
    for(i=0;i<9;i++) if(s[i]==0) pos=i;
    int moves[4]={-3,3,-1,1},count=0;
    int r=pos/3,c=pos%3;
    int k;
    for(k=0;k<4;k++){
        int np=pos+moves[k];
        int nr=np/3,nc=np%3;
        if(np<0||np>8) continue;
        if(abs((pos%3)-(np%3))>1) continue;
        memcpy(out[count],s,9*sizeof(int));
        out[count][pos]=out[count][np];
        out[count][np]=0;
        count++;
    }
    return count;
}

int main(){
    int start[9];
    for(int i=0;i<9;i++) scanf("%d",&start[i]);
    Node *open=NULL,*closed=NULL;
    Node *s=(Node*)malloc(sizeof(Node));
    memcpy(s->state,start,9*sizeof(int));
    s->g=0; s->h=heuristic(start); s->f=s->g+s->h; s->parent=NULL; s->next=NULL;
    push(&open,s);
    int found=0;
    Node *goalNode=NULL;
    while(open){
        Node *cur=pop_lowest(&open);
        if(equal_state(cur->state,goal)){ found=1; goalNode=cur; break;}
        push(&closed,cur);
        int nb[4][9];
        int cnt=neighbors(cur->state,nb);
        for(int i=0;i<cnt;i++){
            if(in_list(closed,nb[i])) continue;
            if(!in_list(open,nb[i])){
                Node *nn=(Node*)malloc(sizeof(Node));
                memcpy(nn->state,nb[i],9*sizeof(int));
                nn->g=cur->g+1;
                nn->h=heuristic(nb[i]);
                nn->f=nn->g+nn->h;
                nn->parent=cur;
                nn->next=NULL;
                push(&open,nn);
            }
        }
    }
    if(found){
        Node *p=goalNode;
        Node *path[1000];
        int c=0;
        while(p){ path[c++]=p; p=p->parent;}
        for(int i=c-1;i>=0;i--) print_state(path[i]->state);
    }else printf("No solution\n");
    return 0;
}
