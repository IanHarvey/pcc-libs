#	$Id$
#
# Makefile.in for libpccsoftfloat.a
#


srcdir = .
top_srcdir = ..
top_builddir = ../
prefix = /usr/local
exec_prefix = ${prefix}
libdir = ${exec_prefix}/lib

CC = i386-netbsdelf-pcc
TARGOS = netbsd
TARGMACH = i386
VERSION = 0.9.9
PCCLIBDIR = $(libdir)/pcc/$(TARGMACH)-$(TARGOS)/$(VERSION)/lib
PCCINCDIR = $(libdir)/pcc/$(TARGMACH)-$(TARGOS)/$(VERSION)/include

CPPFLAGS +=  -I$(top_builddir) -I$(srcdir) -I$(srcdir)/arch/$(TARGMACH)

LIBS = 
AR = ar
RANLIB = ranlib
INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}

HEADERS +=	float.h stdarg.h stdbool.h stddef.h

OBJS +=		cmpdi2.o divdi3.o fixdfdi.o fixsfdi.o fixunsdfdi.o \
		fixunssfdi.o floatdidf.o floatdisf.o floatunsdidf.o \
		moddi3.o muldi3.o negdi2.o qdivrem.o \
		ucmpdi2.o udivdi3.o umoddi3.o 

OBJS +=		ashldi3.o ashrdi3.o lshrdi3.o

OBJS +=		_alloca.o

DEST = libpcc.a

all: $(DEST)

$(DEST): $(OBJS)
	$(AR) r $@ $?
	$(RANLIB) $@

.c.o :
	$(CC) -O $(CPPFLAGS) $(CFLAGS) -c $<

install:
	test -z "$(PCCINCDIR)" || mkdir -p "$(PCCINCDIR)"
	headers='$(HEADERS)'; for i in $$headers; do \
		$(INSTALL) -m 644 $(srcdir)/include/$$i $(PCCINCDIR)/$$i; \
	done
	test -z "$(PCCLIBDIR)" || mkdir -p "$(PCCLIBDIR)"
	$(INSTALL_PROGRAM) $(DEST) $(PCCLIBDIR)

clean:
	/bin/rm -f $(OBJS) $(DEST)

distclean:
	/bin/rm -f Makefile
