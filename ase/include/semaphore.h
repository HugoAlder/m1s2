#include "ctx.h"

#define DISK_IRQ 14

typedef struct sem_s {
    int cpt;
    struct ctx_s *sem_ctx;
} sem_s;

void sem_init(sem_s *sem, unsigned int val);
void sem_down(sem_s *sem);
void sem_up(sem_s *sem);
void empty_it(void);
void start_sched(void);
