
CC = gcc -g
CFLAGS = -Wall -Iinclude -llibs
LDFLAGS = -lSDL2_image -lSDL2
OBJ =  enemies.o player.o SDLFcts.o controller.o main.o 
EXE = execu





$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LDFLAGS)


player.o: sources/player.c include/player.h 
	$(CC) $(CFLAGS) -c sources/player.c -o player.o

enemies.o : sources/enemies.c include/enemies.h include/player.h
	$(CC) $(CFLAGS) -c sources/enemies.c -o enemies.o

controller.o : sources/controller.c include/controller.h include/enemies.h include/player.h
	$(CC) $(CFLAGS) -c sources/controller.c -o controller.o

SDLFcts.o: sources/SDLFcts.c include/SDLFcts.h include/enemies.h include/player.h
	$(CC) $(CFLAGS) -c sources/SDLFcts.c -o SDLFcts.o


main.o: main.c include/player.h include/SDLFcts.h include/controller.h
	$(CC) $(CFLAGS) -c main.c -o main.o


clean:
	rm -f *.o $(EXE)


run: 
	./$(EXE)


all: clean $(EXE) run		