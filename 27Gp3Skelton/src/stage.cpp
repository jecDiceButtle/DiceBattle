#include "stage.h"
#include <memory>
#include <string>
#include <iostream>

#include "logo.hpp"
#include "player.h"
#include "dicemanager.h"

#include <stdio.h>

namespace game
{
	//**************************************************************************************//
	//�쐬����v���O�����ŕK�v�ƂȂ�ϐ��A�萔��`
	//**************************************************************************************//
	const int CSceneStage::JUDGE[3][3]
	{
	//		  G  C  P
	/*G*/	{ 0, 1,-1},
	/*C*/	{-1, 0, 1},
	/*P*/	{ 1,-1, 0}
	};


	//**************************************************************************************//
	//�֐��L�q
	//**************************************************************************************//
	
	int CSceneStage::getAttackJudge(int player, int enemy){
		return JUDGE[player][enemy];
	}

	void CSceneStage::NextPhase()
	{
		phaseinit_ = true;

		switch (phase_)
		{
		case game::CSceneStage::PHASE::SUMMON:
			phase_ = PHASE::MAIN;

			break;
		case game::CSceneStage::PHASE::MAIN:
			phase_ = PHASE::BUTTLE;

			break;
		case game::CSceneStage::PHASE::BUTTLE:
			phase_ = PHASE::END;

			break;
		case game::CSceneStage::PHASE::END:
			phase_ = PHASE::SUMMON;

			break;
		}
	}

	bool CSceneStage::checkMovableDice(const ci_ext::Vec3i &pos)
	{
		//�{�[�h��OK���Ă��ꂽ��
		if (true)
		{
			//�v���C���[�̃R�X�g������̂Ȃ��
			if (true)
			{
				//�v���C���[�̃R�X�g�����炷

				return true;
			}
		}

		return false;
	}

	//**************************************************************************************//
	//�f�t�H���g�֐�
	//**************************************************************************************//

	CSceneStage::CSceneStage(const std::string& objectName)
		:
		Object(objectName),
		state_(STAGESTATE::STANDBY),
		turn_(TURN::null),
		phase_(PHASE::null)
	{

	}
	void CSceneStage::init()
	{

		insertAsChild(new Player("player"));
		insertAsChild(new DiceManager("dicemanager",this->selfPtr()));
		
	}
	void CSceneStage::render()
	{

#if _DEBUG
		gplib::font::Draw_FontTextNC(0, 0, 0.f, "�Q�[�����", ARGB(255, 255, 255, 255), 0);
		
		switch (turn_)
		{
		case game::CSceneStage::TURN::PLAYER1:
			std::cout << "�v���C���[�P" ;
			break;
		case game::CSceneStage::TURN::PLAYER2:
			std::cout << "�v���C���[�Q" ;
			break;
		}


		switch (phase_)
		{
		case game::CSceneStage::PHASE::SUMMON:
			std::cout << ":�����t�F�[�Y" << std::endl;
			break;
		case game::CSceneStage::PHASE::MAIN:
			std::cout << ":���C���t�F�[�Y" << std::endl;
			break;
		case game::CSceneStage::PHASE::BUTTLE:
			std::cout << ":�o�g���t�F�[�Y" << std::endl;
			break;
		case game::CSceneStage::PHASE::END:
			std::cout << ":�G���h�t�F�[�Y" << std::endl;
			break;
		}

#endif

	}
	void CSceneStage::update()
	{
		switch (state_)
		{
		case game::CSceneStage::STAGESTATE::STANDBY:

			//�X�e�[�g�؂�ւ�//
			if (true)
			{
				state_ = CSceneStage::STAGESTATE::PLAYING;
				phase_ = PHASE::SUMMON;
				turn_ = TURN::PLAYER1;
			}
			break;
			
			//=============================================================================
		case game::CSceneStage::STAGESTATE::PLAYING:

			//�t�F�[�Y���M����
			if (phaseinit_)
			{
				//�쐬�\��
				//�t�F�C�Y�̏�Ԃ��e�I�u�W�F�N�g�֑��M���鏈������������
				//�v���C���[�^�[�����������Ⴄ

				phaseinit_ = false;
			}

			//�v���C���[�^�[����������
			if (phase_ == PHASE::END)
			{
				if (turn_ == TURN::PLAYER1)
				{
					turn_ = TURN::PLAYER2;
					NextPhase();
				}

				else if (turn_ == TURN::PLAYER2)
				{
					turn_ = TURN::PLAYER1;
					NextPhase();
				}
			}

			//�X�e�[�g�؂�ւ�//
			if (gplib::input::CheckPush(gplib::input::KEY_SPACE))
			{
				state_ = CSceneStage::STAGESTATE::RESULT;
			}
			break;

			//=============================================================================
			
		case game::CSceneStage::STAGESTATE::RESULT:

			if (gplib::input::CheckPush(gplib::input::KEY_BTN0))
			{
				kill();
				//�V�[���J��
				insertToParent(new Logo("scene_logo"));
			}
			break;
		}

	}
}


