#include "user.h"

int
main(int argc, char **argv)
{
	int i;

	if(argc < 2){
		fprintf(2, "usage: kill pid...\n");
		exit();
	}
	for(i=1; i<argc; i++)
		kill(atoi(argv[i]));
	exit();
}
