UNAME := $(shell uname)

INCLUDELOCAL = -I/usr/local/include -O3
ifeq ($(UNAME), Darwin)
	LIBOPT = -L/opt/X11/lib -lGLU -lGL -lGLC -lm -lode
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
INCL = ../src/../src/VECTOR.h ../src/../src/globals.h
MAIN_INCL = main.o human.o object.o globals.o controllerReader.o action.o controller.o optimization.o shape.o joint.o VECTOR.o characterReader.o IKSolver.o mesh.o value.o transition.o
FLT_INCL = fltReader.o VECTOR.o

CC = g++ -std=c++0x

all: main Makefile

clean: 
	rm *.o main

main: fltReader.o main.o human.o object.o globals.o controllerReader.o phase.o controller.o action.o optimization.o shape.o joint.o VECTOR.o characterReader.o IKSolver.o mesh.o value.o transition.o status.o Makefile transitionFinder.o environment.o heightfield.o fltk.o entity.o envAction.o visualizer.o trajectory.o optimizer.o hierarchy.o objective.o
	$(CC) $(GLFW) -o main *.o $(GLFW2) $(LIBOPT) $(FLTKLD) $(FLTKCXX) $(GVCFLAGS) $(GVLDFLAGS) $(INCLUDELOCAL)

objective.o: ../src/objective.h ../src/objective.cpp
	$(CC) -c ../src/objective.cpp $(INCLUDELOCAL)

hierarchy.o: ../src/hierarchy.h ../src/hierarchy.cpp
	$(CC) -c ../src/hierarchy.cpp $(INCLUDELOCAL)

optimizer.o: ../src/optimizer.h ../src/optimizer.cpp ../src/hierarchy.h ../src/phase.h ../src/trajectory.h ../src/objective.h
	$(CC) -c ../src/optimizer.cpp $(INCLUDELOCAL)

trajectory.o: ../src/trajectory.h ../src/trajectory.cpp ../src/VECTOR.h ../src/globals.h
	$(CC) -c ../src/trajectory.cpp $(INCLUDELOCAL)

visualizer.o: ../src/visualizer.h ../src/visualizer.cpp ../src/VECTOR.h
	$(CC) -c ../src/visualizer.cpp $(INCLUDELOCAL)

envAction.o: ../src/envAction.h ../src/envAction.cpp ../src/action.h ../src/environment.h ../src/object.h ../src/entity.h
	$(CC) -c ../src/envAction.cpp $(INCLUDELOCAL)

entity.o: ../src/../src/entity.cpp ../src/entity.h ../src/object.h ../src/VECTOR.h
	$(CC) -c ../src/entity.cpp $(INCLUDELOCAL)

fltk.o: ../src/fltk.cpp ../src/fltk.h
	$(CC) -c ../src/fltk.cpp $(FLTKCXX)  $(INCLUDELOCAL)

fltReader.o: ../src/fltReader.cpp ../src/fltReader.h ../src/mesh.h ../src/vertex.h
	$(CC) -c  ../src/fltReader.cpp -I/usr/local/include

main.o: ../src/main.cpp ../src/main.h ../src/controller.h ../src/VECTOR.h ../src/globals.h ../src/object.h ../src/human.h ../src/controllerReader.h ../src/characterReader.h ../src/shape.h ../src/fltReader.h ../src/face.h ../src/main.h ../src/transition.h ../src/status.h ../src/transitionFinder.h ../src/fltk.h ../src/environment.h ../src/visualizer.h ../src/trajectory.h optimizer.o hierarchy.o
	$(CC) -c ../src/main.cpp -I/usr/X11R6/include $(INCLUDELOCAL)

human.o: ../src/human.cpp ../src/human.h ../src/joint.h ../src/shape.h ../src/globals.h ../src/VECTOR.h ../src/optimization.h ../src/object.h
	$(CC) -c ../src/human.cpp $(INCLUDELOCAL)

object.o: ../src/object.cpp ../src/object.h ../src/VECTOR.h ../src/shape.h ../src/globals.h ../src/joint.h ../src/environment.h ../src/entity.h
	$(CC) -c ../src/object.cpp $(INCLUDELOCAL)

