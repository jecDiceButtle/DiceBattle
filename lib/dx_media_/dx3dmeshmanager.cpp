

#include "dx3dmeshmanager.h"

extern LPDIRECT3DDEVICE9		pD3DDevice;

Dx_Graphics3D* DX3DMESHMANAGER::getG(){	
	return g; 
}

DX3DMESHMANAGER::DX3DMESHMANAGER()
{
	//描画管理クラスの生成
	g = new Dx_Graphics3D(pD3DDevice);
	//メディア管理クラスの生成
	m_manager = new MediaManager(pD3DDevice);

}
DX3DMESHMANAGER::~DX3DMESHMANAGER()
{
	//メディア管理クラスの破棄
	SAFE_DELETE(m_manager);
	//描画管理クラスの破棄
	SAFE_DELETE(g);
}

void DX3DMESHMANAGER::loadMesh(string handleName,string fileName,string path,MESHTYPE type)
{
	if(type == MESHTYPE::MESH){
		DxMeshTable.insert(map<string,DxMesh*>::value_type(handleName,
			m_manager->LoadMeshFromX((char*)fileName.c_str(),(char*)path.c_str())));
	}else if(type == MESHTYPE::ANIMMESH){
		DxAnimMeshTable.insert(map<string,AnimMesh*>::value_type(
			handleName,
			new AnimMesh(m_manager,fileName.c_str(),path.c_str())
			)
			);
	}
}
void DX3DMESHMANAGER::drawMesh(DxVec3 pos, string handleName, DxVec3 angle, D3DCOLOR color, DxVec3 scale)
{
	if(DxMeshTable.find(handleName) != DxMeshTable.end())
    g->DrawModel(DxMeshTable[handleName], &pos, &scale, &angle, &color);
}
void DX3DMESHMANAGER::drawAnimMesh(DxVec3 pos, string handleName, DxVec3 angle, D3DCOLOR color, DxVec3 scale)
{
	if(DxAnimMeshTable.find(handleName) != DxAnimMeshTable.end())
    g->DrawModel(DxAnimMeshTable[handleName]->mesh, &pos, &scale, &angle, &color);
}
void DX3DMESHMANAGER::ChangeAnim(string handleName,int nowMotion)
{
	if(DxAnimMeshTable.find(handleName) != DxAnimMeshTable.end())
		DxAnimMeshTable[handleName]->anime->ChangeAnim(nowMotion);
}
void DX3DMESHMANAGER::step(string handleName,float spd)
{
	//アニメーション再生
	if(DxAnimMeshTable.find(handleName) != DxAnimMeshTable.end()){
		DxAnimMeshTable[handleName]->anime->PlayAnimation(spd);	
	}
}
float DX3DMESHMANAGER::nowTrack(string handleName,int nowMotion)
{
	D3DXTRACK_DESC desc;
	if(DxAnimMeshTable.find(handleName) != DxAnimMeshTable.end()){
		DxAnimMeshTable[handleName]->anime->GetTrackDesc(nowMotion,&desc);
		return (float)desc.Position;
	}else{
		return -1;
	}
	return -1;
}

