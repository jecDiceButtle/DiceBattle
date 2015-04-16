#include "dicemanager.h"
#include "../../lib/gplib.h"
#include "dice.h"
#include "stage.h"
#include "../../lib/ci_ext/object.hpp"

namespace game
{
	//**************************************************************************************//
	//�쐬����v���O�����ŕK�v�ƂȂ�ϐ��A�萔��`
	//**************************************************************************************//
	const int DiceManager::JUDGE[3][3]
	{
	//		  G  C  P
	/*G*/	{ 0, 1,-1},
	/*C*/	{-1, 0, 1},
	/*P*/	{ 1,-1, 0}
	};

	//**************************************************************************************//
	//�֐��L�q
	//**************************************************************************************//
	
	int DiceManager::getAttackJudge(int player, int enemy){
		return JUDGE[player][enemy];
	}
	
	
	void DiceManager::key()
	{
		if(gplib::input::CheckPush(gplib::input::KEY_LEFT))
		{
			MovingPos(selectDice_, ci_ext::Vec3i(-1, 0, 0));
		}
		if (gplib::input::CheckPush(gplib::input::KEY_RIGHT))
		{
			MovingPos(selectDice_, ci_ext::Vec3i(1, 0, 0));
		}
		if (gplib::input::CheckPush(gplib::input::KEY_UP))
		{
			MovingPos(selectDice_, ci_ext::Vec3i(0, 1, 0));
		}
		if (gplib::input::CheckPush(gplib::input::KEY_DOWN))
		{
			MovingPos(selectDice_, ci_ext::Vec3i(0, -1, 0));
		}
		if (gplib::input::CheckPush(gplib::input::KEY_BTN0))
		{
			//�_�C�X�I�u�W�F�N�g�ɐ����𕷂����ƁB
			(selectDice_ += 1) %= 3;
		}

	}

	void DiceManager::MovingPos(const int no, const ci_ext::Vec3i& pos)
	{
		for (int i = 0; i < dicepos.size(); i++)	//�v���C���[
		{
			for (int j = 0; j < dicepos[i].size(); j++)	//�_�C�X
			{
				if (i == turnPlayer_ && j == no)
					continue;

				if ((dicepos[turnPlayer_][no] + pos).x() == dicepos[i][no].x() 
					&& (dicepos[turnPlayer_][no] + pos).y() == dicepos[i][no].y())
				{
					return;
				}
			}
			
		}

		auto stage = ci_ext::weak_to_shared<CSceneStage>(p_parent);
		if (stage->checkMovableDice((dicepos[turnPlayer_][no] + pos)))
		{
			dicepos[turnPlayer_][no].offset(pos.x(),pos.y());
		}


	}
	/*
		@brief							�^�[���̕ύX
		@param[in]	playerID			�v���C���[���ʔԍ�
		@return							�Ȃ�
	*/
	void DiceManager::ChangeTurn(const int playerID)
	{
		turnPlayer_ = playerID;
		selectDice_ = 0;
	}

	//tuika
	void DiceManager::SetMasu()
	{
		for (int i = 0; i < 2; i++)	//�v���C���[
		{
			for (int j = 0; j < 3; j++)	//�_�C�X�̐�
			{
				int num = i * 3 + j;
				auto dice = ci_ext::weak_to_shared<Dice>(p_dice[num]);
				dice->setMasu(dicepos[i][j].x(), dicepos[i][j].y());
			}
		}

	}

	//**************************************************************************************//
	//�f�t�H���g�֐�
	//**************************************************************************************//


	DiceManager::DiceManager(const std::string& objectName,const std::weak_ptr<Object> ptr)
		:
		Object(objectName),
		p_parent(ptr),
		turnPlayer_(0),
		selectDice_(0)
	{

	}

	void DiceManager::init()
	{
		//�_�C�X�̐���
		for (int i = 0; i < 2; i++)	//�v���C���[
		{
			for (int j = 0; j < 3; j++)	//�_�C�X�̐�
			{
				/*std::string str = "dice_player" + std::to_string(i+1) + "_no" + std::to_string(j);*/
				auto ptr = insertAsChild(new game::Dice("dice", i, j));
				p_dice.push_back(ptr);
			}
		}

		// �_�C�X�̃{�[�h���W�̏�����
		for (int i = 0; i < 2; i++)
		{
			std::vector<ci_ext::Vec3i> temp;
			for (int j = 0; j < 3; j++)
			{
				temp.push_back(ci_ext::Vec3i(i, j, 0));
			}
			dicepos.push_back(temp);
		}
	}
	

	void DiceManager::render()
	{
#if _DEBUG
		gplib::graph::Draw_2DClear();//tuika
		std::string str = "���݃v���C���[ :" + std::to_string(turnPlayer_) +
			",�I���_�C�X :" + std::to_string(selectDice_) + "  X:" +
			std::to_string(dicepos[turnPlayer_][selectDice_].x()) +
			", Y:" + std::to_string(dicepos[turnPlayer_][selectDice_].y());

		gplib::font::Draw_FontTextNC(100, 100, 0.f, str, ARGB(255, 0, 0, 0), 0);


		for (int i = 0; i < dicepos.size(); i++)
		{
			for (int j = 0; j < dicepos[i].size(); j++)
			{
				std::string str = "�v���C���[" + std::to_string(i) +
					",  �_�C�X" + std::to_string(j) + "  X:" +
					std::to_string(dicepos[i][j].x()) +
					", Y:" + std::to_string(dicepos[i][j].y());

				if (i == turnPlayer_ && j == selectDice_)
				{
					gplib::font::Draw_FontTextNC(500 + (i * 300), 100 + 30 * j, 0.f, str, ARGB(255, 255, 0, 0), 0);
				}
				else
				{
					gplib::font::Draw_FontTextNC(500 + (i * 300), 100 + 30 * j, 0.f, str, ARGB(255, 0, 0, 0), 0);
				}	
			}
		}
		gplib::graph::Draw_2DRefresh();//tuika



#endif
	}

	void DiceManager::update()
	{
		key();

		//tuika
		DiceManager::SetMasu();
	}

	void DiceManager::receiveMsg(std::weak_ptr<ci_ext::Object>& sender, const std::string& msg, const int num)
	{

		if (msg == "turn")
		{
			ChangeTurn(num);
		}
		if (msg == "phase")
		{

		}

	}
}