MACH ?= powerpc
TARGET ?= $(MACH)-darwin
VERSION ?= 0.9.9
PCCLIBDIR ?= /usr/local/lib/pcc/$(TARGET)/$(VERSION)/lib

CFLAGS = -I$(MACH) -I. -Wall -Werror -Wstrict-prototypes -Wmissing-prototypes

OBJS = crt0.o crt1.o gcrt1.o dylib1.o

all:	$(OBJS)

crt0.o:	$(MACH)/crt0.c
	$(CC) -r -static -nostdlib -Wl,-keep_private_externs -DCRT -O $(CFLAGS) -o $@ $<

crt1.o:	$(MACH)/crt0.c
	$(CC) -r -nostdlib -Wl,-keep_private_externs -DCRT -DDYNAMIC -O $(CFLAGS) -o $@ $< /usr/lib/dyld

gcrt1.o: $(MACH)/crt0.c
	$(CC) -r -nostdlib -Wl,-keep_private_externs -DCRT -DDYNAMIC -DPROFILE -O $(CFLAGS) -o $@ $< /usr/lib/dyld

dylib1.o: $(MACH)/dylib1.c
	$(CC) -r -nostdlib -Wl,-keep_private_externs -DDYNAMIC -O $(CFLAGS) -o $@ $< 

install:
	mkdir -p ${DESTDIR}$(PCCLIBDIR)
	cp $(OBJS) ${DESTDIR}$(PCCLIBDIR)

clean:
	rm -f $(OBJS)
