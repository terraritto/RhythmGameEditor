#include "../../main_header/Objects/MusicEdit.h"
#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/InputSystem.h"
#include "../../main_header/wrapper/Math.h"
#include "../../main_header/Objects/NotesObject.h"
#include "../../main_header/Objects/TouchNotes.h"
#include "../../main_header/Objects/LongNotes.h"
#include "../../main_header/Objects/WallNotesDown.h"
#include "../../main_header/Objects/WallNotesUp.h"
#include "../../main_header/Objects/TraceNotesObject.h"
#include "DxLib.h"
#include <limits>
#include <algorithm>

MusicEdit::MusicEdit(StartMenu* startMenu)
	: mBpmValue(120)
	, mBpmIndex(0)
	, mBpmMax(0)
	, mLpbLineOffset(0)
	, mLpbValue(4)
	, mStartMenu(startMenu)
	, mCurrentTime(0)
	, mTotalTime(0)
	, mIsMusic(false)
	, mNotesState(NotesState::ETouchNotes)
	, mNotesColor(NotesColor::EBlue)
	, mLaneState(LaneState::EDown)
	, mLongNotesIndex(1)
{
	mBackGround = LoadGraph("object\\GrayBack.png");
	mLpbLineOffset = mBpmLineOffset / mLpbValue;
	mBpmMax = (60000 / mBpmValue) * (mBpmIndex * 4 + 4);
}

void MusicEdit::ProcessInput(const InputState& state)
{
	if (state.Keyboard.GetKeyState(KEY_INPUT_RIGHT) == EPressed)
	{
		mBpmIndex++;
		mBpmMax = (60000 / mBpmValue) * (mBpmIndex * 4 + 4);
	}

	if (state.Keyboard.GetKeyState(KEY_INPUT_LEFT) == EPressed && mBpmIndex > 0)
	{
		mBpmIndex--;
		mBpmMax = (60000 / mBpmValue) * (mBpmIndex * 4 + 4);
	}

	if (state.Keyboard.GetKeyState(KEY_INPUT_UP) == EPressed)
	{
		mWidthDivide = 12 + 1;
		mLaneState = LaneState::EUp;
	}

	if (state.Keyboard.GetKeyState(KEY_INPUT_DOWN) == EPressed)
	{
		mWidthDivide = 6 + 1;
		mLaneState = LaneState::EDown;
	}

	if (state.Keyboard.GetKeyValue(KEY_INPUT_1) == 1)
	{
		mNotesState = NotesState::ETouchNotes;
	}

	if (state.Keyboard.GetKeyValue(KEY_INPUT_2) == 1)
	{
		mNotesState = NotesState::ELongNotes;
	}

	if (state.Keyboard.GetKeyValue(KEY_INPUT_3) == 1)
	{
		mNotesState = NotesState::EWallNotesDown;
	}

	if (state.Keyboard.GetKeyValue(KEY_INPUT_4) == 1)
	{
		mNotesState = NotesState::EWallNotesUp;
	}

	if (state.Keyboard.GetKeyValue(KEY_INPUT_5) == 1)
	{
		mNotesState = NotesState::ETraceNotesObject;
	}

	if (state.Keyboard.GetKeyState(KEY_INPUT_R) == 1)
	{
		mNotesColor = NotesColor::ERed;
	}
	else if (state.Keyboard.GetKeyState(KEY_INPUT_G) == 1)
	{
		mNotesColor = NotesColor::EGreen;
	}
	else if (state.Keyboard.GetKeyState(KEY_INPUT_B) == 1)
	{
		mNotesColor = NotesColor::EBlue;
	}

	if (state.Mouse.GetButtonState(MOUSE_INPUT_LEFT) == ButtonState::EPressed)
	{
		int mouseX = state.Mouse.GetPosition().x, mouseY = state.Mouse.GetPosition().y;
		int x = mBpmX, y = mBpmY, divide = 700 / mWidthDivide;
		int minLpb = INT_MAX, minWidth = INT_MAX, minBpm = 0, distance = INT_MAX;//これが欲しい座標
		for (int i = 0; i < 4; i++)
		{
			for (int j = 1; j <= mLpbValue; j++)
			{
				for (int k = 1; k < mWidthDivide; k++)
				{
					int distanceX = x + mLpbLineOffset * j - mouseX;
					int distanceY = y + divide * k - mouseY;
					int myDistance = std::pow(distanceX, 2) + std::pow(distanceY, 2);
					if (myDistance < distance)
					{
						minLpb = j, minWidth = k, minBpm = i, distance = myDistance;
					}
				}
			}

			x += mBpmLineOffset;
		}

		if (std::sqrt(distance) < 5)
		{
			if (mLaneState == LaneState::EDown) //下レーン
			{
				//DrawCircle(mBpmX + (mBpmLineOffset*minBpm) + mLpbLineOffset * minLpb, y + divide * minWidth, 5, GetColor(0, 255, 0), TRUE);
				switch (mNotesState)
				{
				case NotesState::ETouchNotes:
					MakeTouchNotes(minBpm, minLpb, minWidth);
					break;
				case NotesState::ELongNotes:
					MakeLongNotes(minBpm, minLpb, minWidth);
					break;
				case NotesState::EWallNotesDown:
					MakeWallNotesDown(minBpm, minLpb, minWidth);
					break;
				default:
					break;
				}
			}

			if (mLaneState == LaneState::EUp) //上レーン
			{
				bool input = (state.Keyboard.GetKeyValue(KEY_INPUT_RALT) == 1 || state.Keyboard.GetKeyValue(KEY_INPUT_LALT) == 1);
				switch (mNotesState)
				{
				case NotesState::EWallNotesUp:
					MakeWallNotesUp(minBpm, minLpb, minWidth);
					break;
				case NotesState::ETraceNotesObject:
					MakeTraceNotesObject(minBpm, minLpb, minWidth, input);
					break;
				default:
					break;
				}
			}
		}
	}

	if (state.Mouse.GetButtonState(MOUSE_INPUT_RIGHT) == ButtonState::EPressed)
	{

		int mouseX = state.Mouse.GetPosition().x, mouseY = state.Mouse.GetPosition().y;
		int x = mBpmX, y = mBpmY, divide = 700 / mWidthDivide;
		int minLpb = INT_MAX, minWidth = INT_MAX, minBpm = 0, distance = INT_MAX;//これが欲しい座標
		for (int i = 0; i < 4; i++)
		{
			for (int j = 1; j <= mLpbValue; j++)
			{
				for (int k = 1; k < mWidthDivide; k++)
				{
					int distanceX = x + mLpbLineOffset * j - mouseX;
					int distanceY = y + divide * k - mouseY;
					int myDistance = std::pow(distanceX, 2) + std::pow(distanceY, 2);
					if (myDistance < distance)
					{
						minLpb = j, minWidth = k, minBpm = i, distance = myDistance;
					}
				}
			}

			x += mBpmLineOffset;
		}

		if (std::sqrt(distance) < 5)
		{
			if (mLaneState == LaneState::EDown)
			{
				switch (mNotesState)
				{
				case NotesState::ETouchNotes:
					DeleteTouchNotes(minBpm, minLpb, minWidth);
					break;
				case NotesState::ELongNotes:
					DeleteLongNotes(minBpm, minLpb, minWidth);
					break;
				case NotesState::EWallNotesDown:
					DeleteWallNotesDown(minBpm, minLpb, minWidth);
					break;
				default:
					break;
				}
			}

			if (mLaneState == LaneState::EUp)
			{
				switch (mNotesState)
				{
				case NotesState::EWallNotesUp:
					DeleteWallNotesUp(minBpm, minLpb, minWidth);
					break;
				case NotesState::ETraceNotesObject:
					DeleteTraceNotesObject(minBpm, minLpb, minWidth);
				default:
					break;
				}
			}
		}
	}
}

