# Filesystem

## Example usage

```sh
$ make realclean && make        # Make sure that we start from scratch
$ ./bin/frmt                    # First of all, we create the HD and format it
$ ./bin/mkvol 0 1 255 1 test    # Creating a volume "test" next to the mbr with the size of 255 blocs
$ ./bin/lsvol                   # Check if the volume was created
1/8 volumes :
	0 - test - cyl=0 sect=1 blocs=255 BASE
$ ./bin/if_nfile < etc/test.txt # Creating a file with the content of etc/test.txt
Creating file : 1
$ ./bin/if_pfile 1              # Reading the file previously created
Hello this is a small text file !!
$ ./bin/if_cfile 1              # Copying the file previously created
Copying content of file inode=1 in file inode=3
$ ./bin/if_pfile 3              # Check if the file was copied
Hello this is a small text file !!
$ ./bin/if_dfile 3              # Deleting the file
$ ./bin/if_pfile 3              # Check if the file doesn't exist
if_pfile: src/inode.c:11: read_inode: Assertion `inode->magic == INODE_MAGIC' failed.
[2]    13709 abort (core dumped)  ./bin/if_pfile 3
$ ./bin/dmps 0 4                # We can also check if the file is now a "free_bloc"
000:  04 00 00 00 15 08 80 00 af af af af af af af af
016:  af af af af af af af af af af af af af af af af
032:  af af af af af af af af af af af af af af af af
048:  af af af af af af af af af af af af af af af af
064:  af af af af af af af af af af af af af af af af
080:  af af af af af af af af af af af af af af af af
096:  af af af af af af af af af af af af af af af af
112:  af af af af af af af af af af af af af af af af
128:  af af af af af af af af af af af af af af af af
144:  af af af af af af af af af af af af af af af af
160:  af af af af af af af af af af af af af af af af
176:  af af af af af af af af af af af af af af af af
192:  af af af af af af af af af af af af af af af af
208:  af af af af af af af af af af af af af af af af
224:  af af af af af af af af af af af af af af af af
240:  af af af af af af af af af af af af af af af af
$ ./bin/dmps 0 5                # Same for the content of the file
000:  05 00 00 00 15 08 80 00 af af af af af af af af
016:  af af af af af af af af af af af af af af af af
032:  af af af af af af af af af af af af af af af af
048:  af af af af af af af af af af af af af af af af
064:  af af af af af af af af af af af af af af af af
080:  af af af af af af af af af af af af af af af af
096:  af af af af af af af af af af af af af af af af
112:  af af af af af af af af af af af af af af af af
128:  af af af af af af af af af af af af af af af af
144:  af af af af af af af af af af af af af af af af
160:  af af af af af af af af af af af af af af af af
176:  af af af af af af af af af af af af af af af af
192:  af af af af af af af af af af af af af af af af
208:  af af af af af af af af af af af af af af af af
224:  af af af af af af af af af af af af af af af af
240:  af af af af af af af af af af af af af af af af
```

## Tests

We can also run test to check if some functions are working well :
```sh
$ make realclean && make
$ ./bin/test
test_read_write_sector : [OK]
test_read_write_sector_n : [OK]
test_format_sectors : [OK]
test_create_mbr : [OK]
test_create_volume : [OK]
test_cyl_of_bloc : [OK]
test_sec_of_bloc : [OK]
test_init_super : [OK]
test_load_super : [OK]
```
