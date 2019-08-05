#pragma once

class NotesObject
{
public:
	NotesObject(int bpm, int bpmPage, int lpb, int lane, class StartMenu* owner);
	~NotesObject();

	virtual void Draw() = 0;
	virtual void Update() = 0;

	virtual int GetNotesNumber() = 0;
	virtual char GetColorChar() { return 'n'; }
	virtual int GetNotesIndex() { return -1; }
	inline void SetNotesIndex(int index) { mNotesIndex = index; }
	inline auto GetBPMIndex() { return mBpmIndex; }
	inline auto GetBpmPage() { return mBpmPage; }
	inline auto GetLPBIndex() { return mLpbIndex; }
	inline auto GetLaneIndex() { return mLaneIndex; }
	inline void SetIsSound() { mIsSound = true; }
	auto GetSoundHandle() { return mSoundHandle; }
	virtual inline unsigned int GetColorFromChar();
protected:
	int mBpmIndex;
	int mBpmPage;
	int mLpbIndex;
	int mLaneIndex;
	bool mIsSound;
	class StartMenu* mOwner;
	int mNotesIndex;
	int mSoundHandle;
};