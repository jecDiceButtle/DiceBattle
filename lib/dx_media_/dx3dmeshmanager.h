

#pragma once

#include "dx.h"

#include "media_manager.h"
#include "dx_font.h"
#include "dx_graphics3d.h"
#include	<map>

class DX3DMESHMANAGER
{
private:
	//描画管理クラス
	Dx_Graphics3D *g;
	//メディア管理クラス
	MediaManager *m_manager;	//アニメ付メッシュ
	class AnimMesh{
		public:
		DxAnimeMesh	*mesh;
		Dx_AnimeAuxiliary *anime;
		AnimMesh(MediaManager *manager,string fileName,string path)
		{
			mesh = manager->LoadAnimeMeshFromX((char*)fileName.c_str(),(char*)path.c_str());
			anime = new Dx_AnimeAuxiliary(mesh->pAnimController);
		}
		~AnimMesh()
		{
			
		}
	};
	
	map<string,DxMesh*>		DxMeshTable;
	map<string,AnimMesh*>	DxAnimMeshTable;
public:
	enum MESHTYPE{
		MESH = 0,
		ANIMMESH = 1,
	};
	Dx_Graphics3D* getG();

	DX3DMESHMANAGER();
	~DX3DMESHMANAGER();

  void drawAnimMesh(DxVec3 pos, string handleName, DxVec3 angle, D3DCOLOR color = ARGB(255, 255, 255, 255), DxVec3 scale = DxVec3(1.0f, 1.0f, 1.0f));
  void drawMesh(DxVec3 pos, string handleName, DxVec3 angle, D3DCOLOR color = ARGB(255, 255, 255, 255), DxVec3 scale = DxVec3(1.0f, 1.0f, 1.0f));

	void loadMesh(string handleName,string fileName,string path,MESHTYPE type = MESHTYPE::MESH);
//	void drawMesh(DxVec3 pos,string handleName,DxVec3 angle,D3DCOLOR color = ARGB(255,255,255,255));
//	void drawAnimMesh(DxVec3 pos,string handleName,DxVec3 angle,D3DCOLOR color = ARGB(255,255,255,255));
	void ChangeAnim(string handleName,int nowMotion);
	void step(string handleName,float spd);
	float nowTrack(string handleName,int nowMotion);
};