void MusicEdit::update()
{
	if (mStartMenu->GetMusic())
	{
		mCurrentTime = mStartMenu->GetMusic()->GetCurrentMusicTime();
		mTotalTime = mStartMenu->GetMusic()->GetTotalMusicTime();
		mIsMusic = mStartMenu->GetMusic()->IsMusicStart();
		UpdateMusic();
	}
}

void MusicEdit::UpdateMusic()
{
	if (mLongNotesIndex > 1) {
		for (int i = 1; i < mLongNotesIndex; ++i)//音個数
		{
			std::vector<NotesObject*> longNotes;
			for (auto object : mStartMenu->GetNoteObjects())//指定番号のobjectを取得
			{
				if (object->GetNotesIndex() == i) { longNotes.emplace_back(object); }
			}

			auto startIter = longNotes.begin();
			auto endIter = longNotes.end() - 1;
			int bpmTime = 60000 / mBpmValue;

			int startTime = (*startIter)->GetBpmPage() * bpmTime * 4
				+ bpmTime / mLpbValue * (*startIter)->GetLPBIndex()
				+ (*startIter)->GetBPMIndex() * bpmTime;

			int endTime = (*endIter)->GetBpmPage() * bpmTime * 4
				+ bpmTime / mLpbValue * (*endIter)->GetLPBIndex()
				+ (*endIter)->GetBPMIndex() * bpmTime;
			if (mStartMenu->GetMusic()->IsMusicStart() &&
				mStartMenu->GetMusic()->GetCurrentMusicTime() >= startTime &&
				mStartMenu->GetMusic()->GetCurrentMusicTime() <= endTime)
			{
				if (!CheckSoundMem((*startIter)->GetSoundHandle()))
				{
					PlaySoundMem((*startIter)->GetSoundHandle(), DX_PLAYTYPE_LOOP, TRUE);
				}
			}
			else
			{
				if (CheckSoundMem((*startIter)->GetSoundHandle()))
				{
					StopSoundMem((*startIter)->GetSoundHandle());
				}
			}
		}

	}
}

