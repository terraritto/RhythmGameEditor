#include "../../main_header/Objects/TraceNotesObject.h"
#include "../../main_header/Objects/NotesObject.h"
#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/MusicEdit.h"

TraceNotesObject::TraceNotesObject(int bpm, int bpmPage, int lpb, int lane, int notesIndex, class StartMenu* owner)
	: NotesObject(bpm, bpmPage, lpb, lane, owner)
{
	mSoundHandle = LoadSoundMem("Music\\touchNotes.wav");
	mNotesIndex = notesIndex;
}

int TraceNotesObject::GetNotesNumber()
{
	return 5;
}

int TraceNotesObject::GetNotesIndex()
{
	return mNotesIndex;
}

void TraceNotesObject::Draw()
{
	if (mOwner->GetMusicEdit()->GetBpmIndex() == mBpmPage && mOwner->GetMusicEdit()->CheckLane(GetNotesNumber()))
	{
		DrawCircle(mOwner->GetMusicEdit()->GetBpmX() + (mOwner->GetMusicEdit()->GetBpmLineOffset() * mBpmIndex)
			+ mOwner->GetMusicEdit()->GetLpbLineOffset() * mLpbIndex,
			mOwner->GetMusicEdit()->GetBpmY() + (700 / mOwner->GetMusicEdit()->GetWidthDivide()) * mLaneIndex
			, 5, GetColorFromChar(), TRUE);
	}
}

void TraceNotesObject::Update()
{

}