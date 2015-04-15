#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/gplib.h"
#include "../../lib/ci_ext/vec3.hpp"

namespace game
{
	class CSceneStage : public ci_ext::Object
	{
	private:

		//*************************************************//
		//�@�萔
		//*************************************************//

		//��ԑJ��
		enum class STAGESTATE
		{
			STANDBY,				//�Q�[���O
			PLAYING,				//�Q�[����
			RESULT,					//�Q�[���I�[�o�[
		};

		//�v���C���[�^�[��
		enum TURN
		{
			null = -1,				//�^�[�����ݒ�
			PLAYER1,				//�v���C���[�P
			PLAYER2,				//�v���C���[�Q
		};

		//�^�[���t�F�C�Y
		enum class PHASE
		{
			null = -1,				//�^�[�����ݒ�
			SUMMON,					//����(�A���t�@�ۗ��j
			MAIN,					//�ړ�
			BUTTLE,					//�ΐ�
			END,					//�i�Ƃ肠�������z�u�j
		};


		//*************************************************//
		//�@�ϐ�
		//*************************************************//

	private:
		static const int JUDGE[3][3];

		bool		phaseinit_;						// �t�F�C�Y�̍X�V�t���O

		std::weak_ptr<ci_ext::Object> p_player;		// �v���C���[�̃|�C���^
		std::weak_ptr<ci_ext::Object> p_board;		// �{�[�h�̃|�C���^
		std::weak_ptr<ci_ext::Object> p_dm;			// �{�[�h�̃|�C���^

		//tuika
		std::weak_ptr<ci_ext::Object> p_camera;		// �J�����̃|�C���^
		std::weak_ptr<ci_ext::Object> p_back;		// �w�i�̃|�C���^

		TURN		turn_;							// �v���C���[�^�[��
		STAGESTATE	state_;							// ��ԑJ��
		PHASE		phase_;							// �^�[���t�F�C�Y


		//*************************************************//
		//�@�֐�
		//*************************************************//

	public:

		CSceneStage(const std::string& objectName);

		/*
			@brief			���s����
			@param			�Ȃ�
			@return			���s����		-1:�s�k 0:������ 1:����
		*/
		int getAttackJudge(int player, int enemy);
		

		/*
			@brief			�t�F�C�Y�̍X�V
			@return			�Ȃ�
		*/
		void NextPhase();

		/*
			@brief					�_�C�X�ړ�����
			@param[in]	pos			�ړ���̍��W
			@return					�����������ǂ���
			@true					�������ꂽ
			@false					��������Ă��Ȃ�
		*/
		bool checkMovableDice(const ci_ext::Vec3i &pos);


		void init() override;
		void render() override;
		void update() override;
	};

}