/* vim: set ts=8 sw=8 sts=8 noet tw=78:
 *
 * tup - A file-based build system
 *
 * Copyright (C) 2011-2017  Mike Shal <marfey@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "dir_mutex.h"

int renameat(int olddirfd, const char *oldpath, int newdirfd, const char *newpath)
{
	int rc;

	if(olddirfd != newdirfd) {
		fprintf(stderr, "tup compat renameat error: olddirfd=%i but newdirfd=%i\n", olddirfd, newdirfd);
		return -1;
	}
	char oldpathp[1024];
	char newpathp[1024];
	strcpy(oldpathp, oldpath);
	strcpy(newpathp, newpath);

	//;
#ifdef _WIN32
   extern int movefile(const char *, const char*);
   rc = movefile(oldpathp, newpathp);
#else
dir_mutex_lock(olddirfd)
	rc = rename(oldpathp, newpathp);
	dir_mutex_unlock();
#endif
	return rc;
}
