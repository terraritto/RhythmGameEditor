#include "../../main_header/Objects/MusicLoadMenu.h"
#include "../../main_header/Objects/BpmSelectMenu.h"
#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/Music.h"
#include "../../main_header/Objects/MusicEdit.h"
#include "../../main_header/wrapper/Math.h"
#include "../../Game.h"
#include <iostream>

BpmSelectMenu::BpmSelectMenu(Game* game, TextInf& text, StartMenu* startMenu)
	: UIScreen(game)
	, mStartMenu(startMenu)
{
	mBGPos = Pos(text.x, text.y);

	mBackground = LoadGraph("object/Textbox.png");
	SetTitleTextAndPos(text);

	mInputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);
	SetActiveKeyInput(mInputHandle);
}

BpmSelectMenu::~BpmSelectMenu()
{
	char tempStr[50];
	GetKeyInputString(tempStr, mInputHandle); //“ü—Í‚³‚ê‚½•¶Žš‚ðŽæ“¾
	mBpmText = tempStr; //string‚É—¬‚·

	try {
		int bpm = std::stoi(mBpmText);
		bpm = Math::Clamp(bpm, 1, 1000);
		mStartMenu->SetBPM(bpm);
		mStartMenu->GetMusicEdit()->SetBpmValue(bpm);
	}
	catch (std::invalid_argument e)
	{
		std::cerr << e.what() << std::endl;
	}

	//inputHandle‚Ìíœ
	DeleteKeyInput(mInputHandle);
}

void BpmSelectMenu::Update(float deltaTIme)
{
	UIScreen::Update(deltaTIme);

	if (CheckKeyInput(mInputHandle) != 0)
	{
		Close();
	}
}

void BpmSelectMenu::Draw()
{
	UIScreen::Draw();
	DrawKeyInputString(mBGPos.x+5, mBGPos.y+20, mInputHandle);
}