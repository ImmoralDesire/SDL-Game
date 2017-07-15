#include "GameSettings.h"

GameSettings::GameSettings() {
	this->keyBindRight = new KeyBind(SDLK_d);
	this->HASH.push_back(this->keyBindRight);
}

void GameSettings::setBindState(SDL_Keycode key, bool state) {
	for(std::list<KeyBind*>::iterator it = this->HASH.begin(); it != this->HASH.end(); it++) {
		KeyBind &keyBind = **it;
		if(keyBind.key == key) {
			keyBind.pressed = state;
		}
	}
}

GameSettings::~GameSettings() {
	// TODO Auto-generated destructor stub
}

