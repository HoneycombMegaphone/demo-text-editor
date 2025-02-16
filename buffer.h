#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>

#define BUFFERBLOCKSIZE 0x1000

typedef struct gapBuffer {
	uint8_t *buffer;
	uint64_t bufferSize;
	uint8_t *cursor;
	uint8_t *cursorEnd;
	uint8_t *cursorRight;
} GapBuffer;

GapBuffer gbinit();

#endif
