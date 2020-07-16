#include <stdio.h>
#include <signal.h>

void (*old_fun)(int);

void sigint_handler(int signo)
{
   printf("Ctrl-C 키를 눌루셨죠!!\n");
   printf("또 누르시면 종료됩니다.\n");
   signal(SIGINT, old_fun);   // 또는 signal( SIGINT, SIG_DFL);
}

int main(void)
{
   old_fun = signal(SIGINT, sigint_handler);
   while(1)
   {
      printf("while 돌아가는중\n");
      sleep(1);
   }
}