#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"



#include "../../lib/dx_media_/dx_graphics3d.h"
#include "../../lib/dx_media_/dx3dmeshmanager.h"
#include "../../lib/ci_ext/DrawObj.hpp"
#include "movableObject.h"
	


namespace game
{

	class Dice : public MovableObject
{
	//*************************************************//
	//�@�萔
	//*************************************************//
private:
	enum DIRECT{LEFT,RIGHT,FOWARD,BACK};
	enum TYPE{GU,CH,PA,DEF};

	//�s���X�e�[�^�X
	enum STATE
	{
		DEAD,			// ���ɏ�ԁi�`��Ȃ�����Ȃ��j
		IDOL,			// �ҋ@���
		MOVE,			// �ړ���
		ATTACK,			// �U����
	};

	//�`��X�e�[�^�X
	enum DISPSTATE		
	{
		DICE,			// �T�C�R���̂�
		DICE_CHARA,		// �T�C�R���ƃL�����N�^�[
		CHARA,			// �L�����̂�
	};


	//*************************************************//
	//�@�ϐ�
	//*************************************************//
private:
	int diceID_;
	int playerID_;
	TYPE num[6];
	DIRECT dir_;

	int count_;											// �ړ��J�E���^

	STATE state_;										// �s�����
	DISPSTATE dispstate_;								// �`����
	
	//�ǉ�
	std::weak_ptr<ci_ext::Object> p_mons;			//�����X�^�[�̃|�C���^

	//dice���W
	//float xx;											//�_�C�X��X���W
	//float yy;											//�_�C�X��Y���W
	//float zz;											//�_�C�X��Z���W�k����0�l
	
	ci_ext::Vec3f pos_;									//���W

	ci_ext::Vec3f add_;									//�ړ���

	float masuX;
	float masuY;
	
	//*************************************************//
	//�@�֐�
	//*************************************************//
private:

	/*
		@brief							�ҋ@���̏���
		@return							�Ȃ�
	*/
	void Idol();

	/*
		@brief							�ړ����̏���
		@return							�Ȃ�
	*/
	void Moving();

	/*
		@brief							�ړ����̏���
		@return							�Ȃ�
	*/
	void Attack();


public:
	Dice(const std::string& objectName, const ci_ext::Vec3i& pos = ci_ext::Vec3i::zero());

	void init()	override;
	void render() override;
	void update() override;

	float getDicePosX();
	float getDicePosY(); 

	void swap(DIRECT dir);
	int getTopType();

	/*
		@brief							�A�N�Z�T�A�ҋ@�����ǂ���
		@return							�ҋ@�����ǂ���
		@true							�ҋ@��
	*/
	bool isIdoling();

	/*
		@brief							�ړ�����
		@return							�Ȃ�
	*/
	void Move(const ci_ext::Vec3i& dir,const ci_ext::Vec3i& pos);



	void setMasu(int x, int y);
};

}