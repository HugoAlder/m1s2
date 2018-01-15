#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mbr.h"
#include "vol.h"
#include "hconf.h"
#include "hardware.h"

void empty_it(void) {
    return;
}

void create_vol(int num_cyl, int num_sect, int nb_bloc, int type, char * name) {
    struct volume_s vol;

    load_mbr();

    if (num_sect == 0 && num_cyl == 0) {
        fprintf(stderr, "Cannot overwrite mbr\n");
        exit(-1);
    }

    if (mbr.nbvol == MAX_VOL) {
        fprintf(stderr, "Maximum number volume reached\n");
        exit(-1);
    }

    vol.num_sect = num_sect;
    vol.num_cyl = num_cyl;
    vol.nb_bloc = nb_bloc;
    vol.type = type;

    mbr.vol[mbr.nbvol] = vol;

    init_super(mbr.nbvol, 0x5314, name);

    mbr.nbvol++;
    save_mbr();
}

void usage(void) {
    printf("mk_vol <num_cyl> <num_sect> <nb_bloc> <type> <name>\n");
    printf("VOLUME TYPES :\n");
    printf("\t1 - BASE\n");
    printf("\t2 - ANNEX\n");
    printf("\t3 - OTHER\n");
    printf("Name must have at least 3 chars but no more than 30 chars\n");
}

int main(int argc, char **argv) {
    int vol_type, i;

    if (argc != 6 || argv[4][1] != '\0' || !(strlen(argv[5]) > 3 && strlen(argv[5]) < 30)) {
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

    switch (argv[4][0]) {
    case '1':
        vol_type = BASE;
        break;
    case '2':
        vol_type = ANNEX;
        break;
    case '3':
        vol_type = OTHER;
        break;
    default:
        usage();
        exit(-1);
    }

    create_vol(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), vol_type, argv[5]);

    return 0;
}
