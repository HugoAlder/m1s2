CC	= gcc
CFLAGS	= -m32 -Wall -ansi -pedantic
CFLAGS  += -g

INCDIR  = -Iinclude
LIBS    = -Llib -lhardware

SRC = src
BIN = bin

ALL  = mkhd dmps frmt
ALL += lsvol mkvol frmtvol
ALL += createinode rminode
ALL += if_nfile if_pfile if_cfile if_dfile
ALL += test
BINS = $(ALL:%=$(BIN)/%)

all: $(BINS)

$(ALL): %: $(BIN)/%

$(BIN)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCDIR)

$(BIN)/%:
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

#######
# Clean

.PHONY: all clean realclean
clean:
	$(RM) $(BIN)/*
realclean: clean
	$(RM) vdiskA.bin vdiskB.bin

##########
# Binaries

$(BIN)/mkhd: $(BIN)/mkhd.o
$(BIN)/dmps: $(BIN)/dmps.o $(BIN)/drive.o
$(BIN)/frmt: $(BIN)/frmt.o $(BIN)/drive.o
$(BIN)/lsvol: $(BIN)/lsvol.o $(BIN)/vol.o $(BIN)/mbr.o $(BIN)/drive.o
$(BIN)/mkvol: $(BIN)/mkvol.o $(BIN)/vol.o $(BIN)/mbr.o $(BIN)/drive.o
$(BIN)/frmtvol: $(BIN)/frmtvol.o $(BIN)/mbr.o $(BIN)/drive.o
$(BIN)/createinode: $(BIN)/createinode.o $(BIN)/inode.o $(BIN)/vol.o $(BIN)/mbr.o $(BIN)/drive.o
$(BIN)/rminode: $(BIN)/rminode.o $(BIN)/inode.o $(BIN)/vol.o $(BIN)/mbr.o $(BIN)/drive.o
$(BIN)/if_nfile: $(BIN)/if_nfile.o $(BIN)/ifile.o $(BIN)/inode.o $(BIN)/vol.o $(BIN)/mbr.o $(BIN)/drive.o
$(BIN)/if_cfile: $(BIN)/if_cfile.o $(BIN)/ifile.o $(BIN)/inode.o $(BIN)/vol.o $(BIN)/mbr.o $(BIN)/drive.o
$(BIN)/if_pfile: $(BIN)/if_pfile.o $(BIN)/ifile.o $(BIN)/inode.o $(BIN)/vol.o $(BIN)/mbr.o $(BIN)/drive.o
$(BIN)/if_dfile: $(BIN)/if_dfile.o $(BIN)/ifile.o $(BIN)/inode.o $(BIN)/vol.o $(BIN)/mbr.o $(BIN)/drive.o
$(BIN)/test: $(BIN)/test.o $(BIN)/drive.o $(BIN)/vol.o $(BIN)/mbr.o