void MusicEdit::Draw()
{
	//backGround
	DrawExtendGraph(mBpmX, mBpmY-20, mBpmX + 2000, mBpmY +720, mBackGround, TRUE);

	DrawLpb();
	DrawBpm();
	DrawWidthLine();
	DrawMusicLine();
	DrawLongNotesObject();
	DrawLineNotes();
	DrawFormatString(1500, 60, GetColor(0, 0, 255), "Long object num:%d", mLongNotesIndex-1);
}

void MusicEdit::DrawBpm()
{
	int x = mBpmX, y = mBpmY;
	for (int i = 0; i < 5; i++)
	{
		DrawLine(x, y, x, y + 700, GetColor(255, 0, 0));
		DrawFormatString(x - 3, y - 20, GetColor(255, 0, 0), "%d", mBpmIndex*4 + i);
		x += mBpmLineOffset;
	}
	
	//BPMの時間を示す
	DrawFormatString(x - mBpmLineOffset - 20, y + 700, GetColor(255, 0, 0), "%d", mBpmMax);
}

void MusicEdit::DrawLpb()
{
	int x = mBpmX, y = mBpmY;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= mLpbValue - 1; j++)
		{
			DrawLine(x + mLpbLineOffset * j, y, x + mLpbLineOffset * j, y + 700, GetColor(0, 0, 255));
		}
		x += mBpmLineOffset;
	}
}

void MusicEdit::DrawWidthLine()
{
	int x = mWidthLineX, y = mWidthLineY, divide = 700 / mWidthDivide;
	for (int i = 0; i <= mWidthDivide; i++)
	{
		DrawLine(x, y + divide*i, x + mBpmLineOffset*4, y + divide * i, GetColor(0, 0, 255));
	}
}

void MusicEdit::DrawMusicLine()
{
	if (mIsMusic)//音楽が流れてるならlineは動き続け、それを追う感じになる
	{
		int minTime = (60000 / mBpmValue) * (mBpmIndex * 4);
		//nがあってない場合
		if (!(minTime <= mCurrentTime && mCurrentTime < mBpmMax))
		{
			int n = 0;
			while (true)
			{
				int maxTime = (60000 / mBpmValue) * (n * 4 + 4);
				int minTime = (60000 / mBpmValue) * (n * 4);
				if (mCurrentTime >= minTime && maxTime > mCurrentTime)
				{
					mBpmIndex = n; 
					mBpmMax = (60000 / mBpmValue) * (mBpmIndex * 4 + 4);
					break;
				}
				n++;
			}
		}
		//描画
		minTime = (60000 / mBpmValue) * (mBpmIndex * 4);
		int offSetX = (1.0 - (static_cast<float>(mBpmMax) - mCurrentTime) / (mBpmMax - minTime)) * mBpmLineOffset * 4;
		DrawLine(mBpmX+offSetX, mBpmY, mBpmX + offSetX, mBpmY + 700, GetColor(0, 255, 0));
	}
	else
	{
		int minTime = (60000 / mBpmValue) * (mBpmIndex * 4);
		//nがあってる場合描画
		if (minTime <= mCurrentTime && mCurrentTime < mBpmMax)
		{
			int offSetX = (1.0 - (static_cast<float>(mBpmMax) - mCurrentTime) / (mBpmMax - minTime)) * mBpmLineOffset * 4;
			DrawLine(mBpmX + offSetX, mBpmY, mBpmX + offSetX, mBpmY + 700, GetColor(0, 255, 0));
		}

		if (minTime <= mTotalTime && mTotalTime < mBpmMax)
		{
			int offSetX = (1.0 - (static_cast<float>(mBpmMax) - mTotalTime) / (mBpmMax - minTime)) * mBpmLineOffset * 4;
			DrawLine(mBpmX + offSetX, mBpmY, mBpmX + offSetX, mBpmY + 700, GetColor(255, 255, 0));
		}
	}
}

