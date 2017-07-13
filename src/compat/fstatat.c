/* vim: set ts=8 sw=8 sts=8 noet tw=78:
 *
 * tup - A file-based build system
 *
 * Copyright (C) 2010-2017  Mike Shal <marfey@gmail.com>
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "dir_mutex.h"
#ifdef _WIN32
#include "open_notify.h"
#endif

int fstatat(int dirfd, const char *pathname, struct stat *buf, int flags)
{
	int rc;
#ifdef _WIN32
	char fp[PATH_MAX];
	fp[0] = '\0';
	fullpathfromid(fp, PATH_MAX, dirfd, pathname);
	open_notify_fp(ACCESS_READ, pathname, fp);
	if(flags & AT_SYMLINK_NOFOLLOW) {
		rc = lstat(fp, buf);
	} else {
		rc = stat(fp, buf);
	}
#else
	if(flags & AT_SYMLINK_NOFOLLOW) {
		rc = lstat(pathname, buf);
	} else {
		rc = stat(pathname, buf);
	}
#endif
	
	return rc;
}
