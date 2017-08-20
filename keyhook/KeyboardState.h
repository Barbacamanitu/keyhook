#pragma once
#include <iostream>
//Struct representing all pressed modifier keys9
struct KeyboardState {
	bool Shift;
	bool Ctrl;
	bool Alt;

	void Dump() {
		std::cout << "Modifier Keys:";
		
		if (Shift) { std::cout << " Shift"; }
		if (Ctrl) { std::cout << " Control"; }
		if (Alt) { std::cout << " Alt"; }
		std::cout << std::endl;
	}
};