void MusicEdit::DrawLongNotesObject()
{
	if (mLaneState == LaneState::EDown) {
		for (auto object : mNotesObject)
		{
			if (object.mBpmPage == mBpmIndex) {
				DrawCircle(mBpmX + mBpmLineOffset * object.mBpm
					+ mLpbLineOffset * object.mLpb, mBpmY + (700 / mWidthDivide) * object.mLane
					, 5, GetColor(255, 255, 0), TRUE);
			}
		}

		for (auto object : mWallDownObject)
		{
			if (object.mBpmPage == mBpmIndex) {
				DrawCircle(mBpmX + mBpmLineOffset * object.mBpm
					+ mLpbLineOffset * object.mLpb, mBpmY + (700 / mWidthDivide) * object.mLane
					, 5, GetColor(255, 255, 0), TRUE);
			}
		}
	}

	if (mLaneState == LaneState::EUp)
	{
		for (auto object : mWallUpObject)
		{
			if (object.mBpmPage == mBpmIndex)
			{
				DrawCircle(mBpmX + mBpmLineOffset * object.mBpm
					+ mLpbLineOffset * object.mLpb, mBpmY + (700 / mWidthDivide) * object.mLane
					, 5, GetColor(255, 255, 0), TRUE);
			}
		}

		for (auto object : mTraceNotesObject)
		{
			if (object.mBpmPage == mBpmIndex)
			{
				DrawCircle(mBpmX + mBpmLineOffset * object.mBpm
					+ mLpbLineOffset * object.mLpb, mBpmY + (700 / mWidthDivide) * object.mLane
					, 5, GetColor(255, 255, 0), TRUE);
			}
		}
	}

	switch (mNotesColor)
	{
	case NotesColor::ERed:
		DrawString(1650, 0, "SelectColor:Red", GetColor(0, 0, 255));
		break;
	case NotesColor::EGreen:
		DrawString(1650, 0, "SelectColor:Green", GetColor(0, 0, 255));
		break;
	case NotesColor::EBlue:
		DrawString(1650, 0, "SelectColor:Blue", GetColor(0, 0, 255));
		break;
	default:
		break;
	}

	switch (mNotesState)
	{
	case NotesState::ELongNotes:
		DrawString(1650, 20, "SelectState", GetColor(0, 0, 255));
		DrawString(1650, 40, "LongNotes", GetColor(0, 0, 255));
		break;
	case NotesState::ETouchNotes:
		DrawString(1650, 20, "SelectState", GetColor(0, 0, 255));
		DrawString(1650, 40, "TouchNotes", GetColor(0, 0, 255));
		break;
	case NotesState::ETraceNotesObject:
		DrawString(1650, 20, "SelectState", GetColor(0, 0, 255));
		DrawString(1650, 40, "TraceNotes", GetColor(0, 0, 255));
		break;
	case NotesState::EWallNotesDown:
		DrawString(1650, 20, "SelectState", GetColor(0, 0, 255));
		DrawString(1650, 40, "WallNotes Down", GetColor(0, 0, 255));
		break;
	case NotesState::EWallNotesUp:
		DrawString(1650, 20, "SelectState", GetColor(0, 0, 255));
		DrawString(1650, 40, "WallNotes Up", GetColor(0, 0, 255));
		break;
	default:
		break;
	}
}

