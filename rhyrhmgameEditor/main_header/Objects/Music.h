#pragma once
#include <string>
#include "DxLib.h"

class Music
{
public:
	Music()
		: mTotalMusicTime(0)
		, mCurrentTime(0)
		, mMusicHandle(0)
		, x(10)
		, mLineX(310)
		, mLineY(130)
		, mVolumeLineX(760)
		, mVolume(0)
		, mVolumeX(460)
	{

	}
	~Music();

	void Update();
	void Draw();
	void ProcessInput(const struct InputState& state);
	void MusicStart() { PlaySoundMem(mMusicHandle, DX_PLAYTYPE_BACK, FALSE); }
	void MusicStop() { StopSoundMem(mMusicHandle); }
	bool IsMusicStart() { return CheckSoundMem(mMusicHandle); }
	void SetMusicHandle(std::string musicName) { mMusicHandle = LoadSoundMem(musicName.c_str()); }
	void SetTotalMusicTime() { mTotalMusicTime = GetSoundTotalTime(mMusicHandle); }
	auto GetTotalMusicTime() { return mTotalMusicTime; }
	auto GetCurrentMusicTime() { return mCurrentTime; }
private:
	int mTotalMusicTime;
	int mCurrentTime;
	int mMusicHandle;
	int x;

	int mLineX;
	int mLineY;

	int mVolumeLineX;
	int mVolume;
	int mVolumeX;
};