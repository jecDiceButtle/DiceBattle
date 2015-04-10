
//**************************************************************************
//���f�B�A�Ǘ��N���X
//��{�^�@�F�@�Ȃ�
//�h���^�@�F�@�Ȃ�
//**************************************************************************

#include "media_manager.h"

//�R���X�g���N�^
MediaManager::MediaManager(LPDIRECT3DDEVICE9 dev)
{
	//�e�N�X�`���Ǘ��N���X�̐���
	this->tex_manager = new TextureManager(dev);
	//���b�V���Ǘ��N���X�̐���
	this->mesh_manager = new MeshManager(dev,this->tex_manager);
}
//�f�X�g���N�^
MediaManager::~MediaManager()
{
	SAFE_DELETE(this->mesh_manager);
	SAFE_DELETE(this->tex_manager);
}

//**************************************************************************
//�e�N�X�`���֘A
//**************************************************************************
//�C���[�W�t�@�C������DxTexture�����[�h�@�@�i�ȈՔŁj
LPDIRECT3DTEXTURE9 MediaManager::LoadTexture(string fName,string path)
{
	return this->tex_manager->LoadTextureFile(fName,path);
}
//�C���[�W�t�@�C������DxTexture�����[�h�@�@�i�ڍהŁj
DxTexture* MediaManager::LoadTextureEx(string fName,string path)
{
	return this->tex_manager->LoadTextureFileEx(fName,path);
}

//**************************************************************************
//**************************************************************************
//X�t�@�C������̂R�c���f���f�[�^�����[�h�@�@�i�ȈՔŁA�A�j���[�V��������s�j
DxMesh* MediaManager::LoadMesh(string fName,string path)
{
	return this->mesh_manager->LoadMeshFromX(fName,path);
}
//X�t�@�C������̂R�c���f���f�[�^�����[�h�@�@�i�ڍהŁA�A�j���[�V��������\�j
DxAnimeMesh* MediaManager::LoadAnimeMesh(string fName,string path)
{
	return this->mesh_manager->LoadAnimeMeshFromX(fName,path);
}