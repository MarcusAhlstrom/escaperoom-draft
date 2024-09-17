CC=gcc
CFLAGS=-Werror -Wall -Wextra -Wpedantic -Wmissing-declarations -std=gnu11 -lncurses
PROGNAME=escaperoom

all: $(PROGNAME)

$(PROGNAME): $(PROGNAME).o soundPlayer.o safeFunctions.o stageOne.o stageTwo.o stageThree.o stageFour.o stageFive.o stageSix.o stageSeven.o stageEight.o stageNine.o stageTen.o
	$(CC) -o $(PROGNAME) $(PROGNAME).o soundPlayer.o safeFunctions.o stageOne.o stageTwo.o stageThree.o stageFour.o stageFive.o stageSix.o stageSeven.o stageEight.o stageNine.o stageTen.o $(CFLAGS)

$(PROGNAME).o: main.c
	$(CC) -c main.c -o $(PROGNAME).o $(CFLAGS)

soundPlayer.o: soundPlayer.c soundPlayer.h
	$(CC) -c soundPlayer.c $(CFLAGS)

safeFunctions.o: safeFunctions.c safeFunctions.h
	$(CC) -c safeFunctions.c $(CFLAGS)

stageOne.o: stageOne.c stageOne.h
	$(CC) -c stageOne.c $(CFLAGS)

stageTwo.o: stageTwo.c stageTwo.h
	$(CC) -c stageTwo.c $(CFLAGS)

stageThree.o: stageThree.c stageThree.h
	$(CC) -c stageThree.c $(CFLAGS)

stageFour.o: stageFour.c stageFour.h
	$(CC) -c stageFour.c $(CFLAGS)

stageFive.o: stageFive.c stageFive.h
	$(CC) -c stageFive.c $(CFLAGS)

stageSix.o: stageSix.c stageSix.h
	$(CC) -c stageSix.c $(CFLAGS)

stageSeven.o: stageSeven.c stageSeven.h
	$(CC) -c stageSeven.c $(CFLAGS)

stageEight.o: stageEight.c stageEight.h
	$(CC) -c stageEight.c $(CFLAGS)

stageNine.o: stageNine.c stageNine.h
	$(CC) -c stageNine.c $(CFLAGS)

stageTen.o: stageTen.c stageTen.h
	$(CC) -c stageTen.c $(CFLAGS)

clean:
	rm -f *.o
