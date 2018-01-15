void read_sector(unsigned int cylinder, unsigned int sector,
                 unsigned char *buffer);
void write_sector(unsigned int cylinder, unsigned int sector,
                  const unsigned char *buffer);
void read_sector_n(unsigned int cylinder, unsigned int sector,
                 unsigned char *buffer, int size);
void write_sector_n(unsigned int cylinder, unsigned int sector,
                  const unsigned char *buffer, int size);
void format_sector(unsigned int cylinder, unsigned int sector,
                   unsigned int nsector,
                   unsigned int value);
void reverse_format_sector(unsigned int cylinder, unsigned int sector,
                           unsigned int nsector,
                           unsigned int value);
