INCFLAGS  = -I vecmath/include
INCFLAGS += -I /usr/include/GL
# add printing macros for debugging messages:
# usage:
# dbug "message"/variable eol;
# additional information printed:
# - file name the debug message is coming from,
# - function name the debug message is coming from,
# - line number in that file the debug message is coming from

#define __CLASS_NAME__
# MACROS    = -D__CLASS_NAME__='className(__PRETTY_FUNCTION__)'
# MACROS    = -D'cladssName(x)=\#x'
# MACROS      = -D'logvar(x)=\#x\#\#\#x'
MACROS      = -D'logvar(x)=\#x<<" - "<<x' 
# MACROS    = -D'std::string className(const std::string& prettyFunction)=\
# {\
# 		size_t colons = prettyFunction.find("::");\
# 		if (colons == std::string::npos)\
# 				return "::";\
# 		size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;\
# 		size_t end = colons - begin;\
# 		return prettyFunction.substr(begin,end);\
# }'

MACROS   += -Ddbug='std::cout<<__FILE__<<":"<<__FUNCTION__<<"-"<<__LINE__<<":							"<<'
# MACROS   += -Ddbug='std::cout<<__FILE__<<"("<<__CLASS_NAME__<<"::"<<__FUNCTION__<<")"<<"-"<<__LINE__<<":		"<<'
MACROS   += -Deol='<<std::endl<<__PRETTY_FUNCTION__<<std::endl<<std::endl'

LINKFLAGS = -L. -lRK4 -lglut -lGL -lGLU
CFLAGS    = -g -Wall -ansi $(MACROS)
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
