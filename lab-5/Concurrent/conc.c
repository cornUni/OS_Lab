#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <pthread.h>

#define SHMSIZE 25 * sizeof(int)

sem_t mutex;

int get_counter();
void print_histogram();
void mainpulate_shm(int exp_count, int *shm);

int main(){
    int exp_count;
    printf("enter the number of experiments:\n>");
    scanf("%d", &exp_count);


    sem_init(&mutex, 1, 1);

    // create shm
    key_t id = 6000;

    int shm_id = shmget(id, SHMSIZE, IPC_CREAT | 0666);

    if (shm_id<0){
        perror("Writer error, access denied");
        return -1;
    }

    //get shm

    int *shm;
    if ((shm = shmat(shm_id, NULL, 0)) == (int *)-1)
    {
        perror("Adding address space failed");
        return -1;
    }

    //start time

    //set random
    srand(time(0));

    // make child proc's and divide tasks
    pid_t pid;
    pid = fork();
    
    clock_t start_time = clock();

    if (pid == 0){
        mainpulate_shm(exp_count, shm);
        exit (0);
    }
    else if (pid>0){
        mainpulate_shm(exp_count, shm);
        wait(NULL);
        print_histogram(shm, exp_count);
    }

    clock_t end_time = clock();
    
    
    //close sem and shm
    sem_destroy(&mutex);
    shmdt(shm);
    shmctl(shm_id, IPC_RMID, NULL);
    
    
    double duration = (double)(end_time - start_time)/ CLOCKS_PER_SEC;
    duration *= 1000;
    printf("concurrent process took %f miliseconds to complete\n", duration);

    
}

void mainpulate_shm(int exp_count, int *shm){
    for (int i = 0; i < exp_count / 2; i++)
        {
            int counter = get_counter();
            sem_wait(&mutex);
            shm[counter+12] ++;
            sem_post(&mutex);
            
        }

}

int get_counter(){
            int counter = 0;
            for (int j = 0; j < 12; j++)
            {
                int random = rand() % 101;

                if (random >=49)
                    counter++;
                else
                    counter--;
            }

            return counter;
}

void print_histogram(int *hist, int number_of_samples)
{
    printf("Histogram for sample %d:\n", number_of_samples);
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < hist[i]; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}
