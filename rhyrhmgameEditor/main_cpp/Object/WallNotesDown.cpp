#include "../../main_header/Objects/WallNotesDown.h"
#include "../../main_header/Objects/NotesObject.h"
#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/MusicEdit.h"

WallNotesDown::WallNotesDown(int bpm, int bpmPage, int lpb, int lane, int notesIndex, class StartMenu* owner)
	: NotesObject(bpm, bpmPage, lpb, lane, owner)
{
	mSoundHandle = LoadSoundMem("Music\\touchNotes.wav");
	mNotesIndex = notesIndex;
}

int WallNotesDown::GetNotesNumber()
{
	return 3;
}

int WallNotesDown::GetNotesIndex()
{
	return mNotesIndex;
}

void WallNotesDown::Draw()
{
	if (mOwner->GetMusicEdit()->GetBpmIndex() == mBpmPage && mOwner->GetMusicEdit()->CheckLane(GetNotesNumber()))
	{
		DrawCircle(mOwner->GetMusicEdit()->GetBpmX() + (mOwner->GetMusicEdit()->GetBpmLineOffset() * mBpmIndex)
			+ mOwner->GetMusicEdit()->GetLpbLineOffset() * mLpbIndex,
			mOwner->GetMusicEdit()->GetBpmY() + (700 / mOwner->GetMusicEdit()->GetWidthDivide()) * mLaneIndex
			, 5, GetColorFromChar(), TRUE);
	}
}

void WallNotesDown::Update()
{

}