#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char buf[1024];
	strcpy(buf, argv[1]);
	// Per posizione approssimata stack
	printf("# Buffer Address:\n%p\n", &buf);
	printf("# Buffer Content:\n%s\n", buf);
	
	return(0);
}