//
// Created by damian on 10.07.2020.
//

#ifndef MYPROJECT_SHADER_H
#define MYPROJECT_SHADER_H
#include <Color.h>
#include <world/World.h>
#include "Computations.h"
namespace rt {

class Shader
{
public:
  static util::Color shadeHit(const rt::World &world, const rt::Computations &comps);
};

}// namespace rt


#endif//MYPROJECT_SHADER_H
