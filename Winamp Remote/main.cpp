// ////////////////////////////////////////////////////////////////////////////////////////////////
//
// Media Center Remote Support in Winamp
//
// ////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
 
BOOL WINAPI _DllMainCRTStartup(HANDLE hInst, ULONG ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

int init();
void config();
void quit();

winampGeneralPurposePlugin plugin =
{
	GPPHDR_VER,
	"Media Center Remote Support",
	init,
	config,
	quit,
};

HHOOK hook = NULL;
HWND winamp_hwnd = NULL;

LRESULT CALLBACK ShellProc(int nCode, WPARAM wParam, LPARAM lParam);

int init()
{
	winamp_hwnd = FindWindow("Winamp v1.x", NULL);

	hook = SetWindowsHookEx(WH_SHELL, ShellProc, plugin.hDllInstance, 0);

	if (hook != NULL)
		return 0;

	else
	{
		MessageBox(0, 0, "Failed to hook", 0);
		return -1; 
	}
}

void config()
{
	MessageBox(0, "No Settings Available", "Configuration", 0);
}

void quit()
{
	BOOL unhooked = UnhookWindowsHookEx(hook);

	if ( !unhooked )
		MessageBox(0, 0, "Failed to unhook", 0);
}

int getWinampCommand(LPARAM lParam)
{
	int app_cmd, winamp_cmd;

	app_cmd = GET_APPCOMMAND_LPARAM(lParam);

	if (app_cmd == APPCOMMAND_MEDIA_PLAY_PAUSE)
	{
		if ( SendMessage(winamp_hwnd, WM_USER, 0, IPC_ISPLAYING) == 1)
			winamp_cmd = WINAMP_BUTTON_PAUSE;
		else
			winamp_cmd = WINAMP_BUTTON_PLAY;
	}
	
	else if (app_cmd == APPCOMMAND_MEDIA_STOP)
		winamp_cmd = WINAMP_BUTTON_STOP;
		
	else if (app_cmd == APPCOMMAND_MEDIA_NEXTTRACK)
		winamp_cmd = WINAMP_BUTTON_NEXTTRACK;
		
	else if (app_cmd == APPCOMMAND_MEDIA_PREVIOUSTRACK)
		winamp_cmd = WINAMP_BUTTON_PREVTRACK;
		
	else if (app_cmd == APPCOMMAND_VOLUME_DOWN)
		winamp_cmd = WINAMP_VOLUMEDOWN;
		
	else if (app_cmd == APPCOMMAND_VOLUME_UP)
		winamp_cmd = WINAMP_VOLUMEUP;

	else if (app_cmd == APPCOMMAND_MEDIA_PLAY)
		winamp_cmd = WINAMP_BUTTON_PLAY;
		
	else if (app_cmd == APPCOMMAND_MEDIA_PAUSE)
		winamp_cmd = WINAMP_BUTTON_PAUSE;
		
	else if (app_cmd == APPCOMMAND_MEDIA_RECORD)
	{
		winamp_cmd = WINAMP_OPTIONS_PLEDIT; //hmm, i set it to something more useful - opens playlist

		//give focus to playlist
		HWND winamp_playlist_hwnd = FindWindow("Winamp PE", NULL);

		if ( winamp_playlist_hwnd != NULL )
			SetForegroundWindow(winamp_playlist_hwnd);
	}
		
	else if (app_cmd == APPCOMMAND_MEDIA_FAST_FORWARD)
		winamp_cmd = WINAMP_FFWD5S;
		
	else if (app_cmd == APPCOMMAND_MEDIA_REWIND)
		winamp_cmd = WINAMP_REW5S;
		
	else if (app_cmd == APPCOMMAND_MEDIA_CHANNEL_UP)
		winamp_cmd = WINAMP_BUTTON_NEXTTRACK;
		
	else if (app_cmd == APPCOMMAND_MEDIA_CHANNEL_DOWN)
		winamp_cmd = WINAMP_BUTTON_PREVTRACK;
	
	//else if (app_cmd == APPCOMMAND_HELP)
	//	winamp_cmd = WINAMP_HELP_ABOUT;

	else
		winamp_cmd = -1;

	return winamp_cmd;
}

LRESULT CALLBACK ShellProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if ( nCode == HSHELL_APPCOMMAND )
	{
		int winamp_cmd;

		if ( !IsWindow(winamp_hwnd) ) //TODO: better way?
			winamp_hwnd = FindWindow("Winamp v1.x", NULL);

		winamp_cmd = getWinampCommand(lParam);

		if ( winamp_cmd != -1 )
			SendMessage(winamp_hwnd, WM_COMMAND, winamp_cmd, 0);
	}

	return (CallNextHookEx(hook, nCode, wParam, lParam));
}

__declspec( dllexport ) winampGeneralPurposePlugin * winampGetGeneralPurposePlugin()
{
	return &plugin;
}