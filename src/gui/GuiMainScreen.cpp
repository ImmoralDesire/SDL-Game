#include <iostream>
#include "GuiMainScreen.h"

void GuiMainScreen::initGui() {
	std::cout << "HI" << std::endl;
	this->buttonList.push_back(*new GuiButton(1, this->width / 2 - 100, 200, "Sup"));
}

void GuiMainScreen::drawScreen(int x, int y) {
	SDL_Color color = {255, 255, 255};
	this->fontRenderer.drawString("IDK", (this->width - this->fontRenderer.getWidth("IDK")) / 2, 50, color);
	GuiScreen::drawScreen(x, y);
}

void GuiMainScreen::actionPerformed(GuiButton button) {
	if(button.buttonId == 1) {
		std::cout << "PLEASE WORK" << std::endl;
	}
}

void GuiMainScreen::mouseClicked(int button, int x, int y) {
	GuiScreen::mouseClicked(button, x, y);
}

void GuiMainScreen::mouseReleased(int button, int x, int y) {

}

void GuiMainScreen::updateScreen() {

}

void GuiMainScreen::onGuiClosed() {

}
