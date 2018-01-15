#include <stdio.h>
#include <stdlib.h>
#include "dmps.h"
#include "hconf.h"
#include "hardware.h"
#include "drive.h"

void empty_it(void){
    return;
}

void dmps(unsigned int cyl, unsigned int sec) {
    int i, j;
    unsigned char buf[SECTOR_SIZE];

    read_sector(cyl, sec, buf);

    for (i = 0; i < SECTOR_SIZE; i += 16) {
        printf("%03d: ", i);
        for (j = 0; j < 16; j++)
            printf(" %02x", buf[i + j]);
        printf("\n");
    }
}

void usage(void) {
    printf("dmps <cyl> <sec>\n");
    printf("\tcyl & sec must be in 0..15\n");
}

int main(int argc, char **argv) {
    unsigned int cyl, sec, i;

    if (argc != 3) {
        usage();
        exit(EXIT_FAILURE);
    }

    cyl = atoi(argv[1]);
    sec = atoi(argv[2]);

    if (cyl < 0 || cyl > 15 || sec < 0 || sec > 15) {
        usage();
        exit(EXIT_FAILURE);
    }

    if(init_hardware(HARDWARE_INI) == 0) {
        fprintf(stderr, "Error in hardware initialization\n");
        exit(EXIT_FAILURE);
    }

    for(i=0; i<16; i++)
        IRQVECTOR[i] = empty_it;

    dmps(cyl, sec);

    return 0;
}
