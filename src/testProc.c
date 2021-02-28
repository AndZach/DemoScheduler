#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

//testProcess
int main(int argc, char *argv[])
{
	
	printf ("Hello World. Process %s, duration %s, priority \n					%s. \n\n", argv[0], argv[1], argv[2]);
	double r = (double) rand () / ((double) RAND_MAX);
		for (int i=1; i<r*100000000; i++);
		
	
	return 0;
}

