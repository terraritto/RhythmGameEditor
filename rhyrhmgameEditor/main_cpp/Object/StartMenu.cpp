#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/InputSystem.h"
#include "../../main_header/Objects/MusicLoadMenu.h"
#include "../../main_header/Objects/BpmSelectMenu.h"
#include "../../main_header/Objects/LpbSelectMenu.h"
#include "../../main_header/Objects/NewSaveMenu.h"
#include "../../main_header/Objects/EditFileMenu.h"
#include "../../main_header/Objects/TextLoadMenu.h"
#include "../../main_header/Objects/MusicEdit.h"
#include "../../main_header/Objects/NotesObject.h"
#include "../../Game.h"
#include "../../main_header/Objects/Font.h"

StartMenu::StartMenu(Game* game)
	:UIScreen(game)
	,mBpm(120)
	,mLpb(4)
{
	mBackground = LoadGraph("object/Universe.png");
	mBGPos = Pos(0, 0);

	mTextBox = LoadGraph("object/Textbox.png");
	mTextBoxPos = Pos(1500, 0);

	int xOffset = 1140;
	//create new music
	TextInf textLoad("Load Music", 380, 0, GetColor(0, 0, 255), 20);
	//SetTitleTextAndPos(textLoad);
	mExplainInput = TextInf("編集する音楽ファイルを入力", xOffset, 0, GetColor(0, 0, 255), 20);
	AddButton(textLoad, [this]()
		{
			new MusicLoadMenu(mGame, mExplainInput,this);
		}
	);

	//new save
	TextInf textNewSave("New Save", 570, 0,GetColor(0,0,255),20);
	mExplainNewSave = TextInf("新規作成するファイル名(.csv指定)", xOffset, 0, GetColor(0, 0, 255), 20);
	AddButton(textNewSave, [this]()
		{
			new NewSaveMenu(mGame, mExplainNewSave, this);
		}
	);
	//save
	TextInf textSave("Save", 760, 0, GetColor(0, 0, 255), 20);
	AddButton(textSave, [this]()
		{
			new EditFileMenu(mGame, this);
		}
	);

	//file Load
	TextInf textFileLoad("FileLoad", 950, 0, GetColor(0, 0, 255), 20);
	mExplainFileLoad = TextInf("Loadするファイル名(.csv指定)", xOffset, 0, GetColor(0, 0, 255), 20);
	AddButton(textFileLoad, [this]()
		{
			new TextLoadMenu(mGame, mExplainFileLoad, this);
		}
	);
	//music play
	TextInf textStart("Start", 0, 0, GetColor(0, 0, 255), 20);
	TextInf textStop("Stop", 190, 0, GetColor(0, 0, 255), 20);
	AddButton(textStart, [this]()
		{
			auto music = this->GetMusic();
			if (music && music->IsMusicStart() == false)
			{
				music->MusicStart();
				for (auto object : this->GetNoteObjects())
				{
					int bpmTime = 60000 / this->GetMusicEdit()->GetBpmValue();
					int time = object->GetBpmPage() * bpmTime * 4
						+ bpmTime / this->GetMusicEdit()->GetLpbValue() * object->GetLPBIndex()
						+ object->GetBPMIndex() * bpmTime;
					if (this->GetMusic()->GetCurrentMusicTime() < time)
					{
						object->SetIsSound();
					}
				}
			}
		}
	);
	AddButton(textStop, [this]()
		{
			auto music = this->GetMusic();
			if (music && music->IsMusicStart() == true)
			{
				music->MusicStop();
			}
		}
	);
	//BPM
	TextInf textBpm("BPM", 0, 49, GetColor(0, 0, 255), 20);
	mExplainBpm = TextInf("BPMを入力:1~1000", 400, 50, GetColor(0, 0, 255), 20);
	AddButton(textBpm,
		[this]()
		{
			new BpmSelectMenu(mGame, mExplainBpm, this);
		}
		);

	//LPB
	TextInf textLpb("LPB", 190, 49, GetColor(0, 0, 255), 20);
	mExplainLpb = TextInf("Lpbを入力4~32", 400, 50, GetColor(0, 0, 255), 20);
	AddButton(textLpb,
		[this]()
		{
			new LpbSelectMenu(mGame, mExplainLpb, this);
		}
	);

	//Music Editor(BPM,LPB line)
	mMusicEdit = std::make_unique<MusicEdit>(this);
}

StartMenu::~StartMenu()
{

}

void StartMenu::Draw()
{
	UIScreen::Draw();


	DrawGraph(mTextBoxPos.x, mTextBoxPos.y, mTextBox, TRUE);
	DrawString(mTextBoxPos.x + 5, mTextBoxPos.y, mMusicName.c_str(), GetColor(0, 0, 255)); //MusicName
	DrawFormatString(mTextBoxPos.x + 5,mTextBoxPos.y + 20, GetColor(0, 0, 255), "BPM: %d", mBpm);//BPM
	DrawFormatString(mTextBoxPos.x + 5, mTextBoxPos.y + 40, GetColor(0, 0, 255), "LPB: %d", mLpb);//LPB

	if (mMusic) {
		mMusic->Draw();
	}

	mMusicEdit->Draw();

	for (auto object : mNotesObjects)
	{
		object->Draw();
	}
	DrawFormatString(mTextBoxPos.x, 80, GetColor(0, 0, 255), "object num:%d", mNotesObjects.size());
}

void StartMenu::ProcessInput(const InputState& state)
{
	UIScreen::ProcessInput(state);

	if (mMusic)
	{
		mMusic->ProcessInput(state);
	}

	mMusicEdit->ProcessInput(state);
}

void StartMenu::Update(float deltaTime)
{
	UIScreen::Update(deltaTime);

	if (mMusic)
	{
		mMusic->Update();
	}

	mMusicEdit->update();

	for (auto object : mNotesObjects)
	{
		object->Update();
	}
}

void StartMenu::AddNotes(NotesObject* notes)
{
	int myBpm = notes->GetBPMIndex();
	int myLpb = notes->GetLPBIndex();
	int myBpmPage = notes->GetBpmPage();
	auto iter = mNotesObjects.begin();
	for (; iter != mNotesObjects.end(); ++iter)
	{
		if (myBpmPage > (*iter)->GetBpmPage()) { continue; }
		else if (myBpmPage < (*iter)->GetBpmPage()) { break; }
		else if (myBpmPage == (*iter)->GetBpmPage()) {
			if (myBpm > (*iter)->GetBPMIndex()) { continue; }
			else if (myBpm < (*iter)->GetBPMIndex()) { break; }
			else if (myBpm == (*iter)->GetBPMIndex()) {
				if (myLpb <= (*iter)->GetLPBIndex())
				{
					break;
				}
				else
				{
					continue;
				}
			}
		}
	}
	mNotesObjects.insert(iter, notes);
}

void StartMenu::RemoveNotes(NotesObject* note)
{
	auto iter = std::find(mNotesObjects.begin(), mNotesObjects.end(), note);
	if (iter != mNotesObjects.end())
	{
		mNotesObjects.erase(iter);
	}
}