#pragma once
#include <cmath>
#include <vector>

struct NotesInf
{
	int mBpm;
	int mBpmPage;
	int mLpb;
	int mLane;
	NotesInf(int bpm, int bpmPage, int lpb, int lane)
		: mBpm(bpm)
		, mBpmPage(bpmPage)
		, mLpb(lpb)
		, mLane(lane)
	{

	}
};

class MusicEdit
{
public:
	enum class NotesState
	{
		ETouchNotes,
		ELongNotes,
		EWallNotesDown,
		EWallNotesUp,
		ETraceNotesObject
	};

	enum class NotesColor
	{
		ERed,
		EBlue,
		EGreen
	};

	enum class LaneState
	{
		EUp,
		EDown
	};

	MusicEdit(class StartMenu* startMenu);
	void update();
	void UpdateMusic(); //long�n�̉��̍X�V
	void Draw();
	void DrawBpm(); //Bpm�̐�
	void DrawLpb(); //Lpb�̐�
	void DrawWidthLine(); //����
	void DrawMusicLine(); //Music�Ƃ̘A�g��
	void DrawLongNotesObject();//longNoes�u�����Ƃ��̉��`��
	void DrawLineNotes(); //longNotes�n�̕`�悷�ׂ�

	void MakeTouchNotes(int bpm, int lpb, int lane); //TouchNotes�̍쐬
	void DeleteTouchNotes(int bpm, int lpb, int lane); //TouchNotes�̍폜
	void MakeLongNotes(int bpm, int lpb, int lane); //LongNotes�̐���
	void DeleteLongNotes(int bpm, int lpb, int lane); //LongNotes�̍폜
	void MakeWallNotesDown(int bpm, int lpb, int lane); //WallNotesDown�̐���
	void DeleteWallNotesDown(int bpm, int lpb, int lane); //WallNotesDown�̍폜
	void MakeWallNotesUp(int bpm, int lpb, int lane); //WallNotesUp�̐���
	void DeleteWallNotesUp(int bpm, int lpb, int lane); //WallNotesUp�̍폜
	void MakeTraceNotesObject(int bpm, int lpb, int lane, bool trace); //TraceNotesObject�̐���
	void DeleteTraceNotesObject(int bpm, int lpb, int lane); //TraceNotesObject�̍폜

	void ProcessInput(const struct InputState& state);
	bool CheckLane(int index); //index�Ə㉺���[���̉����p�֐�
	//getter/setter
	void SetBpmValue(int bpm) { mBpmValue = bpm; mBpmMax = (60000 / mBpmValue) * (mBpmIndex * 4 + 4); }
	void SetLpb(int lpb) { mLpbValue = lpb; mLpbLineOffset = mBpmLineOffset / lpb; }
	void SetCurrentTime(int current) { mCurrentTime = current; }
	void SetTotalTime(int total) { mTotalTime = total; }
	void SetLongNotesIndex(int index) { mLongNotesIndex = index; }
	int GetBpmLineOffset() { return mBpmLineOffset; }
	int GetLpbLineOffset() { return mLpbLineOffset; }
	int GetBpmX() { return mBpmX; }
	int GetBpmY() { return mBpmY; }
	int GetWidthDivide() { return mWidthDivide; }
	int GetBpmIndex() { return mBpmIndex; }
	int GetBpmValue() { return mBpmValue; }
	int GetLpbValue() { return mLpbValue; }
	char GetColorChar();
private:
	//BPM�֘A
	const int mBpmLineOffset = 450;
	const int mBpmX = 100;
	const int mBpmY = 200; //���W�I�ȌŒ�ʒu
	int mBpmValue; //BPM
	int mBpmIndex; //BPM�J�ڗp
	int mBpmMax; //�J�ڂ�index���̍ő�BPM
	//LPB�֘A
	int mLpbLineOffset;
	int mLpbValue;
	//����
	const int mWidthLineX = 100;
	const int mWidthLineY = 200;
	int mWidthDivide = 6 + 1;
	//Music�Ƃ̘A�g
	int mCurrentTime;
	int mTotalTime;
	bool mIsMusic;
	//StartMenu
	class StartMenu* mStartMenu;
	//Notes�ҏW���̕�
	NotesState mNotesState;
	NotesColor mNotesColor;
	LaneState mLaneState;
	//long�n�̃m�[�c�̂��߂̂���
	std::vector<NotesInf> mNotesObject;
	std::vector<NotesInf> mWallDownObject;
	std::vector<NotesInf> mWallUpObject;
	std::vector<NotesInf> mTraceNotesObject;
  	int mLongNotesIndex; //long�n�m�[�c�̑��ݐ�

	int mBackGround; //����
};