void MusicEdit::DrawLineNotes()
{
	if (mLongNotesIndex > 1) {
		for (int i = 1; i < mLongNotesIndex; ++i)//描画個数
		{
			std::vector<NotesObject*> longNotes;
			for (auto object : mStartMenu->GetNoteObjects())//指定番号のobjectを取得
			{
				if (object->GetNotesIndex() == i) { longNotes.emplace_back(object); }
			}

			if (!CheckLane((*longNotes.begin())->GetNotesNumber()))
			{
				continue;
			}

			//LongNotes,WallNotesDownの描画
			if ((*longNotes.begin())->GetNotesNumber() == 2 || (*longNotes.begin())->GetNotesNumber() == 3
				|| (*longNotes.begin())->GetNotesNumber() == 4)
			{
				auto startIter = longNotes.begin();
				auto endIter = longNotes.begin() + 1;
				if ((*startIter)->GetBpmPage() == mBpmIndex || (*endIter)->GetBpmPage() == mBpmIndex)
				{
					if ((*startIter)->GetBpmPage() == (*endIter)->GetBpmPage()) { //page一致:start end
						DrawLine(mBpmX + mBpmLineOffset * (*startIter)->GetBPMIndex()
							+ mLpbLineOffset * (*startIter)->GetLPBIndex(), //x1
							mBpmY + (700 / mWidthDivide) * (*startIter)->GetLaneIndex(),//y1
							mBpmX + mBpmLineOffset * (*endIter)->GetBPMIndex()
							+ mLpbLineOffset * (*endIter)->GetLPBIndex(),//x2
							mBpmY + (700 / mWidthDivide) * (*endIter)->GetLaneIndex(),//y2
							(*startIter)->GetColorFromChar(), 3);
					}
					else if ((*endIter)->GetBpmPage() == mBpmIndex) //page一致:end
					{
						DrawLine(mBpmX, //x1
							mBpmY + (700 / mWidthDivide) * (*endIter)->GetLaneIndex(),//y1
							mBpmX + mBpmLineOffset * (*endIter)->GetBPMIndex()
							+ mLpbLineOffset * (*endIter)->GetLPBIndex(),//x2
							mBpmY + (700 / mWidthDivide) * (*endIter)->GetLaneIndex(),//y2
							(*startIter)->GetColorFromChar(), 3);
					}
					else //page一致:start
					{
						DrawLine(mBpmX + mBpmLineOffset * (*startIter)->GetBPMIndex()
							+ mLpbLineOffset * (*startIter)->GetLPBIndex(), //x1
							mBpmY + (700 / mWidthDivide) * (*startIter)->GetLaneIndex(),//y1
							mBpmX + mBpmLineOffset * 4,//x2
							mBpmY + (700 / mWidthDivide) * (*startIter)->GetLaneIndex(),//y2
							(*startIter)->GetColorFromChar(), 3);
					}
				}	

				if ((*startIter)->GetBpmPage() < mBpmIndex && mBpmIndex < (*endIter)->GetBpmPage())//何も置かれてないpage
				{
					DrawLine(mBpmX, //x1
						mBpmY + (700 / mWidthDivide) * (*startIter)->GetLaneIndex(),//y1
						mBpmX + mBpmLineOffset * 4,//x2
						mBpmY + (700 / mWidthDivide) * (*startIter)->GetLaneIndex(),//y2
						(*startIter)->GetColorFromChar(), 3);
				}
			}

			if ((*longNotes.begin())->GetNotesNumber() == 5) //traceNotesはもっとめんどくさい線になる
			{
				for (auto iter = longNotes.begin(); iter != (longNotes.end() - 1); ++iter)
				{
					auto startIter = iter;
					auto endIter = iter + 1;
					int bpmPages = (*endIter)->GetBpmPage() - (*startIter)->GetBpmPage() - 1;
					bpmPages = bpmPages >= 0 ? bpmPages : 0;

					int x1 = mBpmLineOffset * (*startIter)->GetBPMIndex()
						+ mLpbLineOffset * (*startIter)->GetLPBIndex();
					int y1 = (700 / mWidthDivide) * (*startIter)->GetLaneIndex();
					int xStart = mBpmLineOffset * 4;
					int xEnd = xStart + bpmPages * mBpmLineOffset * 4;
					int x2 = xEnd + mBpmLineOffset * (*endIter)->GetBPMIndex()
						+ mLpbLineOffset * (*endIter)->GetLPBIndex();
					int y2 = (700 / mWidthDivide) * (*endIter)->GetLaneIndex();

					if ((*startIter)->GetBpmPage() == mBpmIndex || (*endIter)->GetBpmPage() == mBpmIndex)
					{
						if ((*startIter)->GetBpmPage() == (*endIter)->GetBpmPage()) { //page一致:start end
							DrawLine(mBpmX + x1, //x1
								mBpmY + y1,//y1
								mBpmX + mBpmLineOffset * (*endIter)->GetBPMIndex()
								+ mLpbLineOffset * (*endIter)->GetLPBIndex(),//x2
								mBpmY + (700 / mWidthDivide) * (*endIter)->GetLaneIndex(),//y2
								(*endIter)->GetColorFromChar(), 3);
						}
						else if ((*endIter)->GetBpmPage() == mBpmIndex) //page一致:end
						{
							int yEnd = (y2 - y1) / static_cast<float>((x2 - x1)) * (xEnd - x1) + y1;
							DrawLine(mBpmX, //x1
								mBpmY + yEnd,//y1
								mBpmX + +mBpmLineOffset * (*endIter)->GetBPMIndex()
								+ mLpbLineOffset * (*endIter)->GetLPBIndex(),//x2
								mBpmY + (700 / mWidthDivide) * (*endIter)->GetLaneIndex(),//y2
								(*startIter)->GetColorFromChar(), 3);
						}
						else //page一致:start
						{
							int yStart = (y2 - y1) / static_cast<float>((x2 - x1)) * (xStart - x1) + y1;
							DrawLine(mBpmX + mBpmLineOffset * (*startIter)->GetBPMIndex()
								+ mLpbLineOffset * (*startIter)->GetLPBIndex(), //x1
								mBpmY + (700 / mWidthDivide) * (*startIter)->GetLaneIndex(),//y1
								mBpmX + mBpmLineOffset * 4,//x2
								mBpmY + yStart//y2
								, (*startIter)->GetColorFromChar(), 3);
						}
					}

					if ((*startIter)->GetBpmPage() < mBpmIndex && mBpmIndex < (*endIter)->GetBpmPage())//何も置かれてないpage
					{
						int xOffset = (mBpmIndex - (*startIter)->GetBpmPage() - 1)
							* mBpmLineOffset * 4;
						int yStart = (y2 - y1) / static_cast<float>((x2 - x1)) *
							(xStart + xOffset - x1) + y1;
						int yEnd = (y2 - y1) / static_cast<float>((x2 - x1)) *
							(xStart + xOffset + mBpmLineOffset * 4 - x1) + y1;
						DrawLine(mBpmX, //x1
							mBpmY + yStart,//y1
							mBpmX + mBpmLineOffset * 4,//x2
							mBpmY + yEnd,//y2
							(*startIter)->GetColorFromChar(), 3);
					}
				}
			}
		}
	}
}

void MusicEdit::MakeTouchNotes(int bpm, int lpb, int lane)
{
	for (auto object : mStartMenu->GetNoteObjects())
	{
		if (bpm == object->GetBPMIndex() && lpb == object->GetLPBIndex() &&
			lane == object->GetLaneIndex() && mBpmIndex == object->GetBpmPage()
			&& CheckLane(object->GetNotesNumber())
			)
		{
			return;
		}
	}

	char cl = GetColorChar();

	new TouchNotes(bpm, mBpmIndex, lpb, lane, cl, mStartMenu);
}

