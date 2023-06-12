#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
  setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

  int myMoney = 100;
  unsigned int yourMoney = 0;
  int money = 0;

  char flag[45];
  FILE *f = fopen("flag.txt", "r");
  if (f == NULL)
  {
    printf("%s", "no flag file found!");
    exit(0);
  }
  fgets(flag, 45, f);

  while (myMoney > 0)
  {
    printf("I have %d dollars, how many of them do you want?\n", myMoney);

    scanf("%d", &money);
    getchar();

    if (money < 100)
    {
      if (myMoney > money)
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
    if (yourMoney > 1000)
    {
      char buf[100];
      printf("wow you've printed money out of thin air, you have %u!!! Is there anything you would like to say to the audience?\n", yourMoney);
      fgets(buf, 100, stdin);
      printf("wow you said: ");
      printf(buf);
      printf("\nthat's truly fascinating!\n");
      exit(0);
    }
  }
  return 0;
}
