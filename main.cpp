/******************************************************************************
Welcome to GDB Online.
... bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla bla 
*******************************************************************************/

// #define SHEEPS_01

#define	USE_VERSION_DATA

#ifdef USE_VERSION_DATA
#include "version.h"
#endif

#define HERD_01

#ifdef SHEEPS_01
#include "testSheeps01.h"
#endif

#ifdef HERD_01
#include "testHerd01.h"
#endif


int main()
{
#ifdef	USE_VERSION_DATA
	printf("Version: %s\t", PROJECT_VERSION);
	printf("%s\n", PROJECT_VERSION_DESCRIPTION);
	printf("Project name: %s\n", PROJECT_NAME);
	printf("Description: %s\n", PROJECT_DESCRIPTION);
	printf("Author: %s\t", PROJECT_AUTHOR);
	printf("%s\n", PROJECT_COPYRIGHT);
	printf("Note: %s\n", PROJECT_COMMENTS);
	
#endif

#ifdef SHEEPS_01
    testSheeps01();
#endif
#ifdef HERD_01
    testHerd01();
#endif

    return 0;
}


