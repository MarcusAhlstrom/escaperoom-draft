#ifndef STAGE_THREE
#define STAGE_THREE

#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions

void stageThree();
long long timeInMilliseconds(void);
void ensureUARTConnection(int *serial_port, struct termios *tty);
void playBoomboxSound(const char *filename);
int readBoombox(char *out);

#endif
