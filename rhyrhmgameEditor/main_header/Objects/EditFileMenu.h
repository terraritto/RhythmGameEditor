#pragma once
#include "UIScreen.h"

class EditFileMenu : public UIScreen
{
public:
	EditFileMenu(class Game* game, class StartMenu* startMenu);
	~EditFileMenu();
private:
	class StartMenu* mStartMenu;
};