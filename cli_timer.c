#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>


void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s seconds\n", argv[0]);
        return EXIT_FAILURE;
    }

    int seconds = atoi(argv[1]);
    if (seconds <= 0) {
        fprintf(stderr, "argument cannot be negative\n");
        return EXIT_FAILURE;
    }

    struct timespec req, rem;
    req.tv_sec = seconds;
    req.tv_nsec = 0;

    int res = clock_nanosleep(CLOCK_REALTIME, 0, &req, &rem);
    if (res != 0) {
        if (res == EINTR) {
            fprintf(stderr, "interrupted by signal\n");
        } else {
            die("clock_nanosleep");
        }
        return EXIT_FAILURE;
    }

    printf("%d seconds passed\n", seconds);
    return EXIT_SUCCESS;
}
