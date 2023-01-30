#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>


const int n = 5;
const int e = 0;
const int h = 1;
const int t = 2;
int left(int philsopher_num){
    return (philsopher_num + 4) % n;
}
int right(int philsopher_num){
    return (philsopher_num + 1) % n;
}
int state[5];
int philsopher[5] = {0, 1, 2, 3, 4};
sem_t lock;
sem_t S[5];

void check(int philsopher_num){
    if (state[philsopher_num] == h && 
        state[left(philsopher_num)] != e &&
        state[right(philsopher_num)] != e){
            state[philsopher_num] = e;
            sleep(2);

            printf("philsopher number %d takes fork %d and %d\nphilsopher number %d is eating\n", philsopher_num + 1, left(philsopher_num) + 1 , philsopher_num + 1, philsopher_num + 1);

            sem_post(&S[philsopher_num]);
        }
}

void acquire_fork(int philsopher_num){
    sem_wait(&lock);
    state[philsopher_num] = h;

    printf("philsopher number %d is hungry\n", philsopher_num + 1);
    check(philsopher_num);
    sem_post(&lock);
    sem_wait(&S[philsopher_num]);
    sleep(1);
}
void release_fork(int philsopher_num){
    sem_wait(&lock);
    state[philsopher_num] = t;
    printf("philsopher num %d releases fork_%d and fork_%d\nphilsopher number %d is thinking\n", philsopher_num + 1 , left(philsopher_num) + 1 , philsopher_num + 1, philsopher_num + 1);

    check(left(philsopher_num));
    check(right(philsopher_num));
    sem_post(&lock);

}
void *_philsopher(void *num){
    while(1){
        int *i = num;
        sleep(1);
        acquire_fork(*i);
        sleep(0);
        release_fork(*i);    
        }
}

int main(){
    pthread_t thread_id[n];
    sem_init(&lock, 0, 1);
    for(int i = 0 ; i < n ; ++i) sem_init(&S[i], 0, 0);
    for (int i = 0 ; i < n ; ++i){
        pthread_create(&thread_id[i], 0, _philsopher, &philsopher[i]);
        printf("philsopher number %d is thinking\n", i + 1);
    }
    for (int i = 0 ; i < n ; ++i) pthread_join(thread_id[i], 0);    
}