#ifndef VGA_H
#define VGA_H

#define VGAWIDTH 80
#define VGAHEIGHT 25

#define VGA_BLACK_FG (0b0000 << 4)
#define VGA_BLUE_FG (0b0001 << 4)
#define VGA_GREEN_FG (0b0010 << 4)
#define VGA_RED_FG (0b0100 << 4)
#define VGA_WHITE_FG (0b1111 << 4) 

#define VGA_BLACK_BG (0b0000)
#define VGA_BLUE_BG (0b0001)
#define VGA_GREEN_BG (0b0010)
#define VGA_RED_BG (0b0100)
#define VGA_WHITE_BG (0b1111) 

#include "types.h"

void VGA_clearScreen();
void VGA_printChar(char c, uint8_t attrib, uint16_t x, uint16_t y);
void VGA_printStr(const char* s, uint8_t attrib, uint16_t x, uint16_t y);
void VGA_printNum64(uint64_t num, uint8_t attrib, uint16_t x, uint16_t y);

#endif
