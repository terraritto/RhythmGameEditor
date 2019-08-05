#include "../../main_header/Objects/WallNotesUp.h"
#include "../../main_header/Objects/NotesObject.h"
#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/MusicEdit.h"

WallNotesUp::WallNotesUp(int bpm, int bpmPage, int lpb, int lane, int notesIndex, StartMenu* owner)
	: NotesObject(bpm, bpmPage, lpb, lane, owner)
{
	mSoundHandle = LoadSoundMem("Music\\touchNotes.wav");
	mNotesIndex = notesIndex;
}

int WallNotesUp::GetNotesNumber()
{
	return 4;
}

int WallNotesUp::GetNotesIndex()
{
	return mNotesIndex;
}

void WallNotesUp::Draw()
{
	if (mOwner->GetMusicEdit()->GetBpmIndex() == mBpmPage && mOwner->GetMusicEdit()->CheckLane(GetNotesNumber()))
	{
		DrawCircle(mOwner->GetMusicEdit()->GetBpmX() + (mOwner->GetMusicEdit()->GetBpmLineOffset() * mBpmIndex)
			+ mOwner->GetMusicEdit()->GetLpbLineOffset() * mLpbIndex,
			mOwner->GetMusicEdit()->GetBpmY() + (700 / mOwner->GetMusicEdit()->GetWidthDivide()) * mLaneIndex
			, 5, GetColorFromChar(), TRUE);
	}
}

void WallNotesUp::Update()
{

}