void MusicEdit::MakeLongNotes(int bpm, int lpb, int lane)
{
	for (auto object : mStartMenu->GetNoteObjects())
	{
		if (bpm == object->GetBPMIndex() && lpb == object->GetLPBIndex() &&
			lane == object->GetLaneIndex() && mBpmIndex == object->GetBpmPage()
			&& CheckLane(object->GetNotesNumber())
			)
		{
			return;
		}
	}

	for (auto object : mNotesObject)
	{
		//オブジェクトが存在したらそれはできないのでだめ
		if (bpm == object.mBpm && mBpmIndex == object.mBpmPage && lpb == object.mLpb)
		{
			return;
		}
	}
	
	mNotesObject.emplace_back(NotesInf(bpm, mBpmIndex,lpb,lane));

	if (mNotesObject.size() == 2) //連続のノーツなので2つ
	{
		char cl = GetColorChar();

		//ソートして最小とする
		std::sort(mNotesObject.begin(), mNotesObject.end(),
			[](const NotesInf & a, const NotesInf & b)
			{
				if (a.mBpmPage < b.mBpmPage)
				{
					return true;
				}
				else if (a.mBpmPage > b.mBpmPage)
				{
					return false;
				}
				else if (a.mBpm < b.mBpm)
				{
					return true;
				}
				else if (a.mBpm == b.mBpm)
				{
					if (a.mLpb < b.mLpb)
					{
						return true;
					}
				}
				return false;
					//((a.mBpm < b.mBpm) && (a.mLpb < b.mLpb) && (a.mBpmPage <= b.mBpmPage));
			}
		);

		//laneは一つに確定 ここ変える
		int lanePos = mNotesObject.begin()->mLane;

		//生成
		for (auto object : mNotesObject)
		{
			new LongNotes(object.mBpm, object.mBpmPage, object.mLpb,
				lanePos, cl, mLongNotesIndex, mStartMenu);
		}
		//LongObjectが生成される
		mLongNotesIndex++;
		//生成されたので削除
		mNotesObject.clear();
	}
}

void MusicEdit::MakeWallNotesDown(int bpm, int lpb, int lane)
{
	for (auto object : mStartMenu->GetNoteObjects())
	{
		if ((bpm == object->GetBPMIndex() && lpb == object->GetLPBIndex() &&
			lane == object->GetLaneIndex() && mBpmIndex == object->GetBpmPage())
			&& CheckLane(object->GetNotesNumber())
			)
		{
			return;
		}
	}

	for (auto object : mWallDownObject)
	{
		//オブジェクトが存在したらそれはできないのでだめ
		if (bpm == object.mBpm && mBpmIndex == object.mBpmPage && lpb == object.mLpb)
		{
			return;
		}
	}

	mWallDownObject.emplace_back(NotesInf(bpm, mBpmIndex, lpb, lane));

	if (mWallDownObject.size() == 2) //連続のノーツなので2つ
	{
		//ソートして最小とする
		std::sort(mWallDownObject.begin(), mWallDownObject.end(),
			[](const NotesInf & a, const NotesInf & b)
			{
				if (a.mBpmPage < b.mBpmPage)
				{
					return true;
				}
				else if (a.mBpmPage > b.mBpmPage)
				{
					return false;
				}
				else if (a.mBpm < b.mBpm)
				{
					return true;
				}
				else if (a.mBpm == b.mBpm)
				{
					if (a.mLpb < b.mLpb)
					{
						return true;
					}
				}
				return false;
				//((a.mBpm < b.mBpm) && (a.mLpb < b.mLpb) && (a.mBpmPage <= b.mBpmPage));
			}
		);

		//laneは一つに確定 ここ変える
		int lanePos = mWallDownObject.begin()->mLane;

		//生成
		for (auto object : mWallDownObject)
		{
			new WallNotesDown(object.mBpm, object.mBpmPage, object.mLpb,
				lanePos, mLongNotesIndex, mStartMenu);
		}
		//LongObjectが生成される
		mLongNotesIndex++;
		//生成されたので削除
		mWallDownObject.clear();
	}
}

void MusicEdit::MakeWallNotesUp(int bpm, int lpb, int lane)
{
	for (auto object : mStartMenu->GetNoteObjects())
	{
		if ((bpm == object->GetBPMIndex() && lpb == object->GetLPBIndex() &&
			lane == object->GetLaneIndex() && mBpmIndex == object->GetBpmPage())
			&& CheckLane(object->GetNotesNumber())
			)
		{
			return;
		}
	}

	for (auto object : mWallUpObject)
	{
		//オブジェクトが存在したらそれはできないのでだめ
		if (bpm == object.mBpm && mBpmIndex == object.mBpmPage && lpb == object.mLpb)
		{
			return;
		}
	}

	mWallUpObject.emplace_back(NotesInf(bpm, mBpmIndex, lpb, lane));

	if (mWallUpObject.size() == 2) //連続のノーツなので2つ
	{
		//ソートして最小とする
		std::sort(mWallUpObject.begin(), mWallUpObject.end(),
			[](const NotesInf & a, const NotesInf & b)
			{
				if (a.mBpmPage < b.mBpmPage)
				{
					return true;
				}
				else if (a.mBpmPage > b.mBpmPage)
				{
					return false;
				}
				else if (a.mBpm < b.mBpm)
				{
					return true;
				}
				else if (a.mBpm == b.mBpm)
				{
					if (a.mLpb < b.mLpb)
					{
						return true;
					}
				}
				return false;
				//((a.mBpm < b.mBpm) && (a.mLpb < b.mLpb) && (a.mBpmPage <= b.mBpmPage));
			}
		);

		//laneは一つに確定 ここ変える
		int lanePos = mWallUpObject.begin()->mLane;

		//生成
		for (auto object : mWallUpObject)
		{
			new WallNotesUp(object.mBpm, object.mBpmPage, object.mLpb,
				lanePos, mLongNotesIndex, mStartMenu);
		}
		//LongObjectが生成される
		mLongNotesIndex++;
		//生成されたので削除
		mWallUpObject.clear();
	}
}

