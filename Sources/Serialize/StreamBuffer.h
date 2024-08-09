#pragma once

#include <stdint.h>

#include <Core/Error.h>
#include <Serialize/Utils.h>


namespace zv
{
  class StreamBuffer
  {
  public:
    explicit StreamBuffer(char* ptr_buffer, int32_t buffer_size)
      : m_ptr_buffer(ptr_buffer)
      , m_buffer_size(buffer_size)
    {}
    virtual ~StreamBuffer() = default;

  public:
    void release()
    {
      m_ptr_buffer = nullptr;
      m_buffer_size = 0;
    }

  protected:
    template<typename T>
    [[nodiscard]] T* get_data(int32_t offset) const noexcept(true)
    {
      ZV_ASSERT_MSG(offset >= 0 && offset < m_buffer_size, "[StreamBuffer::get_data] Offset is invalid. {{offset:{}, size:{}}}", offset, m_buffer_size);
      return get_offset_ptr<T>(m_ptr_buffer, offset);
    }

    [[nodiscard]] constexpr bool empty(void) const noexcept { return m_ptr_buffer == nullptr; }

	private:
		char* m_ptr_buffer{ nullptr };
		int32_t	m_buffer_size{ 0 };
  };
}
