#include "Game.h"
#include "main_header\Actors\Actor.h"
#include "main_header\Objects\UIScreen.h"
#include "main_header\Objects\Font.h"
#include "main_header\Objects\StartMenu.h"
#include "main_header\Objects\InputSystem.h"
#include "main_header\Objects\NotesObject.h"
#include <algorithm>

Game::Game()
	: mGameState(GameState::EGamePlay)
	, mUpdatingActors(false)
	, mTickCount(0)
{

}

bool Game::Initialize()
{
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

	SetGraphMode(1920, 1080, 32);
	//SetGraphMode(768, 1024, 32);

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0) { return false; };

	SetDrawScreen(DX_SCREEN_BACK);

	//initialize input system
	mInputSystem = new InputSystem();
	if (!mInputSystem->Initialize())
	{
		return false;
	}
	
	//SetMouseDispFlag(FALSE);
	
	mTickCount = GetNowCount();
	//ChangeLightTypePoint(VGet(-1000.0f, 1000.0f, -1000.0f),2000.0f,0.0f,0.0006f,0.0f);
	//SetUseLighting(FALSE);

	LoadData();

	unsigned int color = GetColor(0, 0, 255);
	SetKeyInputStringColor(color,color,color,color,color,color,color);

	return true;
}

void Game::Shutdown()
{
	UnLoadData();
	DxLib_End();
}

void Game::RunLoop()
{
	while (mGameState != GameState::EQuit && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	mInputSystem->PrepareForUpdate();

	mInputSystem->Update();
	const InputState& state = mInputSystem->GetState();

	if (state.Keyboard.GetKeyState(KEY_INPUT_ESCAPE) == EReleased)
	{
		mGameState = GameState::EQuit;
		if (mStartMenu->GetMusic())
		{
			mStartMenu->GetMusic()->MusicStop();
		}
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		if (mGameState == GameState::EGamePlay) {
			actor->ProcessInput(state);
		}
	}

	mUIStack.back()->ProcessInput(state);
	/*
	for (auto ui : mUIStack)
	{
		ui->ProcessInput(state);
	}
	*/

	mUpdatingActors = false;
}

void Game::GenerateOutput()
{
	
	for (auto actor : mActors)
	{
		if (actor->GetIsDrawModel<bool>()) {
			auto chara = actor->GetModelHandle();
			if (chara)
			{
				VECTOR pos = actor->GetPosition<VECTOR>();
				pos = Math::VectorTransAxis(pos);
				MV1SetPosition(chara, pos);
				MV1DrawModel(chara);

			}
		}
	}

	//UI draw
	for (auto ui : mUIStack)
	{
		ui->Draw();
	}
}

void Game::UpdateGame()
{
	//Time
	float deltaTime = (GetNowCount() - mTickCount) / 1000.0f;
	if (deltaTime > 0.05f) { deltaTime = 0.05f; }
	mTickCount = GetNowCount();

	// update all actors
	if (mGameState == GameState::EGamePlay)
	{
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->Update(deltaTime);
		}
		mUpdatingActors = false;

		//move any pending actors to mActors
		for (auto pending : mPendingActors)
		{
			pending->ComputeWorldTransform();
			mActors.emplace_back(pending);
		}
		mPendingActors.clear();

		//Add any dead actors to temporary array
		std::vector<Actor*> deadActors;
		for (auto actor : mActors)
		{
			if (actor->GetState<Actor::State>() == Actor::EDead)
			{
				deadActors.emplace_back(actor);
			}
		}

		// Delete dead actors(which removes them from mActors)
		// delete:can remove entity
		for (auto actor : deadActors)
		{
			delete actor;
		}
	}

	//update UI screens
	for (auto ui : mUIStack)
	{
		if (ui->GetState() == UIScreen::EActive)
		{
			ui->Update(deltaTime);
		}
	}

	//Delete any UIScreens that are closed
	auto iter = mUIStack.begin();
	while (iter != mUIStack.end())
	{
		if ((*iter)->GetState() == UIScreen::EClosing)
		{
			delete* iter;
			iter = mUIStack.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void Game::LoadData()
{
	mStartMenu = new StartMenu(this);
}

void Game::UnLoadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}

//Actor
void Game::AddActor(Actor* actor)
{
	//if updating actors, add pending actors
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	//is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		//swap to end of vector and pop off
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	//is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		//swap to end of vector and pop off
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::PushUI(UIScreen* screen)
{
	mUIStack.emplace_back(screen);
}

Font* Game::GetFont(const std::string& fontName)
{
	auto iter = mFonts.find(fontName);
	if (iter != mFonts.end())
	{
		return iter->second;
	}
	else
	{
		Font* font = new Font(this);
		if (font->Load(fontName))
		{
			mFonts.emplace(fontName, font);
		}
		else
		{
			font->Unload();
			delete font;
			font = nullptr;
		}
		return font;
	}
}