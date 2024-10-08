CC=gcc
CFLAGS=-Werror -Wall -Wextra -Wpedantic -Wmissing-declarations -std=gnu11 -lncurses
PROGNAME=escaperoom

all: $(PROGNAME)

$(PROGNAME): $(PROGNAME).o soundPlayer.o safeFunctions.o loginScreen.o twoFaScreen.o boomboxInterface.o stageFour.o stageFive.o stageSix.o stageSeven.o stageEight.o stageTen.o chatScreen.o ai.o lineContainer.o triggerWordContainer.o pong.o math.o saveSystem.o simonSays.o wordGrid.o audioCheckScreen.o usbChecker.o
	$(CC) -o $(PROGNAME) $(PROGNAME).o soundPlayer.o safeFunctions.o loginScreen.o twoFaScreen.o boomboxInterface.o stageFour.o stageFive.o stageSix.o stageSeven.o stageEight.o stageTen.o chatScreen.o ai.o lineContainer.o triggerWordContainer.o pong.o math.o saveSystem.o simonSays.o wordGrid.o audioCheckScreen.o usbChecker.o $(CFLAGS)

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

boomboxInterface.o: boomboxInterface/boomboxInterface.c boomboxInterface/boomboxInterface.h
	$(CC) -c boomboxInterface/boomboxInterface.c $(CFLAGS)

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

stageTen.o: stageTen.c stageTen.h
	$(CC) -c stageTen.c $(CFLAGS)

chatScreen.o: chatScreen/chatScreen.c chatScreen/chatScreen.h
	$(CC) -c chatScreen/chatScreen.c $(CFLAGS)

ai.o: chatScreen/ai.c chatScreen/ai.h
	$(CC) -c chatScreen/ai.c $(CFLAGS)

lineContainer.o: chatScreen/lineContainer.c chatScreen/lineContainer.h
	$(CC) -c chatScreen/lineContainer.c $(CFLAGS)

triggerWordContainer.o: chatScreen/triggerWordContainer.c chatScreen/triggerWordContainer.h
	$(CC) -c chatScreen/triggerWordContainer.c $(CFLAGS)

pong.o: games/pong.c games/pong.h
	$(CC) -c games/pong.c $(CFLAGS)

math.o: games/math.c games/math.h
	$(CC) -c games/math.c $(CFLAGS)

saveSystem.o: utils/saveSystem.c utils/saveSystem.h
	$(CC) -c utils/saveSystem.c $(CFLAGS)

simonSays.o: games/simonSays.c games/simonSays.h
	$(CC) -c games/simonSays.c $(CFLAGS)

wordGrid.o: games/wordGrid.c games/wordGrid.h
	$(CC) -c games/wordGrid.c $(CFLAGS)

audioCheckScreen.o: audioCheck/audioCheckScreen.c audioCheck/audioCheckScreen.h
	$(CC) -c audioCheck/audioCheckScreen.c $(CFLAGS)
	
usbChecker.o: usbChecker/usbChecker.c usbChecker/usbChecker.h
	$(CC) -c usbChecker/usbChecker.c $(CFLAGS)

clean:
	rm -f *.o
