#include "../../main_header/Objects/LongNotes.h"
#include "../../main_header/Objects/NotesObject.h"
#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/MusicEdit.h"

LongNotes::LongNotes(int bpm, int bpmPage, int lpb, int lane, char color, int notesIndex, class StartMenu* owner)
	: NotesObject(bpm, bpmPage, lpb, lane, owner)
	, mColor(color)
{
	mSoundHandle = LoadSoundMem("Music\\touchNotes.wav");
	mNotesIndex = notesIndex;
}

int LongNotes::GetNotesNumber()
{
	return 2;
}

char LongNotes::GetColorChar()
{
	return mColor;
}

int LongNotes::GetNotesIndex()
{
	return mNotesIndex;
}

void LongNotes::Draw()
{
	if (mOwner->GetMusicEdit()->GetBpmIndex() == mBpmPage && mOwner->GetMusicEdit()->CheckLane(GetNotesNumber()))
	{
		DrawCircle(mOwner->GetMusicEdit()->GetBpmX() + (mOwner->GetMusicEdit()->GetBpmLineOffset() * mBpmIndex)
			+ mOwner->GetMusicEdit()->GetLpbLineOffset() * mLpbIndex,
			mOwner->GetMusicEdit()->GetBpmY() + (700 / mOwner->GetMusicEdit()->GetWidthDivide()) * mLaneIndex
			, 5, GetColorFromChar(), TRUE);
	}
}

void LongNotes::Update()
{

}