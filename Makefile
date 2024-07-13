# make all will create
#  libcgal4gp.so (to be used by "install" under GP)
#
# Under GP: install("width", "GG", "f", "./libcgal4gp.so") enables
# you to subsequently use f(n,M) to call width(n,M)

TARGET = cgal4gp

CFLAGS     = -O3 -Wall -ffp-contract=off -fno-strict-aliasing
EXTRACFLAGS=

CC         = /usr/bin/g++
CPPFLAGS   = -I. -I/usr/local/include -fPIC
LD         = /usr/bin/gcc
LDFLAGS    = -O3 -Wall -ffp-contract=off -fno-strict-aliasing    -Wl,--export-dynamic 
MODLD      = /usr/bin/gcc
MODLDFLAGS = -shared  $(CFLAGS) $(DLCFLAGS) -Wl,-shared 
EXTRAMODLDFLAGS = -lc -lm -L/usr/local/lib # -lpari
EXTRALIBS  =

RUNPTH     = -Wl,-rpath "/usr/local/lib"
DLCFLAGS   = -fPIC
LIBS       = -lm -L/usr/local/lib

RM = rm -f

OBJS = $(TARGET).o
DYN = lib$(TARGET).so
ALL = $(DYN)

all: $(ALL)
	gp -q < simple.gp

dynlib: $(DYN)

$(DYN): $(OBJS)
	$(MODLD) -o $@ $(MODLDFLAGS) $(EXTRACFLAGS) $(OBJS) $(EXTRAMODLDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(EXTRACFLAGS) $(CPPFLAGS) $(DLCFLAGS) $<
clean:
	-$(RM) *.o $(ALL)
