#include <stdio.h>
#include <stdlib.h>

#include "mbr.h"
#include "vol.h"
#include "hconf.h"
#include "hardware.h"
#include "ifile.h"

void empty_it(void){
    return;
}

void dfile(unsigned int inumber) {
    int status;

    status = delete_inode(inumber);
    if (!status) {
        fprintf(stderr, "Error while deleting file %d\n", inumber);
        exit(EXIT_FAILURE);
    }
}

void usage(const char *prgm) {
    fprintf(stderr, "[%s] usage:\n\t"
            "%s [vol] inumber\n", prgm, prgm);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    int i, vol;
    unsigned int inumber;

    if (argc == 2) {
        vol = 0;
        inumber = atoi(argv[1]);
    } else if (argc == 3) {
        vol = atoi(argv[1]);
        inumber = atoi(argv[2]);
    } else
        usage(argv[0]);

    if (init_hardware(HARDWARE_INI) == 0) {
        fprintf(stderr, "Error in hardware initialization\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 16; i++)
        IRQVECTOR[i] = empty_it;

    load_mbr();
    load_super(vol);

    dfile(inumber);
    save_super();

    exit(EXIT_SUCCESS);
}
