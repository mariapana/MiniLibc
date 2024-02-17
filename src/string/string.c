// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	char *str;

	for (str = destination; *source != '\0'; str++, source++)
		*str = *source;

	*str = *source;

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	char *str;

	for (str = destination; *source != '\0' && len--; str++, source++)
		*str = *source;

	*str = *source;

	return destination;
}

char *strcat(char *destination, const char *source)
{
	char *str = destination;

	while (*str != '\0') {
		str++;
	}

	while (*source != '\0') {
		*str = *source;
		str++, source++;
	}

	*str = *source;

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	char *str = destination;

	while (*str != '\0') {
		str++;
	}

	while (*source != '\0' && len--) {
		*str = *source;
		str++, source++;
	}

	*str = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2) {
		str1++, str2++;
	}

	if (*str1 == *str2) {
		return 0;
	} else if (*str1 > *str2) {
		return 1;
	}

	return -1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	while (*str1 && *str2 && *str1 == *str2 && len--) {
		str1++, str2++;
	}

	if (*str1 == *str2 || len == 0) {
		return 0;
	} else if (*str1 > *str2) {
		return 1;
	}

	return -1;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	while (*str != '\0' && *str != c) {
		str++;
	}

	if (*str == c)
		return (char *)str;

	return NULL;
}

char *strrchr(const char *str, int c)
{
	const char *last_occurrence = NULL;

    while (*str != '\0') {
        if (*str == c) {
            last_occurrence = str;
        }
        str++;
    }

    return (char *)last_occurrence;
}

char *strstr(const char *haystack, const char *needle)
{
	// Corner case: Empty needle is always found at the beginning
	if (*needle == '\0') {
		return (char *)haystack;
	}

	while (*haystack != '\0') {
		const char *h = haystack;
		const char *n = needle;

        while (*h == *n && *h != '\0' && *n != '\0') {
			h++, n++;
		}

		// Substring found
		if (*n == '\0') {
			return (char *)haystack;
		}

		haystack++;
    }

	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	// Corner case: Empty needle is always found at the end
	if (*needle == '\0') {
		return (char *)haystack + strlen(haystack);
	}

	const char *last_occurrence = NULL;

	while (*haystack != '\0') {
		const char *h = haystack;
		const char *n = needle;

        while (*h == *n && *h != '\0' && *n != '\0') {
			h++, n++;
		}

		// Substring found
		if (*n == '\0') {
			last_occurrence = haystack;
		}

		haystack++;
    }
	return (char *)last_occurrence;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	char *d = (char *)destination;
	const char *s = (const char *)source;

	while (num--) {
		*d++ = *s++;
	}

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	char *d = (char *)destination;
	const char *s = (const char *)source;

	// Source and destination are the same => no need to move
    if (d == s) {
        return d;
    }

    if (s < d && s + num > d) {
        // Overlapping memory => copy from end to beginning
        d += num;
        s += num;

        while (num--) {
            *--d = *--s;
        }
    } else {
        // Non-overlapping memory => copy from beginning to end
        while (num--) {
            *d++ = *s++;
        }
    }

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char *p1 = (const unsigned char *)ptr1;
	const unsigned char *p2 = (const unsigned char *)ptr2;

	while (num--) {
		if (*p1 < *p2) {
			return -1;
		} else if (*p1 > *p2) {
			return 1;
		}

		p1++, p2++;
	}

	return 0;
}

void *memset(void *source, int value, size_t num)
{
	unsigned char *s = source;
	unsigned char v = value;

	while (num--) {
		*s++ = v;
	}

	return source;
}
