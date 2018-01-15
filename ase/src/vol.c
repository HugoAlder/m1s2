#include <string.h>
#include <assert.h>
#include "vol.h"
#include "mbr.h"
#include "hconf.h"

void init_super(unsigned int vol, unsigned int serial, char * name) {
    struct freebloc_s freebloc;
    int i;

    superbloc.magic = MAGIC_SB;
    superbloc.serial = serial;
    strncpy(superbloc.name, name, 32);
    superbloc.num_bloc = BLOC_NULL;
    superbloc.nb_freeblocs = mbr.vol[vol].nb_bloc - 1;
    superbloc.fst_freebloc = 1;

    for (i = 1; i < mbr.vol[vol].nb_bloc - 1; i++) {
        freebloc.next_freebloc = i + 1;
        freebloc.magic = MAGIC_FB;
        write_bloc_n(vol, i, (unsigned char *) &freebloc, sizeof(freebloc));
    }

    freebloc.next_freebloc = BLOC_NULL;
    freebloc.magic = MAGIC_FB;
    write_bloc_n(vol, i, (unsigned char *) &freebloc, sizeof(freebloc));
    current_vol = vol;
    save_super();
}

int load_super(unsigned int vol) {
    if (vol >= mbr.nbvol) return 0;

    read_bloc_n(vol, 0, (unsigned char *) &superbloc, sizeof(superbloc));

    if (superbloc.magic != MAGIC_SB) return 0;
    current_vol = vol;

    return 1;
}

void save_super(void) {
    write_bloc_n(current_vol, 0, (unsigned char *) &superbloc, sizeof(superbloc));
}

unsigned int new_bloc(void) {
    struct freebloc_s freelist;
    unsigned int res;
    assert(superbloc.magic == MAGIC_SB);

    res = superbloc.fst_freebloc;
    if (res == BLOC_NULL) return res;

    read_bloc_n(current_vol, res, (unsigned char *) &freelist, sizeof(freelist));
    superbloc.fst_freebloc = freelist.next_freebloc;
    superbloc.nb_freeblocs--;

    save_super();
    return res;
}

void format_bloc(unsigned int vol, unsigned int nbloc) {
    unsigned char buffer[SECTOR_SIZE];
    unsigned int i;

    for (i = 0; i < SECTOR_SIZE; i++)
        buffer[i] = 0;

    write_bloc(vol, nbloc, buffer);
}

void free_bloc(unsigned int bloc) {
    struct freebloc_s fb;

    assert(superbloc.magic == MAGIC_SB);

    fb.next_freebloc = superbloc.fst_freebloc;
    fb.magic = MAGIC_FB;
    superbloc.fst_freebloc = bloc;
    superbloc.nb_freeblocs++;

    write_bloc_n(current_vol, bloc, (unsigned char *) &fb, sizeof(struct freebloc_s));
    save_super();
}
