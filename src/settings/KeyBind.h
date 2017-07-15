#ifndef KEYBIND_H
#define KEYBIND_H

#include <SDL2/SDL.h>

class KeyBind {
public:
	SDL_Keycode key;
	bool pressed;

	KeyBind(SDL_Keycode a) : key(a), pressed(false) {}

	bool isPressed() {
		return pressed;
	}

	void setState(bool state) {
		this->pressed = state;
	}

	virtual ~KeyBind() {}
};

#endif
