#include "unistd.h"
#include "stdio.h"
   #include <stdlib.h>

int main(int a, char** b)
{
	if(a < 2)
		return(printf("Please tell me a number as Argument! :)\n"));
	for(int i = 0; i < atoi(b[1]); i++)
		printf(":)\n");
}
