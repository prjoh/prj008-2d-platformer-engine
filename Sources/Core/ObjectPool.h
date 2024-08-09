#pragma once

#include <array>
#include <cassert>

#include <Core/Error.h>
#include <Core/Guid.h>

#include <Util/NonMovable.h>
#include <Util/PrimitiveTypes.h>


namespace zv
{
  class PooledObject : public NonMovable
  {
    template <typename ObjectType, std::size_t PoolSize>
    friend class ObjectPool;
  
  public:
    enum class ObjectHandle : s32 { Invalid = -1 };

  public:
    PooledObject() = default;
    virtual ~PooledObject() = default;

  public:
    const ObjectHandle get_object_handle() const { return m_id; }

  private:
    void set_next(PooledObject* ptr_next) { m_ptr_next = ptr_next; }
    auto get_next() const -> PooledObject* { return m_ptr_next; }

    void set_object_handle(s32 id) { m_id = static_cast<ObjectHandle>(id); }

  private:
    PooledObject* m_ptr_next{ nullptr };
    ObjectHandle m_id{ ObjectHandle::Invalid };
  };

  class IObjectPoolBase : public NonMovable {};

  template <typename ObjectType>
  class IObjectPool : public IObjectPoolBase
  {
  public:
    virtual auto create() -> ObjectType* { return nullptr; }  // TODO
    virtual void destroy(ObjectType* ptr_object) {}

    virtual auto get_object(PooledObject::ObjectHandle handle) const -> const PooledObject* { return nullptr; }  // TODO
  };

  template <typename ObjectType, std::size_t PoolSize>
  class ObjectPool : public IObjectPool<ObjectType>
  {
    static_assert(std::is_base_of<PooledObject, ObjectType>::value,
                  "ObjectType must be a type or sub-type of PooledObject");

  public:
    ObjectPool()
    {
      m_ptr_first_available = &m_objects[0];

      for (s32 i = 0; i < PoolSize - 1; i++)
      {
        m_objects[i].set_next(&m_objects[i + 1]);
        m_objects[i].set_object_handle(i);
      }

      m_objects[PoolSize - 1].set_next(nullptr);
    }
    ~ObjectPool() = default;

  public:
    auto create() -> ObjectType* override
    {
      // Make sure the pool isn't full.
      ZV_ASSERT(m_ptr_first_available != nullptr);

      // Remove it from the available list.
      auto* ptr_object = m_ptr_first_available;
      m_ptr_first_available = ptr_object->get_next();

      return static_cast<ObjectType*>(ptr_object);
    }

    void destroy(ObjectType* ptr_object) override
    {
      ptr_object->set_next(m_ptr_first_available);
      m_ptr_first_available = ptr_object;
    }

    auto get_object(PooledObject::ObjectHandle handle) const -> const PooledObject* override
    {
      if ((size_t)handle < 0 || (size_t)handle > PoolSize)
      {
        return nullptr;
      }

      // TODO: Verify object state

      return &m_objects[(size_t)handle];
    }


  private:
    std::array<ObjectType, PoolSize> m_objects{};
    PooledObject* m_ptr_first_available{ nullptr };
  };
}
