#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "gui/GuiScreen.h"
#include "gui/GuiMainScreen.h"
#include "settings/GameSettings.h"

using namespace std;

SDL_Window *window;
SDL_GLContext context;

GuiScreen *currentScreen;

GameSettings *gameSettings = new GameSettings();

#define displayName "I don't know what to call this"
#define maxFps 60

Mix_Music *music = NULL;

int displayWidth = 854;
int displayHeight = 480;

bool running = true;

int fpsCounter;
Uint32 lastTick;

bool setupOpenGL();
void runTick();
void runTickMouse(SDL_Event event);
void runTickKeyboard(SDL_Event event);
void updateDisplay();
void checkWindowResize();
void displayGui(GuiScreen * gui);
void shutdown();

int main(int argc, char *argv[]) {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		cout << "Failed to initialized SDL!" << endl;
	}
	window = SDL_CreateWindow(
			displayName,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			displayWidth,
			displayHeight,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if(window == NULL) {
		cout << "Yo, ze vindow is ze null doe, y doe?" << endl;
	}

	context = SDL_GL_CreateContext(window);

	setupOpenGL();

	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	SDL_GL_SetSwapInterval(1);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, displayWidth, displayHeight, 0, -1.0, 1.0);
	glViewport(0, 0, displayWidth, displayHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	SDL_GL_SwapWindow(window);

	TTF_Init();
	IMG_Init(IMG_INIT_JPG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

	Mix_VolumeMusic(50);

	music = Mix_LoadMUS("res/music/memes.wav");
	cout << Mix_PlayMusic(music, -1) << endl;

	displayGui(new GuiMainScreen());

	while(running) {
		if(gameSettings->keyBindRight->isPressed()){
			std::cout << "THIS SHIT HAS BEEN PRESSED MOFO" << std::endl;
		}

		runTick();

		Uint32 starting_tick = SDL_GetTicks();

		if ((1000 / maxFps) > SDL_GetTicks() - starting_tick) {
		    SDL_Delay(1000 / maxFps - (SDL_GetTicks() - starting_tick));
		}

		updateDisplay();
	}

	SDL_DestroyWindow(window);

	Mix_FreeMusic(music);

	Mix_CloseAudio();

	TTF_Quit();

	SDL_Quit();

	return 0;
}

void updateDisplay() {
	SDL_GL_SwapWindow(window);
	checkWindowResize();
}

void checkWindowResize() {
	int i = displayWidth;
	int j = displayHeight;
	SDL_GetWindowSize(window, &displayWidth, &displayHeight);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if(displayWidth != i || displayHeight != j) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, displayWidth, displayHeight, 0, -1.0, 1.0);
		glViewport(0, 0, displayWidth, displayHeight);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		currentScreen->setResolution(displayWidth, displayHeight);
	}
}

bool setupOpenGL()
{
	// Set our OpenGL version.
	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return true;
}

void runTick() {
	int x, y;
	SDL_Event event;

	SDL_GetMouseState(&x, &y);
	currentScreen->drawScreen(x, y);

	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT: {
				shutdown();
				break;
			}
		}

		runTickMouse(event);
		runTickKeyboard(event);
	}
}

void runTickMouse(SDL_Event event) {
	if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		currentScreen->handleMouseInput(event.button);
	}
}

void runTickKeyboard(SDL_Event event) {
	if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		gameSettings->setBindState(event.key.keysym.sym, event.key.state);
	}
}

void displayGui(GuiScreen *gui) {
	currentScreen = gui;
	currentScreen->setResolution(displayWidth, displayHeight);
}

void shutdown() {
	running = false;
}
