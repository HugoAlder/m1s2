#include <stdio.h>
#include <stdlib.h>

#include "mbr.h"
#include "hconf.h"
#include "hardware.h"
#include "vol.h"
#include "inode.h"

void empty_it(void){
    return;
}

void usage(void) {
    printf("createinode [vol]\n");
}

int main(int argc, char **argv) {
    int i, vol;


    if (init_hardware(HARDWARE_INI) == 0) {
        fprintf(stderr, "Error in hardware initialization\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 16; i++)
        IRQVECTOR[i] = empty_it;

    load_mbr();

    if (mbr.nbvol == 0) {
        fprintf(stderr, "No volume found. Create one first.\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        vol = atoi(argv[1]);
        if (vol < 0 || vol >= mbr.nbvol) {
            fprintf(stderr, "Volume %d not found\n", vol);
            exit(EXIT_FAILURE);
        }
    } else if (argc == 1) {
        printf("No volume specified, setting to volume 0\n");
        vol = 0;
    } else {
        usage();
        exit(EXIT_FAILURE);
    }

    printf("Creating inode inside volume %d\n", vol);
    load_super(vol);
    printf("Created inode : %d\n", create_inode(TYPE_FILE));
    printf("There are %d blocs remaining in volume %d\n", superbloc.nb_freeblocs, vol);
    return 0;
}
