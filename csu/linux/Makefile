MACH=i386
ABI=elf

CFLAGS = -I$(MACH) -I. -Wall -Wstrict-prototypes -Wmissing-prototypes

OBJS = crt0.o crt1.o crti.o crtn.o crtbegin.o crtend.o

all:	$(OBJS)

crt0.o:	$(MACH)/crt0.c
	$(CC) -O $(CFLAGS) -c -o $@ $<

crt1.o:	$(MACH)/crt0.c
	$(CC) -O $(CFLAGS) -c -o $@ $<

gcrt1.o: $(MACH)/crt0.c
	$(CC) -O -DDYNAMIC -DPROFILE $(CFLAGS) -c -o $@ $<

crti.o: $(MACH)/crti.c
	$(CC) -O $(CFLAGS) -c -o $@ $<

crtn.o: $(MACH)/crtn.c
	$(CC) -O $(CFLAGS) -c -o $@ $<

crtbegin.o: crtbegin.c
	$(CC) -O $(CFLAGS) -c -o $@ $<

crtend.o: crtend.c
	$(CC) -O $(CFLAGS) -c -o $@ $<

install:
	mkdir -p /usr/local/lib/pcc/$(MACH)-linux/0.9.9/lib
	cp $(OBJS) /usr/local/lib/pcc/$(MACH)-linux/0.9.9/lib

clean:
	rm -f $(OBJS)
