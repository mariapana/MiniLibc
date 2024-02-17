#include <internal/syscall.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

// Source: https://github.com/kraj/musl/blob/a6c49977772a200216bd3a63b490d467663384b6/src/unistd/sleep.c
unsigned int sleep(unsigned int seconds)
{
    struct timespec tv = {.tv_sec = seconds, .tv_nsec = 0};

    if (nanosleep(&tv, &tv))
        return tv.tv_sec;

    return 0;
}

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    return syscall(__NR_nanosleep, req, rem);;
}
