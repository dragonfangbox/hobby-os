#ifndef VGA_H
#define VGA_H

#define VGAWIDTH 80
#define VGAHEIGHT 25

#include "types.h"

void VGA_clearScreen();
void VGA_printChar(char c, uint8_t attrib, uint16_t x, uint16_t y);
void VGA_printStr(const char* s, uint8_t attrib, uint16_t x, uint16_t y);

#endif
