#include <stdlib.h>
#include <assert.h>
#include "ctx.h"
#include "hardware.h"

#define MAGIC 0xdeadbeef

int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void *args) {
    ctx->stack = malloc(stack_size);
    ctx->entrypoint = f;
    ctx->args = args;
    ctx->state = CTX_RDY;
    ctx->magic = MAGIC;
    ctx->esp = ctx->stack + stack_size - sizeof(void*);
    ctx->ebp = ctx->esp;
    return (ctx->stack != NULL);
}

void start_current_ctx(void) {
    current_ctx->state = CTX_RUNNING;
    current_ctx->entrypoint(current_ctx->args);
    current_ctx->state = CTX_TERMINATED;
    (current_ctx->previous)->next = current_ctx->next;
    (current_ctx->next)->previous = current_ctx->previous;
    yield();
    exit(0);
}

void switch_to_ctx(struct ctx_s *ctx) {
    assert(ctx->magic == MAGIC);
    irq_disable();
    if (current_ctx != NULL) {
        asm("mov %%esp, %0":"=r"(current_ctx->esp));
        asm("mov %%ebp, %0":"=r"(current_ctx->ebp));
    }
    current_ctx = ctx;
    asm("mov %0, %%esp"::"r"(current_ctx->esp));
    asm("mov %0, %%ebp"::"r"(current_ctx->ebp));
    if (current_ctx->state == CTX_RDY) {
        start_current_ctx();
    }
    irq_enable();
}

struct ctx_s *create_ctx (int stack_size, func_t f, void *args) {
    struct ctx_s *ctx = malloc(sizeof(struct ctx_s));

    if (!init_ctx(ctx, stack_size, f, args)) {
        free(ctx);
        return NULL;
    }

    if (current_ctx == NULL) {
        current_ctx = ctx;
        current_ctx->next = ctx;
        current_ctx->previous = ctx;
    } else {
        ctx->previous = current_ctx;
        ctx->next = current_ctx->next;
        current_ctx->next = ctx;
        (current_ctx->next)->previous = ctx;
    }

    return ctx;
}

void yield() {
    switch_to_ctx(current_ctx->next);
}

void irq_enable() {
    _mask(1);
    _out(TIMER_ALARM, 0xFFFFFFFE);
}

void irq_disable() {
    _mask(0);
}
