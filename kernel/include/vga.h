#ifndef VGA_H
#define VGA_H

#define VGAWIDTH 80
#define VGAHEIGHT 25

#define VGA_BLACK_FG (0000 << 4)
#define VGA_WHITE_FG (1111 << 4) 

#define VGA_BLACK_BG (0000)
#define VGA_WHITE_BG (1111) 

#include "types.h"

void VGA_clearScreen();
void VGA_printChar(char c, uint8_t attrib, uint16_t x, uint16_t y);
void VGA_printStr(const char* s, uint8_t attrib, uint16_t x, uint16_t y);
void VGA_printNum64(uint64_t num, uint8_t attrib, uint16_t x, uint16_t y);

#endif
