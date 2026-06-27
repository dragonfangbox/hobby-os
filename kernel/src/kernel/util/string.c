#include "string.h"

void *memset(void *s, int c, uint32_t count)
{
	char *xs = s;

	while (count--)
		*xs++ = c;
	return s;
}
