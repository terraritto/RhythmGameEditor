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