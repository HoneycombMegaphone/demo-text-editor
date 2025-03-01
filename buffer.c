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

void gbCursorBackward (GapBuffer *buf, uint8_t distance) {
	if (buf -> buffer > buf -> cursorLeft - distance) {
		uint8_t temp = buf -> cursorRight - buf -> cursorLeft;
		buf -> cursorRight = buf -> cursorRight + temp;
		buf -> cursorLeft = buf -> buffer;
	} else {
		buf -> cursorLeft = buf -> cursorLeft - distance;
		buf -> cursorRight = buf -> cursorRight - distance;
	}
	memcpy(buf -> cursorLeft, buf -> cursorLeft + distance, buf -> cursorRight - buf -> cursorLeft);
	return;
}

void gbCursorForward (GapBuffer *buf, uint8_t distance) {
	if (buf -> cursorRight > buf -> buffer + buf -> bufferSize) {
		//resize buffer & perform action
	}
	buf -> cursorLeft = buf -> cursorLeft + distance;
	buf -> cursorRight = buf -> cursorRight + distance;
	memcpy(buf -> cursorLeft, buf -> cursorLeft - distance, buf -> cursorRight - buf -> cursorLeft);
	return;
}
