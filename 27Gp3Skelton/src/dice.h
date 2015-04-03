#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"

namespace game
{

class Dice : public ci_ext::Object
{
	//*************************************************//
	//�@�萔
	//*************************************************//
private:

	static const int HOGE;				// �萔�̗�B�폜���邱�ƁB


	//*************************************************//
	//�@�ϐ�
	//*************************************************//
private:

	int piyo;							// �ϐ��̗�B�폜���邱�ƁB


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
	Dice(const std::string& objectName);


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

};

}