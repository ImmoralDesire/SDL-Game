#include "GuiButton.h"
#include "../GuiScreen.h"

void GuiButton::drawButton(int x, int y) {
	glPushMatrix();
	glColor4f(0.7, 0.7, 0.7, 1);
	glBegin(GL_QUADS); {
		glVertex3f(this->x, this->y, 0);
		glVertex3f(this->x + this->width, this->y,0 );
		glVertex3f(this->x + this->width, this->y + this->height, 0);
		glVertex3f(this->x, this->y + this->height,  0);
	}
	glEnd();

	float xCenter = this->x + (this->width - GuiScreen::fontRenderer.getWidth(this->text.c_str())) / 2;
	float yCenter = this->y + (this->height - GuiScreen::fontRenderer.getHeight(this->text.c_str())) / 2;
	SDL_Color color = {0, 0, 0};
	GuiScreen::fontRenderer.drawString(this->text.c_str(), xCenter, yCenter, color);
	glPopMatrix();
}

GuiButton::~GuiButton() {
}

