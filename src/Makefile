PROGRAM = crazy-roll
CFLAGS  = -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL

$(PROGRAM): ../includes/game.h game.o main.o
	$(CC) $(LDFLAGS) -o $@ game.o main.o $(LDLIBS)
	
game.o: game.c ../includes/game.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)
	
main.o: main.c ../includes/game.h
	$(CC) $(LDFLAGS) -c -o $@ $< $(LDLIBS)
	
.PHONY : clean

clean: 
	rm *.o $(PROGRAM)
