#include <stdio.h>
#include <stdlib.h>

void C_Application_Firewall(char *in_buf)
{
	// Dummy Function
	for (char c = *in_buf++; c != '\x00'; c = *in_buf++)
	{
		if (c == 'A')
		{
			printf("You have been blocked!\n");
			exit(-1);
		}
	}
}

void CAFtest(void)
{
	char buf[256] = {0};
	printf("\nC Application Firewall Test - please try a payload:\n");
	gets(buf); // Vulnerable
	C_Application_Firewall(buf);
	printf(buf); // Vulnerable (buf not formatted)
}

int main(int argc, char *argv[])
{
	while (1)
	{
		CAFtest();
	}
}
