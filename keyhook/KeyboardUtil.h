#pragma once
#include <Windows.h>
struct KeyboardState;
class KeyboardUtil {
public:
	static bool IsKeyModifier(DWORD vk);
	static bool IsKeyShift(DWORD vk);
	static bool IsKeyControl(DWORD vk);
	static bool IsKeyAlt(DWORD vk);
	static void UpdateKeyboardState(KeyboardState* state, DWORD vk, bool isDown);
};