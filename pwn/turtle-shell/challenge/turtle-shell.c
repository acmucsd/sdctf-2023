#include <stdio.h>
#include <string.h>

char *bad = "\xb0\x3b";

int main()
{
  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);
  char buf[50];
  printf("Say something to make the turtle come out of its shell\n");
  fgets(buf, 50, stdin);
  if(strstr(buf, bad) == NULL){
    int (*ret)() = (int (*)())buf;

  ret();
  }
  return 0;
}