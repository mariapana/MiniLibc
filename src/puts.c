// SPDX-License-Identifier: BSD-3-Clause
#include <unistd.h>

void puts(const char *str)
{
	while (*str != '\0') {
		write(1, str, 1);
		str++;
	}

	write(1, "\n", 1);
}
