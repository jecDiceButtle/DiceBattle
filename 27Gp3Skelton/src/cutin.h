#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"

namespace game
{

class Cutin : public ci_ext::Object
{
	//*************************************************//
	//�@�萔
	//*************************************************//
private:

//	static const int HOGE;				// �萔�̗�B�폜���邱�ƁB


	//*************************************************//
	//�@�ϐ�
	//*************************************************//
private:

	float cutinX;
//	int piyo;							// �ϐ��̗�B�폜���邱�ƁB


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
	Cutin(const std::string& objectName,int y);
	~Cutin();
	int cutinY;
	int draw();

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