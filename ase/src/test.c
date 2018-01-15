#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>

#include "hconf.h"
#include "drive.h"
#include "vol.h"
#include "mbr.h"
#include "hardware.h"

#define CURRENT_VOL 0

struct test_struct_s {
    unsigned int magic;
    unsigned int foo;
};

void test_read_write_sector(void) {
    /* strlen("TEST WRITE AND READ") = 19. */
    unsigned char in_buffer[SECTOR_SIZE] = "TEST WRITE AND READ";
    unsigned char out_buffer[SECTOR_SIZE];

    /* Test read and write at sector 0 on cylinder 0. */
    write_sector(0, 0, in_buffer);
    read_sector(0, 0, out_buffer);
    assert(!memcmp(in_buffer, out_buffer, (size_t) 19));
    bzero(out_buffer, SECTOR_SIZE);

    /* Test read and write at sector 13 on cylinder 7. */
    write_sector(13, 7, in_buffer);
    read_sector(13, 7, out_buffer);
    assert(!memcmp (in_buffer, out_buffer, (size_t) 19));
    bzero(out_buffer, SECTOR_SIZE);

    /* Test read and write at sector 15 on cylinder 15. */
    write_sector(15, 15, in_buffer);
    read_sector(15, 15, out_buffer);
    assert(!memcmp(in_buffer, out_buffer, (size_t) 19));
    bzero(out_buffer, SECTOR_SIZE);

    printf("test_read_write_sector : [OK]\n");
}

void test_read_write_sector_n(void) {
    struct test_struct_s test_w, test_r;

    test_w.magic = 0xacdccafe;
    test_w.foo = 1337;

    write_sector_n(1, 2, (unsigned char *) &test_w,
                   sizeof (struct test_struct_s));
    read_sector_n(1, 2, (unsigned char *) &test_r,
                  sizeof(struct test_struct_s));
    assert(test_w.magic == test_r.magic);
    assert(test_w.foo == test_r.foo);
    bzero(&test_r, sizeof(struct test_struct_s));

    write_sector_n(12, 3, (unsigned char *) &test_w,
                   sizeof(struct test_struct_s));
    read_sector_n(12, 3, (unsigned char *) &test_r,
                  sizeof(struct test_struct_s));
    assert(test_w.magic == test_r.magic);
    assert(test_w.foo == test_r.foo);
    bzero(&test_r, sizeof(struct test_struct_s));

    write_sector_n(15, 15, (unsigned char *) &test_w,
                   sizeof(struct test_struct_s));
    read_sector_n(15, 15, (unsigned char *) &test_r,
                  sizeof(struct test_struct_s));
    assert(test_w.magic == test_r.magic);
    assert(test_w.foo == test_r.foo);
    bzero(&test_r, sizeof(struct test_struct_s));

    printf("test_read_write_sector_n : [OK]\n");
}

void test_format_sectors(void) {
    /* strlen("TEST WRITE AND READ") = 19. */
    unsigned char in_buffer[SECTOR_SIZE] = "TEST WRITE AND READ";
    unsigned char out_buffer[SECTOR_SIZE];

    /* Test read and write at sector 0 on cylinder 0. */
    write_sector(0, 0, in_buffer);
    read_sector(0, 0, out_buffer);
    assert(!memcmp (in_buffer, out_buffer, (size_t) 19));

    format_sector(0, 0, 1, 0xafafafaf);

    read_sector(0, 0, out_buffer);
    assert(memcmp(in_buffer, out_buffer, (size_t) 19));

    printf("test_format_sectors : [OK]\n");
}

void test_create_mbr(void) {
    memset(&mbr, '0', sizeof(struct mbr_s));
    assert(mbr.magic != MAGIC_MBR);
    load_mbr();
    assert(mbr.magic == MAGIC_MBR);

    printf("test_create_mbr : [OK]\n");
}

void test_create_volume(void) {
    struct volume_s volume;

    volume.num_cyl = 0;
    volume.num_sect = 1;
    volume.nb_bloc = 255;
    volume.type = BASE;

    mbr.vol[mbr.nbvol] = volume;
    mbr.nbvol++;

    save_mbr();

    printf("test_create_volume : [OK]\n");
}

void test_cyl_of_bloc(void) {
    assert(cyl_of_bloc(CURRENT_VOL, 0) == 0);
    assert(cyl_of_bloc(CURRENT_VOL, 14) == 0);
    assert(cyl_of_bloc(CURRENT_VOL, 15) == 1);
    assert(cyl_of_bloc(CURRENT_VOL, 20) == 1);
    assert(cyl_of_bloc(CURRENT_VOL, 32) == 2);
    printf("test_cyl_of_bloc : [OK]\n");
}

void test_sec_of_bloc(void) {
    assert(sec_of_bloc(CURRENT_VOL, 0) == 1);
    assert(sec_of_bloc(CURRENT_VOL, 4) == 5);
    assert(sec_of_bloc(CURRENT_VOL, 20) == 5);
    assert(sec_of_bloc(CURRENT_VOL, 30) == 15);
    printf("test_sec_of_bloc : [OK]\n");
}

void test_init_super(void) {
    memset(&superbloc, '0', sizeof (struct superbloc_s));

    assert(superbloc.magic != MAGIC_SB);
    init_super(CURRENT_VOL, 0x1122, "test");
    assert(superbloc.magic == MAGIC_SB);

    printf("test_init_super : [OK]\n");
}

void test_load_super(void) {
    memset(&superbloc, '0', sizeof (struct superbloc_s));

    assert(superbloc.magic != MAGIC_SB);
    assert(load_super(CURRENT_VOL) == 1);

    printf("test_load_super : [OK]\n");
}

void empty_it(void) {
    return;
}

int main(void) {
    int i;

    if(init_hardware(HARDWARE_INI) == 0) {
        fprintf(stderr, "Error in hardware initialization\n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < 16; i++)
        IRQVECTOR[i] = empty_it;

    test_read_write_sector();
    test_read_write_sector_n();
    test_format_sectors();
    test_create_mbr();
    test_create_volume();
    test_cyl_of_bloc();
    test_sec_of_bloc();
    test_init_super();
    test_load_super();

    return EXIT_SUCCESS;
}
