/*
  Named Pipe Demo by Andrei Borovsky <borovsky@tochka.ru>.
  This code is freeware.
*/
#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;

#define FIFO_NAME "/tmp/named_pip"

int main ()
{
  cout << "IN X3" << endl;
  FILE * f;
  char ch;
  f = fopen(FIFO_NAME, "r");
  char readingBuffer[1024];
  fgets(readingBuffer, 7, f);
  cout << "READ FROM CLIENT! : " << readingBuffer << endl;
  fclose(f);

  return 0;
}

