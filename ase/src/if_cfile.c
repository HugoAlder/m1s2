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

static void cfile(unsigned int sinumber) {
    file_desc_t sfd, dfd;
    unsigned int dinumber;
    int status;
    int c;

    dinumber = create_ifile(TYPE_FILE);
    if (!dinumber) {
        fprintf(stderr, "Error while creating file\n");
        exit(EXIT_FAILURE);
    }

    printf("Copying content of file inode=%d in file inode=%d\n", sinumber, dinumber);

    status = open_ifile(&dfd, dinumber);
    if (status) {
        fprintf(stderr, "Error while opening file %d\n", dinumber);
        exit(EXIT_FAILURE);
    }

    status = open_ifile(&sfd, sinumber);
    if (status) {
        fprintf(stderr, "Error while opening file %d\n", sinumber);
        exit(EXIT_FAILURE);
    }

    while ((c = readc_ifile(&sfd)) != -1)
        writec_ifile(&dfd, c);

    close_ifile(&dfd);
    close_ifile(&sfd);
}

static void usage(const char *prgm) {
    fprintf(stderr, "[%s] usage:\n\t"
            "%s inumber\n", prgm, prgm);
    exit(EXIT_FAILURE);
}

int main (int argc, char *argv[]) {
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

    cfile(inumber);
    save_super();

    exit(EXIT_SUCCESS);
}
