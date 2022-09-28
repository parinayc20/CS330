#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
pipeline(int argc, char* argv[])
{
    if(argc != 3)
    {
        fprintf(2, "Usage : pipeline n x\n");
        exit(1);
    }

    if(atoi(argv[1]) <= 0)
    {
        fprintf(2, "n should be a positive number\n");
        exit(1);
    }

    //TODO: implement the good input technique

    // int first_digit = argv[2][0] - '0';

    if(!atoi(argv[2]) )
    {
        fprintf(2, "x should be a number\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    int x = atoi(argv[2]);
    int ret_val = 0;
    int pipefd[2];

    while(1) {
        n--;
        if(n == -1)
            break;

        if(pipe(pipefd) < 0)
        {
            fprintf(2, "Pipe could not be created. Aborting ... \n");
            exit(1);
        }

        int f = fork();
        if(f < 0){
            fprintf(2, "Error: cannot fork. Aborting...\n");
		    exit(1);
        }
        else
        if(f == 0) {
            if (read(pipefd[0], &x, sizeof(int)) < 0) {
                fprintf(2, "Error: cannot read. Aborting...\n");
                exit(1);
            }
            close(pipefd[0]);
            close(pipefd[1]);
        }
        else {
            x += getpid();
            fprintf(2, "%d : %d\n", getpid(), x);
            if (write(pipefd[1], &x, sizeof(int)) < 0) {
                fprintf(2, "Error: cannot write. Aborting...\n");
                exit(1);
            }
            close(pipefd[1]);
            close(pipefd[0]);
            wait(&ret_val);
            exit(ret_val);
        }
    }

    exit(0);
}
