#include <stdio.h>

typedef struct {
    int pid;
    int bt;
    int wt;
    int tt;
    int sum_slice;
} process;


int main()
{
    int size;
    printf("Enter number of processes:\n");
    scanf("%d",&size);
    int bt[size];
    process processes[size];
    for(int i=0 ; i<size; i++){
        printf("Enter cpu burst time for process %d:\n", i+1);
        scanf("%d",&bt[i]);
        process p;
        p.bt = bt[i];
        p.wt = 0;
        p.pid=i;
        processes[i] = p;
        processes[i].sum_slice = 0;
    }

    int timeQuantom;
    int time = 0;
    printf("Enter time quantom\n");
    scanf("%d",&timeQuantom);
    int condition = 1;
    int i=0;
    while(condition>0){
        if(processes[i].bt>=timeQuantom){
            processes[i].bt -= timeQuantom;
            processes[i].wt += (time - processes[i].sum_slice );
            time += timeQuantom;
            processes[i].sum_slice = time;
            printf("process %d\n",i+1);
            printf("time = %d\n",time);
            printf("sum_slice = %d, burstTime = %d, WaitingTime = %d\n",processes[i].sum_slice, processes[i].bt, processes[i].wt);
        }
        else{
            if (processes[i].bt != 0){ 
                int temp = processes[i].bt;
                processes[i].bt = 0;
                processes[i].wt += (time - processes[i].sum_slice);
                time += temp;
                processes[i].sum_slice = time;
                printf("process %d\n",i+1);
                printf("time = %d\n",time);
                printf("sum_slice = %d, burstTime = %d, WaitingTime = %d\n",processes[i].sum_slice, processes[i].bt, processes[i].wt);
            }
            else if (processes[i].bt == 0){
                processes[i].tt = time;
            }
        }
    i++;
        if(i==size){
            i=0;
        }
        condition = 0;
        for(int j=0 ; j<size ; j++){
            if(processes[j].bt !=0){
                condition = 1;
            }
        }
    }


    //for(int i=0 ; i<size; i++){
      //  printf("waiting time: %d\n",processes[i].wt);
        //printf("turnaround time: %d\n",processes[i].tt);
    //}

   double waitSum, waitAvg, ttSum, ttAvg;
    for(int i=0 ; i<size; i++){
        printf("i: %d, pid: %d, bt: %d, wt: %d, tt: %d\n", i, processes[i].pid, processes[i].bt, processes[i].wt, processes[i].tt);
        waitSum += processes[i].wt;
        ttSum += processes[i].tt;
    }

    waitAvg = waitSum/size;
    ttAvg = ttSum/size;


    printf("Waiting Time Avg = %f\n", waitAvg);
    printf("Turnaround Time Avg = %f\n", ttAvg);

    return 0;
}
