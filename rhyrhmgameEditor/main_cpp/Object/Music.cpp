#include "../../main_header/Objects/Music.h"
#include "../../main_header/Objects/InputSystem.h"
#include "../../main_header/wrapper/Math.h"

void Music::Draw()
{
	DrawLine(10, mLineY, mLineX-10, mLineY,GetColor(0,255,255)); //音楽再生線
	DrawCircle(x, mLineY, 5, GetColor(255, 0, 0)); //再生位置円
	DrawFormatString(mLineX + 10, mLineY, GetColor(0, 0, 255), "%d / %d", mCurrentTime, mTotalMusicTime);

	DrawLine(460, mLineY, mVolumeLineX - 10, mLineY, GetColor(0, 255, 255)); //音楽再生線
	DrawCircle(mVolumeX, mLineY, 5, GetColor(255, 0, 0)); //再生位置円
	DrawFormatString(mVolumeLineX + 10, mLineY, GetColor(0, 0, 255), "%d / %d", mVolume, 255);
}

Music::~Music()
{
	StopSoundMem(mMusicHandle);
	DeleteSoundMem(mMusicHandle);
}

void Music::ProcessInput(const InputState& state)
{
	if (state.Mouse.GetButtonState(MOUSE_INPUT_LEFT))
	{
		Position mousePos = state.Mouse.GetPosition();
		if (mousePos.y <= mLineY + 10 && mousePos.y >= mLineY - 10 &&
			mousePos.x >= 0 && mousePos.x <= mLineX
			&& !IsMusicStart()
			)
		{
			x =Math::Clamp(static_cast<int>(mousePos.x),10,mLineX - 10);
			mCurrentTime = mTotalMusicTime * Math::Clamp((x - 10.0) / (mLineX - 20), 0.0, 1.0);
			SetSoundCurrentTime(mCurrentTime, mMusicHandle);
		}

		if (mousePos.y <= mLineY + 10 && mousePos.y >= mLineY - 10 &&
			mousePos.x >= 450 && mousePos.x <= mVolumeLineX)
		{
			mVolumeX = Math::Clamp(static_cast<int>(mousePos.x), 460, mVolumeLineX - 10);
			mVolume = 255 * Math::Clamp((mVolumeX - 460.0) / (mVolumeLineX - 10 - 460), 0.0, 1.0);
			ChangeVolumeSoundMem(mVolume, mMusicHandle);
		}
	}
}

void Music::Update()
{
	if (IsMusicStart())
	{
		mCurrentTime = GetSoundCurrentTime(mMusicHandle);
		x = (mCurrentTime / static_cast<float>(mTotalMusicTime) * (mLineX-20)) + 10;
	}
}