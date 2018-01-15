#ifndef MBR_H
#define MBR_H

#define MAX_VOL 8
#define MAGIC_MBR 0xabbabaab

struct mbr_s mbr;

enum vol_types {
    BASE, ANNEX, OTHER
};

struct volume_s {
    int num_sect;
    int num_cyl;
    int nb_bloc;
    enum vol_types type;
};

struct mbr_s {
    struct volume_s vol[MAX_VOL];
    int nbvol;
    int magic;
};

void save_mbr(void);
void load_mbr(void);
int sec_of_bloc(int vol, int bloc);
int cyl_of_bloc(int vol, int bloc);
void read_bloc(int vol, int bloc, unsigned char *buf);
void write_bloc(int vol, int bloc, const unsigned char *buf);
void read_bloc_n(int vol, int bloc, unsigned char *buf, int size);
void write_bloc_n(int vol, int bloc, const unsigned char *buf, int size);

#endif
