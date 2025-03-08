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

void gbResize(GapBuffer *buf, uint64_t offset) {
	uint64_t s = buf->bufferSize << offset,
		 crsize = buf->bufferEnd - buf->cursorRight;
	uint8_t *cursor_new_right, *temp = realloc(buf->buffer, s);
	int64_t disparity = temp - buf->buffer;
	buf->buffer = temp;
	buf->bufferSize = s;
	buf->bufferEnd = buf->buffer + buf->bufferSize - 1;
	buf->cursorLeft += disparity;
	buf->cursorRight += disparity;
	cursor_new_right = buf->bufferEnd - crsize;
	memcpy(cursor_new_right + 1, buf->cursorRight + 1, crsize);
	buf->cursorRight = cursor_new_right;
}

void gbInsert(GapBuffer *buf, void *data, uint64_t size) {
	uint64_t gap = buf->cursorRight - buf->cursorLeft + 1,
		resize_power = 0;
	while (gap < size)
		gap += buf->bufferSize << resize_power++;
	if (resize_power > 0)
		gbResize(buf, resize_power);

	memcpy(buf->cursorLeft, data, size);
	buf->cursorLeft += size;
}

void gbDelete(GapBuffer *buf, uint64_t size) {
	if (buf->cursorLeft - buf->buffer > size) {
		buf->cursorLeft = buf->buffer;
		return;
	}
	buf->cursorLeft -= size;
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
