#include "mbr.h"
#include "drive.h"
#include "hconf.h"

void save_mbr(void) {
    write_sector_n(0, 0, (unsigned char *) &mbr, sizeof(struct mbr_s));
}

void load_mbr(void) {
    read_sector_n(0, 0, (unsigned char *) &mbr, sizeof(struct mbr_s));

    if (mbr.magic != MAGIC_MBR) {
        mbr.magic = MAGIC_MBR;
        mbr.nbvol = 0;
    }
}


int cyl_of_bloc(int vol, int bloc) {
    return mbr.vol[vol].num_cyl + (mbr.vol[vol].num_sect + bloc) / NB_SECTOR;
}

int sec_of_bloc(int vol, int bloc) {
    return (mbr.vol[vol].num_sect + bloc) % NB_SECTOR;
}


void read_bloc(int vol, int bloc, unsigned char *buf) {
    read_sector(cyl_of_bloc(vol, bloc), sec_of_bloc(vol, bloc), buf);
}

void write_bloc(int vol, int bloc, const unsigned char *buf) {
    write_sector(cyl_of_bloc(vol, bloc), sec_of_bloc(vol, bloc), buf);
}


void read_bloc_n(int vol, int bloc, unsigned char *buf, int size) {
    read_sector_n(cyl_of_bloc(vol, bloc), sec_of_bloc(vol, bloc), buf, size);
}

void write_bloc_n(int vol, int bloc, const unsigned char *buf, int size) {
    write_sector_n(cyl_of_bloc(vol, bloc), sec_of_bloc(vol, bloc), buf, size);
}