void MusicEdit::MakeTraceNotesObject(int bpm, int lpb, int lane, bool trace)
{
	if (trace) //traceがtrueならobjectを生成
	{
		//ソートして最小とする
		std::sort(mTraceNotesObject.begin(), mTraceNotesObject.end(),
			[](const NotesInf & a, const NotesInf & b)
			{
				if (a.mBpmPage < b.mBpmPage)
				{
					return true;
				}
				else if (a.mBpmPage > b.mBpmPage)
				{
					return false;
				}
				else if (a.mBpm < b.mBpm)
				{
					return true;
				}
				else if (a.mBpm == b.mBpm)
				{
					if (a.mLpb < b.mLpb)
					{
						return true;
					}
				}
				return false;
				//((a.mBpm < b.mBpm) && (a.mLpb < b.mLpb) && (a.mBpmPage <= b.mBpmPage));
			}
		);

		//生成
		for (auto object : mTraceNotesObject)
		{
			new TraceNotesObject(object.mBpm, object.mBpmPage, object.mLpb,
				object.mLane, mLongNotesIndex, mStartMenu);
		}
		//LongObjectが生成される
		mLongNotesIndex++;
		//生成されたので削除
		mTraceNotesObject.clear();
		
		return; //生成処理はこれで終わりなのでここで返る
	}

	for (auto object : mStartMenu->GetNoteObjects())
	{
		if ((bpm == object->GetBPMIndex() && lpb == object->GetLPBIndex() &&
			lane == object->GetLaneIndex() && mBpmIndex == object->GetBpmPage())
			&& CheckLane(object->GetNotesNumber())
			)
		{
			return;
		}
	}

	for (auto object : mTraceNotesObject)
	{
		//オブジェクトが存在したらそれはできないのでだめ
		if (bpm == object.mBpm && mBpmIndex == object.mBpmPage && lpb == object.mLpb)
		{
			return;
		}
	}

	mTraceNotesObject.emplace_back(NotesInf(bpm, mBpmIndex, lpb, lane));
}

void MusicEdit::DeleteTouchNotes(int bpm, int lpb, int lane)
{
	for (auto object : mStartMenu->GetNoteObjects())
	{
		if (bpm == object->GetBPMIndex() && lpb == object->GetLPBIndex() &&
			lane == object->GetLaneIndex() && mBpmIndex == object->GetBpmPage()
			&& object->GetNotesNumber() == 1
			)
		{
			delete object;
			return;
		}
	}
}

void MusicEdit::DeleteLongNotes(int bpm, int lpb, int lane)
{
	//最初は仮LongNotesの方の削除
	for (auto object : mNotesObject)
	{
		if (bpm == object.mBpm && lpb == object.mLpb &&
			lane == object.mLane && mBpmIndex == object.mBpmPage)
		{
			mNotesObject.clear();
			return;
		}
	}

	int index = -1;
	for (auto object : mStartMenu->GetNoteObjects()) //消すインデックスが存在するか決める
	{
		if (bpm == object->GetBPMIndex() && lpb == object->GetLPBIndex() &&
			lane == object->GetLaneIndex() && mBpmIndex == object->GetBpmPage()
			&& object->GetNotesNumber() == 2)
		{
			index = object->GetNotesIndex();
		}
	}
	if (index == -1) { return; } //これは存在しないので抜ける

	while (true) //indexが同じならそれは同じノーツなので削除
	{
		int n = 0;
		for (auto object : mStartMenu->GetNoteObjects())
		{
			if (object->GetNotesIndex() == index)
			{
				delete object;
				continue;
			}
			n++;
		}
		if (n == mStartMenu->GetNoteObjects().size()) { break; }
	}

	//indexを下げて合わせる
	for (auto object : mStartMenu->GetNoteObjects())
	{
		if (object->GetNotesIndex() > index)
		{
			object->SetNotesIndex(object->GetNotesIndex() - 1);
		}
	}

	//全体のindexを下げる
	mLongNotesIndex--;
}

