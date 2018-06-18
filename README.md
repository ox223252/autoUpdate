# autoUpdtae

Library created to manage, auto update of software from git repo.

## tree to work for example:
```C
.
├── a.out
├── makefile
├── README.md
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


## TODO:
 -[x] updtae from git
 -[x] rebuild & restart
 -[ ] update binary from web server

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int rebuild ( const char * const execName );
int gitCheck ( const char * const path );

int main( int argc, char ** argv )
{
	if ( ( gitCheck ( "src/freeOnExit" ) == -1 ) ||
		( gitCheck ( "src/autoUpdate" ) == -1 ) )
	{
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