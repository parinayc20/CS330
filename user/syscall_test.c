#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void 
test_getppid()
{
    int pid = getpid();
    int ppid = getppid();
    fprintf(2, "pid = %d, ppid = %d\n", pid, ppid);
    return;
}

void
test_waitpid()
{
    int x = fork();
    if (x < 0) {
        fprintf(2, "Error: cannot fork\nAborting...\n");
        exit(0);
    }
    else if (x > 0) {
        sleep(1);
        fprintf(1, "%d: Parent.\n", getpid());
        int wait_val = waitpid(-1, 0);
        printf("%d\n", wait_val);
    }
    else {
        fprintf(1, "%d: Child.\n", getpid());
    }

    exit(0);   
}

void
test_yield()
{
    yield();
}

void 
test_getpa()
{
    int x = 2;
    int y = 3;
    fprintf(2, "Physical Address = %p\n", getpa(&x));
    fprintf(2, "Physical Address = %p\n", getpa(&y));
}

void
test_pinfo()
{
    struct procstat pstat;

    int x = fork();
    if (x < 0) {
        fprintf(2, "Error: cannot fork\nAborting...\n");
        exit(0);
    }
    else if (x > 0) {
        sleep(1);
        fprintf(1, "%d: Parent.\n", getpid());
        if (pinfo(-1, &pstat) < 0) fprintf(1, "Cannot get pinfo\n");
        else fprintf(1, "pid=%d, ppid=%d, state=%s, cmd=%s, ctime=%d, stime=%d, etime=%d, size=%p\n",
            pstat.pid, pstat.ppid, pstat.state, pstat.command, pstat.ctime, pstat.stime, pstat.etime, pstat.size);
        if (pinfo(x, &pstat) < 0) fprintf(1, "Cannot get pinfo\n");
        else fprintf(1, "pid=%d, ppid=%d, state=%s, cmd=%s, ctime=%d, stime=%d, etime=%d, size=%p\n\n",
            pstat.pid, pstat.ppid, pstat.state, pstat.command, pstat.ctime, pstat.stime, pstat.etime, pstat.size);
        fprintf(1, "Return value of waitpid=%d\n", waitpid(x, 0));
    }
    else {
        fprintf(1, "%d: Child.\n", getpid());
        if (pinfo(-1, &pstat) < 0) fprintf(1, "Cannot get pinfo\n");
        else fprintf(1, "pid=%d, ppid=%d, state=%s, cmd=%s, ctime=%d, stime=%d, etime=%d, size=%p\n\n",
            pstat.pid, pstat.ppid, pstat.state, pstat.command, pstat.ctime, pstat.stime, pstat.etime, pstat.size);
    }

    exit(0);
}

int g (int x)
{
   return x*x;
}

int f (void)
{
   int x = 10;

   fprintf(2, "Hello world! %d\n", g(x));
   return 0;
}

int
main(int argc, char* argv[]) 
{
    if(argc != 2)
    {
        fprintf(2, "Usage: uptime\n");
        exit(1);
    }

    int num = atoi(argv[1]);
    if(num == 1)
        test_getppid();
    else
    if (num == 2)
        test_yield();
    else
    if (num == 3)
        test_getpa();
    else
    if (num == 4)
    {
        // printf("P %d", f);
        int x = forkf(f);
        printf("%d\n", x);
        if (x < 0) {
            fprintf(2, "Error: cannot fork\nAborting...\n");
            exit(0);
        }
        else if (x > 0) {
            sleep(1);
            fprintf(1, "%d: Parent.\n", getpid());
            wait(0);
        }
        else {
            fprintf(1, "%d: Child.\n", getpid());
        }

        exit(0);
    }
    else
    if (num == 5)
    {
        test_waitpid();
    }
    else
    if (num == 6)
        ps();
    else
    if (num == 7)
        test_pinfo();
    else {}
    exit(0);
}