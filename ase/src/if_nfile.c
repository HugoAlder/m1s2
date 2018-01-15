#include <stdio.h>
#include <stdlib.h>

#include "hardware.h"
#include "hconf.h"
#include "ifile.h"
#include "vol.h"
#include "mbr.h"

void empty_it(void){
    return;
}

static void nfile() {
    file_desc_t fd;
    unsigned int inumber;
    int status;
    int c;

    inumber = create_ifile(TYPE_FILE);
    if (!inumber) {
        fprintf(stderr, "Error while creating file\n");
        exit(EXIT_FAILURE);
    }

    printf("Creating file : %u\n", inumber);

    status = open_ifile(&fd, inumber);
    if (status) {
        fprintf(stderr, "Error while opening file %d\n", inumber);
        exit(EXIT_FAILURE);
    }

    while((c = getchar()) != FILE_EOF)
        writec_ifile(&fd, c);

    close_ifile(&fd);
}

static void usage(const char *prgm) {
    fprintf(stderr, "[%s] usage:\n\t"
            "%s [volume]\n", prgm, prgm);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    int i, vol;

    if (argc == 1)
        vol = 0;
    else if (argc == 2)
        vol = atoi(argv[1]);
    else
        usage(argv[0]);

    if (init_hardware(HARDWARE_INI) == 0) {
        fprintf(stderr, "Error in hardware initialization\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 16; i++)
        IRQVECTOR[i] = empty_it;

    load_mbr();
    load_super(vol);

    nfile();

    save_super();

    exit(EXIT_SUCCESS);
}
