PROGRAM = crazy-roll
CFLAGS  = -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): game.o main.o image.o
	$(CC) $(LDFLAGS) -o $@ image.o game.o main.o $(LDLIBS)

image.o: image.c ../includes/image.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)
	
game.o: game.c ../includes/game.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)
	
main.o: main.c ../includes/game.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)
	
.PHONY : clean

clean: 
	rm *.o $(PROGRAM)
