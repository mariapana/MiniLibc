// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	// mode -> permissions
	mode_t mode = 0;

	// Checking to see if the O_CREAT flag is set
	if (flags & O_CREAT) {
		// mode needs to be specified
		va_list vl;
		va_start(vl, flags);
		mode = va_arg(vl, mode_t);
		va_end(vl);
	}

	long fd = syscall(__NR_open, filename, flags, mode);

	if (fd < 0) {
		errno = -fd;
		return -1;
	}

	return fd;
}
