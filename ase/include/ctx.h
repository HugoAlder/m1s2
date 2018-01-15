typedef void (func_t)(void*);

#define TIMER_ALARM 0xF8
#define TIMER_PARAM 0xF4
#define TIMER_IRQ   2

enum state_e {
    CTX_RDY, CTX_RUNNING, CTX_TERMINATED, CTX_BLOCKED
};

struct ctx_s {
    void *esp;
    void *ebp;
    int magic;
    char *stack;
    enum state_e state;
    func_t *entrypoint;
    void *args;

    struct ctx_s *previous;
    struct ctx_s *next;
};

struct ctx_s * current_ctx;

int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void *args);
void start_current_ctx(void);
void switch_to_ctx(struct ctx_s *ctx);
struct ctx_s *create_ctx (int stack_size, func_t f, void *args);
void yield();
void irq_enable();
void irq_disable();
