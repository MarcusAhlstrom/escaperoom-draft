#include "../includeAll.h"
#include <sys/types.h>
#include <sys/stat.h>

void check_usb_sticks(Save *save) {

  //char *check1USB = "stat /dev/disk/by-uuid/9C05-81B5 > /tmp/hello.txt 2>&1";
  char *check1USB = "/dev/disk/by-uuid/9C05-81B5";
  char *check2USB = "/dev/disk/by-uuid/1CA3-1328";
  char *check3USB = "/dev/disk/by-uuid/EE43-5823";

int hello[] = {1, 1, 1};
int ch = -1;

while(ch == -1){
  struct stat statedStruct;

  hello[0] = lstat(check1USB, &statedStruct);
  if(hello[0] == 0)
    save->usb1 = true;

  hello[1] = lstat(check2USB, &statedStruct);
  if(hello[1] == 0)
    save->usb2 = true;

  hello[2] = lstat(check3USB, &statedStruct);
  if(hello[2] == 0)
    save->usb3 = true;


  int ch = getch();
  if(ch != -1)
    printf("digit : %d\n", (int)ch);

  if(ch == (int)'q')
    break;

}


}
