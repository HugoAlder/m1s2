#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ifile.h"
#include "mbr.h"
#include "vol.h"

unsigned int create_ifile(enum file_type_e type) {
    unsigned int inumber;

    inumber = create_inode(type);
    if (!inumber) {
        fprintf(stderr, "(create_ifile) Unable to create inode\n");
    }

    return inumber;
}

int open_ifile(file_desc_t *fd, unsigned int inumber) {
    struct inode_s inode;
    read_inode(inumber, &inode);
    fd->inumber = inumber;
    fd->size = inode.size;
    fd->pos = 0;
    fd->dirty = 0;
    read_bloc(current_vol, vbloc_of_bloc(inumber, 0, 1), fd->buf);
    return 0;
}

void flush_ifile(file_desc_t *fd) {
    int bloc, vbloc;

    if(fd->dirty) {
        bloc = fd->pos / SECTOR_SIZE;
        vbloc = vbloc_of_bloc(fd->inumber, bloc, 1);
        write_bloc(current_vol, vbloc, fd->buf);
        fd->dirty = 0;
    }
}

int readc_ifile(file_desc_t *fd) {
    int res;
    if(fd->pos >= fd->size) {
        return FILE_EOF;
    }
    res = fd->buf[fd->pos % SECTOR_SIZE];
    seek_ifile(fd, 1);
    return res;
}

int writec_ifile(file_desc_t *fd, char c) {
    fd->buf[fd->pos % SECTOR_SIZE] = c;

    if (!fd->dirty) {
        fd->dirty = 1;
    }

    if (fd->size < fd->pos)
        fd->size = fd->pos;

    seek_ifile(fd, 1);
    return fd->pos - 1;
}

void seek_ifile(file_desc_t * fd, int offset) {
    unsigned int old_pos = fd->pos;
    unsigned int fbloc, vbloc;

    fd->pos += offset;

    /* does the seek imply a jump in another bloc? */
    if ((fd->pos / SECTOR_SIZE) != (old_pos / SECTOR_SIZE)) {
        flush_ifile(fd);

        /* the bloc index of the new buffer */
        fbloc = fd->pos / SECTOR_SIZE;
        vbloc = vbloc_of_bloc(fd->inumber, fbloc, 0);

        if (!vbloc)
            /* the bloc #0 is full of zeros */
            memset(fd->buf, 0, SECTOR_SIZE);
        else
            read_bloc(current_vol, vbloc, fd->buf);
    }
}

void close_ifile(file_desc_t *fd) {
    struct inode_s inode;
    flush_ifile(fd);

    read_inode(fd->inumber, &inode);
    inode.size = fd->size;
    write_inode(fd->inumber, &inode);
}
