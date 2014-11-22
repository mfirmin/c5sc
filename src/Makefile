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
INCL = VECTOR.h globals.h
MAIN_INCL = main.o human.o object.o globals.o controllerReader.o action.o controller.o optimization.o shape.o joint.o VECTOR.o characterReader.o IKSolver.o mesh.o value.o transition.o
FLT_INCL = fltReader.o VECTOR.o

CC = g++ -std=c++0x

all: main Makefile

clean: 
	rm *.o main

main: fltReader.o main.o human.o object.o globals.o controllerReader.o phase.o controller.o action.o optimization.o shape.o joint.o VECTOR.o characterReader.o IKSolver.o mesh.o value.o transition.o status.o Makefile transitionFinder.o environment.o heightfield.o fltk.o entity.o envAction.o visualizer.o trajectory.o optimizer.o hierarchy.o objective.o
	$(CC) $(GLFW) -o main *.o $(GLFW2) $(LIBOPT) $(FLTKLD) $(FLTKCXX) $(GVCFLAGS) $(GVLDFLAGS) $(INCLUDELOCAL)

objective.o: objective.h objective.cpp
	$(CC) -c objective.cpp $(INCLUDELOCAL)

hierarchy.o: hierarchy.h hierarchy.cpp
	$(CC) -c hierarchy.cpp $(INCLUDELOCAL)

optimizer.o: optimizer.h optimizer.cpp hierarchy.h phase.h trajectory.h objective.h
	$(CC) -c optimizer.cpp $(INCLUDELOCAL)

trajectory.o: trajectory.h trajectory.cpp VECTOR.h globals.h
	$(CC) -c trajectory.cpp $(INCLUDELOCAL)

visualizer.o: visualizer.h visualizer.cpp VECTOR.h
	$(CC) -c visualizer.cpp $(INCLUDELOCAL)

envAction.o: envAction.h envAction.cpp action.h environment.h object.h entity.h
	$(CC) -c envAction.cpp $(INCLUDELOCAL)

entity.o: entity.cpp entity.h object.h VECTOR.h
	$(CC) -c entity.cpp $(INCLUDELOCAL)

fltk.o: fltk.cpp fltk.h
	$(CC) -c fltk.cpp $(FLTKCXX)  $(INCLUDELOCAL)

fltReader.o: fltReader.cpp fltReader.h mesh.h vertex.h
	$(CC) -c  fltReader.cpp -I/usr/local/include

main.o: main.cpp main.h controller.h VECTOR.h globals.h object.h human.h controllerReader.h characterReader.h shape.h fltReader.h face.h main.h transition.h status.h transitionFinder.h fltk.h environment.h visualizer.h trajectory.h optimizer.o hierarchy.o
	$(CC) -c main.cpp -I/usr/X11R6/include $(INCLUDELOCAL)

human.o: human.cpp human.h joint.h shape.h globals.h VECTOR.h optimization.h object.h
	$(CC) -c human.cpp $(INCLUDELOCAL)

object.o: object.cpp object.h VECTOR.h shape.h globals.h joint.h environment.h entity.h
	$(CC) -c object.cpp $(INCLUDELOCAL)

globals.o: globals.cpp globals.h VECTOR.h
	$(CC) -c globals.cpp $(INCLUDELOCAL)

controllerReader.o: controllerReader.cpp controllerReader.h globals.h controller.h phase.h human.h action.h IKSolver.h value.h transition.h xpressivefunctions.h envAction.h
	$(CC) -c controllerReader.cpp -ftemplate-depth-750 $(INCLUDELOCAL)

phase.o: phase.cpp phase.h human.h value.h action.h transition.h status.h
	$(CC) -c phase.cpp $(INCLUDELOCAL)

controller.o: controller.cpp controller.h phase.h globals.h value.h
	$(CC) -c controller.cpp $(INCLUDELOCAL)

action.o: action.cpp action.h optimization.h globals.h object.h joint.h value.h environment.h
	$(CC) -c action.cpp $(INCLUDELOCAL)

optimization.o: optimization.cpp optimization.h human.h joint.h value.h
	$(CC) -c optimization.cpp $(INCLUDELOCAL)

shape.o: shape.cpp shape.h VECTOR.h globals.h
	$(CC) -c shape.cpp $(INCLUDELOCAL)

joint.o: joint.cpp joint.h VECTOR.h globals.h optimization.h object.h
	$(CC) -c joint.cpp $(INCLUDELOCAL)

VECTOR.o: VECTOR.cpp VECTOR.h $(INCL)
	$(CC) -c VECTOR.cpp $(INCLUDELOCAL)

characterReader.o: characterReader.cpp characterReader.h globals.h
	$(CC) -c characterReader.cpp $(INCLUDELOCAL)

IKSolver.o: IKSolver.cpp IKSolver.h joint.h action.h VECTOR.h joint.h value.h
	$(CC) -c IKSolver.cpp $(INCLUDELOCAL)

mesh.o: mesh.cpp mesh.h component.h vertex.h
	$(CC) -c mesh.cpp $(INCLUDELOCAL)

value.o: value.cpp value.h globals.h
	$(CC) -c value.cpp $(INCLUDELOCAL)

transition.o: transition.h transition.cpp globals.h value.h human.h environment.h
	$(CC) -c transition.cpp $(INCLUDELOCAL)

status.o: status.cpp status.h VECTOR.h human.h globals.h
	$(CC) -c status.cpp $(INCLUDELOCAL)

transitionFinder.o: transitionFinder.cpp transitionFinder.h status.h hierarchy.h
	$(CC) -c transitionFinder.cpp $(INCLUDELOCAL)

environment.o: environment.cpp environment.h object.h env_functions.h heightfield.h entity.h VECTOR.h
	$(CC) -c environment.cpp -ftemplate-depth-750 $(INCLUDELOCAL)

heightfield.o: heightfield.cpp heightfield.h object.h globals.h
	$(CC) -c heightfield.cpp $(INCLUDELOCAL)
