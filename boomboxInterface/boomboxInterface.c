#include "../includeAll.h"

#include <sys/time.h>

void stageThree(){
  // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
  int serial_port;

  // Create new termios struct, we call it 'tty' for convention
  struct termios tty;

  // Read in existing settings, and handle any error
  while(tcgetattr(serial_port, &tty) != 0) {
    serial_port = open("/dev/ttyUSB0", O_RDWR);
    //printf("\n", errno, strerror(errno));
  }

  serial_port = open("/dev/ttyUSB0", O_RDWR);
  
  //ensureUARTConnection(&serial_port, &tty);

  /*// Save tty settings, also checking for error
  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
    printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
  }*/

  // Write to serial port
  //unsigned char msg[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
  //const char hellogg[] = ":/simon3.wav\n";
  //unsigned char hellogg[] = { ':', '/', 's', 'i', 'm', 'o', 'n', '1', '.', 'w', 'a', 'v', '\n', '\0' };
  int writes = 0;
  long long lastTime = timeInMilliseconds();
  
  while (writes < 3) {
    //ensureUARTConnection(&serial_port, &tty);
    if ((timeInMilliseconds()-lastTime) > 5000) {
      printf("Write\n");
      //write(serial_port, hellogg, sizeof(hellogg));
      playBoomboxSound(":/simon3.wav\n");
      writes++;
      lastTime = timeInMilliseconds();
    }
    
  }
  usleep(1000000);
  playBoomboxSound(":/doom.wav\n");
  fprintf(stderr, "read\n");
  usleep(1000000);
  char read_buf[256];
  printf("read\n");
  readBoombox(read_buf);
  while (strcmp(read_buf, "w") != 0) {
    fprintf(stderr, "read");
    readBoombox(read_buf);
  }
  usleep(1000000);
  playBoomboxSound("-\n");
  usleep(1000000);
  playBoomboxSound(":/whoosh.wav\n");
  usleep(1000000);
  playBoomboxSound(":/doommm.wav\n");
  usleep(100000000);
  printf("WHATT\n");
  /*
  for(int i = 0; i < 10; i++){
    usleep(1100000);
    printf("Write\n");
    write(serial_port, hellogg, sizeof(hellogg));
  }*/
  // Allocate memory for read buffer, set size according to your needs
  /*char read_buf [256];
  for(int i = 0; i < 1; i++){
    // Normally you wouldn't do this memset() call, but since we will just receive
    // ASCII data for this example, we'll set everything to 0 so we can
    // call printf() easily.
    memset(&read_buf, '\0', sizeof(read_buf));
    //for(int i = 0; i < 20; i++){
    // Read bytes. The behaviour of read() (e.g. does it block?,
    // how long does it block for?) depends on the configuration
    // settings above, specifically VMIN and VTIME
    int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

    // n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
    if (num_bytes < 0) {
      printf("Error reading: %s", strerror(errno));
      exit(EXIT_FAILURE);
    }

    // Here we assume we received ASCII data, but you might be sending raw bytes (in that case, don't try and
    // print it to the screen like this!)
    printf("Read %i bytes. Received message: %s", num_bytes, read_buf);
  }
  close(serial_port);*/
  stageFour();
}

void ensureUARTConnection(int *serial_port, struct termios *tty) {
  if (tcgetattr(*serial_port, tty) != 0) {
    printf("Speaker USB connection severed. Please give me my voice back.\n");
    // Keep trying to open USB until it works.
    while(tcgetattr(*serial_port, tty) != 0) {
      close(*serial_port);
      *serial_port = open("/dev/ttyUSB0", O_RDWR);
      //printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }
    tty->c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty->c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty->c_cflag &= ~CSIZE; // Clear all bits that set the data size
    tty->c_cflag |= CS8; // 8 bits per byte (most common)
    tty->c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty->c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty->c_lflag &= ~ICANON;
    tty->c_lflag &= ~ECHO; // Disable echo
    tty->c_lflag &= ~ECHOE; // Disable erasure
    tty->c_lflag &= ~ECHONL; // Disable new-line echo
    tty->c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty->c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty->c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    tty->c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty->c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

    tty->c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty->c_cc[VMIN] = 0;

    // Set in/out baud rate to be 9600
    cfsetispeed(tty, B9600);
    cfsetospeed(tty, B9600);
    // And this sets the settings correctly (wait until it works?)
    while (tcsetattr(*serial_port, TCSANOW, tty) != 0) {
      close(*serial_port);
      *serial_port = open("/dev/ttyUSB0", O_RDWR);
      //printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
  }
}

void playBoomboxSound(const char *filename) {
  // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
  int serial_port;
  // Create new termios struct, we call it 'tty' for convention
  struct termios tty;
  
  serial_port = open("/dev/ttyUSB0", O_RDWR);
  ensureUARTConnection(&serial_port, &tty);
  
  write(serial_port, filename, strlen(filename));
  usleep(100000);
  
  close(serial_port);
}

int readBoombox(char *out) {
  char read_buf[256];
  // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
  int serial_port;
  // Create new termios struct, we call it 'tty' for convention
  struct termios tty;
  
  serial_port = open("/dev/ttyUSB0", O_RDWR);
  ensureUARTConnection(&serial_port, &tty);
  
  for(int i = 0; i < 1; i++){
    // Normally you wouldn't do this memset() call, but since we will just receive
    // ASCII data for this example, we'll set everything to 0 so we can
    // call printf() easily.
    memset(&read_buf, '\0', sizeof(read_buf));
    //for(int i = 0; i < 20; i++){
    // Read bytes. The behaviour of read() (e.g. does it block?,
    // how long does it block for?) depends on the configuration
    // settings above, specifically VMIN and VTIME
    int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

    // n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
    if (num_bytes < 0) {
      printf("Error reading: %s", strerror(errno));
      return num_bytes;
    }

    // Here we assume we received ASCII data, but you might be sending raw bytes (in that case, don't try and
    // print it to the screen like this!)
    fprintf(stderr,"Read %i bytes. Received message: %s\n", num_bytes, read_buf);
  }
  out = strcpy(out, read_buf);
  close(serial_port);
  return 0;
}

long long timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}
