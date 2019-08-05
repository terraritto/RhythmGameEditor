#include "../../main_header/Objects/Music.h"
#include "../../main_header/Objects/InputSystem.h"
#include "../../main_header/wrapper/Math.h"

void Music::Draw()
{
	DrawLine(10, 110, 100, 110,GetColor(0,255,255)); //âπäyçƒê∂ê¸
	DrawCircle(x, 110, 5, GetColor(255, 0, 0)); //çƒê∂à íuâ~
	DrawFormatString(120, 110, GetColor(0, 0, 255), "%d / %d", mCurrentTime, mTotalMusicTime);
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
		if (mousePos.y <= 110 + 5 && mousePos.y >= 110 - 5 &&
			mousePos.x >= 0 && mousePos.x <= 110
			&& !IsMusicStart()
			)
		{
			x =Math::Clamp(static_cast<int>(mousePos.x),10,100);
			mCurrentTime = mTotalMusicTime * Math::Clamp((x - 10.0) / 90, 0.0, 1.0);
			SetSoundCurrentTime(mCurrentTime, mMusicHandle);
		}
	}
}

void Music::Update()
{
	if (IsMusicStart())
	{
		mCurrentTime = GetSoundCurrentTime(mMusicHandle);
		x = (mCurrentTime / static_cast<float>(mTotalMusicTime) * 90.0) + 10;
	}
}