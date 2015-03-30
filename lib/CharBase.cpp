

#include "gplib.h"
#include "CharBase.h"
#include "ci_ext/Polygon.hpp"
#include "ci_ext/color.hpp"
#include "ci_ext/vec3.hpp"

using namespace gplib;

//------------------------------------------------------
//CharBase���p���ėp����
//----------------------
//�A�j���[�V�����ݒ�
//max : �O�ɖ߂閇��
//speed : �A�j�����x
void charabase::SetAnim(Anim& anim, int max, float speed)
{
	anim.cnt = 0.f;
	anim.max = max;
	anim.speed = speed;
	anim.no = 0;
}

//�A�j���X�V
//���̊֐���no�̒l���X�V����Bno�̒l��
//CharBase.src.x()�ɑ������B
//�A�j���̏�����ύX�������ꍇ�͈ȉ�
/*
	StepAnim(obj.anim);
	//�ȉ��ŃA�j���[�V�����w��\
	int animTable[] = {0,1,0,2};
	//���ۂɗ��p����ꍇ��
	animTable[obj.anim.no]
	StepAnim(obj.anim);

*/
bool charabase::StepAnim(Anim& anim)
{
	anim.cnt += anim.speed;
	if(anim.cnt >= 1.f){
		anim.cnt = 0;
		anim.no++;
		if(anim.no >= anim.max){
			anim.no = 0;
		}
		return true;
	}
	return false;
}

//----------------------
//�A�j���[�V������~
//speed��0�ɂ��邾���Ȃ̂ŁA�ĊJ���͍ēxSetAnim���K�v
void charabase::StopAnim(Anim& anim)
{
	anim.speed = 0.f;
}

//----------------------
//�A�j���[�V�����J�n
//speed���w�肵���l�ɂ��邾���Ȃ̂ŁA�ĊJ���͍ēxSetAnim���K�v
//anim : �A�j���[�V�������s�������A�j���\����
//speed : �A�j���[�V�����̑��x
void charabase::StartAnim(Anim& anim,float speed)
{
	anim.speed = speed;
}
//------------------------------------------------------
//CharBase����������
//
/*
//��{�ƂȂ�`�b�v�̃T�C�Y�Ɨ��p����摜
BaseData base = {CHARWID,CHARHGT,charIMG};
//�������@�w��O�̒l�͏����l�ɂȂ�B
//���̏ꍇ��wid,hgt,img�ȊO�͏����l
InitCharBase(player.pos,base);

//���̏ꍇ��wid,hgt,img,x,y�ȊO�͏����l
InitCharBase(player.pos,base,STARTPOSX,STARTPOSY);

���p����ۂ͉��t���Oshow���U�ɂȂ��Ă��邽�߁A
UseChar�ŉ���Ԃɂ��邱�ƁB
*/
void charabase::InitCharBase(CharaBase& cb, const BaseData& base,
						float x,float y,float z,float addx,float addy,float addz,
					  int srcX,int srcY,int srcZ,float angle, float scaleX,float scaleY,float scaleZ,
						int alpha, int red, int green, int blue)
{
	cb.width = base.wid;
	cb.height = base.hgt;
	cb.resname = base.resname;
	
	cb.pos.set(x, y, z);
	cb.add.set(addx, addy, addz);
	cb.scale.set(scaleX, scaleY, scaleZ);
	cb.angle = angle;
	cb.src.set((float)srcX, (float)srcY, (float)srcZ);
	
	cb.color.set((unsigned int)alpha, (unsigned int)red, (unsigned int)green, (unsigned int)blue);

	cb.show = false;
}

void charabase::InitCharBase(CharaBase& cb, float x, float y, float z, float addx, float addy, float addz,
					const std::string& resname, int srcX, int srcY, int srcZ, int w, int h,
					float angle, float scaleX,float scaleY,float scaleZ,
					int alpha, int red, int green, int blue)
{
	cb.pos.set(x, y, z);
	cb.add.set(addx, addy, addz);
	cb.scale.set(scaleX, scaleY, scaleZ);
	cb.src.set((float)srcX, (float)srcY, (float)srcZ);

	cb.resname = resname;
	cb.width = w;
	cb.height = h;
	cb.angle = angle;

	cb.color.set((unsigned int)alpha, (unsigned int)red, (unsigned int)green, (unsigned int)blue);

	cb.show = false;

}

