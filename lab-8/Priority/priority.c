#include <stdio.h>

struct process{
    int pid;
    int bt;
    int wt, tt;
    int priority;
};

void swap(int x, int y){
    int temp = x;
    x = y;
    y = temp;
}

int main() {
    int n;
    printf("Enter number of processes:\n");
    scanf("%d",&n);
    int bt[n];
    int pt[n];
    struct process processes[n];
    struct process sorted[n];
    for(int i=0 ; i<n; i++){
        printf("Enter cpu burst time for process %d:\n", i+1);
        scanf("%d",&bt[i]);
        printf("Enter priority for process %d:\n", i+1);
        scanf("%d",&pt[i]);
        struct process p;
        p.bt = bt[i];
        p.priority = pt[i];
        p.pid=i;
        processes[i] = p;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].priority > processes[j].priority)
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