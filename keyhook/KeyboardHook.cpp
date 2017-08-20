#include "stdafx.h"
#include "KeyboardHook.h"


KeyboardHook::KeyboardHook()
{
	// Install the low-level keyboard & mouse hooks
	hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook::LowLevelKeyboardProc, 0, 0);
}


KeyboardHook::~KeyboardHook()
{
	UnhookWindowsHookEx(hhkLowLevelKybd);
}

bool KeyboardHook::isActive() {
	if (!GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		return true;
	} 
	else
	{
		return false;
	}
}

LRESULT CALLBACK KeyboardHook::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION)
	{

		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
		char theCode = MapVirtualKey(p->vkCode, MAPVK_VK_TO_CHAR);
		switch (wParam)
		{
		case WM_KEYDOWN:
			std::cout << "Keydown: " << theCode << std::endl;
			break;
		case WM_SYSKEYDOWN:
			//std::cout << "SysKeydown: " << theCode << std::endl;
			break;
		case WM_KEYUP:
			if (theCode > 0) {
				std::cout << "Keyup: " << theCode << std::endl;
			}
			else {
				std::cout << "Blank keyup" << std::endl;
			}
			break;
		case WM_SYSKEYUP:

			break;
		default:
			break;
		}
	}
	return(CallNextHookEx(NULL, nCode, wParam, lParam));
}
