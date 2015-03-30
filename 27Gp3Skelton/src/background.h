#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/vec3.hpp"
#include "../../lib/ci_ext/color.hpp"

namespace game
{

class IBackGround : public ci_ext::Object
{
  std::string resname_;
  ci_ext::Vec3f pos_;
  ci_ext::Vec3f size_;
  ci_ext::Vec3f scale_;
  ci_ext::Color color_;

public:
  IBackGround(const std::string& objectName,const std::string &resname);

  void init();

  void render() override;
  void update() override;

};

}