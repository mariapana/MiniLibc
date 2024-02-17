// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

struct Block {
    size_t size;
    struct Block* next;
};

// Pointer to head of free memory list
static struct Block* free_list = NULL;

void *malloc(size_t size)
{
	size_t total_size = size + sizeof(struct Block);
	struct Block *block = NULL;

	if (size == 0) {
		return NULL;
	}

	// Find free block in the list
	struct Block *curr = free_list;
	struct Block *prev = NULL;

	while (curr) {
		if (curr->size >= total_size) {
			if (prev) {
				prev->next = (struct Block *)((char *)curr + total_size);
			} else {
				free_list = (struct Block *)((char *)curr + total_size);
			}

			block = curr;
			break;
		}

		prev = curr;
		curr = curr->next;
	}

	if (!block) {
		// No available block was found, allocate new block
		block = (struct Block *)mmap(NULL, total_size, PROT_READ | PROT_WRITE,
									 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		if (block == MAP_FAILED) {
			return NULL;
		}

		block->size = total_size;
	}

	return (void *)(block + 1);
}

void *calloc(size_t nmemb, size_t size)
{
	size_t total_size = nmemb * size;

	void *ptr = malloc(total_size);

	if (ptr) {
		memset(ptr, 0, total_size);
	}

	return ptr;
}

void free(void *ptr)
{
	if (!ptr) {
		return;
	}

	// Get block header
	struct Block *block = (struct Block *)ptr - 1;

	// Add block to free memory list
	block->next = free_list;

	// Release memory
	munmap(block, block->size);
}

void *realloc(void *ptr, size_t size)
{
	if (!ptr) {
		return malloc(size);
	}

	if (size == 0) {
		free(ptr);
		return NULL;
	}

	// Get old block header
	struct Block *old_block = (struct Block *)ptr - 1;
	size_t old_size = old_block->size;

	if (size <= old_size) {
		return ptr;
	}

	void *new_ptr = malloc(size);

	if (new_ptr) {
		memcpy(new_ptr, ptr, old_size - sizeof(struct Block));

		free(ptr);

		return new_ptr;
	}

	return NULL;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	if (nmemb == 0 || size == 0) {
        free(ptr);
        return NULL;
    }

    if (nmemb > (size_t)-1 / size) {
        return NULL;
    }

    return realloc(ptr, nmemb * size);
}
