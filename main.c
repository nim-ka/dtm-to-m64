#include "controllers.h"
#include <stdio.h>
#include <math.h>

int main () {
	FILE *dtm;
	FILE *m64;
	
	struct gcController dtmBuffer[1];
	struct n64Controller m64Buffer;
	
	double cStickAngle;
	
	dtm = fopen("input.dtm", "r");
	m64 = fopen("output.m64", "w");
	
	if (dtm == NULL) return 1;
	
	fseek(dtm, 0x100, SEEK_SET);
	fseek(m64, 0x300, SEEK_SET);
	
	while (fread(dtmBuffer, 8, 1, dtm)) {
		cStickAngle = atan2(dtmBuffer[0].cStickY - 128, dtmBuffer[0].cStickX - 128) * (180.0 / M_PI);
		
		m64Buffer = {
			.buttonA: dtmBuffer[0].buttonA,
			.buttonB: dtmBuffer[0].buttonB,
			.buttonZ: dtmBuffer[0].buttonZ,
			.buttonS: dtmBuffer[0].buttonS,
			.dpadUp: dtmBuffer[0].dpadUp,
			.dpadDown: dtmBuffer[0].dpadDown,
			.dpadLeft: dtmBuffer[0].dpadLeft,
			.dpadRight: dtmBuffer[0].dpadRight,
			.reserved: 0x0,
			.buttonL: dtmBuffer[0].buttonL,
			.buttonR: dtmBuffer[0].buttonR,
			.cUp: cStickAngle >= 45 && cStickAngle <= 135,
			.cDown: cStickAngle >= 225 && cStickAngle <= 315,
			.cLeft: cStickAngle >= 135 && cStickAngle <= 225,
			.cRight: cStickAngle >= 315 || cStickAngle <= 45
		};
		
		fwrite({m64Buffer}, 4, 1, m64);
	}
	
	return 0;
}
