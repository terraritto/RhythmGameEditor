#include "../../main_header/Objects/TouchNotes.h"
#include "../../main_header/Objects/NotesObject.h"
#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/MusicEdit.h"

TouchNotes::TouchNotes(int bpm, int bpmPage, int lpb, int lane, char color, StartMenu* owner)
	: NotesObject(bpm, bpmPage, lpb, lane, owner)
	, mColor(color)
{
	mSoundHandle = LoadSoundMem("Music\\touchNotes.wav");
}

int TouchNotes::GetNotesNumber()
{
	return 1;
}

char TouchNotes::GetColorChar()
{
	return mColor;
}

void TouchNotes::Draw()
{
	if (mOwner->GetMusicEdit()->GetBpmIndex() == mBpmPage && mOwner->GetMusicEdit()->CheckLane(GetNotesNumber()))
	{
		unsigned int col;
		switch (mColor)
		{
		case 'r':
			col = GetColor(255, 0, 0);
			break;
		case 'g':
			col = GetColor(0, 255, 0);
			break;
		case 'b':
			col = GetColor(0, 0, 255);
		}

		DrawCircle(mOwner->GetMusicEdit()->GetBpmX() + (mOwner->GetMusicEdit()->GetBpmLineOffset() * mBpmIndex)
			+ mOwner->GetMusicEdit()->GetLpbLineOffset() * mLpbIndex,
			mOwner->GetMusicEdit()->GetBpmY() + (700 / mOwner->GetMusicEdit()->GetWidthDivide()) * mLaneIndex
			, 5, col, TRUE);
	}
}

void TouchNotes::Update()
{
	int bpmTime = 60000 / mOwner->GetMusicEdit()->GetBpmValue();
	int time = mBpmPage * bpmTime * 4
		+ bpmTime/mOwner->GetMusicEdit()->GetLpbValue() * mLpbIndex
		+ mBpmIndex * bpmTime;
	if (mOwner->GetMusic() && mIsSound == true)
	{
		if (mOwner->GetMusic()->IsMusicStart() && mOwner->GetMusic()->GetCurrentMusicTime() >= time)
		{
			PlaySoundMem(mSoundHandle, DX_PLAYTYPE_BACK, FALSE);
			mIsSound = false;
		}
	}
}