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

	const ci_ext::Vec3i DiceManager::STARTMASU[2][2] =
	{
		{ ci_ext::Vec3i(1, 0, 0), ci_ext::Vec3i(3, 0, 0) },
		{ ci_ext::Vec3i(1, 4, 0), ci_ext::Vec3i(3, 4, 0) }
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
		if (gplib::input::CheckPush(gplib::input::KEY_LEFT))
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
			//�_�C�X�ɑI��`��
			// dice->select();

			bool selectF = true;			//�I���t���O

			//�_�C�X�̂����ꂩ���ړ����͑I��ύX��s��
			std::string str = "p" + std::to_string(turnPlayer_);
			auto objects = getObjectsFromChildren({ "dice", str });
			for (auto obj : objects)
			{
				auto dice = ci_ext::weak_to_shared<game::Dice>(obj);

				if (dice->isMoving())
					selectF = false;
			}


			if (selectF)
			{
				//�I���\�ȃ_�C�X��T���B
				for (int i = 1; i <= (int)dicemasu[turnPlayer_].size(); i++)
				{
					int no = (selectDice_ + i) % (int)dicemasu[turnPlayer_].size();

					//�I������Ă���_�C�X�̎����I���ł��邩
					auto dice = ci_ext::weak_to_shared<Dice>(getDicePtr(turnPlayer_, no));

					if (dice->isIdoling())
					{
						selectDice_ = no;
						break;
					}
				}
			}
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
			
			dice->Move(dir, dicemasu[turnPlayer_][no]);
		}


	}
	void DiceManager::ChangeTurn(const int playerID)
	{
		if (turnPlayer_ != playerID)
		{
			turnPlayer_ = playerID;
			selectDice_ = 0;
		}
	}

	//**************************************************************************************//
	void DiceManager::Check()
	{
		//=============================
		// �ׂ荇�����_�C�X���m�F
		//=============================

		ci_ext::Vec3i dir[] =
		{

			ci_ext::Vec3i(-1, 0, 0),		// ��
			ci_ext::Vec3i(1, 0, 0),			// �E
			ci_ext::Vec3i(0, 1, 0),			// ��
			ci_ext::Vec3i(0, -1, 0),		// ��

		};

		int enemyPlayer = (turnPlayer_ + 1) % 2;
		battledice.clear();


		for (int i = 0; i < dicemasu[turnPlayer_].size(); i++)	//�����̃_�C�X�̐�
		{
			bool inflag= false;				//�}���t���O
			pBattleDice temp;
			temp.selectF = false;

			//��������_�C�X���U���\���ǂ����i����łȂ����ǂ����j
			auto offdice = ci_ext::weak_to_shared<Dice>(getDicePtr(turnPlayer_, i));
			if (!offdice->isIdoling()) continue;

			temp.p_offense = offdice;

			for (int j = 0; j < dicemasu[enemyPlayer].size(); j++)	//����̃_�C�X�̐�
			{
				//�G�_�C�X�������Ă��邩�ǂ���
				auto defdice = ci_ext::weak_to_shared<Dice>(getDicePtr(enemyPlayer, j));
				if (!defdice->isIdoling()) continue;

				for (int k = 0; k < 4; k++)							//�����̊m�F�̉�
				{
					//�ׂ荇���Ă��邩����
					if ((dicemasu[turnPlayer_][i] + dir[k]).x() == dicemasu[enemyPlayer][i].x()
						&& (dicemasu[turnPlayer_][i] + dir[k]).y() == dicemasu[enemyPlayer][i].y())
					{
						inflag = true;
						temp.p_defense.push_back(defdice);
						break;
					}


				}

			}

			if (inflag)
				battledice.push_back(temp);

		}
	}
	
	

	//**************************************************************************************//


	void DiceManager::Summon()
	{
		//�����t�F�C�Y�͂Ƃ肠�����ۗ�
		//�f�X��Ԃ��Ȃ��ꍇ�͎��̃t�F�[�Y��

		bool nextF = true;		//�t�F�C�Y�ړ��t���O

		std::string str = "p" + std::to_string(turnPlayer_);
		auto objects = getObjectsFromChildren({ "dice", str });

		for (auto obj : objects)
		{
			auto dice = ci_ext::weak_to_shared<game::Dice>(obj);
			if (dice->isDying())
				nextF = false;
		}

		if (nextF)
		{
			auto parent = ci_ext::weak_to_shared<CSceneStage>(p_parent);
			parent->NextPhase();
		}

	}
	void DiceManager::Main()
	{
		key();
	}
	void DiceManager::Battle()
	{
		switch (batphase_)
		{
			//======================
			//�U������L�����̊m�F
			//======================
		case game::DiceManager::check:
			
			Check();
			//�U���ҋ@�O�Ȃ�end

			if (battledice.empty())
			{
				batphase_ = end;
			}

			//1�ȏ�Ȃ�AtkSelect
			else
			{
				batphase_ = atkSelect;
			}
			break;

			//======================
			//�U�����̃L�����I��
			//======================
		case game::DiceManager::atkSelect:
			
			//�U���ҋ@��1�L�����Ȃ�emySelect
			if (battledice.size() == 1)
			{
				batphase_ = emySelect;
			}
			//�U���ҋ@2�Ȃ�I��������
			else
			{

			}


			break;

			//======================
			//�h�䑤�̑I��
			//======================
		case game::DiceManager::emySelect:


			
			for (auto bdice : battledice)
			{
				if (bdice.selectF)
				{
					//�U���ҋ@1�Ȃ�battle
					if (bdice.p_defense.size() == 1)
					{
						batphase_ = battle;
					}
					//�U���ҋ@2�Ȃ�I��������
					else
					{

					}
					
				}
			}
			
			

			


			break;

			//======================
			//���s�̔���ƍU���A�j���[�V����
			//======================
		case game::DiceManager::battle:



			break;

			//======================
			//�_���[�W�����ƃ_�C�X�̍폜
			//======================
		case game::DiceManager::destroy:

			break;

			//======================
			//�U���_�C�X���Ȃ��ꍇ�A���̃t�F�[�Y��
			//======================
		case game::DiceManager::end:
			
			auto parent = ci_ext::weak_to_shared<CSceneStage>(p_parent);
			parent->NextPhase();
			break;
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
		// �_�C�X�̃}�X���W�̏�����
		for (int i = 0; i < 2; i++)
		{
			std::vector<ci_ext::Vec3i> temp;
			for (int j = 0; j < 2; j++)
			{
				temp.push_back(STARTMASU[i][j]);
			}
			dicemasu.push_back(temp);
		}
	}

	void DiceManager::init()
	{
		//�_�C�X�̐���
		for (int i = 0; i < 2; i++)	//�v���C���[
		{
			for (int j = 0; j < 2; j++)	//�_�C�X�̐�
			{
				std::string str = "dice_p" + std::to_string(i) + "_no" + std::to_string(j);
				auto ptr = insertAsChild(new game::Dice(str,dicemasu[i][j]));
			}
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
		switch (phase_)
		{
			//�����t�F�C�Y
		case 0:
			Summon();
			break;
			//���C���t�F�C�Y
		case 1:
			Main();
			break;
			//�o�g���t�F�C�Y
		case 2:
			Battle();
			break;
		}

	}

	//���b�Z�[�W��M
	void DiceManager::receiveMsg(std::weak_ptr<ci_ext::Object>& sender, const std::string& msg)
	{
		//���b�Z�[�W����
		auto msgVec = gplib::text::split(msg, ",");

		for (auto ms : msgVec){
			//����ɕ���
			auto mVec = gplib::text::split(ms, "=");
			
				if (mVec[0] == "player")
				{
					ChangeTurn(stoi(mVec[1]));
				}
				if (mVec[0] == "phase")
				{
					phase_ = stoi(mVec[1]);
				}
			}
	}
}