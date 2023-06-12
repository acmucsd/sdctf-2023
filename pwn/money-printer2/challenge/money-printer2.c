#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
   setbuf(stderr, NULL);

  unsigned int myMoney = 2147483647;
  unsigned int yourMoney = 1000;
  int money = 0;
  puts("You may have gotten me last time, but I have so much more money now that you'll never be richer than me!\n");
    
  while (myMoney > 0)
  {
    printf("I have %u dollars, how many of them do you want?\n", myMoney);

    scanf("%d", &money);
    getchar();

    if (money < 100)
    {
      if ((long long)myMoney > money)
      {
        printf("you can have %d dollars!\n", money);
        myMoney = myMoney - money;
        yourMoney = yourMoney + money;
      }
      else
      {
        printf("I don't have that much!\n");
      }
    }
    else
    {
      printf("you clearly can't get that much!\n");
    }
    if (yourMoney > 2147483647)
    {
      char buf[100];
      printf("wow you've printed money out of thin air, you have %u!!! Is there anything you would like to say to the audience?\n", yourMoney);
      fgets(buf, 100, stdin);
      printf("wow you said: ");
      printf(buf);
      break;
    }
  }
  return 0;
}

void func(){
  system('/bin/sh');
}