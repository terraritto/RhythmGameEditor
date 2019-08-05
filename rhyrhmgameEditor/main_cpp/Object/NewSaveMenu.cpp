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
	//bpm lpb �ȃt�@�C�����̉��菑��
	textFile << mStartMenu->GetMusicName() << "," << mStartMenu->GetBPM() << ","
		<< mStartMenu->GetLPB() << std::endl;

	//�S�ẴI�u�W�F�N�g�����菑��
	for (auto object : mStartMenu->GetNoteObjects())
	{
		textFile << object->GetNotesNumber() << "," //notes�̎��
			<< object->GetBPMIndex() << ","         //BPM�ʒu
			<< object->GetBpmPage() << ","          //BPM�ԍ�
			<< object->GetLPBIndex() << ","         //LPB�ʒu
			<< object->GetLaneIndex() << ","        //Lane�ʒu
			<< object->GetColorChar() << ","        //�F
			<< object->GetNotesIndex()              //longNotes�p�ԍ�
			<< std::endl;
	}

	textFile.close();
}