#pragma once
#include "UIScreen.h"
#include <string>
#include <memory>

class BpmSelectMenu : public UIScreen
{
public:
	BpmSelectMenu(class Game* game, TextInf& text, class StartMenu* startMenu);
	~BpmSelectMenu();

	void Update(float deltaTime) override;
	void Draw() override;
private:
	int mInputHandle;
	std::string mBpmText;
	class StartMenu* mStartMenu;
};