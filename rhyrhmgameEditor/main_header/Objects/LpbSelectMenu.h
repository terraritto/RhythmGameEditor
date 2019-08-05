#pragma once
#pragma once
#include "UIScreen.h"
#include <string>
#include <memory>

class LpbSelectMenu : public UIScreen
{
public:
	LpbSelectMenu(class Game* game, TextInf& text, class StartMenu* startMenu);
	~LpbSelectMenu();

	void Update(float deltaTime) override;
	void Draw() override;
private:
	int mInputHandle;
	std::string mLpbText;
	class StartMenu* mStartMenu;
};