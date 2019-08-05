#pragma once
#include "UIScreen.h"
#include <string>
#include <memory>

class TextLoadMenu : public UIScreen
{
public:
	TextLoadMenu(class Game* game, TextInf& text, class StartMenu* startMenu);
	~TextLoadMenu();

	//file Search
	bool FileExist();
	void FileRead();
	std::vector <std::string> Split(std::string& input, char delimiter);

	void Update(float deltaTime) override;
	void Draw() override;
private:
	int mInputHandle;
	std::string mFileName;
	class StartMenu* mStartMenu;
};