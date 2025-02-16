#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

GapBuffer gbinit() {
	GapBuffer buf;
	buf.bufferSize = BUFFERBLOCKSIZE;
	buf.buffer = malloc(buf.bufferSize);
	buf.cursor = buf.buffer;
	buf.cursorEnd = buf.cursor; // no characters at the start...
	buf.cursorRight = buf.buffer + buf.bufferSize; // and no characters at the end
	
	return buf;
}
