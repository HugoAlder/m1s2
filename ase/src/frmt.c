#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dmps.h"
#include "hconf.h"
#include "hardware.h"
#include "drive.h"

void empty_it(void){
    return;
}

void frmt(int r) {
    int i, ncyl, nsect;

    _out(0x3F6, 0x16); /* DSKINFO */
    ncyl = (_in(0x110) << 8) +  _in(0x111);
    nsect = (_in(0x112) << 8) +  _in(0x113);

    if (r == 0) {
        for (i = 0; i < ncyl; i++)
            format_sector(i, 0, nsect, 0xafafafaf);
    } else {
        for (i = 0; i < ncyl; i++)
            reverse_format_sector(i, 0, nsect, 0xafafafaf);
    }
}

void usage(void) {
    printf("frmt [-r]/n");
}

int main(int argc, char **argv) {
    int i;

    if (argc != 1 && argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    if(init_hardware(HARDWARE_INI) == 0) {
        fprintf(stderr, "Error in hardware initialization\n");
        exit(EXIT_FAILURE);
    }

    for(i=0; i<16; i++)
        IRQVECTOR[i] = empty_it;

    if (argc == 2 && strcmp(argv[1], "-r") == 0)
        frmt(1);
    else
        frmt(0);

    return 0;
}
