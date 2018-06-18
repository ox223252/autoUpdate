#ifndef __AUTOUPDATE_H__
#define __AUTOUPDATE_H__

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

////////////////////////////////////////////////////////////////////////////////
/// \file autoUpdate.h
/// \brief library to manage program update/upgrade
/// \author ox223252
/// \date 2018-06
/// \copyright GPLv2
/// \version 0.2
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// \fn int rebuild ( const char * const execName );
/// \param [in] execName : name of binary file
/// \brief this function will execute make, kill the program process, and 
///     restart it
/// \return X: failure occured, see errno for more details
////////////////////////////////////////////////////////////////////////////////
int rebuild ( const char * const execName );

////////////////////////////////////////////////////////////////////////////////
/// \fn int gitCheck ( const char * const path, unsigned char forceRese );
/// \param [in] path : path to the git folder what should be updated
/// \param [in] forceRese : set this flag to force to reset git repo to the head
///     of remote branch
/// \brief this function will execute a git pull for the folder path
/// \return -1: the folder was updated
///         0: no update was needed
///         X: failure occured, see errno for more details
////////////////////////////////////////////////////////////////////////////////
int gitCheck ( const char * const path, unsigned char forceReset );

#endif