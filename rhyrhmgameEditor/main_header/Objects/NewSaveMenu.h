#pragma once
#include "UIScreen.h"

class NewSaveMenu : public UIScreen
{
public:
	NewSaveMenu(class Game* game, TextInf& text, class StartMenu* startMenu);
	~NewSaveMenu();

	void Update(float deltaTime) override;
	void Draw() override;
private:
	void FileWrite();
	int mInputHandle;
	std::string mFileName;
	class StartMenu* mStartMenu;
};