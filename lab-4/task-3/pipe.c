#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE  200


void reverse_string(char str[]);

int main(int argc, char* argv[]) {
    int fd[2];
    if (pipe(fd) == -1) {
        return 1;
    }
    
    int pid = fork();
    if (pid == -1) {
        perror("Some error occurred in creating child process");
        return -1;
    }
    
    if (pid == 0) {
        close(fd[0]);
    
        char str[SIZE];
        printf("Input string: ");
        fgets(str, SIZE, stdin);
        str[strlen(str) - 1] = '\0';
        
        int n = strlen(str) + 1;
        if (write(fd[1], &n, sizeof(int)) < 0) {
            return -1;
        }
        
        if (write(fd[1], &str, sizeof(char) * n) < 0) {
            return -1;
        }
        
        close(fd[1]);
    } else {
        close(fd[1]);
        char str[SIZE];
        int n;
        
        if (read(fd[0], &n, sizeof(int)) < 0) {
            return -1;
        }
        if (read(fd[0], &str, sizeof(int) * n) < 0) {
            return -1;
        }
        reverse_string(str);
        
        close(fd[0]);
        wait(NULL);
    }
    
    return 0;
}


void reverse_string(char str[SIZE]){
    for (size_t i = 0; i < strlen(str); i++)
    {
        char c = str[i];
        if(c >= 'a' && c <= 'z') {
            str[i] = str[i] - 32;
            continue;
            }
            if(c >= 'A' && c <= 'Z') {
            str[i] = str[i] + 32;
            continue;
            }
    }

    printf("%s\n", str);
    
}