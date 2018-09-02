#include "controllers.h"
#include <stdio.h>
#include <math.h>

int main () {
	// Files
	FILE *dtm;
	FILE *template;
	FILE *m64;
	
	// File buffers
	struct gcController dtmBuffer[1];
	char templateBuffer[0x400];
	struct n64Controller m64Buffer[1];
	
	// Frame and VI counts have to be written into the m64
	unsigned char frames[4];
	unsigned char vis[4];
	
	// For turning C stick X and Y on GC controller into C buttons on N64 controller
	double cStickAngle;
	
	// Initialize files
	printf("Initializing files...\n");
	
	dtm = fopen("input.dtm", "r");
	template = fopen("template.m64", "r");
	m64 = fopen("output.m64", "w");
	
	if (dtm == NULL || template == NULL || m64 == NULL) return 1;
	
	// Copy template to m64
	fread(templateBuffer, 1, 0x400, template);
	fwrite(templateBuffer, 1, 0x400, m64);
	
	// Read frames and VIs from dtm
	printf("Writing M64 header...\n");
	
	fseek(dtm, 0x00D, SEEK_SET);
	fread(frames, 1, 4, dtm);
	
	fseek(dtm, 0x015, SEEK_SET);
	fread(vis, 1, 4, dtm);
	
	// Write frames and VIs to m64
	fseek(m64, 0x00C, SEEK_SET);
	fwrite(frames, 1, 4, m64);
	
	fseek(m64, 0x018, SEEK_SET);
	fwrite(vis, 1, 4, m64);
	
	// Put dtm pointer at start of controller data
	fseek(dtm, 0x100, SEEK_SET);
	
	// Put m64 pointer at start of controller data
	fseek(m64, 0x400, SEEK_SET);
	
	printf("Writing controller data...\n");
	
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
		m64Buffer[0].joystickX = dtmBuffer[0].joystickX;
		m64Buffer[0].joystickY = dtmBuffer[0].joystickY;
		
		fwrite(m64Buffer, 4, 1, m64);
	}
	
	printf("Closing files...\n");
	
	fclose(dtm);
	fclose(template);
	fclose(m64);
	
	printf("Done!\n");
	
	return 0;
}
