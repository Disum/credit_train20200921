#include <stdio.h>
#include "solve.h"
#define ERROR (-1)

int main(int argc, char **argv)
{
	int result;

	if( argc!=6 )
	{
		fprintf(stderr, "Usage: %s a b s t x\n", argv[0]);
		return ERROR;
	}

	result = sovle(argv[1], argv[2], argv[3], argv[4], argv[5]);
	if( result<0 )
	{
		switch( result )
		{
			case ERR_OPEN:
				fprintf(stderr, "Can not open file.\n");
				break;
			case ERR_READ:
				fprintf(stderr, "Can not read element.\n");
				break;
			case ERR_CMP:
				fprintf(stderr, "Incorrect comparsion string: %s\n", argv[5]);
				break;
			default:
				fprintf(stderr, "Unknown error with code %d\n", result);
		}
		return ERROR;
	}
	printf("Function returned: %d\n", result);

	return 0;
}
