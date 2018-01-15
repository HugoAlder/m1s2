#include <stdio.h>
#include <stdlib.h>

#include "mbr.h"
#include "drive.h"
#include "hconf.h"
#include "hardware.h"

void empty_it(void) {
    return;
}

void frmtvol(int vol) {
    int i;

    load_mbr();

    if (mbr.nbvol < vol) {
        fprintf(stderr, "Volume %d doesn't exists\n", vol);
        exit(-1);
    }

    for (i = 1; i < mbr.vol[vol].nb_bloc; i++) {
        format_sector(cyl_of_bloc(vol, i), sec_of_bloc(vol, i), 1, 0xafafafaf);
    }
}

void usage() {
    printf("frmtvol <vol>\n");
}

int main(int argc, char **argv) {
    int i;

    if (argc != 2) {
        usage();
        exit(-1);
    }

    if (init_hardware(HARDWARE_INI) == 0) {
        fprintf(stderr, "Error in hardware initialization\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 16; i++)
        IRQVECTOR[i] = empty_it;

    _mask(1);

    frmtvol(atoi(argv[1]));

    return 0;
}
