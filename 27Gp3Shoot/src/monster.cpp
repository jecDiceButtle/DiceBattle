#include "monster.h"
#include "../../lib/gplib.h"

//tuika
#include "movableObject.h"

//3D�J����
extern Dx_Camera *dxCamera;
extern LPDIRECT3DDEVICE9 pD3DDevice;
//���b�V���S�̊Ǘ��N���X
extern DX3DMESHMANAGER *meshManage;
extern Dx_Camera *dxCamera;
//tuika


namespace game
{
	//tuika
	using namespace ci_ext;
	using namespace gplib;
	//tuika


	//**************************************************************************************//
	//�쐬����v���O�����ŕK�v�ƂȂ�ϐ��A�萔��`
	//**************************************************************************************//



	//**************************************************************************************//
	//�֐��L�q
	//**************************************************************************************//




	Monster::Monster(const std::string& objectName)
		:
		MovableObject(
		DrawObjf(objectName)
		)
	{

	}

	void Monster::render()
	{
		
	}

	void Monster::update()
	{

	}

}