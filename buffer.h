#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>

typedef struct gapBuffer {
	uint64_t bufferSize;
	uint8_t *buffer;
	uint8_t *bufferEnd;
	uint8_t *cursorLeft;
	uint8_t *cursorRight;
} GapBuffer;

GapBuffer gbinit(uint64_t initial_size);

void gbInsert(GapBuffer *buf, void *data, uint64_t size);

void gbDelete(GapBuffer *buf, uint64_t size);

void gbCursorBackward(GapBuffer *buf, uint64_t distance);

void gbCursorForward(GapBuffer *buf, uint64_t distance);

#endif
