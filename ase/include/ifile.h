#include "hconf.h"
#include "inode.h"

#define FILE_EOF -1

struct file_desc_s {
  unsigned int pos;
  unsigned int inumber;
  unsigned char buf[SECTOR_SIZE];
  unsigned int dirty;
  unsigned int size;
};

typedef struct file_desc_s file_desc_t;

unsigned int create_ifile(enum file_type_e type);
int open_ifile(file_desc_t * fd, unsigned int number);
void flush_ifile(file_desc_t * fd);
int readc_ifile(file_desc_t * fd);
int writec_ifile(file_desc_t * fd, char c);
/* TODO : Seek relatif */
void seek_ifile(file_desc_t * fd, int offset);
void close_ifile(file_desc_t * fd);
