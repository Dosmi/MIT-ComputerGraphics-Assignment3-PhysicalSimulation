INCFLAGS  = -I vecmath/include
INCFLAGS += -I /usr/include/GL
# add printing macros for debugging messages:
# usage:
# dbug "message"/variable eol;
# additional information printed:
# - file name the debug message is coming from,
# - function name the debug message is coming from,
# - line number in that file the debug message is coming from

MACROS    = -D'dvar(x)=\#x<<" = "<<x'

# MACROS   += -DWAIT='std::cin.get()'
MACROS   += -DWAIT=''

MACROS   += -Ddbug='std::cout<<__FILE__<<":"<<__FUNCTION__<<"-"<<__LINE__<<":							"<<'

MACROS   += -Deol='<<std::endl<<std::endl'
# MACROS   += -Deol='<<std::endl<<__PRETTY_FUNCTION__<<std::endl<<std::endl'



LINKFLAGS = -L. -lRK4 -lglut -lGL -lGLU
CFLAGS    = -g -Wall -ansi $(MACROS) -std=c++11
CC        = g++
SRCS      = $(wildcard *.cpp)
SRCS     += $(wildcard vecmath/src/*.cpp)
OBJS      = $(SRCS:.cpp=.o)
PROG      = a3

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

clean:
	rm $(OBJS) $(PROG)
