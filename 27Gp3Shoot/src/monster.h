#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"

//tuika
#include "../../lib/dx_media_/dx_graphics3d.h"
#include "../../lib/dx_media_/dx3dmeshmanager.h"
#include "../../lib/ci_ext/DrawObj.hpp"
#include "movableObject.h"
//tuika

namespace game
{

	class Monster : public MovableObject
{
	//*************************************************//
	//�@�萔
	//*************************************************//
private:




	//*************************************************//
	//�@�ϐ�
	//*************************************************//
private:
	int monster_num;
	ci_ext::Vec3f m_pos;

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

	//monsternum=0(KUJIRA)monsternum=1(KINOKO)monsternum=2(TORI)
	Monster(const std::string& objectName, const ci_ext::Vec3f pos, const int monsternum);


	/*
		@brief							�`��
		@return							�Ȃ�
	*/
	void render() override;

	/*
		@brief							�t���[���X�V
		@return							�Ȃ�
	*/
	void update() override;


	/*
		@brief							���W�̈ړ��m�F
		@param[in]	pos					�ړ���̍��W
		@return							�ړ��\���ǂ���
		@true							��
		@false							�s��
	*/




};

}