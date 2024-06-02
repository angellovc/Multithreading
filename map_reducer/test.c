#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{

  char *string = "helo\0";


  int length = strlen(string);

  printf("%i\n", length);  
}