#include "dicemanager.h"
#include "../../lib/gplib.h"
#include "dice.h"
#include "stage.h"

namespace game
{
	//**************************************************************************************//
	//�쐬����v���O�����ŕK�v�ƂȂ�ϐ��A�萔��`
	//**************************************************************************************//


	//**************************************************************************************//
	//�֐��L�q
	//**************************************************************************************//
	void DiceManager::key()
	{
		if(gplib::input::CheckPush(gplib::input::KEY_LEFT))
		{
			MovingPos(0, ci_ext::Vec3i(-1, 0, 0));
		}
		if (gplib::input::CheckPush(gplib::input::KEY_RIGHT))
		{
			MovingPos(0, ci_ext::Vec3i(1, 0, 0));
		}
		if (gplib::input::CheckPush(gplib::input::KEY_UP))
		{
			MovingPos(0, ci_ext::Vec3i(0, 1, 0));
		}
		if (gplib::input::CheckPush(gplib::input::KEY_DOWN))
		{
			MovingPos(0, ci_ext::Vec3i(0, -1, 0));
		}

	}

	void DiceManager::MovingPos(const int no, const ci_ext::Vec3i& pos)
	{
		for (int i = 0; i < dicepos.size(); i++)
		{
			if (i == no) continue;

			if ((dicepos[no] + pos) == dicepos[no])
			{
				return;
			}
		}

		auto stage = ci_ext::weak_to_shared<CSceneStage>(p_parent);
		if (stage->checkMovableDice((dicepos[no] + pos)))
		{
			dicepos[no].offset(pos.x(),pos.y());
		}

	}


	//**************************************************************************************//
	//�f�t�H���g�֐�
	//**************************************************************************************//


	DiceManager::DiceManager(const std::string& objectName,const std::weak_ptr<Object> ptr)
		:
		Object(objectName),
		p_parent(ptr)
	{

	}

	void DiceManager::init()
	{
		//�_�C�X�̐���
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				//std::string str = "dice_player" + std::to_string(i+1) + "_no" + std::to_string(j);
				auto ptr = insertAsChild(new game::Dice("dice", i, j));
				p_dice.push_back(ptr);
			}
		}

		// �_�C�X�̃{�[�h���W�̏�����
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				dicepos.push_back(ci_ext::Vec3i(5, 5, 0));
			}
		}


	}

	void DiceManager::render()
	{
#if _DEBUG

		std::string str = std::to_string(dicepos[0].x()) + ", " + std::to_string(dicepos[0].y());

		gplib::font::Draw_FontTextNC(100, 100, 0.f, str, ARGB(255, 255, 255, 255), 0);


#endif
	}

	void DiceManager::update()
	{
		key();
	}

}