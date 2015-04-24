#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"


namespace game
{

	class Back : public ci_ext::Object
{
	//*************************************************//
	//�@�萔
	//*************************************************//
private:
	

	//*************************************************//
	//�@�ϐ�
	//*************************************************//
private:

	int back_num;

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
	//backnum=0(STAGEBACK)
	Back(const std::string& objectName, const int backnum);


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