#include <string.h>
#include "hardware.h"
#include "hconf.h"
#include "semaphore.h"

struct sem_s mutex;

void read_sector(unsigned int cyl, unsigned int sec,
                 unsigned char *buffer) {
    _out(0x110, (cyl >> 8) & 0xFF);
    _out(0x111, cyl & 0xFF);
    _out(0x112, (sec >> 8) & 0xFF);
    _out(0x113, sec  & 0xFF);
    _out(HDA_CMDREG, 2); /* SEEK */
    _sleep(14);

    _out(0x110, 0);
    _out(0x111, 1);
    _out(HDA_CMDREG, 4); /* READ */
    _sleep(14);

    memcpy(buffer, MASTERBUFFER, SECTOR_SIZE);
}

void write_sector(unsigned int cyl, unsigned int sec,
                  const unsigned char *buffer) {
    _out(0x110, (cyl >> 8) & 0xFF);
    _out(0x111, cyl & 0xFF);
    _out(0x112, (sec >> 8) & 0xFF);
    _out(0x113, sec  & 0xFF);
    _out(HDA_CMDREG, 2); /* SEEK */
    _sleep(14);

    memcpy(MASTERBUFFER, buffer, SECTOR_SIZE);

    _out(0x110, 0);
    _out(0x111, 1);
    _out(HDA_CMDREG, 6); /* WRITE */
    _sleep(14);
}

void read_sector_n(unsigned int cyl, unsigned int sec,
                   unsigned char *buffer, int size) {

    if (mutex == NULL)
        sem_init(&mutex, 0);

    _out(0x110, (cyl >> 8) & 0xFF);
    _out(0x111, cyl & 0xFF);
    _out(0x112, (sec >> 8) & 0xFF);
    _out(0x113, sec  & 0xFF);
    _out(HDA_CMDREG, 2); /* SEEK */
    sem_down(&mutex);

    _out(0x110, 0);
    _out(0x111, 1);
    _out(HDA_CMDREG, 4); /* READ */
    sem_down(&mutex);

    memcpy(buffer, MASTERBUFFER, size);
}

void write_sector_n(unsigned int cyl, unsigned int sec,
                    const unsigned char *buffer, int size) {
    int i;
    for (i = 0; i < 256; i++) {
        MASTERBUFFER[i] = 0xaf;
    }

    _out(0x110, (cyl >> 8) & 0xFF);
    _out(0x111, cyl & 0xFF);
    _out(0x112, (sec >> 8) & 0xFF);
    _out(0x113, sec  & 0xFF);
    _out(HDA_CMDREG, 2); /* SEEK */
    _sleep(14);

    memcpy(MASTERBUFFER, buffer, size);

    _out(0x110, 0);
    _out(0x111, 1);
    _out(HDA_CMDREG, 6); /* WRITE */
    _sleep(14);
}


void format_sector(unsigned int cyl, unsigned int sec,
                   unsigned int nsec,
                   unsigned int value) {
    unsigned int i;
    for (i = sec; i < sec + nsec; i++) {
        _out(0x110, (cyl >> 8) & 0xFF);
        _out(0x111, cyl & 0xFF);
        _out(0x112, (i >> 8) & 0xFF);
        _out(0x113, i  & 0xFF);
        _out(HDA_CMDREG, 2); /* SEEK */
        _sleep(14);

        _out(0x110, 0);
        _out(0x111, 1);
        _out(0x112, (value >> 24) & 0xFF);
        _out(0x113, (value >> 16) & 0xFF);
        _out(0x114, (value >>  8) & 0xFF);
        _out(0x115, value & 0xFF);
        _out(HDA_CMDREG, 8); /* FORMAT */
        _sleep(14);
    }
}

void reverse_format_sector(unsigned int cyl, unsigned int sec,
                          unsigned int nsec,
                          unsigned int value) {
    unsigned int i;
    for (i = sec + nsec; i >= sec; i--) {
        _out(0x110, (cyl >> 8) & 0xFF);
        _out(0x111, cyl & 0xFF);
        _out(0x112, (i >> 8) & 0xFF);
        _out(0x113, i  & 0xFF);
        _out(HDA_CMDREG, 2); /* SEEK */
        _sleep(14);

        _out(0x110, 0);
        _out(0x111, 1);
        _out(0x112, (value >> 24) & 0xFF);
        _out(0x113, (value >> 16) & 0xFF);
        _out(0x114, (value >>  8) & 0xFF);
        _out(0x115, value & 0xFF);
        _out(HDA_CMDREG, 8); /* FORMAT */
        _sleep(14);
    }
}
