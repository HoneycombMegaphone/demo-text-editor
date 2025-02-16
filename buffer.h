#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>

#define BUFFERBLOCKSIZE 0x1000

typedef struct gapBuffer {
	uint64_t bufferSize;
	uint8_t *buffer;
	uint8_t *cursorLeft;
	uint8_t *cursorRight;
} GapBuffer;

GapBuffer gbinit();

#endif
