#include "hconf.h"

#define INODE_MAGIC 0x441919
#define NB_DIRECT ((SECTOR_SIZE - sizeof(int) * 4 - sizeof(enum file_type_e)) / sizeof(int))
#define NB_INDIRECT (SECTOR_SIZE / sizeof(int))

enum file_type_e {
    TYPE_FILE, TYPE_DIRECTORY
};

struct inode_s {
    int magic;
    enum file_type_e type;
    int size;
    unsigned int direct[NB_DIRECT];
    unsigned int indirect;
    unsigned int indirect2;
};

void read_inode(unsigned int inumber, struct inode_s * inode);
void write_inode(unsigned int inumber, struct inode_s * inode);
unsigned int create_inode(enum file_type_e type);
int delete_inode(unsigned int inumber);
void free_indirect(unsigned int indirectn);
unsigned int vbloc_of_bloc(unsigned int inumber, unsigned int fbloc, int do_allocate);
