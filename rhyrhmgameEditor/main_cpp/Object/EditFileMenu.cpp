#include "../../main_header/Objects/EditFileMenu.h"
#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/NotesObject.h"
#include "../../Game.h"
#include <fstream>
#include <iostream>

EditFileMenu::EditFileMenu(Game* game, StartMenu* startMenu)
	:UIScreen(game)
	, mStartMenu(startMenu)
{
	Close();
}

EditFileMenu::~EditFileMenu()
{
	std::ofstream textFile;
	textFile.open("Text\\" + mStartMenu->GetFileName(), std::ios::trunc);
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