#ifndef GUIMAINSCREEN_H
#define GUIMAINSCREEN_H

#include "GuiScreen.h"

class GuiMainScreen : public GuiScreen {
public:
	GuiMainScreen() : GuiScreen() {};

	void mouseClicked(int button, int x, int y);
	void mouseReleased(int button, int x, int y);

	void initGui();
	void drawScreen(int x, int y);
	void updateScreen();
	void onGuiClosed();
	void actionPerformed(GuiButton button);

	virtual ~GuiMainScreen() {};
};

#endif
