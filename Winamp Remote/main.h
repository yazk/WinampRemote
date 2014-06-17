#define _WIN32_WINNT 0x0501
#define WIN32_MEAN_AND_LEAN

#include <windows.h>
#include <winuser.h>

//From Winamp SDK
#include "gen.h"
#include "wa_ipc.h"

// WINAMP_BUTTON1 = 40044 = Previous Track
// WINAMP_BUTTON2 = 40045 = Play
// WINAMP_BUTTON3 = 40046 = Pause
// WINAMP_BUTTON4 = 40047 = Stop
// WINAMP_BUTTON5 = 40048 = Next Track

//Easier to read...
#define WINAMP_BUTTON_PREVTRACK 40044
#define WINAMP_BUTTON_PLAY		40045
#define WINAMP_BUTTON_PAUSE		40046
#define WINAMP_BUTTON_STOP		40047
#define WINAMP_BUTTON_NEXTTRACK	40048