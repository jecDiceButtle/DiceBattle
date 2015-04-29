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
	
	std::weak_ptr<ci_ext::Object> DiceManager::getDicePtr(const int player, const int id)
	{
		std::string str = "dice_p" + std::to_string(player) + "_no" + std::to_string(id);

		return getObjectFromChildren(str);
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

	void DiceManager::MovingPos(const int no, const ci_ext::Vec3i& dir)
	{
		//=============================
		// �_�C�X�ֈړ��ł��邩�m�F
		//=============================
		auto dice = ci_ext::weak_to_shared<Dice>(getDicePtr(turnPlayer_, no));
		//�ҋ@���ȊO�͈ړ��s��
		if (!dice->isIdoling()) 
			return;

		//=============================
		// �ׂ荇�����_�C�X���m�F
		//=============================

		for (int i = 0; i < dicemasu.size(); i++)	//�v���C���[
		{
			for (int j = 0; j < dicemasu[i].size(); j++)	//�_�C�X
			{
				if (i == turnPlayer_ && j == no)
					continue;

				if ((dicemasu[turnPlayer_][no] + dir).x() == dicemasu[i][j].x() 
					&& (dicemasu[turnPlayer_][no] + dir).y() == dicemasu[i][j].y())
				{
					return;
				}
			}
			
		}

		//=============================
		// �R�X�g�̊m�F�ƃ_�C�X�̈ړ�
		//=============================

		auto stage = ci_ext::weak_to_shared<CSceneStage>(p_parent);
		if (stage->checkMovableDice((dicemasu[turnPlayer_][no] + dir)))
		{
			dicemasu[turnPlayer_][no].offset(dir.x(),dir.y());

			auto dice = ci_ext::weak_to_shared<Dice>(getDicePtr(turnPlayer_, selectDice_));
			
			//�֐��ύX���s�����̂Œ��ӁI
			//���@dice->Move(dir, dicemasu[turnPlayer_][no]);
			dice->prepareMove(dicemasu[turnPlayer_][no]);
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
				std::string str = "dice_p" + std::to_string(i) + "_no" + std::to_string(j);
				auto ptr = insertAsChild(new game::Dice(str, ci_ext::Vec3i(i, j, 0)));
			}
		}

		// �_�C�X�̃}�X���W�̏�����
		for (int i = 0; i < 2; i++)
		{
			std::vector<ci_ext::Vec3i> temp;
			for (int j = 0; j < 3; j++)
			{
				temp.push_back(ci_ext::Vec3i(i, j, 0));
			}
			dicemasu.push_back(temp);
		}
	}
	

	void DiceManager::render()
	{
#ifdef _DEBUG
		gplib::graph::Draw_2DClear();//tuika
		std::string str = "���݃v���C���[ :" + std::to_string(turnPlayer_) +
			",�I���_�C�X :" + std::to_string(selectDice_) + "  X:" +
			std::to_string(dicemasu[turnPlayer_][selectDice_].x()) +
			", Y:" + std::to_string(dicemasu[turnPlayer_][selectDice_].y());

		gplib::font::Draw_FontTextNC(100, 100, 0.f, str, ARGB(255, 0, 0, 0), 0);


		for (int i = 0; i < dicemasu.size(); i++)
		{
			for (int j = 0; j < dicemasu[i].size(); j++)
			{
				std::string str = "�v���C���[" + std::to_string(i) +
					",  �_�C�X" + std::to_string(j) + "  X:" +
					std::to_string(dicemasu[i][j].x()) +
					", Y:" + std::to_string(dicemasu[i][j].y());

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