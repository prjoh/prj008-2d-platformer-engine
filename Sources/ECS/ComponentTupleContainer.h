#pragma once

#include <tuple>
#include <vector>


namespace zv
{
    // Define ComponentTuple class to wrap std::tuple<T*>
    template<typename... Ts>
    class ComponentTuple
    {
    public:
      // Construct ComponentTuple from pointers
      ComponentTuple(Ts*... args) : m_tuple(args...) {}

      // Accessor method to get the pointer type contained in the tuple
      template<typename T>
      T* get() const {
        static_assert(std::disjunction_v<std::is_same<T, Ts>...>, "T must be one of the tuple types");
        return std::get<T*>(m_tuple);
      }

    private:
      std::tuple<Ts*...> m_tuple;
    };

  template<typename... Ts>
  class ComponentTupleContainer
  {
  public:
    // Iterator for ComponentTupleContainer
    class Iterator {
    public:
      using iterator_category = std::input_iterator_tag;
      using value_type = ComponentTuple<Ts...>;
      using difference_type = std::ptrdiff_t;
      using pointer = value_type*;
      using reference = value_type&;

      Iterator(typename std::vector<ComponentTuple<Ts...>>::iterator iter) : iter_(iter) {}

      Iterator& operator++() {
        ++iter_;
        return *this;
      }

      Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
      }

      bool operator==(const Iterator& other) const {
        return iter_ == other.iter_;
      }

      bool operator!=(const Iterator& other) const {
        return !(*this == other);
      }

      reference operator*() const {
        return *iter_;
      }

    private:
      typename std::vector<ComponentTuple<Ts...>>::iterator iter_;
    };

    Iterator begin() {
      return Iterator(m_tuples.begin());
    }

    Iterator end() {
      return Iterator(m_tuples.end());
    }


  public:
    // Add a new ComponentTuple to the container
    void add_component_tuple(Ts*... args) {
      m_tuples.emplace_back(args...);
    }

    void clear()
    {
      m_tuples.clear();
    }

  private:
    std::vector<ComponentTuple<Ts...>> m_tuples;
  };
}
