#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"
#include "defs.h"
#include "sleeplock.h"
#include "buffer.h"

struct buffer buf_arr[NUM_BUFFER];
struct sleeplock insert_lock;
struct sleeplock delete_lock;

void
bufferinit() {
    initsleeplock(&insert_lock, "insert-lock");
    initsleeplock(&delete_lock, "delete-lock");

    for(int i = 0; i < NUM_BUFFER; i++) {
        struct buffer* buff = &buf_arr[i];
        initsleeplock(&buff->lock, "buffer-lock");
        buff->value = -1;
        buff->full = 0;
        buff->inserted = 0;
        buff->deleted = 0;
    }
}