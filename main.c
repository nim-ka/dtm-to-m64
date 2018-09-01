#include "controllers.h"
#include <stdio.h>
#include <math.h>

int main () {
	FILE *dtm;
	FILE *m64;
	
	struct gcController dtmBuffer[1];
	struct n64Controller m64Buffer[1];
	
	double cStickAngle;
	
	dtm = fopen("input.dtm", "r");
	m64 = fopen("output.m64", "w");
	
	if (dtm == NULL) return 1;
	
	fseek(dtm, 0x100, SEEK_SET);
	fseek(m64, 0x300, SEEK_SET);
	
	while (fread(dtmBuffer, 8, 1, dtm)) {
		cStickAngle = atan2(dtmBuffer[0].cStickY - 128, dtmBuffer[0].cStickX - 128) * (180.0 / M_PI);
		
		m64Buffer[0].buttonA = dtmBuffer[0].buttonA;
		m64Buffer[0].buttonB = dtmBuffer[0].buttonB;
		m64Buffer[0].buttonZ = dtmBuffer[0].buttonZ;
		m64Buffer[0].buttonS = dtmBuffer[0].buttonS;
		m64Buffer[0].dpadUp = dtmBuffer[0].dpadUp;
		m64Buffer[0].dpadDown = dtmBuffer[0].dpadDown;
		m64Buffer[0].dpadLeft = dtmBuffer[0].dpadLeft;
		m64Buffer[0].dpadRight = dtmBuffer[0].dpadRight;
		m64Buffer[0].reserved = 0x0;
		m64Buffer[0].buttonL = dtmBuffer[0].buttonL;
		m64Buffer[0].buttonR = dtmBuffer[0].buttonR;
		m64Buffer[0].cUp = cStickAngle >= 45 && cStickAngle <= 135;
		m64Buffer[0].cDown = cStickAngle >= 225 && cStickAngle <= 315;
		m64Buffer[0].cLeft = cStickAngle >= 135 && cStickAngle <= 225;
		m64Buffer[0].cRight = cStickAngle >= 315 || cStickAngle <= 45;
		
		fwrite(m64Buffer, 4, 1, m64);
	}
	
	return 0;
}
