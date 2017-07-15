#ifndef FONTRENDERER_H
#define FONTRENDERER_H

#include <string>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class FontRenderer {

public:
	const char* font;
	std::string name;
	int size;

	FontRenderer();
	FontRenderer(const char* font, std::string name, int size);
	void drawChar();
	void drawString(const char* text, float x, float y, SDL_Color color);
	float getWidth(const char* width);
	float getHeight(const char* height);
	SDL_Surface getSurface(const char* text);
	virtual ~FontRenderer();
};

#endif
