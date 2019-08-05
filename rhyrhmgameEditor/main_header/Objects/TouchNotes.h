#pragma once
#include "NotesObject.h"

class TouchNotes :public NotesObject
{
public:
	TouchNotes(int bpm, int bpmPage, int lpb, int lane, char color, class StartMenu* owner);

	void Draw() override;
	void Update() override;

	int GetNotesNumber() override;
	char GetColorChar() override;
private:
	char mColor;
};