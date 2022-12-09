#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>

#define SHMSIZE 50

char *strrev(char *str);

int main(){

    key_t id = 6000;

    int shm_id = shmget(id, SHMSIZE, 0666);
    if (shm_id<0){
        perror("Reader error: Access denied");
        return 0;
    }

    char *shm = (shm = shmat(shm_id, NULL, 0)); 
        
	if(shm=="-1")
	{
		perror("Reader Error: Problem in attaching");
	        return 0;
	}

    printf("\nReader Read: ");	
	char *s = shm;
	char buff[100];
	int count=0;
	for (s = shm; *s!='\0'; s++)
        {	
		char c = *s;
		putchar(c);
		buff[count]=c;	
		count++;
	}    	
	putchar('\n');

    char *revs = strrev(buff);
	printf("\nReader Wrote: %s\n",buff);
	
	s = shm;
	*s++;
	for (int i=0;i<strlen(buff);i++)
	{
		char c = buff[i];		
		*s++ = c;
	
    }
	
	*s = '\0';
	*shm ='*';

    return 0;
}

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}