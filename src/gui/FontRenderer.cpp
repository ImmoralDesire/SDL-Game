#include "FontRenderer.h"

FontRenderer::FontRenderer(const char* font, std::string name, int size) {
	this->font = font;
	this->name = name;
	this->size = size;
}

void FontRenderer::drawString(const char* text, float x, float y, SDL_Color color) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint texture;
	SDL_Surface *surface;

	TTF_Font *mFont = TTF_OpenFont(this->font, this->size);

	surface = TTF_RenderText_Blended(mFont, text, color);

	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);

	gluBuild2DMipmaps(GL_TEXTURE_2D,4,surface->w,surface->h,GL_RGBA,GL_UNSIGNED_BYTE,surface->pixels);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	GLboolean textureIsEnabled = glIsEnabled(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);

	glColor3ub(color.r,color.g,color.b);
	//Renders images using quads, Coords are flipped to prevent being upside down
	glBegin(GL_QUADS);

	glTexCoord2f(0,0); glVertex2f(x, y);
	glTexCoord2f(1,0); glVertex2f(x + surface->w, y);
	glTexCoord2f(1,1); glVertex2f(x + surface->w, y + surface->h);
	glTexCoord2f(0,1); glVertex2f(x, y + surface->h);

	glEnd();

	if(!textureIsEnabled){
		glDisable(GL_TEXTURE_2D);
	}

	glDisable(GL_BLEND);
	glColor3f(1, 1, 1);

	TTF_CloseFont(mFont);

	glDeleteTextures(1, &texture);

	if(surface)
		SDL_FreeSurface(surface);
}

SDL_Surface FontRenderer::getSurface(const char* text) {
	GLuint texture;
	SDL_Surface *surface;
	SDL_Color color = {255, 255, 255};

	TTF_Font *mFont = TTF_OpenFont(this->font, this->size);

	surface = TTF_RenderText_Blended(mFont, text, color);

	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);

	gluBuild2DMipmaps(GL_TEXTURE_2D,4,surface->w,surface->h,GL_RGBA,GL_UNSIGNED_BYTE,surface->pixels);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	TTF_CloseFont(mFont);

	if(surface)
		SDL_FreeSurface(surface);

	glDeleteTextures(1, &texture);

	return *surface;
}

float FontRenderer::getWidth(const char* text) {
	return getSurface(text).w;
}

float FontRenderer::getHeight(const char* text) {
	return getSurface(text).h;
}

FontRenderer::~FontRenderer() {
}

