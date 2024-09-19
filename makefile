CC=gcc
CFLAGS=-Werror -Wall -Wextra -Wpedantic -Wmissing-declarations -std=gnu11 -lncurses
PROGNAME=escaperoom

all: $(PROGNAME)

$(PROGNAME): $(PROGNAME).o soundPlayer.o safeFunctions.o loginScreen.o twoFaScreen.o stageThree.o stageFour.o stageFive.o stageSix.o stageSeven.o stageEight.o stageNine.o stageTen.o chatScreen.o
	$(CC) -o $(PROGNAME) $(PROGNAME).o soundPlayer.o safeFunctions.o loginScreen.o twoFaScreen.o stageThree.o stageFour.o stageFive.o stageSix.o stageSeven.o stageEight.o stageNine.o stageTen.o chatScreen.o $(CFLAGS)

$(PROGNAME).o: main.c
	$(CC) -c main.c -o $(PROGNAME).o $(CFLAGS)

soundPlayer.o: soundPlayer.c soundPlayer.h
	$(CC) -c soundPlayer.c $(CFLAGS)

safeFunctions.o: utils/safeFunctions.c utils/safeFunctions.h
	$(CC) -c utils/safeFunctions.c $(CFLAGS)

loginScreen.o: loginScreen/loginScreen.c loginScreen/loginScreen.h
	$(CC) -c loginScreen/loginScreen.c $(CFLAGS)

twoFaScreen.o: twoFaScreen/twoFaScreen.c twoFaScreen/twoFaScreen.h
	$(CC) -c twoFaScreen/twoFaScreen.c $(CFLAGS)

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

chatScreen.o: chatScreen/chatScreen.c chatScreen/chatScreen.h
	$(CC) -c chatScreen/chatScreen.c $(CFLAGS)

clean:
	rm -f *.o
