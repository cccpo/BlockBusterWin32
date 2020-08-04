#include "KeyInput.h"

bool KeyInput::IsKeyPressed(int vKey){
	return (GetAsyncKeyState(vKey) & 0x8000) != 0;
}