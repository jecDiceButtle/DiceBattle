
//**************************************************************************
//メディア管理クラス
//基本型　：　なし
//派生型　：　なし
//**************************************************************************

#include "media_manager.h"

//コンストラクタ
MediaManager::MediaManager(LPDIRECT3DDEVICE9 dev)
{
	//テクスチャ管理クラスの生成
	this->tex_manager = new TextureManager(dev);
	//メッシュ管理クラスの生成
	this->mesh_manager = new MeshManager(dev,this->tex_manager);
}
//デストラクタ
MediaManager::~MediaManager()
{
	SAFE_DELETE(this->mesh_manager);
	SAFE_DELETE(this->tex_manager);
}

//**************************************************************************
//テクスチャ関連
//**************************************************************************
//イメージファイルからDxTextureをロード　　（簡易版）
LPDIRECT3DTEXTURE9 MediaManager::LoadTexture(string fName,string path)
{
	return this->tex_manager->LoadTextureFile(fName,path);
}
//イメージファイルからDxTextureをロード　　（詳細版）
DxTexture* MediaManager::LoadTextureEx(string fName,string path)
{
	return this->tex_manager->LoadTextureFileEx(fName,path);
}

//**************************************************************************
//**************************************************************************
//Xファイルからの３Ｄモデルデータをロード　　（簡易版、アニメーション制御不可）
DxMesh* MediaManager::LoadMesh(string fName,string path)
{
	return this->mesh_manager->LoadMeshFromX(fName,path);
}
//Xファイルからの３Ｄモデルデータをロード　　（詳細版、アニメーション制御可能）
DxAnimeMesh* MediaManager::LoadAnimeMesh(string fName,string path)
{
	return this->mesh_manager->LoadAnimeMeshFromX(fName,path);
}