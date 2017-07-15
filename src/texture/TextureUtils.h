#ifndef TEXTUREUTILS_H
#define TEXTUREUTILS_H

#include <map>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "ResourceLocation.h"

class TextureUtils {
public:
	std::map<ResourceLocation, GLuint> textureMap;

	TextureUtils();
	void bindTexture(ResourceLocation a);
	virtual ~TextureUtils();
};

#endif
