#include <stdio.h>

int main () {
	FILE *dtm;
	char buffer[8];
	
	dtm = fopen("input.dtm", "r");
	
	if (dtm == NULL) return 1;
	
	fseek(dtm, 0x300, SEEK_SET);
	
	while (fread(buffer, 1, 8, dtm)) {
		printf(buffer);
	}
	
	return 0;
}
