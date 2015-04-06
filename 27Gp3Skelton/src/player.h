#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"

namespace game
{

class Player : public ci_ext::Object
{
	//*************************************************//
	//�@�萔
	//*************************************************//
private:
	static const int DEFAULTCOST;

	//*************************************************//
	//�@�ϐ�
	//*************************************************//
private:

	std::weak_ptr<ci_ext::Object> p_parent;				// �e�̃|�C���^
	std::vector<int>cost;								// �R�X�g


	//*************************************************//
	//�@�֐�
	//*************************************************//
private:


public:

	/*
		@brief							�R���X�g���N�^
		@param[in]	objectName			�I�u�W�F�N�g��
		@param[in]	ptr					�e�̃|�C���^
		@return							�Ȃ�
	*/
	Player(const std::string& objectName, const std::weak_ptr<Object> ptr);



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
		@brief							�R�X�g�m�F
		@param[in] id					�v���C���[ID
		@return							�R�X�g�c���Ă邩�ǂ���
		@true							�c���Ă���
		@false							�c���Ă��Ȃ�
	*/
	bool isCostRemain(const int id);		

	/*
		@brief							�R�X�g����
		@param[in] id					�v���C���[ID
		@param[in] point				���炷�ʁi��{�l1�j
		@return							�Ȃ�
	*/
	void CostDecrease(const int id,const int point = 1);		

	/*
		@brief							�R�X�g��߂�
		@param[in] id					�v���C���[ID
		@return							�Ȃ�
	*/
	void CostReset(const int id);


};

}