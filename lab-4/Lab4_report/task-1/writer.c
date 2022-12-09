#include<stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMSIZE 50

int main (){

    key_t id = 6000;

    int shm_id = shmget(id, SHMSIZE, IPC_CREAT | 0666);

    if (shm_id<0){
        perror("Writer error, access denied");
        return 0;
    }

    char *shm = shmat(shm_id, NULL, 0);

    if (shm=="-1"){
        perror("Writter error, problem in attaching shared memory");
        return 0;
    }

    char msg[100] = "Dive into SHM";
    char *s = shm;
    printf("\n message from writer:  ");
    for (int  i = 0; i <strlen(msg); i++)
    {
        char c = msg[i];
        putchar(c);
        *s++ = c;
    }

    *s = '\0';

    printf("\nWriter Sleeping...\n");
    while (*shm!='*')
    {
        sleep(1);
    }

    printf("\nReader said::");	
	for (s = shm+1; *s!= '\0'; s++)
        	putchar(*s);
    putchar('\n');
    
    return 0;
    
}