void charabase::InitCharBase(CharaBase& cb, const ci_ext::Vec3f& pos, const ci_ext::Vec3f& add,
	const std::string& resname, const ci_ext::Vec3f& src, int w, int h,
	float angle, const ci_ext::Vec3f& scale,
	int alpha, int red ,int green, int blue)
{
	cb.pos = pos;
	cb.add = add;
	cb.scale = scale;
	cb.src = src;

	cb.resname = resname;
	cb.width = w;
	cb.height = h;
	cb.angle = angle;

	cb.color.set((unsigned int)alpha, (unsigned int)red, (unsigned int)green, (unsigned int)blue);

	cb.show = false;

}

//------------------------------------------------------
//CharBase�R���X�g���N�^

charabase::CharaBase::CharaBase()
:
color(255)
{
}


//------------------------------------------------------
//CharBase����������
//���ׂĂO�ɂ���B

void charabase::InitCharBase(CharaBase& cb)
{
	CharaBase zeroCharBase = {};
	cb = zeroCharBase;
}

//----------------------
//���p�`�F�b�N
bool charabase::CheckUseChar(const CharaBase& cb)
{
	return (cb.show == true);
}

//----------------------
//�ėp�ړ�
void charabase::MoveChar(CharaBase& cb)
{
	cb.pos.offset(cb.add);
}

//----------------------
//�ėp��������
void charabase::NoUseChar(CharaBase& cb)
{
	cb.show = false;
}

//----------------------
//�ėp�o������
void charabase::UseChar(CharaBase& cb)
{
	cb.show = true;
}

//----------------------
//����p��`�쐬 ������W�
//�傫�����N���b�s���O�T�C�Y�ƈقȂ�ꍇ�ɗ��p����B
//startx,starty : ����_����̃I�t�Z�b�g�l�A�l�����ォ����Z�����
//endx,endy : �E���_����̃I�t�Z�b�g�l�A�l���E�����猸�Z�����
void charabase::MakeRectLeftTop(RECT &rt, const CharaBase& cb, int startx, int starty, int endx, int endy)
{
	SetRect(&rt, (int)cb.pos.x()+startx, (int)cb.pos.y() + starty,
				(int)cb.pos.x()+cb.width - endx,(int)cb.pos.y()+cb.height - endy);
}

//----------------------
//����p��`�쐬 �������W�
//�傫�����N���b�s���O�T�C�Y�ƈقȂ�ꍇ�ɗ��p����B
//startx,starty : ����_����̃I�t�Z�b�g�l�A�l�����ォ����Z�����
//endx,endy : �E���_����̃I�t�Z�b�g�l�A�l���E�����猸�Z�����
void charabase::MakeRect(RECT &rt, const CharaBase& cb, int startx, int starty, int endx, int endy)
{
	SetRect(&rt, (int)cb.pos.x() - cb.width / 2 + startx, (int)cb.pos.y() - cb.height / 2 + starty,
				(int)cb.pos.x()+cb.width/2 - endx,(int)cb.pos.y()+cb.height/2 - endy);
}

