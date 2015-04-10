#pragma once
#include "../../lib/ci_ext/object.hpp"

#include "../../lib/ci_ext/xinput.hpp" 


#include "../../lib/dx_media_/dx_graphics3d.h"
#include "../../lib/dx_media_/dx3dmeshmanager.h"

#include "Logo.hpp"


#ifdef _DEBUG
#include "stage.h"
#endif

#include"lib_WindowDx.hpp"
#include"lib_Window.hpp"

extern std::shared_ptr<Dx_Camera> dxCamera;
extern std::shared_ptr<DX3DMESHMANAGER> meshManage;

//���[�g�I�u�W�F�N�g
class Root : public ci_ext::Object
{
	int frame_;
	std::weak_ptr<ci_ext::Window> window_;
public:
	Root(std::weak_ptr<ci_ext::Window> window)
		:
		Object("root"),
		frame_(0),
		window_(window)
	{
		
	}

	void init(std::shared_ptr<ci_ext::Object> thisObjectPtr)
	{
		setWeakPtr(thisObjectPtr);

		//=============================================
		//	3D������
		//=============================================

		//gplib::camera::InitCamera(gplib::system::WINW / 2, gplib::system::WINH / 2, 0, 0);

		//3D�J�����ݒ�@�J�����ʒu�̓f�t�H���g�@�����_��0,0,0
		float eye_pos_x = 0.0f;
		float eye_pos_y = 0.0f;
		float eye_pos_z = -50.0f;
		float eye_look_x = 0.0f;
		float eye_look_y = -10.0f;
		float eye_look_z = -30.0f;

		/////////////////////////////////////////////////////////////////////////�@�@
		//?)���̃J�����͉��Ɏg���񂾁H
		//////////////////////////////////////////////////////////////////////////
		dxCamera = std::shared_ptr<Dx_Camera>(new Dx_Camera);
		dxCamera->SetEyePos(DxVec3(eye_pos_x, eye_pos_y, eye_pos_z));
		dxCamera->SetLookPos(eye_look_x, eye_look_y, eye_look_z);

		/////////////////////////////////////////////////////////////////////////�@�@
		//?)meshManage�Ƃ͈��
		//////////////////////////////////////////////////////////////////////////
		//�X�e�[�W�RD�I�u�W�F�N�g
		meshManage = std::shared_ptr<DX3DMESHMANAGER>(new DX3DMESHMANAGER);

		//�J��������r���[�s��Ǝˉe�s���ݒ�
		meshManage->getG()->Setup3DEnv(dxCamera);

		meshManage->loadMesh("dice", "bossshot.x", "res/x/", DX3DMESHMANAGER::MESHTYPE::MESH);


#ifdef _DEBUG

		insertAsChild(new game::CSceneStage("scene_stage"));
#elif
		insertAsChild(new game::Logo("scene_logo"));

#endif

	}

	void update() override
	{
		++frame_;

	}
	void render() override
	{
#ifdef _DEBUG

		//gplib::debug::DFPS();

#endif
	}
	int frame() const { return frame_; }

	RECT getWindowSize()
	{
		return window_.lock()->getWndSize();
	}
};
