#pragma once
#include "UIScreen.h"
#include <string>
#include <memory>

class MusicLoadMenu : public UIScreen
{
public:
	MusicLoadMenu(class Game* game, TextInf& text, class StartMenu* startMenu);
	~MusicLoadMenu();

	//file Search
	bool FileExist();

	void Update(float deltaTime) override;
	void Draw() override;
private:
	int mInputHandle;
	std::string mFileName;
	class StartMenu* mStartMenu;
};