#include <assert.h>
#include <stdio.h>

#include "inode.h"
#include "mbr.h"
#include "vol.h"

void read_inode(unsigned int inumber, struct inode_s * inode) {
    assert(superbloc.magic == MAGIC_SB);
    read_bloc_n(current_vol, inumber, (unsigned char *) inode, sizeof(struct inode_s));
    assert(inode->magic == INODE_MAGIC);
}

void write_inode(unsigned int inumber, struct inode_s * inode) {
    assert(superbloc.magic == MAGIC_SB);
    write_bloc_n(current_vol, inumber, (unsigned char *) inode, sizeof(struct inode_s));
    assert(inode->magic == INODE_MAGIC);
}

unsigned int create_inode(enum file_type_e type) {
    int i;
    unsigned int inumber;
    struct inode_s inode;

    inode.magic = INODE_MAGIC;
    inode.type = type;
    inode.size = 0;
    inode.indirect = BLOC_NULL;
    inode.indirect2 = BLOC_NULL;
    for (i = 0; i < NB_DIRECT; i++) {
        inode.direct[i] = BLOC_NULL;
    }

    inumber = new_bloc();
    if (!inumber) return BLOC_NULL;
    write_inode(inumber, &inode);
    return inumber;
}

int delete_inode(unsigned int inumber) {
    struct inode_s inode;
    unsigned int t[NB_INDIRECT];
    int i;

    read_inode(inumber, &inode);

    for (i = 0; i < NB_DIRECT; i++) {
        if (inode.direct[i] != BLOC_NULL) {
            free_bloc(inode.direct[i]);
        }
    }

    free_indirect(inode.indirect);

    if (inode.indirect2) {
        read_bloc_n(current_vol, inode.indirect2, (unsigned char*) &t, sizeof(t));
        for (i = 0; i < NB_INDIRECT; i++) {
            free_indirect(t[i]);
        }
        free_bloc(inode.indirect2);
    }
    free_bloc(inumber);

    return inumber;
}

void free_indirect(unsigned int indirectn) {
    unsigned int t[NB_INDIRECT];
    int i;

    if (indirectn == BLOC_NULL) return;

    read_bloc_n(current_vol, indirectn, (unsigned char *) t, NB_INDIRECT * sizeof(int));

    for (i = 0; i < NB_INDIRECT; i++) {
        if (t[i] != BLOC_NULL) free_bloc(t[i]);
    }
    free_bloc(indirectn);
}

unsigned int vbloc_of_bloc(unsigned int inumber, unsigned int fbloc, int do_allocate) {
    struct inode_s inode;
    unsigned int t[NB_INDIRECT];
    int index2, index1;

    read_inode(inumber, &inode);
    if (fbloc < NB_DIRECT) {
        if (do_allocate && inode.direct[fbloc] == BLOC_NULL) {
            inode.direct[fbloc] = new_bloc();
            format_bloc(current_vol, inode.direct[fbloc]);
            write_inode(inumber, &inode);
        }

        return inode.direct[fbloc];
    }

    fbloc -= NB_DIRECT;
    if (fbloc < NB_INDIRECT) {
        /* TODO: do_allocate */
        if (inode.indirect == BLOC_NULL) return BLOC_NULL;
        read_bloc(current_vol, inode.indirect, (unsigned char *) t);
        /* TODO: do_allocate */
        return t[fbloc];
    }

    fbloc -= NB_INDIRECT;

    /* TODO: do_allocate in indirect2 */

    if (!inode.indirect2) return BLOC_NULL;

    index2 = fbloc / NB_INDIRECT;
    index1 = fbloc % NB_INDIRECT;
    read_bloc(current_vol, inode.indirect2, (unsigned char *) t);
    if (!t[index2]) return BLOC_NULL;
    read_bloc(current_vol, t[index2], (unsigned char *) t);
    if (!t[index1]) return BLOC_NULL;
    return t[index1];
}
