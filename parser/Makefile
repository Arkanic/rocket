CC=gcc
CFLAGS=-O3 -std=gnu99 -Wno-unused-result
TLMOUT=ll.o json.o tlm.o
LLTESTOUT=ll.o ll_test.o

all: tlm

%.o: %.c
	$(CC) $(CFLAGS) -c $<

tlm: $(TLMOUT)
	$(CC) $(CFLAGS) -g -o tlm $(TLMOUT)

ll_test: $(LLTESTOUT)
	$(CC) $(CFLAGS) -g -o ll_test $(LLTESTOUT)

clean:
	rm -rf *.o tlm ll_test

.PHONY: clean