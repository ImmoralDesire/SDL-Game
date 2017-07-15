#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <iostream>
#include <list>
#include "KeyBind.h"

class GameSettings {
public:

	KeyBind *keyBindRight;

	std::list<KeyBind*> HASH;

	GameSettings();
	void setBindState(SDL_Keycode key, bool state);
	void getKeyState(SDL_Keycode) {

	}
	virtual ~GameSettings();
};

#endif
