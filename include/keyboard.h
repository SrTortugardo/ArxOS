#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

void keyboard_handler(void);
char getchar(void);
void gets(char *buffer, int max_len);

#endif