#define MAGIC_SB 0x314159
#define MAGIC_FB 0x800815
#define BLOC_NULL 0

struct superbloc_s {
    unsigned int magic;
    unsigned int serial;
    char name[32];
    unsigned int num_bloc;
    unsigned int nb_freeblocs;
    unsigned int fst_freebloc;
};

struct freebloc_s {
    unsigned int next_freebloc;
    unsigned int magic;
};

void init_super(unsigned int vol, unsigned int serial, char * name);
int load_super(unsigned int vol);
void save_super(void);
unsigned int new_bloc(void);
void format_bloc(unsigned int vol, unsigned int nbloc);
void free_bloc(unsigned int bloc);

unsigned int current_vol;
struct superbloc_s superbloc;
