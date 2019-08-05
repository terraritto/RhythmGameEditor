#include "../../main_header/Objects/MusicLoadMenu.h"
#include "../../main_header/Objects/LpbSelectMenu.h"
#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/Music.h"
#include "../../main_header/Objects/MusicEdit.h"
#include "../../main_header/wrapper/Math.h"
#include "../../Game.h"
#include <iostream>

LpbSelectMenu::LpbSelectMenu(Game* game, TextInf& text, StartMenu* startMenu)
	: UIScreen(game)
	, mStartMenu(startMenu)
{
	mBGPos = Pos(text.x, text.y);

	mBackground = LoadGraph("object/Textbox.png");
	SetTitleTextAndPos(text);

	mInputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);
	SetActiveKeyInput(mInputHandle);
}

LpbSelectMenu::~LpbSelectMenu()
{
	char tempStr[50];
	GetKeyInputString(tempStr, mInputHandle); //“ü—Í‚³‚ê‚½•¶Žš‚ðŽæ“¾
	mLpbText = tempStr; //string‚É—¬‚·

	try {
		int lpb = std::stoi(mLpbText);
		lpb = Math::Clamp(lpb, 4, 32);
		mStartMenu->SetLPB(lpb);
		mStartMenu->GetMusicEdit()->SetLpb(lpb);
	}
	catch (std::invalid_argument e)
	{
		std::cerr << e.what() << std::endl;
	}

	//inputHandle‚Ìíœ
	DeleteKeyInput(mInputHandle);
}

void LpbSelectMenu::Update(float deltaTIme)
{
	UIScreen::Update(deltaTIme);

	if (CheckKeyInput(mInputHandle) != 0)
	{
		Close();
	}
}

void LpbSelectMenu::Draw()
{
	UIScreen::Draw();
	DrawKeyInputString(mBGPos.x + 5, mBGPos.y + 20, mInputHandle);
}