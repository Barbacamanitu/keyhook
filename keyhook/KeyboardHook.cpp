#include "stdafx.h"
#include "KeyboardHook.h"



void KeyboardHook::Keydown(DWORD virtualKey, DWORD scanCode){
	//Set keyboard state for modifier keys
	KeyboardUtil::UpdateKeyboardState(&mKeyboardState, virtualKey, true);

	//Execute all observers of this event.
	for (auto f : mKeyObserverMap[KeyEventType::DOWN]) {
		f(virtualKey, scanCode);
	}
}

void KeyboardHook::Keyup(DWORD virtualKey, DWORD scanCode){
	//Set keyboard state for modifier keys
	KeyboardUtil::UpdateKeyboardState(&mKeyboardState, virtualKey, false);

	//Execute all observers of this event.
	for (auto f : mKeyObserverMap[KeyEventType::UP]) {
		f(virtualKey, scanCode);
	}
}


//Singleton method. Return instance if it exists, and create an instance if not.
KeyboardHook& KeyboardHook::getInstance()
{
	static KeyboardHook instance;
	return instance;
}

void KeyboardHook::AddKeyObserver(KeyEventType eventType, KeyEventObserver observer)
{
	mKeyObserverMap[eventType].push_back(observer);
}

KeyboardState KeyboardHook::getModifierState()
{
	return mKeyboardState;
}

//Constructor.
KeyboardHook::KeyboardHook() {

}

//Destructor.
KeyboardHook::~KeyboardHook() {
}

/*
	Low level system callback related methods below this line.
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

LRESULT CALLBACK KeyboardHook::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION)
	{

		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
		char theCode = MapVirtualKey(p->vkCode, MAPVK_VK_TO_CHAR);
		switch (wParam)
		{
		case WM_KEYDOWN:
			getInstance().Keydown(p->vkCode, p->scanCode);
			break;
		case WM_SYSKEYDOWN:
			//std::cout << "SysKeydown: " << theCode << std::endl;
			break;
		case WM_KEYUP:
			getInstance().Keyup(p->vkCode, p->scanCode);
			break;
		case WM_SYSKEYUP:

			break;
		default:
			break;
		}
	}
	return (CallNextHookEx(NULL, nCode, wParam, lParam));
}


void KeyboardHook::registerHook()
{
	// Install the low-level keyboard hook
	hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook::LowLevelKeyboardProc, 0, 0);
}

void KeyboardHook::unregisterHook()
{
	//Unhook keyboard
	UnhookWindowsHookEx(hhkLowLevelKybd);
}