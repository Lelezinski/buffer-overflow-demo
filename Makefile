CC=gcc
CFLAGS=-fno-stack-protector -w

LIB=-lbcm2835

SRCDIR=./src/
OUTDIR=./out/
RESDIR=./res/

SRC=morsecode.c
OUT=morsecode

all: shell morsecode payload

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

morsecode: $(SRCDIR)$(SRC)
	$(CC) $(CFLAGS) $(SRCDIR)$(SRC) -o $(OUTDIR)$(OUT) $(LIB)
	execstack -s $(OUTDIR)$(OUT)

payload: $(SRCDIR)$(SRC)
	$(RESDIR)makepayload.sh

shell: $(RESDIR)shell.c
	$(CC) -o $(RESDIR)shell $(RESDIR)shell.c

clean: 
	rm -f *.o $(OUTDIR)$(OUT) $(RESDIR)shell $(RESDIR)payload.bin