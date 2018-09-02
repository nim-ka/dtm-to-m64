struct gcController {
	unsigned int cStickY: 8;
	unsigned int cStickX: 8;
	unsigned int joystickY: 8;
	unsigned int joystickX: 8;
	unsigned int pressureR: 8;
	unsigned int pressureL: 8;
	int reserved: 4;
	int buttonR: 1;
	int buttonL: 1;
	int dpadRight: 1;
	int dpadLeft: 1;
	int dpadDown: 1;
	int dpadUp: 1;
	int buttonZ: 1;
	int buttonY: 1;
	int buttonX: 1;
	int buttonB: 1;
	int buttonA: 1;
	int buttonS: 1;
};

struct n64Controller {
	int joystickY: 8; // signed
	int joystickX: 8; // signed
	int reserved: 2;
	int buttonL: 1;
	int buttonR: 1;
	int cUp: 1;
	int cDown: 1;
	int cLeft: 1;
	int cRight: 1;
	int buttonA: 1;
	int buttonB: 1;
	int buttonZ: 1;
	int buttonS: 1;
	int dpadUp: 1;
	int dpadDown: 1;
	int dpadLeft: 1;
	int dpadRight: 1;
};
