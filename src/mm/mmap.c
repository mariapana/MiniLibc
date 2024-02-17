// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

// Source: musl
#define UNIT 8192ULL
#define INT64_MAX (0x7fffffffffffffff)
#define OFF_MASK ((-0x2000ULL << (8*sizeof(long)-1)) | (UNIT-1))

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	if (offset & OFF_MASK) {
		errno = EINVAL;
		return MAP_FAILED;
	}

	if (length >= INT64_MAX) {
		errno = ENOMEM;
		return MAP_FAILED;
	}

	long r = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);

	if (r < 0) {
		errno = -r;
		return MAP_FAILED;
	}

	return (void *)r;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	if (new_size >= INT64_MAX) {
		errno = ENOMEM;
		return MAP_FAILED;
	}

	long r = syscall(__NR_mremap, old_address, old_size, new_size, flags);

	if (r < 0) {
		errno = -r;
	}

	return (void *)r;
}

int munmap(void *addr, size_t length)
{
	int r = syscall(__NR_munmap, addr, length);

	if (r < 0) {
		errno = -r;
		return -1;
	}

	return 0;
}
