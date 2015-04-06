#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"
#include <vector>
#include <memory>

namespace game
{

class DiceManager : public ci_ext::Object
{
	//*************************************************//
	//�@�萔
	//*************************************************//
private:

	//*************************************************//
	//�@�ϐ�
	//*************************************************//
private:

	std::weak_ptr<ci_ext::Object> p_parent;				// �e�̃|�C���^

	std::vector<std::weak_ptr<ci_ext::Object>> p_dice;	// �_�C�X�I�u�W�F�N�g�̃|�C���^

	std::vector<std::vector<ci_ext::Vec3i>> dicepos;	// �_�C�X�I�u�W�F�N�g�̍��W�i�O�v���C���[:��_�C�X�j

	int	turnPlayer_;									// ���݂̃^�[���v���C���[
	int selectDice_;									// �w�肵�Ă���_�C�X

	//*************************************************//
	//�@�֐�
	//*************************************************//
private:

	/*
		@brief							�L�[���͏���
		@return							�Ȃ�
	*/
	void key();

	/*
		@brief							���̃_�C�X�̍��W�����ɂ�
		@param[in] no					�_�C�X�̔z��
		@param[in] dir					�����x�N�g��
		@return							�Ȃ�
	*/
	void MovingPos(const int no, const ci_ext::Vec3i& pos);	


public:

	/*
		@brief							�^�[���̕ύX
		@param[in]	playerID			�v���C���[���ʔԍ�
		@return							�Ȃ�
	*/
	void ChangeTurn(const int playerID);


	/*
		@brief							�R���X�g���N�^
		@param[in]	objectName			�I�u�W�F�N�g��
		@param[in]	ptr					�e�̃|�C���^
		@return							�Ȃ�
	*/
	DiceManager(const std::string& objectName, const std::weak_ptr<Object> ptr);


	/*
		@brief							�T�C�R���쐬
		@return							�Ȃ�
	*/
	void init() override;


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