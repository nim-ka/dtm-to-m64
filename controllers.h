struct gcController {
	bool buttonS: 1;
	bool buttonA: 1;
	bool buttonB: 1;
	bool buttonX: 1;
	bool buttonY: 1;
	bool dpadUp: 1;
	bool dpadDown: 1;
	bool dpadLeft: 1;
	bool dpadRight: 1;
	bool buttonL: 1;
	bool buttonR: 1;
	int reserved: 4;
	unsigned int pressureL: 8;
	unsigned int pressureR: 8;
	unsigned int joystickX: 8;
	unsigned int joystickY: 8;
	unsigned int cstickX: 8;
	unsigned int cstickY: 8;
};

struct n64Controller {
	bool buttonA: 1;
	bool buttonB: 1;
	bool buttonZ: 1;
	bool buttonS: 1;
	bool dpadUp: 1;
	bool dpadDown: 1;
	bool dpadLeft: 1;
	bool dpadRight: 1;
	int reserved: 2;
	bool buttonL: 1;
	bool buttonR: 1;
	bool cUp: 1;
	bool cDown: 1;
	bool cLeft: 1;
	bool cRight: 1;
};
