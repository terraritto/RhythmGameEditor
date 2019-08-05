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
	void UpdateMusic(); //long系の音の更新
	void Draw();
	void DrawBpm(); //Bpmの線
	void DrawLpb(); //Lpbの線
	void DrawWidthLine(); //横線
	void DrawMusicLine(); //Musicとの連携線
	void DrawLongNotesObject();//longNoes置いたときの仮描画
	void DrawLineNotes(); //longNotes系の描画すべて

	void MakeTouchNotes(int bpm, int lpb, int lane); //TouchNotesの作成
	void DeleteTouchNotes(int bpm, int lpb, int lane); //TouchNotesの削除
	void MakeLongNotes(int bpm, int lpb, int lane); //LongNotesの生成
	void DeleteLongNotes(int bpm, int lpb, int lane); //LongNotesの削除
	void MakeWallNotesDown(int bpm, int lpb, int lane); //WallNotesDownの生成
	void DeleteWallNotesDown(int bpm, int lpb, int lane); //WallNotesDownの削除
	void MakeWallNotesUp(int bpm, int lpb, int lane); //WallNotesUpの生成
	void DeleteWallNotesUp(int bpm, int lpb, int lane); //WallNotesUpの削除
	void MakeTraceNotesObject(int bpm, int lpb, int lane, bool trace); //TraceNotesObjectの生成
	void DeleteTraceNotesObject(int bpm, int lpb, int lane); //TraceNotesObjectの削除

	void ProcessInput(const struct InputState& state);
	bool CheckLane(int index); //indexと上下レーンの解決用関数
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
	//BPM関連
	const int mBpmLineOffset = 450;
	const int mBpmX = 100;
	const int mBpmY = 200; //座標的な固定位置
	int mBpmValue; //BPM
	int mBpmIndex; //BPM遷移用
	int mBpmMax; //遷移のindex内の最大BPM
	//LPB関連
	int mLpbLineOffset;
	int mLpbValue;
	//横線
	const int mWidthLineX = 100;
	const int mWidthLineY = 200;
	int mWidthDivide = 6 + 1;
	//Musicとの連携
	int mCurrentTime;
	int mTotalTime;
	bool mIsMusic;
	//StartMenu
	class StartMenu* mStartMenu;
	//Notes編集中の物
	NotesState mNotesState;
	NotesColor mNotesColor;
	LaneState mLaneState;
	//long系のノーツのためのもの
	std::vector<NotesInf> mNotesObject;
	std::vector<NotesInf> mWallDownObject;
	std::vector<NotesInf> mWallUpObject;
	std::vector<NotesInf> mTraceNotesObject;
  	int mLongNotesIndex; //long系ノーツの存在数

	int mBackGround; //裏側
};