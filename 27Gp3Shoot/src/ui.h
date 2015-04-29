#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"

#include "../../lib/dx_media_/dx_graphics3d.h"
#include "../../lib/dx_media_/dx3dmeshmanager.h"
#include "../../lib/ci_ext/DrawObj.hpp"
#include "movableObject.h"




namespace game
{

	class UI : public MovableObject
	{
		//*************************************************//
		//�@�萔
		//*************************************************//
	private:


		//*************************************************//
		//�@�ϐ�
		//*************************************************//
	public:
		enum UITYPE{ POPUP, CHARA, PHASE, CUTINMONSTER, CUTINPHASE };
	private:
		UITYPE type_;
		float x, y;
		int turnPlayer_;
		int phase_;


		//cutin_monster
		bool	M_initF;
		bool	P_initF;
		std::weak_ptr<ci_ext::Object> timer_;
		enum MOVESTATE{ M_RIGHTCENTER, M_CENTER, M_CENTERLEFT, P_RIGHTCENTER, P_CENTER, P_CENTERLEFT };
		MOVESTATE M_state_, P_state_;
		float phaseC_x, phaseC_y;
		float charaC_x, charaC_y;

		//cutin_phase
		//std::weak_ptr<ci_ext::Object> timer_;
		/*enum P_MOVESTATE{ P_RIGHTCENTER, P_CENTER, P_CENTERLEFT };*/
		/*	P_MOVESTATE P_state_;*/


		//popup

		float sizeX;
		float sizeY;
		bool flag;
		bool Yes;
		bool No;


		//chara
		int turn;
		float player1scale;
		float player2scale;

		//phase
		float scaleX;
		float scaleY;

		//*************************************************//
		//�@�֐�
		//*************************************************//
	private:


	public:

		/*
		@brief							�R���X�g���N�^
		@param[in]	objectName			�I�u�W�F�N�g��
		@return							�Ȃ�
		*/
		UI(const std::string& objectName, UITYPE type, float posx = 0, float posy = 0);
		void flagset();
		void ChangeTurn(const int playerID);
		void Changephase(const int phase);
		/*
		@brief							�`��
		@return							�Ȃ�
		*/

		void init() override;


		void render() override;

		void update() override;


		void receiveMsg(std::weak_ptr<ci_ext::Object>& sender, const std::string& msg) override;
		/*
		@brief							�t���[���X�V
		@return							�Ȃ�
		*/


	};
}