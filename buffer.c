#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"


GapBuffer gbinit() {
	GapBuffer buf;
	buf.bufferSize = BUFFERBLOCKSIZE;
	buf.buffer = malloc(buf.bufferSize);
	buf.bufferEnd = buf.buffer + buf.bufferSize - 1;
	buf.cursorLeft = buf.buffer; // no characters at the start
	buf.cursorRight = buf.bufferEnd; // and no characters at the end

	return buf;
}

void gbResize(GapBuffer *buf, uint64_t remainder) {
	if (buf->cursorLeft + remainder > buf->cursorRight) {
		uint64_t gap = buf->cursorRight - buf->cursorLeft;
		uint8_t offset = remainder/(buf->bufferSize - gap);
		uint8_t *temp = realloc(buf->buffer, buf->bufferSize << offset);
		buf->buffer = temp;
		buf->bufferSize = buf->bufferSize << offset;
		buf->bufferEnd = buf->buffer + buf->bufferSize - 1;
		buf->cursorRight = buf->bufferEnd - remainder;
		buf->cursorLeft = buf->cursorRight - gap;
	}
}

void gbCursorBackward(GapBuffer *buf, uint64_t distance) {
	uint64_t d2 = distance;

	if (buf->cursorLeft - d2 < buf->buffer)
		d2 = buf->cursorLeft - buf->buffer;

	if (d2 == 0)
		return;

	buf->cursorLeft -= d2;
	buf->cursorRight -= d2;
	
	memcpy(buf->cursorRight + 1, buf->cursorLeft, d2);
}

void gbCursorForward(GapBuffer *buf, uint64_t distance) {
	uint64_t d2 = distance;

	if (buf->cursorRight + d2 > buf->bufferEnd)
		d2 = buf->bufferEnd - buf->cursorRight;

	if (d2 == 0)
		return;

	memcpy(buf->cursorLeft, buf->cursorRight + 1, d2);

	buf->cursorLeft += d2;
	buf->cursorRight += d2;
}
