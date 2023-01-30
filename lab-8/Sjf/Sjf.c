#include <stdio.h>
#include <stdlib.h>
struct process{
    int pid;
    int bt;
    int wt, tt;
};

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void pprint(struct process p){
    printf("pid: %d\tburst time: %d\t waiting time: %d\tturnaround time: %d\n", p.pid, p.bt, p.wt, p.tt);
}

int main() {
    int n;
    printf("Enter number of processes:\n");
    scanf("%d",&n);
    int bt[n];
    struct process processes[n];
    struct process sorted[n];
    for(int i=0 ; i<n; i++){
        printf("Enter cpu burst time for process %d:\n", i+1);
        scanf("%d",&bt[i]);
        struct process p;
        p.bt = bt[i];
        p.pid=i;
        processes[i] = p;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].bt > processes[j].bt)
            {
                //swap pid:
                int temp =  processes[i].pid;
                processes[i].pid = processes[j].pid;
                processes[j].pid = temp;
                //swap bt:
                temp =  processes[i].bt;
                processes[i].bt = processes[j].bt;
                processes[j].bt = temp;
            }
        }
    }

    processes[0].wt = 0;
    processes[0].tt = processes[0].bt;
    for(int i=1 ; i<n; i++){
        int wt = 0;
        for(int j=0; j<i ; j++){
            wt += processes[j].bt;
        }
        processes[i].wt=wt;
    }
    for(int i=0 ; i<n; i++){
        processes[i].tt=processes[i].wt + processes[i].bt;
    }

    float wtAvg , ttAvg = 0;
    float wtSum, ttSum = 0;
    for(int i=0 ; i<n; i++){
        printf("i: %d, pid: %d, bt: %d, wt: %d, tt: %d\n", i, processes[i].pid, processes[i].bt, processes[i].wt, processes[i].tt);
        wtSum += processes[i].wt;
        ttSum += processes[i].tt;
    }
    wtAvg = wtSum/n;
    ttAvg = ttSum/n;


    printf("Waiting Time Avg = %f\n", wtAvg);
    printf("Turnaround Time Avg = %f\n", ttAvg);

    return 0;
}