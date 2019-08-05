#pragma once
#include "NotesObject.h"

class LongNotes : public NotesObject
{
public:
	LongNotes(int bpm, int bpmPage, int lpb, int lane, char color, int notesIndex, class StartMenu* owner);

	void Draw() override;
	void Update() override;

	int GetNotesIndex() override;
	int GetNotesNumber() override;
	char GetColorChar() override;
private:
	char mColor;
};