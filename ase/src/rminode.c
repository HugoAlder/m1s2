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
    printf("rminode [vol] [inode]\n");
}

int main(int argc, char **argv) {
    int i, vol, inode;

    if (init_hardware(HARDWARE_INI) == 0) {
        fprintf(stderr, "Error in hardware initialization\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 16; i++)
        IRQVECTOR[i] = empty_it;

    load_mbr();

    if (argc == 3) {
        vol = atoi(argv[1]);
        inode = atoi(argv[2]);
        if (vol < 0 || vol >= mbr.nbvol) {
            fprintf(stderr, "Volume %d not found\n", vol);
            exit(EXIT_FAILURE);
        }
    } else {
        usage();
        exit(EXIT_FAILURE);
    }

    printf("Creating inode inside volume %d\n", vol);
    load_super(vol);
    printf("Removed inode : %d\n", delete_inode(inode));
    printf("There are %d blocs remaining in volume %d\n", superbloc.nb_freeblocs, vol);
    return 0;
}
