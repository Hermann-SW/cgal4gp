# make all will create
#  libcgal4gp.so (to be used by "install" under GP)
#
# Under GP: install("get_squared_width", "vG&&", , "./libcgal4gp.so")
# enables you to subsequently use get_squared_width(points, num, denom) in GP

TARGET = cgal4gp

CC         = /usr/bin/g++
#CPPFLAGS   = -I. -I/usr/local/include -fPIC -Wall -pedantic -Wextra
CPPFLAGS   = -O3 -ffp-contract=off -fno-strict-aliasing -fPIC -Wall -pedantic -Wextra
LD         = /usr/bin/g++
LDFLAGS    = -O3 -Wall -ffp-contract=off -fno-strict-aliasing    -Wl,--export-dynamic 
MODLD      = /usr/bin/g++
MODLDFLAGS = -shared -Wl,-shared 
EXTRAMODLDFLAGS = -lc -lm -L/usr/local/lib # -lpari

RM = rm -f

OBJS = $(TARGET).o
DYN = lib$(TARGET).so
ALL = $(DYN)

all: $(ALL)
	gp -q < simple.gp

dynlib: $(DYN)

$(DYN): $(OBJS)
	$(MODLD) -o $@ $(MODLDFLAGS) $(OBJS) $(EXTRAMODLDFLAGS)

clean:
	-$(RM) *.o $(ALL)
