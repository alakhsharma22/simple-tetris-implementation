#ifndef TERMINAL_H
#define TERMINAL_H

#include <unistd.h>

void enableRawMode();
void disableRawMode();

bool kbhit();

#endif
