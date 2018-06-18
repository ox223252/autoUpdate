# autoUpdtae

Library created to manage, auto update of software from git repo.

## functions:
### rebuild:
```C
int rebuild ( const char * const execName );
```

This function should be called to execute a `make` in the main dir and relaunch the software.

### gitCheck:
```C
int gitCheck ( const char * const path, uint8_t forceReset );
```

This function should be called to check if a remote git dir changed, and pull then. The for


## Example:
### tree to work for example:
```C
.
├── a.out
├── makefile
└── src
    ├── autoUpdate
    │   ├── autoUpdate.c
    │   ├── autoUpdate.h
    │   ├── LICENSE
    │   └── README.md
    ├── freeOnExit
    │   ├── freeOnExit.c
    │   ├── freeOnExit.h
    │   ├── LICENSE
    │   └── README.md
    └── main.c
```

### example sources:
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "autoUpdate/autoUpdate.h"

int main( int argc, char ** argv )
{
	if ( ( gitCheck ( "src/freeOnExit", 1 ) == -1 ) ||
		( gitCheck ( "src/autoUpdate", 1 ) == -1 ) ||
		( gitCheck ( ".", 0 ) == -1 ) )
	{
		printf ( "rebuild\n" );
		if ( rebuild ( argv[ 0 ] ) )
		{
			printf ( "failed on restart\n" );
		}
		else
		{
			printf ( "rebuild failed\n" );
		}
	}
	printf ( "end\n" );

	return 0;
}
```

## TODO:
 -[x] updtae from git
 -[x] rebuild & restart
 -[ ] update binary from web server
