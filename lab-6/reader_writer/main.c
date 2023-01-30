#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


int main_pid, pid;
int sharedmemid;

typedef struct shared_memory_node{
    int ctr, reader_ctr;
    pthread_mutex_t lock;
} node;


void reader(){
    node * mem = (node *)shmat(sharedmemid, 0, 0);
    //printf("%d ,%d", mem->ctr, mem->reader_ctr);
    if (mem == (node *) -1){
        printf("error occured ! line ");
        exit(-1);
    }
    int flag = 1;
    while(flag){
        mem->reader_ctr++;
        if (mem->reader_ctr == 1){
            pthread_mutex_lock(&(mem->lock));
        }
        printf("\nREADER %d STARTS on counter %d\n", getpid(),mem->ctr);
    
    if (mem->ctr >= 5) flag = 0;
    mem->reader_ctr--;
    if (mem->reader_ctr == 0){
        pthread_mutex_unlock(&(mem->lock));
    } 
    sleep(0.03);
    }
    if (shmdt(mem) == -1){
        printf("error occured ! line ");
        exit(-1);
    }
}

void writer(){
    node * mem = (node *)shmat(sharedmemid, 0, 0);
    //printf("%d ,%d", mem->ctr, mem->reader_ctr);
    if (mem == (node *) -1){
        printf("error occured ! line");
        exit(-1);
    }
    int flag = 1;
    while(flag){
        pthread_mutex_lock(&(mem->lock));
        mem->ctr++;
        printf("\nWRITER %d STARTS on counter %d\n",getpid(), mem->ctr);
        if (mem->ctr >= 5){
            flag = 0;
        }
        pthread_mutex_unlock(&(mem->lock));
        sleep(0.03);
    }
    if (shmdt(mem) == -1){
        printf("error occured ! line ");
        exit(-1);
    }
    sleep(1);
}


int main(int argc, char *argv[]){
    printf("shared memory creation process running...\n");
    sharedmemid = shmget(IPC_PRIVATE, sizeof(node), IPC_CREAT | 0666);
    //printf("%d", sharedmemid);
    if (sharedmemid < 0){
        printf("error occured! : line ");
        exit(-1);

    }
    node * shared_memory_node = (node *)shmat(sharedmemid, 0, 0);
    if (shared_memory_node == (node *) - 1){
        printf("error occured! : line ");
        exit(-1);
    }
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init((&(shared_memory_node)->lock), &attr);
    if (shmdt(shared_memory_node) == -1){
        printf("error occured! : line ");
        exit(-1);
    }
    main_pid = getpid();
    pid = fork();
    if (!pid){
        writer();
        return 0;
    }
    for (int i = 0 ; i < 2 ; ++i){
        int temp = getpid();
        if (temp == main_pid){
            pid = fork();
        }
        else{
            break;
        }
    }
    if (pid == 0){
        reader();
        return 0;
    }
    int temp = getpid();
    if (temp == main_pid){
        for (int i = 0 ; i < 3 ; ++i){
            wait(0);
        }
    }
    if (shmctl(sharedmemid, IPC_RMID, 0) == -1){
        printf("error occured! line ");
        exit(-1);
    }
    return 0;

}