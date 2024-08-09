#pragma once

#include <ECS/Component.h>
#include <Math/Vector2.h>


namespace zv { class CommandSystem; }

namespace zv
{
  class SingletonPlayerCommand final : public SingletonComponent
  {
    friend class Game;
    friend class CommandSystem;
    friend class ActorControllerSystem;

  public:
    struct Args : public ComponentArgs
    {
    };

    template <typename T>
    struct Command
    {
    public:
      explicit Command(T value) { m_value = value; }

      void set(T value)
      {
        m_updated = m_value != value;
        m_value = value;
      }

      T get() const { return m_value; }

      bool is_updated() const { return m_updated; }
    
    private:
      bool m_updated{ false };
      T    m_value;
    };

  public:
    SingletonPlayerCommand() { m_type = eSingletonComponentType::SingletonPlayerCommand; }
    ~SingletonPlayerCommand() = default;

  private:
    // TODO: Call location unclear!!!
    void create(const ComponentArgs* ptr_args = nullptr) override {}

  private:
    Command<f32>  m_horizontal_move{ 0.0f };
    Command<bool> m_jump_down{ false };
    Command<bool> m_jump_pressed{ false };
  };

  template<>
  inline void SingletonPlayerCommand::Command<f32>::set(f32 value)
  {
    m_updated = !zv::is_near_equal(m_value, value);
    m_value = value;
  }

  template<>
  inline void SingletonPlayerCommand::Command<f64>::set(f64 value)
  {
    m_updated = !zv::is_near_equal(m_value, value);
    m_value = value;
  }
}

// inline void zv::SingletonPlayerCommand::create(const ComponentArgs* pArgs)
// {
//   // TODO: Add to base class???
//   ZV_ASSERT_MSG(pArgs != nullptr, "Expected SingletonPlayerCommand::Args was null.");
//
//   const auto args = *reinterpret_cast<const Args*>(pArgs);
// }
