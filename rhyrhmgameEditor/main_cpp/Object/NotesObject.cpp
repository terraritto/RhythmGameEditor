#include "../../main_header/Objects/NotesObject.h"
#include "../../main_header/Objects/StartMenu.h"

NotesObject::NotesObject(int bpm, int bpmPage, int lpb, int lane, StartMenu* owner)
	: mBpmIndex(bpm)
	, mBpmPage(bpmPage)
	, mLpbIndex(lpb)
	, mLaneIndex(lane)
	, mOwner(owner)
	, mIsSound(false)
{
	mOwner->AddNotes(this);
}

NotesObject::~NotesObject()
{
	mOwner->RemoveNotes(this);
}

inline unsigned int NotesObject::GetColorFromChar()
{
	switch (GetColorChar())
	{
	case 'r':
		return GetColor(255,0,0);
		break;
	case 'g':
		return GetColor(0, 255, 0);
		break;
	case 'b':
		return GetColor(0,0,255);
		break;
	default:
		if (GetNotesNumber() == 3 || GetNotesNumber() == 4)
		{
			return GetColor(255, 0, 255);
		}
		else if (GetNotesNumber() == 5)
		{
			return GetColor(0, 255, 255);
		}
		break;
	}
}