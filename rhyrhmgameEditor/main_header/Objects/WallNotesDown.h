#pragma once
#include "NotesObject.h"

class WallNotesDown : public NotesObject
{
public:
	WallNotesDown(int bpm, int bpmPage, int lpb, int lane, int notesIndex, class StartMenu* owner);
	void Draw() override;
	void Update() override;

	int GetNotesIndex() override;
	int GetNotesNumber() override;
};