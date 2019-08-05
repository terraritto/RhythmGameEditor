#include "../../main_header/Objects/TextLoadMenu.h"
#include "../../main_header/Objects/StartMenu.h"
#include "../../main_header/Objects/Music.h"
#include "../../main_header/Objects/MusicEdit.h"
#include "../../main_header/Objects/TouchNotes.h"
#include "../../main_header/Objects/LongNotes.h"
#include "../../main_header/Objects/WallNotesDown.h"
#include "../../main_header/Objects/WallNotesUp.h"
#include "../../main_header/Objects/TraceNotesObject.h"
#include "../../Game.h"
#include <filesystem>
#include <fstream>
#include <sstream>

TextLoadMenu::TextLoadMenu(Game* game, TextInf& text, StartMenu* startMenu)
	:UIScreen(game)
	, mStartMenu(startMenu)
{
	mBGPos = Pos(text.x, text.y);

	mBackground = LoadGraph("object/Textbox.png");
	SetTitleTextAndPos(text);

	mInputHandle = MakeKeyInput(50, FALSE, FALSE, FALSE);
	SetActiveKeyInput(mInputHandle);
}

TextLoadMenu::~TextLoadMenu()
{
	//�t�@�C���̑��ݗL�����m�F
	if (FileExist())
	{
		FileRead();
	}

	//inputHandle�̍폜
	DeleteKeyInput(mInputHandle);
}

void TextLoadMenu::Update(float deltaTIme)
{
	UIScreen::Update(deltaTIme);

	if (CheckKeyInput(mInputHandle) != 0)
	{
		Close();
	}

}

void TextLoadMenu::Draw()
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

bool TextLoadMenu::FileExist()
{
	char tempStr[50];
	GetKeyInputString(tempStr, mInputHandle); //���͂��ꂽ�������擾
	mFileName = tempStr; //string�ɗ���

	std::string fileDir =  "Text\\"; fileDir += mFileName; //�t�@�C���ʒu
	if (std::filesystem::exists(fileDir))
	{
		return true; //���݂���
	}

	return false;//���݂��Ȃ�
}

void TextLoadMenu::FileRead()
{
	//�t�@�C���Ǎ���
	std::ifstream ifs("Text\\" + mFileName);
	std::string line;
	int count = 0;
	int maxIndex = 0; //LongNotes��index�p
	while (std::getline(ifs, line))
	{
		auto musicData = Split(line, ',');
		if (count == 0)
		{
			//���y���̎�荞��
			mStartMenu->SetMusicName(musicData[0]);
			//���y�̎�荞��
			std::shared_ptr<Music> music = std::make_unique<Music>();
			music->SetMusicHandle("Music\\" + musicData[0]);
			music->SetTotalMusicTime();
			mStartMenu->SetMusic(std::move(music));
			//Bpm�̎�荞��
			mStartMenu->SetBPM(std::stoi(musicData[1]));
			mStartMenu->GetMusicEdit()->SetBpmValue(std::stoi(musicData[1]));
			//Lpb�̓Ǎ���
			mStartMenu->SetLPB(std::stoi(musicData[2]));
			mStartMenu->GetMusicEdit()->SetLpb(std::stoi(musicData[2]));
		}
		else
		{
			switch (std::stoi(musicData[0]))
			{
			case 1:
				new TouchNotes(
					std::stoi(musicData[1]),
					std::stoi(musicData[2]),
					std::stoi(musicData[3]),
					std::stoi(musicData[4]),
					(musicData[5])[0],
					mStartMenu
				);
				break;
			case 2:
				new LongNotes(
					std::stoi(musicData[1]),
					std::stoi(musicData[2]),
					std::stoi(musicData[3]),
					std::stoi(musicData[4]),
					(musicData[5])[0],
					std::stoi(musicData[6]),
					mStartMenu
				);
				break;
			case 3:
				new WallNotesDown(
					std::stoi(musicData[1]),
					std::stoi(musicData[2]),
					std::stoi(musicData[3]),
					std::stoi(musicData[4]),
					std::stoi(musicData[6]),
					mStartMenu
				);
				break;
			case 4:
				new WallNotesUp
				(
					std::stoi(musicData[1]),
					std::stoi(musicData[2]),
					std::stoi(musicData[3]),
					std::stoi(musicData[4]),
					std::stoi(musicData[6]),
					mStartMenu
				);
				break;
			case 5:
				new TraceNotesObject
				(
					std::stoi(musicData[1]),
					std::stoi(musicData[2]),
					std::stoi(musicData[3]),
					std::stoi(musicData[4]),
					std::stoi(musicData[6]),
					mStartMenu
				);
				break;
			default:
				break;
			}

			//max�l���m��
			maxIndex = maxIndex < std::stoi(musicData[6]) ? std::stoi(musicData[6]) : maxIndex;
		}
		count++;
	}

	mStartMenu->GetMusicEdit()->SetLongNotesIndex(maxIndex + 1);
}

std::vector<std::string> TextLoadMenu::Split(std::string& input, char delimiter)
{
	std::istringstream stream(input);
	std::string field;
	std::vector<std::string> result;
	while (std::getline(stream, field, delimiter))
	{
		result.push_back(field);
	}
	return result;
}