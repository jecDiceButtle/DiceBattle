#pragma once

#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/Counter.hpp"

#include <iostream>
#include "title.h"

namespace game
{

class Logo : public ci_ext::Object
{
  enum class State//�V�[���؂�ւ��p
  {
    up,    //��������񓧖���
    stop,  //���S�\��
    down,  //�񓧖����瓧����
    end    //�I������
  };
  State state_;  //���݂̃V�[��
  int alpha_;    //�񓧖��x
  std::weak_ptr<ci_ext::Object> timer_; //�o�ߎ��Ԃ��Ǘ�
  std::string resname_;

  //�\�������鎞�Ԃ�b�Őݒ�
  const float waitSecond_ = 1.0f;     //��\������t�F�[�h�C���J�n�܂ł̕b��
  const float chhangeAlphaSec_ = 0.6f;//�t�F�[�h�C���t�F�[�h�A�E�g�̕b��
  const float drawLogoSec_ = 2.0f;    //���S��\�����Ă��鎞��

  void changeState(State nextState)
  {
    switch (nextState)
    {
    case State::up:
      alpha_ = alpha_ < 0 ? 0 : alpha_;
      break;

    case State::stop:
      alpha_ = 255;
      break;

    case State::down:
      alpha_ = alpha_ > 255 ? 255 : alpha_;
      break;

    case State::end:
      //�V�[���J��
      insertToParentSleep(new CSceneTitle("Title"), 120);
      kill();
      break;
    }
    state_ = nextState;
  }
public:
  Logo(const std::string& taskname)
    :
    Object(taskname),
    state_(State::up),
    alpha_(0),
    resname_("logo")
  {
    gplib::graph::Draw_LoadObject(resname_, "res/gra/logo.png");
  }

  //�R���X�g���N�^�ł͐e�q�֌W���\�z�ł��Ȃ��d�l�Ȃ̂ŁA
  //�������Ɏq����o�^�������ꍇ��init()�ōs��
  //init()�̓I�u�W�F�N�g���ꊇ�ǉ�����Ƃ��Ɏ����ŌĂ΂��
  void init() override
  {
    //�J�E���^�𐶐����A�����擾���Ȃ��ėǂ��悤��weak_ptr��ێ����Ă���
    timer_ = insertAsChild(new ci_ext::TimeCounter<float>(name() + "timecounter_"));
  }

  //���̃I�u�W�F�N�g������������j�������Ƃ��ɌĂ΂��A�f�X�g���N�^
  ~Logo() override
  {
    gplib::graph::Draw_DeleteObject(resname_);
  }

  //�P�t���[���ōs���\�������A���S�̂ݕ\������
  void render() override
  {
    gplib::graph::Draw_Graphics(
      gplib::system::WINW / 2, gplib::system::WINH / 2, 0.5f,
      resname_,
      0, 0,
      gplib::graph::Draw_GetImageWidth(resname_), gplib::graph::Draw_GetImageHeight(resname_),
      0,
      1.0f, 1.0f,
      alpha_);
  }
  void renderPause() override
  {
    render();
    std::cout << "Logo::pause" << std::endl;
  }
  //�P�t���[���ōs������
  void update() override
  {
    float ms = 0;
    {
      //�I�u�W�F�N�g�����b�N���Ďg�p�\�ɂ��A�^�C�}�[��������̃~���b���擾����
      auto timer = ci_ext::weak_to_shared<ci_ext::TimeCounter<float>>(timer_);
      float temp = (timer->get() - waitSecond_);//�t�F�[�h�C���ɓ���܂ł̎��Ԃ͊��Z���Ȃ�
      ms = temp < 0 ? 0 : temp;
    }
    //���݂̃X�e�[�g�ɂ���ď�����ύX
    switch (state_)
    {
      //�񓧖��x�����Z
      case State::up:
        alpha_ = static_cast<int>(255.0f * (ms / chhangeAlphaSec_));
        if (ms > chhangeAlphaSec_)
          changeState(State::stop);
        break;

      //��~��
      case State::stop:
        //�K��b��������A�������̏����ֈڍs
        if (ms > chhangeAlphaSec_ + drawLogoSec_)
          changeState(State::down);
        break;

      //������
      case State::down:
        {
          //�t�F�[�h�A�E�g�ɓ��鎞�Ԃ���K��̕b���Ńt�F�[�h�A�E�g���I��������
          auto temp = (chhangeAlphaSec_ + chhangeAlphaSec_ + drawLogoSec_) - ms;
          alpha_ = static_cast<int>(255.0f * (temp / chhangeAlphaSec_));
          if (temp < 0.0f)
            changeState(State::end);
        }
        break;
    }
  }

};

}