MACH=powerpc

CFLAGS = -I$(MACH) -I. -Wall -Werror -Wstrict-prototypes -Wmissing-prototypes

OBJS = crt0.o crt1.o gcrt1.o

all:	$(OBJS)

crt0.o:	$(MACH)/crt0.c
	$(CC) -r -static -nostdlib -keep_private_externs -O $(CFLAGS) -o $@ $<

crt1.o:	$(MACH)/crt0.c
	$(CC) -r -nostdlib -keep_private_externs -DDYNAMIC -O $(CFLAGS) -o $@ $< /usr/lib/dyld

gcrt1.o: $(MACH)/crt0.c
	$(CC) -r -nostdlib -keep_private_externs -DDYNAMIC -DPROFILE -O $(CFLAGS) -o $@ $< /usr/lib/dyld

install:
	mkdir -p /usr/local/lib/pcc/$(MACH)-darwin/0.9.9/lib
	cp $(OBJS) /usr/local/lib/pcc/$(MACH)-darwin/0.9.9/lib

clean:
	rm -f $(OBJS)
