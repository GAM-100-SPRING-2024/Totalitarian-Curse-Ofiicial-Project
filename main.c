#include "cprocessing.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "logo.h"
#include "constants.h"

// MAIN
// Starts the file and runs DigiPen logo for 2 sec
// Receives resolution from constants.c
// User exits by pressing ESC

void exit() {
    if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
        CP_Engine_Terminate();
    }
}


int main(void) {
	// Creates user screen
	GetMonitorResolution();
	CP_System_SetWindowSize((int)screenWidth, (int)screenHeight);
	//

	// Prints the DigiPen Logo
	CP_Engine_SetNextGameState(init_logo, update_logo, exit_logo);

	// Exits the Game
	CP_Engine_SetPreUpdateFunction(exit);

	// Runs Program
	CP_Engine_Run();
	return 0;
}
