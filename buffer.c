#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"


GapBuffer gbinit() {
	GapBuffer buf;
	buf.bufferSize = BUFFERBLOCKSIZE;
	buf.buffer = malloc(buf.bufferSize);
	buf.cursorLeft = buf.buffer; // no characters at the start
	buf.cursorRight = buf.buffer + buf.bufferSize - 1; // and no characters at the end
	
	return buf;
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
	uint8_t *buf_end = buf->buffer + buf->bufferSize - 1;
	uint64_t d2 = distance;

	if (buf->cursorRight + d2 > buf_end)
		d2 = buf_end - buf->cursorRight;

	if (d2 == 0)
		return;

	memcpy(buf->cursorLeft, buf->cursorRight + 1, d2);

	buf->cursorLeft += d2;
	buf->cursorRight += d2;
}
