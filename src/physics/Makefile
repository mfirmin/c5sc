UNAME := $(shell uname)

INCLUDELOCAL = -I/usr/local/include -O3
ifeq ($(UNAME), Darwin)
	LIBOPT = -L/opt/X11/lib -L/usr/local/lib -lode
	FLTKLD = -L/usr/local/lib -lfltk -lpthread -framework Cocoa
	FLTKCXX = -I/usr/local/include -I/usr/local/include/FL/images -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT
endif
ifeq ($(UNAME), Linux)
	LIBOPT = -L/usr/X11R6/lib -lGLU -lGL -lGLC -lm -lode
	FLTKCXX = -I/usr/local/include -I/usr/local/include/FL/images -I/usr/local/include/freetype2 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT
	FLTKLD = -L/usr/local/lib -lfltk -lXext -lXft -lfontconfig -lXinerama -lpthread -ldl -lm -lX11
endif

GVCFLAGS = `pkg-config libgvc --cflags` -Wall -g -O2
GVLDFLAGS = `pkg-config libgvc --libs`

CC = g++ -std=c++0x

all: ode Makefile

clean: 
	rm *.o ode

ode: ODEWrapper.o
	$(CC) -o ode *.o $(INCLUDELOCAL) $(LIBOPT) 

ODEWrapper.o: ODEWrapper.h ODEWrapper.cpp VECTOR.h
	$(CC) -c ODEWrapper.cpp $(LIBOPT) $(INCLUDELOCAL)
