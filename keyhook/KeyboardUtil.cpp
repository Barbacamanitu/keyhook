#include "stdafx.h"
#include "KeyboardUtil.h"
#include "KeyboardState.h"

bool KeyboardUtil::IsKeyModifier(DWORD vk) {
	return (IsKeyShift(vk) || IsKeyControl(vk) || IsKeyAlt(vk));
}

bool KeyboardUtil::IsKeyShift(DWORD vk) {
	return (vk == VK_LSHIFT || vk == VK_RSHIFT || vk == VK_SHIFT);
}

bool KeyboardUtil::IsKeyControl(DWORD vk) {
	return (vk == VK_LCONTROL || vk == VK_RCONTROL || vk == VK_CONTROL);
}

bool KeyboardUtil::IsKeyAlt(DWORD vk) {
	return (vk == VK_MENU);
}

void KeyboardUtil::UpdateKeyboardState(KeyboardState * state, DWORD vk, bool isDown)
{
	if (IsKeyShift(vk)) {
		state->Shift = isDown;
	}

	if (IsKeyControl(vk)) {
		state->Ctrl = isDown;
	}

	if (IsKeyAlt(vk)) {
		state->Alt = isDown;
	}
}
