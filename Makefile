OBJS	= main.o
SOURCE	= main.cpp
HEADER	=
OUT	= main
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm -lGL -L/usr/X11R6/lib -lGLU -lglut -lGLEW 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)
	./main
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)
