#pragma once
#include "UIScreen.h"
#include "Music.h"
#include <memory>

class StartMenu : public UIScreen
{
public:
	StartMenu(class Game* game);
	~StartMenu();
	void Draw() override;
	void ProcessInput(const struct InputState& state) override;
	void Update(float deltaTime) override;

	void AddNotes(class NotesObject* note);
	void RemoveNotes(class NotesObject* note);

	void SetMusicName(std::string musicName) { mMusicName = musicName; }
	auto GetMusicName() { return mMusicName; }
	void SetFileName(std::string fileName) { mFileName = fileName; }
	auto GetFileName() const { return mFileName; }
	void SetMusic(std::shared_ptr<Music> music) { mMusic = move(music); }
	auto GetMusic() { return mMusic.get(); }
	auto GetMusicEdit() { return mMusicEdit.get(); }
	auto GetNoteObjects() { return mNotesObjects; }
	void SetBPM(int bpm) { mBpm = bpm; }
	int GetBPM() const { return mBpm; }
	void SetLPB(int lpb) { mLpb = lpb; }
	int GetLPB() const { return mLpb; }
private:
	TextInf mExplainInput;
	TextInf mExplainBpm;
	TextInf mExplainLpb;
	TextInf mExplainNewSave;
	TextInf mExplainFileLoad;
	std::string mMusicName;
	std::string mFileName;

	std::shared_ptr<Music> mMusic;
	std::shared_ptr<class MusicEdit> mMusicEdit;

	int mBpm;
	int mLpb;

	std::vector<class NotesObject*> mNotesObjects;

	//textbox—p
	int mTextBox;
	Pos mTextBoxPos;
};