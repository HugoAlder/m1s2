#include <stdio.h>
#include <stdlib.h>
#include "semaphore.h"
#include "hardware.h"

void sem_init(struct sem_s *sem, unsigned int val) {
    sem->cpt = val;
    sem->sem_ctx = NULL;
}

void sem_up(struct sem_s *sem) {
    irq_disable();
    sem->cpt++;
    if (sem->cpt <= 0) {
        sem->sem_ctx->state = CTX_RUNNING;
        sem->sem_ctx = sem->sem_ctx->next;
        _mask(1);
        yield();
    }
    irq_enable();
}

void sem_down(struct sem_s *sem) {
    irq_disable();
    sem->cpt--;
    if (sem->cpt < 0) {
        current_ctx->state = CTX_BLOCKED;
        current_ctx->next = sem->sem_ctx;
        sem->sem_ctx = current_ctx;
        _mask(1);
        yield();
    }
    irq_enable();
}

void empty_it(void) {
    return;
}

void resume(void) {
    sem_up(&mutex);
}

void start_sched(void) {
    unsigned int i;
    if (init_hardware("hardware.ini") == 0) {
        fprintf(stderr, "init_hardware error\n");
        exit(-1);
    }

    for (i = 0; i < 16; ++i)
        IRQVECTOR[i] = empty_it;

    IRQVECTOR[TIMER_IRQ] = yield;
    IRQVECTOR[DISK_IRQ] = resume;
    _out(TIMER_PARAM, 128 + 64 + 32 + 8);
    _out(TIMER_ALARM, 0xFFFFFFFE);

    irq_enable();

    for (i = 0; i < (1 << 28); ++i);

    return;
}
