
//**************************************************************************
//���b�V���֘A�̊�{�\����
//��{�^�@�F�@�Ȃ�
//�h���^�@�F�@DxMesh,DxAnimeMesh
//**************************************************************************

#pragma once

#include "dx.h"

//���b�V���֘A�̊�{�\����
typedef struct DxBaseMesh
{
	//�t�@�C����
	char *file_name;

	//�R���X�g���N�^
	DxBaseMesh();
	//�t�@�C�����̎擾
	virtual char* GetFileName();
}DxBaseMesh;