globals.o: ../src/globals.cpp ../src/globals.h ../src/VECTOR.h
	$(CC) -c ../src/globals.cpp $(INCLUDELOCAL)

controllerReader.o: ../src/controllerReader.cpp ../src/controllerReader.h ../src/globals.h ../src/controller.h ../src/phase.h ../src/human.h ../src/action.h ../src/IKSolver.h ../src/value.h ../src/transition.h ../src/xpressivefunctions.h ../src/envAction.h
	$(CC) -c ../src/controllerReader.cpp -ftemplate-depth-750 $(INCLUDELOCAL)

phase.o: ../src/phase.cpp ../src/phase.h ../src/human.h ../src/value.h ../src/action.h ../src/transition.h ../src/status.h
	$(CC) -c ../src/phase.cpp $(INCLUDELOCAL)

controller.o: ../src/controller.cpp ../src/controller.h ../src/phase.h ../src/globals.h ../src/value.h
	$(CC) -c ../src/controller.cpp $(INCLUDELOCAL)

action.o: ../src/action.cpp ../src/action.h ../src/optimization.h ../src/globals.h ../src/object.h ../src/joint.h ../src/value.h ../src/environment.h
	$(CC) -c ../src/action.cpp $(INCLUDELOCAL)

optimization.o: ../src/optimization.cpp ../src/optimization.h ../src/human.h ../src/joint.h ../src/value.h
	$(CC) -c ../src/optimization.cpp $(INCLUDELOCAL)

shape.o: ../src/shape.cpp ../src/shape.h ../src/VECTOR.h ../src/globals.h
	$(CC) -c ../src/shape.cpp $(INCLUDELOCAL)

joint.o: ../src/joint.cpp ../src/joint.h ../src/VECTOR.h ../src/globals.h ../src/optimization.h ../src/object.h
	$(CC) -c ../src/joint.cpp $(INCLUDELOCAL)

VECTOR.o: ../src/VECTOR.cpp ../src/VECTOR.h $(INCL)
	$(CC) -c ../src/VECTOR.cpp $(INCLUDELOCAL)

characterReader.o: ../src/characterReader.cpp ../src/characterReader.h ../src/globals.h
	$(CC) -c ../src/characterReader.cpp $(INCLUDELOCAL)

IKSolver.o: ../src/IKSolver.cpp ../src/IKSolver.h ../src/joint.h ../src/action.h ../src/VECTOR.h ../src/joint.h ../src/value.h
	$(CC) -c ../src/IKSolver.cpp $(INCLUDELOCAL)

mesh.o: ../src/mesh.cpp ../src/mesh.h ../src/component.h ../src/vertex.h
	$(CC) -c ../src/mesh.cpp $(INCLUDELOCAL)

value.o: ../src/value.cpp ../src/value.h ../src/globals.h
	$(CC) -c ../src/value.cpp $(INCLUDELOCAL)

transition.o: ../src/transition.h ../src/transition.cpp ../src/globals.h ../src/value.h ../src/human.h ../src/environment.h
	$(CC) -c ../src/transition.cpp $(INCLUDELOCAL)

status.o: ../src/status.cpp ../src/status.h ../src/VECTOR.h ../src/human.h ../src/globals.h
	$(CC) -c ../src/status.cpp $(INCLUDELOCAL)

transitionFinder.o: ../src/transitionFinder.cpp ../src/transitionFinder.h ../src/status.h ../src/hierarchy.h
	$(CC) -c ../src/transitionFinder.cpp $(INCLUDELOCAL)

environment.o: ../src/environment.cpp ../src/environment.h ../src/object.h ../src/env_functions.h ../src/heightfield.h ../src/entity.h ../src/VECTOR.h
	$(CC) -c ../src/environment.cpp -ftemplate-depth-750 $(INCLUDELOCAL)

heightfield.o: ../src/heightfield.cpp ../src/heightfield.h ../src/object.h ../src/globals.h
	$(CC) -c ../src/heightfield.cpp $(INCLUDELOCAL)
