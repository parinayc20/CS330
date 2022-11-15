#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"
#include "procstat.h"
#include "sleeplock.h"
#include "barr.h"

struct barr barriers[NUM_BARRIER];

void
barrinit() {
    for(int i=0; i<NUM_BARRIER; i++) {
        (&barriers[i])->set = 0;
    }
}

void
barrier(int inst_num, int id, int np) {
    struct proc* p = myproc();
    int pid;
    acquire(&p->lock);
    pid = p->pid;
    release(&p->lock);
    struct barr *b = &barriers[id];

    acquiresleep(&b -> lock);
    acquiresleep(&printlock);
    printf("%d: Entered barrier#%d for barrier array id %d\n", pid, inst_num, id);
    releasesleep(&printlock);
    b->processes += 1;
    if(b->processes < np) {
        // while(b->processes < np)
        cond_wait(&b->cv, &b->lock);
    }
    else {
        cond_broadcast(&b->cv);
        b->processes = 0;
    }
    acquiresleep(&printlock);
    printf("%d: Finished barrier#%d for barrier array id %d\n", pid, inst_num, id);
    releasesleep(&printlock);
    releasesleep(&b->lock);
}

int
barrier_alloc() {
    for(int i = 0; i < NUM_BARRIER; i++) {
        struct barr *b = &barriers[i];
        if(b -> set == 0)
        {
            b -> set = 1;
            initsleeplock(&b -> lock, "barrier lock");
            b -> cv = 1;
            b -> processes = 0;
            return i;
        }
    }
    return -1;
}

int
barrier_free(int id) {
    struct barr *b = &barriers[id];
    if(b->set == 0) 
        return -1;
    b->set = 0;
    return 0;
}