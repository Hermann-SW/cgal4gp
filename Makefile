# make all will create
#  libcgal4gp.so (to be used by "install" under GP)
#
# Under GP: install("get_squared_width", "v&&", , "./libcgal4gp.so")
# enables you to subsequently use get_squared_width(num, denom) in GP

TARGET = cgal4gp

CC         = /usr/bin/g++
CPPFLAGS   = -O3 -ffp-contract=off -fno-strict-aliasing -fPIC -Wall -pedantic -Wextra -std=c++14
LD         = /usr/bin/g++
LDFLAGS    = -O3 -Wall -ffp-contract=off -fno-strict-aliasing    -Wl,--export-dynamic 
MODLD      = /usr/bin/g++
MODLDFLAGS = -shared -Wl,-shared 
EXTRAMODLDFLAGS = -lc -lm -lgmp

RM = rm -f

OBJS = $(TARGET).o
DYN = lib$(TARGET).so
ALL = $(DYN)

all: $(ALL)
	gp -q < simple.gp

viewer:
	cd Basic_Viewer && ./build+run

dynlib: $(DYN)

$(DYN): $(OBJS)
	$(MODLD) -o $@ $(MODLDFLAGS) $(OBJS) $(EXTRAMODLDFLAGS)

cpplint: cgal4gp.cpp
	cpplint --filter=-legal/copyright $<

cppcheck: cgal4gp.cpp
	cppcheck --enable=all --suppress=missingIncludeSystem $< --check-config

clean:
	-$(RM) *.o $(ALL)
