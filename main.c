#include "controllers.h"
#include <stdio.h>

int main () {
	FILE *dtm;
	FILE *m64;
	struct gcController dtmBuffer[1];
	struct n64Controller m64Buffer[1];
	
	dtm = fopen("input.dtm", "r");
	m64 = fopen("output.m64", "w");
	
	if (dtm == NULL) return 1;
	
	fseek(dtm, 0x100, SEEK_SET);
	fseek(m64, 0x300, SEEK_SET);
	
	while (fread(dtmBuffer, 8, 1, dtm)) {
		printf(dtmBuffer[0].buttonA ? "A" : " ");
	}
	
	return 0;
}