//----------------------
//����p��`�쐬 �������W��@�g�嗦�l��
//�傫�����N���b�s���O�T�C�Y�ƈقȂ�ꍇ�ɗ��p����B
//startx,starty : ����_����̃I�t�Z�b�g�l�A�l�����ォ����Z�����
//endx,endy : �E���_����̃I�t�Z�b�g�l�A�l���E�����猸�Z�����
void charabase::MakeRectScales(RECT &rt, const CharaBase& cb, int startx, int starty, int endx, int endy)
{
	SetRect(
    &rt,
    int(cb.pos.x() - ((float)cb.width*cb.scale.x()) / 2.f + (float)startx),
    int(cb.pos.y() - ((float)cb.height * cb.scale.y()) / 2.f + (float)starty),
    int(cb.pos.x() + ((float)cb.width*cb.scale.x()) / 2.f - (float)endx),
    int(cb.pos.y() + ((float)cb.height * cb.scale.y()) / 2.f - (float)endy));
}
//----------------------
//�ėp�`�揈�� �����
void charabase::Draw_CharBuruburu(const CharaBase& cb, int range)
{
  int buruburu_x = math::GetRandom(-range, range);
	int buruburu_y = math::GetRandom(-range, range);
	graph::Draw_Graphics(
    cb.pos.x()+buruburu_x, cb.pos.y()+buruburu_y, cb.pos.z(),
    cb.resname,
    cb.width	* (int)(cb.src.x()),
    cb.height * (int)(cb.src.y()),
    cb.width, cb.height,
    cb.angle,
    cb.scale.x(), cb.scale.y(),
	(u_char)cb.color.a(), (u_char)cb.color.r(), (u_char)cb.color.g(), (u_char)cb.color.b());
}

//----------------------
//�ėp�`�揈�� �����
void charabase::Draw_Char(const CharaBase& pos)
{
	graph::Draw_Graphics(
				pos.pos.x(),pos.pos.y(),pos.pos.z(),
				pos.resname,
				pos.width	* (int)(pos.src.x()),
				pos.height * (int)(pos.src.y()),
				pos.width,pos.height,
				pos.angle,
				pos.scale.x(),pos.scale.y(),
				(u_char)pos.color.a(), (u_char)pos.color.r(), (u_char)pos.color.g(), (u_char)pos.color.b());
}

//----------------------
//�ėp�`�揈�� ����
void charabase::Draw_Char2(const CharaBase& pos)
{
  graph::Draw_GraphicsLeftTop(
				pos.pos.x(),pos.pos.y(),pos.pos.z(),
				pos.resname,
				pos.width	* (int)(pos.src.x()),
				pos.height * (int)(pos.src.y()),
				pos.width,pos.height,
				pos.angle,nullptr,
				pos.scale.x(),pos.scale.y(),
				(u_char)pos.color.a(), (u_char)pos.color.r(), (u_char)pos.color.g(), (u_char)pos.color.b());
}


//----------------------
//�ėp�`�揈�� �����
void charabase::Draw_CharNC(const CharaBase& pos)
{

	graph::Draw_GraphicsNC(
				pos.pos.x(),pos.pos.y(),pos.pos.z(),
				pos.resname,
				pos.width	* (int)(pos.src.x()),
				pos.height * (int)(pos.src.y()),
				pos.width,pos.height,
				pos.angle,
				pos.scale.x(),pos.scale.y(),
				(u_char)pos.color.a(), (u_char)pos.color.r(), (u_char)pos.color.g(), (u_char)pos.color.b());
}

//----------------------
//�ėp�`�揈�� ����
void charabase::Draw_Char2NC(const CharaBase& pos)
{
	graph::Draw_GraphicsLeftTopNC(
				pos.pos.x(),pos.pos.y(),pos.pos.z(),
				pos.resname,
				pos.width	* (int)(pos.src.x()),
				pos.height * (int)(pos.src.y()),
				pos.width,pos.height,
				pos.angle,nullptr,
				pos.scale.x(),pos.scale.y(),
				(u_char)pos.color.a(), (u_char)pos.color.r(), (u_char)pos.color.g(), (u_char)pos.color.b());
}
//----------------------
//������`�F�b�N
bool charabase::HitCheck(const CharaBase& v1, const CharaBase& v2, bool debug_mode)
{
	RECT rt1;
	RECT rt2;
	charabase::MakeRect(rt1, v1);
	charabase::MakeRect(rt2,v2);
//�f�o�b�O----------------
  if (debug_mode)
  {
    graph::Draw_CkRect(rt1);
    graph::Draw_CkRect(rt2);
  }
//�����܂�----------------
	if(math::RectCheck(&rt1,&rt2) ){
			return true;
	}else{
		return false;
	}
}

