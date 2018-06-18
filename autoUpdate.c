////////////////////////////////////////////////////////////////////////////////
/// \copiright ox223252, 2018
///
/// This program is free software: you can redistribute it and/or modify it
///     under the terms of the GNU General Public License published by the Free
///     Software Foundation, either version 2 of the License, or (at your
///     option) any later version.
///
/// This program is distributed in the hope that it will be useful, but WITHOUT
///     ANY WARRANTY; without even the implied of MERCHANTABILITY or FITNESS FOR
///     A PARTICULAR PURPOSE. See the GNU General Public License for more
///     details.
///
/// You should have received a copy of the GNU General Public License along with
///     this program. If not, see <http://www.gnu.org/licenses/>
////////////////////////////////////////////////////////////////////////////////

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "autoUpdate.h"

int rebuild ( const char * const execName )
{
	char * cmd = NULL;
	pid_t pid = 0;
	if ( !execName )
	{
		errno = EINVAL;
		return ( __LINE__ );
	}

	printf ( "Git update : \n" );

	cmd = malloc ( strlen ( execName ) + 30 );
	if ( !cmd )
	{
		return ( __LINE__ );
	}
	sprintf ( cmd, "make" );
	system ( cmd );

	sleep ( 1 );

	sprintf ( cmd, "kill %d && %s", getpid ( ), execName );
	system ( cmd );

	return ( __LINE__ );
}

int gitCheck ( const char * const path )
{
	int link[ 2 ];
	char * cmd = NULL;
	struct stat s;
	pid_t pid = 0;
	FILE * fd = NULL;

	if ( !path )
	{
		errno = EINVAL;
		return ( __LINE__ );
	}

	// check if path is a valid path
	if ( stat ( path, &s ) == -1 )
	{ // no such file or directory
		return ( __LINE__ );
	}
	else if ( S_ISDIR ( s.st_mode ) )
	{ // it's a dir
	}
	else
	{ // it's not dir
		errno = ENOTDIR;
		return ( __LINE__ );
	}

	cmd = malloc ( strlen ( path ) + 256 );
	if ( !cmd )
	{
		return ( __LINE__ );
	}

	sprintf ( cmd, "cd %s && "
		"git reset --hard HEAD 2>/dev/null 1>/dev/null && "
		"git pull", 
		path );

	fd = popen ( cmd, "re" );
	if ( !fd )
	{
		return ( 0 );
	}

	while ( fscanf ( fd, "%256[^\n]", cmd ) > 0 )
	{
		if ( !strcmp ( cmd, "Already up-to-date." ) )
		{
			free ( cmd );
			cmd = NULL;
			return  ( 0 );
		}
	}

	free ( cmd );
	cmd = NULL;
	pclose ( fd );
	return ( -1 );
}