#include "movableObject.h"
#include "../../lib/ci_ext/math.hpp"

#include <iostream>

namespace game
{

MovableObject::MovableObject(const std::string& objectName, const ci_ext::DrawObjf& f, float degree, float speed)
  :
  Object(objectName),
  body_(f),
  velocity_( cos(ci_ext::DegreeToRadian(degree)) * speed, -sin(ci_ext::DegreeToRadian(degree)) * speed, 0)
{
}

void MovableObject::render()
{
  body_.render();
}

void MovableObject::update()
{
  body_.offsetPos(velocity_);
  auto halfsize = body_.halfsize<float>();
  if (!gplib::camera::InScreenCameraCenter(
    body_.x(), body_.y(),
    halfsize.x(),
    halfsize.y()))
  {
    std::cout << "kill" << std::endl;
    kill();
  }
}

ci_ext::DrawObjf MovableObject::getBody()
{
  return body_;
}

ci_ext::Vec3f MovableObject::getVelocity()
{
  return velocity_;
}

}