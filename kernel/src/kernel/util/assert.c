#include "assert.h"

#include "panic.h"

#ifndef NDEBUG
void assert(bool cond, char* msg) {
	if (!cond) {
		kpanic(msg);
	}
}
#else
void assert(bool cond, char* msg) {
	return;
}
#endif
