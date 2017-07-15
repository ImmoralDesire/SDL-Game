#ifndef GUISCREEN_H
#define GUISCREEN_H

#include <list>
#include "Gui.h"
#include "components/GuiButton.h"
#include "FontRenderer.h"

class GuiScreen : public Gui {
public:
	std::list<GuiButton> buttonList;

	int width;
	int height;

	GuiButton *selectedButton;

	static FontRenderer fontRenderer;

	GuiScreen() {};
	virtual ~GuiScreen() {};

	void handleMouseInput(SDL_MouseButtonEvent event) {
		if(event.state == SDL_PRESSED) {
			this->mouseClicked(event.button, event.x, event.y);
		} else {
			this->mouseReleased(event.button, event.x, event.y);
		}
	}

	virtual void mouseClicked(int button, int x, int y) {
		if(button == 1) {
			for(std::list<GuiButton>::iterator it = buttonList.begin(); it != buttonList.end(); it++) {
				GuiButton button = *it;

				if(button.isHovered(x, y)) {
					this->selectedButton = (GuiButton*) &button;
					this->actionPerformed(button);
				}
			}
		}
	}

	virtual void mouseReleased(int button, int x, int y) {
			this->selectedButton = NULL;
	}

	virtual void initGui() = 0;
	virtual void updateScreen() = 0;
	virtual void onGuiClosed() = 0;
	virtual void actionPerformed(GuiButton button) = 0;

	virtual void drawScreen(int x, int y) {
		for(std::list<GuiButton>::iterator it = buttonList.begin(); it != buttonList.end(); it++) {
			GuiButton button = *it;
			button.drawButton(x, y);
		}
	}

	void setResolution(int width, int height) {
		this->width = width;
		this->height = height;
		this->buttonList.clear();
		this->initGui();
	}
};

#endif
