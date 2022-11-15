#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"
#include "defs.h"
#include "sem_buffer.h"

struct sem_buffer sem_buf_arr[NUM_SEM_BUFFER];
struct sem_t pro;
struct sem_t con;
struct sem_t empty;
struct sem_t full;

void
sembufferinit(){
    sem_init(&pro,1);
    sem_init(&con,1);
    sem_init(&full,0);
    sem_init(&empty,NUM_SEM_BUFFER);

    for(int i=0;i < NUM_SEM_BUFFER; i++)
        (sem_buf_arr[i]).value = -1;
}