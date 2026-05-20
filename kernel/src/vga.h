#ifndef VGA_H
#define VGA_H

#define VGAWIDTH 80
#define VGAHEIGHT 25

#include "types.h"

void VGA_clearScreen();
void VGA_printChar(char c, byte attrib, u16 x, u16 y);
void VGA_printStr(const char* s, byte attrib, u16 x, u16 y);

#endif