void MusicEdit::DeleteWallNotesDown(int bpm, int lpb, int lane)
{
	//最初は仮LongNotesの方の削除
	for (auto object : mWallDownObject)
	{
		if (bpm == object.mBpm && lpb == object.mLpb &&
			lane == object.mLane && mBpmIndex == object.mBpmPage)
		{
			mWallDownObject.clear();
			return;
		}
	}

	int index = -1;
	for (auto object : mStartMenu->GetNoteObjects()) //消すインデックスが存在するか決める
	{
		if (bpm == object->GetBPMIndex() && lpb == object->GetLPBIndex() &&
			lane == object->GetLaneIndex() && mBpmIndex == object->GetBpmPage()
			&& object->GetNotesNumber() == 3)
		{
			index = object->GetNotesIndex();
		}
	}
	if (index == -1) { return; } //これは存在しないので抜ける

	while (true) //indexが同じならそれは同じノーツなので削除
	{
		int n = 0;
		for (auto object : mStartMenu->GetNoteObjects())
		{
			if (object->GetNotesIndex() == index)
			{
				delete object;
				continue;
			}
			n++;
		}
		if (n == mStartMenu->GetNoteObjects().size()) { break; }
	}

	//indexを下げて合わせる
	for (auto object : mStartMenu->GetNoteObjects())
	{
		if (object->GetNotesIndex() > index)
		{
			object->SetNotesIndex(object->GetNotesIndex() - 1);
		}
	}

	//全体のindexを下げる
	mLongNotesIndex--;
}

void MusicEdit::DeleteWallNotesUp(int bpm, int lpb, int lane)
{
	//最初は仮LongNotesの方の削除
	for (auto object : mTraceNotesObject)
	{
		if (bpm == object.mBpm && lpb == object.mLpb &&
			lane == object.mLane && mBpmIndex == object.mBpmPage)
		{
			mTraceNotesObject.clear();
			return;
		}
	}

	int index = -1;
	for (auto object : mStartMenu->GetNoteObjects()) //消すインデックスが存在するか決める
	{
		if (bpm == object->GetBPMIndex() && lpb == object->GetLPBIndex() &&
			lane == object->GetLaneIndex() && mBpmIndex == object->GetBpmPage()
			&& object->GetNotesNumber() == 4)
		{
			index = object->GetNotesIndex();
		}
	}
	if (index == -1) { return; } //これは存在しないので抜ける

	while (true) //indexが同じならそれは同じノーツなので削除
	{
		int n = 0;
		for (auto object : mStartMenu->GetNoteObjects())
		{
			if (object->GetNotesIndex() == index)
			{
				delete object;
				continue;
			}
			n++;
		}
		if (n == mStartMenu->GetNoteObjects().size()) { break; }
	}

	//indexを下げて合わせる
	for (auto object : mStartMenu->GetNoteObjects())
	{
		if (object->GetNotesIndex() > index)
		{
			object->SetNotesIndex(object->GetNotesIndex() - 1);
		}
	}

	//全体のindexを下げる
	mLongNotesIndex--;
}

void MusicEdit::DeleteTraceNotesObject(int bpm, int lpb, int lane)
{
	//最初は仮LongNotesの方の削除
	for (auto object : mTraceNotesObject)
	{
		if (bpm == object.mBpm && lpb == object.mLpb &&
			lane == object.mLane && mBpmIndex == object.mBpmPage)
		{
			mTraceNotesObject.clear();
			return;
		}
	}

	int index = -1;
	for (auto object : mStartMenu->GetNoteObjects()) //消すインデックスが存在するか決める
	{
		if (bpm == object->GetBPMIndex() && lpb == object->GetLPBIndex() &&
			lane == object->GetLaneIndex() && mBpmIndex == object->GetBpmPage()
			&& object->GetNotesNumber() == 5)
		{
			index = object->GetNotesIndex();
		}
	}
	if (index == -1) { return; } //これは存在しないので抜ける

	while (true) //indexが同じならそれは同じノーツなので削除
	{
		int n = 0;
		for (auto object : mStartMenu->GetNoteObjects())
		{
			if (object->GetNotesIndex() == index)
			{
				delete object;
				continue;
			}
			n++;
		}
		if (n == mStartMenu->GetNoteObjects().size()) { break; }
	}

	//indexを下げて合わせる
	for (auto object : mStartMenu->GetNoteObjects())
	{
		if (object->GetNotesIndex() > index)
		{
			object->SetNotesIndex(object->GetNotesIndex() - 1);
		}
	}

	//全体のindexを下げる
	mLongNotesIndex--;
}

char MusicEdit::GetColorChar()
{
	char cl;
	switch (mNotesColor)
	{
	case NotesColor::ERed:
		cl = 'r';
		break;
	case NotesColor::EGreen:
		cl = 'g';
		break;
	case NotesColor::EBlue:
		cl = 'b';
		break;
	}

	return cl;
}

bool MusicEdit::CheckLane(int index)
{
	if (index == 1 && mLaneState == LaneState::EDown)
	{
		return true;
	}
	if (index == 2 && mLaneState == LaneState::EDown)
	{
		return true;
	}
	if (index == 3 && mLaneState == LaneState::EDown)
	{
		return true;
	}
	if (index == 4 && mLaneState == LaneState::EUp)
	{
		return true;
	}
	if (index == 5 && mLaneState == LaneState::EUp)
	{
		return true;
	}

	return false;
}