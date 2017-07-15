#ifndef GUI_COMPONENTS_GUIBUTTON_H_
#define GUI_COMPONENTS_GUIBUTTON_H_

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Gui.h"

class GuiButton : public Gui{
public:
	int buttonId;
	int x, y;
	int width, height;
	std::string text;

	GuiButton(int a, int b, int c, std::string d) :
		buttonId(a),
		x(b), y(c),
		width(200), height(200),
		text(d) {}
	GuiButton(int a, int b, int c, int d, int e, std::string f) :
		buttonId(a),
		x(b), y(c),
		width(d), height(e),
		text(f) {}

	void drawButton(int x, int y);

	bool isHovered(int x, int y) {
		return x >= this->x && x <= this->x + this->width &&
			   y >= this->y && y <= this->y + this->height;
	}

	virtual ~GuiButton();
};

#endif