//----------------------
//������`�F�b�N �g�嗦�l��
bool charabase::HitCheckScales(const CharaBase& v1, const CharaBase& v2, bool debug_mode)
{
	RECT rt1;
	RECT rt2;
	charabase::MakeRectScales(rt1, v1);
	charabase::MakeRectScales(rt2, v2);
	//�f�o�b�O----------------
  if (debug_mode)
  {
    graph::Draw_CkRect(rt1);
    graph::Draw_CkRect(rt2);
  }
  //�����܂�----------------
	if (math::RectCheck(&rt1, &rt2)){
		return true;
	}
	else{
		return false;
	}
}

//----------------------
//�g�`��
//  cb_ charbase���
//  color �F���iARGB�ł��w��\�j
//  lineweight ���C���̑���
void charabase::Draw_Frame(const CharaBase& cb, ci_ext::Color color, int lineweight)
{
  ci_ext::Polygon<float> a(
    ci_ext::Vec3<float>(cb.pos.x(), cb.pos.y(), cb.pos.z()), //pos
    {
    ci_ext::Vec3<float>(-cb.width / 2.0f, -cb.height / 2.0f, 0.0f),
    ci_ext::Vec3<float>(-cb.width / 2.0f, cb.height / 2.0f, 0.0f),
    ci_ext::Vec3<float>(cb.width / 2.0f, cb.height / 2.0f, 0.0f),
    ci_ext::Vec3<float>(cb.width / 2.0f, -cb.height / 2.0f, 0.0f),
    },//vertex
    cb.angle,//degree
    ci_ext::Vec3<float>(cb.scale.x(), cb.scale.y(), 1.0f)//scale
    );

    a.draw(color, lineweight);
}
//----------------------
//������`�F�b�N
bool charabase::HitCheck2(const CharaBase& cb1, const CharaBase& cb2, bool debug_mode)
{
  //�|���S������Ĕ��肳����
  ci_ext::Polygon<float> a(
    ci_ext::Vec3<float>(cb1.pos.x(), cb1.pos.y(), cb1.pos.z()), //pos
    {
    ci_ext::Vec3<float>(-cb1.width / 2.0f, -cb1.height / 2.0f, 0.0f),
    ci_ext::Vec3<float>(-cb1.width / 2.0f, cb1.height / 2.0f, 0.0f),
    ci_ext::Vec3<float>(cb1.width / 2.0f, cb1.height / 2.0f, 0.0f),
    ci_ext::Vec3<float>(cb1.width / 2.0f, -cb1.height / 2.0f, 0.0f),
    },//vertex
    cb1.angle,//degree
    ci_ext::Vec3<float>(cb1.scale.x(), cb1.scale.y(), 1.0f)//scale
    );

  ci_ext::Polygon<float> b(
    ci_ext::Vec3<float>(cb2.pos.x(), cb2.pos.y(), cb2.pos.z()),
    {
    ci_ext::Vec3<float>(-cb2.width / 2.0f, -cb2.height / 2.0f, 0.0f),
    ci_ext::Vec3<float>(-cb2.width / 2.0f, cb2.height / 2.0f, 0.0f),
    ci_ext::Vec3<float>(cb2.width / 2.0f, cb2.height / 2.0f, 0.0f),
    ci_ext::Vec3<float>(cb2.width / 2.0f, -cb2.height / 2.0f, 0.0f),
    },
    cb2.angle,
    ci_ext::Vec3<float>(cb2.scale.x(), cb2.scale.y(), 1.0f)
    );

  if (debug_mode)
  {
    charabase::Draw_Frame(cb1, 0xFFFF0000, 1);
    charabase::Draw_Frame(cb2, 0xFFFF0000, 1);
  }
  if (a.intersect(b))
  {
    return true;
  }
  return false;
}


//�����܂�
//------------------------------------------------------
