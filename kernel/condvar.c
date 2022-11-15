#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"
#include "procstat.h"
#include "condvar.h"

void
cond_wait (cond_t *cv, struct sleeplock *lock) {
    printf("wait start\n");
    condsleep(cv, lock);
    printf("wait end\n");
}

void
cond_signal (cond_t *cv) {
    wakeupone(cv);
}

void
cond_broadcast (cond_t *cv) {
    printf("Start broadcast\n");
    wakeup(cv);
    printf("end broadcast\n");
}