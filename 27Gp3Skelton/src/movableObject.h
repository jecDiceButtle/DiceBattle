#pragma once
#include "../../lib/ci_ext/object.hpp"
#include "../../lib/ci_ext/DrawObj.hpp"

namespace game
{

class MovableObject : public ci_ext::Object
{
  ci_ext::DrawObjf body_;
  ci_ext::Vec3f velocity_;
public:
  MovableObject(const std::string& objectName, const ci_ext::DrawObjf& f,
    float degree, float speed);
  ci_ext::DrawObjf getBody();
  ci_ext::Vec3f getVelocity();

  //–¢Žg—p
  void render() override;
  void update() override;
};

}