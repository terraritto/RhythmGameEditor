#include "../../main_header/Objects/MusicLoadMenu.h"
#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/Music.h"
#include "../../Game.h"
#include <filesystem>

MusicLoadMenu::MusicLoadMenu(Game* game, TextInf& text, StartMenu* startMenu)
	:UIScreen(game)
	,mStartMenu(startMenu)
{
	mBGPos = Pos(text.x, text.y);

	mBackground = LoadGraph("object/Textbox.png");
	SetTitleTextAndPos(text);

	mInputHandle = MakeKeyInput(50,FALSE,FALSE,FALSE);
	SetActiveKeyInput(mInputHandle);
}

MusicLoadMenu::~MusicLoadMenu()
{
	//�t�@�C���̑��ݗL�����m�F
	if (FileExist())
	{
		mStartMenu->SetMusicName(mFileName);
		
		//�t�@�C�������݂���̂ŁAMusic���쐬����
		std::shared_ptr<Music> music = std::make_unique<Music>();
		std::string musicName = "Music\\" + mFileName;
		music->SetMusicHandle(musicName.c_str());
		music->SetTotalMusicTime();
		mStartMenu->SetMusic(std::move(music)); //�n���Ă��
	}

	//inputHandle�̍폜
	DeleteKeyInput(mInputHandle);
}

void MusicLoadMenu::Update(float deltaTIme)
{
	UIScreen::Update(deltaTIme);

	if (CheckKeyInput(mInputHandle) != 0)
	{
		Close();
	}

}

void MusicLoadMenu::Draw()
{
	UIScreen::Draw();
	DrawKeyInputString(mBGPos.x + 5, mBGPos.y + 20, mInputHandle);
	
	/*�Ȃ�S���ꗗ���ł��邯�ǂƂ肠�����̓p�X
	int z = 50;
	int y = 300;
	for (const std::filesystem::directory_entry& x : std::filesystem::directory_iterator("Music\\"))
	{
		std::string ss = x.path().string();
		DrawString(z, y, ss.c_str(), GetColor(0, 0, 255));
		y += 50;
	}
	*/
}

bool MusicLoadMenu::FileExist()
{
	char tempStr[50];
	GetKeyInputString(tempStr, mInputHandle); //���͂��ꂽ�������擾
	mFileName = tempStr; //string�ɗ���
	
	std::string fileDir = "Music\\"; fileDir += mFileName; //�t�@�C���ʒu
	if (std::filesystem::exists(fileDir))
	{
		return true; //���݂���
	}

	return false;//���݂��Ȃ�
}