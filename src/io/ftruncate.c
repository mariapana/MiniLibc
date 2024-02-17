// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int ftruncate(int fd, off_t length)
{
	int r = syscall(__NR_ftruncate, fd, length);

	if (r < 0) {
		errno = -r;
		return -1;
	}

	return r;
}
