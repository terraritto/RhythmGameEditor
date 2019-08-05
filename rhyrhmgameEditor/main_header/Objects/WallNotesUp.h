#pragma once
#include "NotesObject.h"

class WallNotesUp : public NotesObject
{
public:
	WallNotesUp(int bpm, int bpmPage, int lpb, int lane, int notesIndex, class StartMenu* owner);
	void Draw() override;
	void Update() override;

	int GetNotesIndex() override;
	int GetNotesNumber() override;
};