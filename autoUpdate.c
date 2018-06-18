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
#include "../freeOnExit/freeOnExit.h"

int rebuild ( const char * const execName )
{
	char * cmd = NULL;
	FILE * fd = 0;

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

	fd = popen ( cmd, "re" );
	if ( !fd )
	{
		free ( cmd );
		cmd = NULL;
		return ( 0 );
	}
	pclose ( fd );

	sleep ( 1 );

	sprintf ( cmd, "%s &", execName );

	if ( fork() )
	{ // restart new processus in the same term
		execl ( execName, execName, NULL );
	}
	else
	{ // free memory and exit clearly
		sleep ( 1 );
		free ( cmd );
		cmd = NULL;
		exit ( 0 );
	}

	return ( __LINE__ );
}

int gitCheck ( const char * const path, uint8_t forceReset )
{
	char * cmd = NULL;
	struct stat s;
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

	if ( forceReset )
	{ // force to reset to the head of git remote head
		sprintf ( cmd, "cd %s && "
			"git reset --hard HEAD 2>/dev/null 1>/dev/null && "
			"git pull", 
			path );
	}
	else
	{ // keep modification from remote head
		sprintf ( cmd, "cd %s && "
			"git pull", 
			path );	
	}

	fd = popen ( cmd, "re" );
	if ( !fd )
	{
		return ( __LINE__ );
	}

	while ( fscanf ( fd, "%256[^\n]", cmd ) > 0 )
	{
		if ( !strcmp ( cmd, "Already up-to-date." ) )
		{
			free ( cmd );
			cmd = NULL;
			pclose ( fd );
			return  ( 0 );
		}
	}

	free ( cmd );
	cmd = NULL;
	pclose ( fd );
	return ( -1 );
}