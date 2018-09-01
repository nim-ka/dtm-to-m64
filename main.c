#include "controllers.h"
#include <stdio.h>

int main () {
	FILE *dtm;
	FILE *m64;
	struct gcController dtmBuffer;
	struct n64Controller m64Buffer;
	
	dtm = fopen("input.dtm", "r");
	m64 = fopen("output.m64", "w");
	
	if (dtm == NULL) return 1;
	
	fseek(dtm, 0x100, SEEK_SET);
	fseek(m64, 0x300, SEEK_SET);
	
	while (fread(dtmBuffer, 8, 1, dtm)) {
		printf(dtmBuffer.buttonA ? "A" : " ");
	}
	
	return 0;
}
