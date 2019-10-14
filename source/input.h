#ifndef input_h
#define input_h

#include <stdio.h>
#include <sys/select.h>
#include <termio.h>

static struct termio savemodes;
static int havemodes = 0;

char last_input = 0;

void setupEnterAvoidance() {
    struct termio modmodes;
    if (ioctl(fileno(stdin), TCGETA, &savemodes) < 0) {
        return;
    }
    havemodes = 1;
    modmodes = savemodes;
    modmodes.c_lflag &= ~ICANON;
    modmodes.c_cc[VMIN] = 1;
    modmodes.c_cc[VTIME] = 0;
    ioctl(fileno(stdin), TCSETAW, &modmodes);
}

char readInput() {
    fd_set rfds;
    struct timeval tv;
    int retval;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 250000;
    retval = select(1, &rfds, NULL, NULL, &tv);
    if (retval > 0) last_input = getchar();
    return last_input;
}

#endif