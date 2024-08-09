#pragma once

#include <Util/PrimitiveTypes.h>


namespace zv
{
  enum class eComponentType : s32
  {
    Collider,
    PlayerController,

    Size,
  };

  enum class eSingletonComponentType : s32
  {
    SingletonCamera,
    SingletonInput,
    SingletonPlayerCommand,
    SingletonPhysicsContactInfo,
    SingletonPhysicsWorld,

    Size,
  };
}
