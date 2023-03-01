#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char buf[512];
	strcpy(buf, argv[1]);
	printf("# Buffer Content:\n%s\n", buf);
	
	return(0);
}