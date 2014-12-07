UNAME := $(shell uname)

INCLUDELOCAL = -I/usr/local/include -O3
ifeq ($(UNAME), Darwin)
	LIBOPT = -L/opt/X11/lib -L/usr/local/lib -lGLU -lGL -lGLC -lm -lode
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

GLFW = `pkg-config --cflags glfw3`
GLFW2 = `pkg-config --static --libs glfw3`

CC = g++ -std=c++0x

all: world Makefile

clean: 
	rm *.o world

world: world.o ../physics/ode.o ../entity/entity.o ../entity/geometry.o ../entity/box.o ../renderer/renderer.o
	$(CC) $(GLFW) -o world *.o ../physics/ode.o ../entity/entity.o ../entity/geometry.o ../entity/box.o ../renderer/renderer.o $(GLFW2) $(INCLUDELOCAL) $(LIBOPT)  

../renderer/renderer.o: ../entity/Entity.h ../entity/Geometry.h ../renderer/Renderer.cpp ../renderer/Renderer.h
	cd ../renderer; \
	$(CC) -c Renderer.cpp -o renderer.o $(LIBOPT) $(INCLUDELOCAL)
	cd ../world;

../physics/ode.o: ../physics/ODEWrapper.h ../physics/ODEWrapper.cpp ../math/VECTOR.h
	cd ../physics; \
	$(CC) -c ODEWrapper.cpp -o ode.o $(LIBOPT) $(INCLUDELOCAL)
	cd ../world;

../entity/entity.o: ../entity/Entity.h ../Entity/Entity.cpp 
	cd ../entity; \
	$(CC) -c Entity.cpp -o entity.o $(LIBOPT) $(INCLUDELOCAL)
	cd ../world;

../entity/geometry.o: ../entity/Geometry.h ../entity/Geometry.cpp
	cd ../entity; \
	$(CC) -c Geometry.cpp -o geometry.o $(LIBOPT) $(INCLUDELOCAL)
	cd ../world;

../entity/box.o: ../entity/Box.h ../entity/Box.cpp ../entity/Geometry.h
	cd ../entity; \
	$(CC) -c Box.cpp -o box.o $(LIBOPT) $(INCLUDELOCAL)
	cd ../world;

world.o: world.h world.cpp ../math/VECTOR.h ../entity/entity.h ../physics/ODEWrapper.h
	$(CC) -c World.cpp $(LIBOPT) $(INCLUDELOCAL)
