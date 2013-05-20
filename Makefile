#usage
#make CFG=release

CPP = g++
CC = gcc
CPPFLAGS += -std=c++11 -Wall -Wextra -pedantic-errors
INCLUDE = -Isrc/

LIB = `pkg-config --libs sfml-all`

ifeq ($(CFG),)
CFG=debug
endif

ifeq ($(CFG),debug)
CPPFLAGS += -ggdb -DDEBUG
else
CPPFLAGS += -O2
endif
CPPFLAGS += $(INCLUDE)

VPATH=src:src/util/:src/config/:src/core/:src/log/:src/logic/
TARGET=gameoflife

SRC = \
	main.cpp \
	Application.cpp \
	AppStateGame.cpp \
	Grid.cpp

OBJ = $(patsubst %.cpp, objs.$(CFG)/%.o, ${SRC})
DEP = $(patsubst %.cpp, deps.$(CFG)/%.d, ${SRC})

all: ${TARGET}

${TARGET}: ${OBJ}
	mkdir -p $(dir $@)
	$(CPP) $^ $(LIBDIR) $(LIB) -o $@

test:
	echo $(OBJ)
	echo $(DEP)

objs.$(CFG)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) -c $(CPPFLAGS) $< -o $@

.PHONY: clean deps

clean:
	rm -r objs.debug deps.debug ${TARGET}
	rm -r objs.release deps.release