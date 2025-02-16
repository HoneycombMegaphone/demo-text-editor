#include <stdint.h>

#define BUFFERBLOCKSIZE 0x1000
#define BUFFERGAPSIZE 0x100

#ifndef BUFFER_H_
#define BUFFER_H_

typedef struct gapBuffer {
	uint8_t *buffer;
	uint64_t bufferSize;
	uint8_t *cursor;
	uint8_t *cursorEnd;

} GapBuffer;

GapBuffer init() {
	struct gapBuffer GapBuffer;
	uint64_t bufferSize = BUFFERBLOCKSIZE;
	uint8_t* buffer = malloc(buffer);
	uint8_t* cursor = buffer;
	uint8_t* cursorEnd = cursor + BUFFERGAPSIZE;
	
	GapBuffer.buffer = buffer;
	GapBuffer.bufferSize = bufferSize;
	GapBuffer.cursor = cursor;
	GapBuffer.cursorEnd = cursorEnd;
	return GapBuffer;
}

#endif
