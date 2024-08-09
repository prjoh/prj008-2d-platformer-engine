#pragma once

#include <string>

#include <Util/PrimitiveTypes.h>


#define ZV_DEBUG_MODE_ENABLED 1
#define ZV_DEV_TOOLS_ENABLED 0
#define ZV_LOG_ENABLED 1
#define ZV_ASSERT_ENABLED 1

namespace zv
{
  constexpr s32 ZV_WINDOW_WIDTH_DEFAULT = 1280;
  constexpr s32 ZV_WINDOW_HEIGHT_DEFAULT = 720;

  const std::string ZV_EDITOR_TITLE = "Zen Vision Engine";
  const std::string ZV_GAME_TITLE = "My New Game";

  constexpr f32 ZV_FIXED_TIME_STEP = 1.0f / 60.0f;
  constexpr s32 ZV_VELOCITY_ITERATIONS = 8;
  constexpr s32 ZV_POSITION_ITERATIONS = 3;

  constexpr s32 ZV_ENTITY_SIZE = 1 << 14;
  constexpr s32 ZV_ENTITY_COMPONENT_SIZE = 1 << 8;
  constexpr u32 ZV_SYSTEM_SIZE = 3;

  constexpr u32 ZV_RENDERABLE_SIZE = 1 << 14;
  constexpr u32 ZV_COLLIDER_COMPONENT_SIZE = 1 << 14;
  constexpr u32 ZV_PLAYER_CONTROLLER_COMPONENT_SIZE = 1 << 2;

  constexpr u32 ZV_CONTACT_EVENTS_SIZE = 1 << 9;

  enum class eColliderCategory : u16
  {
    Default = 1 << 0,
    Player  = 1 << 1,
    Ground  = 1 << 2,
  };
}
