#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mbr.h"
#include "hconf.h"
#include "hardware.h"
#include "vol.h"

void empty_it(void){
    return;
}

void ls_vol(void) {
    int i;

    load_mbr();

    if (mbr.nbvol == 0) {
        printf("No volume\n");
        return;
    }

    printf("%d/8 volumes :\n", mbr.nbvol);
    for (i = 0; i < mbr.nbvol; i++) {
        if (load_super(i) == 0) {
            fprintf(stderr, "Error: superbloc n°%d corrupted\n", i);
            continue;
        }

        printf("\t%d - %s - cyl=%d sect=%d blocs=%d ",
               i, superbloc.name, mbr.vol[i].num_cyl, mbr.vol[i].num_sect, mbr.vol[i].nb_bloc);

        switch (mbr.vol[i].type) {
        case BASE:
            printf("BASE\n");
            break;
        case ANNEX:
            printf("ANNEX\n");
            break;
        case OTHER:
            printf("OTHER\n");
            break;
        default:
            printf("???\n");
            break;
        }
    }
}

int main(void) {
    int i;

    if(init_hardware(HARDWARE_INI) == 0) {
        fprintf(stderr, "Error in hardware initialization\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < 16; i++)
        IRQVECTOR[i] = empty_it;

    ls_vol();
    return 0;
}
