#include "../../main_header/Objects/NewSaveMenu.h"
#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/NotesObject.h"
#include "../../Game.h"
#include <fstream>
#include <iostream>

NewSaveMenu::NewSaveMenu(Game* game, TextInf& text, StartMenu* startMenu)
	: UIScreen(game)
	, mStartMenu(startMenu)
{
	mBGPos = Pos(text.x, text.y);
	mBackground = LoadGraph("object/Textbox.png");
	SetTitleTextAndPos(text);

	mInputHandle = MakeKeyInput(50, TRUE, FALSE, FALSE);
	SetActiveKeyInput(mInputHandle);
}

NewSaveMenu::~NewSaveMenu()
{
	if (CheckKeyInput(mInputHandle) == 1)
	{
		char tempStr[50];
		GetKeyInputString(tempStr, mInputHandle);
		mFileName = tempStr;
		FileWrite();
		mStartMenu->SetFileName(mFileName);
	}

	DeleteKeyInput(mInputHandle);
}

void NewSaveMenu::Update(float deltaTime)
{
	UIScreen::Update(deltaTime);

	if (CheckKeyInput(mInputHandle) != 0)
	{
		Close();
	}
}

void NewSaveMenu::Draw()
{
	UIScreen::Draw();
	DrawKeyInputString(mBGPos.x + 5, mBGPos.y + 20, mInputHandle);
}

void NewSaveMenu::FileWrite()
{
	std::ofstream textFile;
	textFile.open("Text\\" + mFileName, std::ios::out);
	//bpm lpb 曲ファイル名の殴り書き
	textFile << mStartMenu->GetMusicName() << "," << mStartMenu->GetBPM() << ","
		<< mStartMenu->GetLPB() << std::endl;

	//全てのオブジェクトを殴り書き
	for (auto object : mStartMenu->GetNoteObjects())
	{
		textFile << object->GetNotesNumber() << "," //notesの種類
			<< object->GetBPMIndex() << ","         //BPM位置
			<< object->GetBpmPage() << ","          //BPM番号
			<< object->GetLPBIndex() << ","         //LPB位置
			<< object->GetLaneIndex() << ","        //Lane位置
			<< object->GetColorChar() << ","        //色
			<< object->GetNotesIndex()              //longNotes用番号
			<< std::endl;
	}

	textFile.close();
}