#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

GapBuffer gbinit() {
	GapBuffer buf;
	buf.bufferSize = BUFFERBLOCKSIZE;
	buf.buffer = malloc(buf.bufferSize);
	buf.cursorLeft = buf.buffer; // no characters at the start
	buf.cursorRight = buf.buffer + buf.bufferSize - 1; // and no characters at the end
	
	return buf;
}
