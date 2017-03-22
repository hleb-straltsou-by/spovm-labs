/*
  Named Pipe Demo by Andrei Borovsky <borovsky@tochka.ru>.
  This code is freeware.
*/
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/named_pip"

using namespace std;

int main(int argc, char * argv[])
{
  cout << "IN X2" << endl;
  FILE * f;
  f = fopen(FIFO_NAME, "w");
  if (f == NULL)
  {
    printf("Не удалось открыть файл\n");
    return -1;
  }
  fputs("hello!", f);
  fflush(f);
  fclose(f);

  return 0;
}
