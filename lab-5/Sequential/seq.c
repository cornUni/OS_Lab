#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void printHistogram(int *hist){
    int i,j;
    for(i=0; i<25; i++){
        printf("hist[%d] : ", i - 12);
        for (j = 0; j < hist[i]; j++)
        {
            printf("*");
        }
        printf("\n");
        
    }
}


int main(int argc, char const *argv[])
{
    int sample_count;
	printf("Count of samples: ");
	scanf("%d", &sample_count);

    if (sample_count <= 0)
        return 0;
    

    srand(time(NULL));
    clock_t start_time = clock();

    int hist[25] = {0};



    for (int i = 0; i < sample_count; i++)
    {
        int counter = 0;
        for (int j = 0; j < 12; j++)
        {
            int random = rand() % 101;
            if (random >= 49)
                counter++;
            else
                counter--;
        }

        hist[12+counter]++;
        
    }

    clock_t end_time = clock();

    double duration = (double)(end_time - start_time)/ CLOCKS_PER_SEC;
    duration *= 1000;
    printf("Sequential process took %f miliseconds to complete\n", duration);

    printHistogram(hist);
     
    return 0;
}


