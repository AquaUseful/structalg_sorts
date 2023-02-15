#pragma once

#include <bits/iterator_concepts.h>
#include <cassert>
#include <compare>
#include <concepts>
#include <iterator>
#include <vector>

template <std::random_access_iterator BaseIt> class StrideIterator {
public:
  using Self = StrideIterator;
  using SelfRef = Self &;
  using ConstSelfRef = const Self &;

  using difference_type = typename BaseIt::difference_type;
  using value_type = typename BaseIt::value_type;
  using pointer = typename BaseIt::pointer;
  using reference = typename BaseIt::reference;

public:
  StrideIterator() = default;
  StrideIterator(ConstSelfRef) = default;
  StrideIterator(SelfRef &&) = default;

  StrideIterator(const BaseIt iterator, const difference_type step)
      : m_base{iterator}, m_step{step} {}

  inline constexpr reference operator*() const { return *m_base; }

  inline constexpr SelfRef operator++() {
    m_base += m_step;
    return *this;
  }

  inline constexpr SelfRef operator--() {
    m_base -= m_step;
    return *this;
  }

  inline constexpr Self operator++(int) {
    const Self old = *this;
    operator++();
    return old;
  }

  inline constexpr Self operator--(int) {
    const Self old = *this;
    operator--();
    return old;
  }

  inline constexpr std::strong_ordering operator<=>(ConstSelfRef rhs) const {
    assert_comparability(rhs);
    return m_base <=> rhs.m_base;
  }

  inline constexpr bool operator==(ConstSelfRef rhs) const {
    assert_comparability(rhs);
    return m_base == rhs.m_base;
  }

  inline constexpr SelfRef operator+=(const difference_type diff) {
    m_base += diff * m_step;
    return *this;
  }
  inline constexpr SelfRef operator-=(const difference_type diff) {
    m_base -= diff * m_step;
    return *this;
  }

  inline constexpr difference_type operator-(ConstSelfRef rhs) const {
    assert_comparability(rhs);
    return ((m_base - rhs.m_base) / m_step);
  }

  inline constexpr Self operator+(difference_type diff) const {
    Self copy = *this;
    return copy += diff;
  }
  inline constexpr Self operator-(difference_type diff) const {
    Self copy = *this;
    return copy -= diff;
  }
  inline constexpr reference operator[](const difference_type diff) const {
    return *(this + diff);
  }

  inline constexpr friend Self operator+(const difference_type lhs, Self rhs) {
    return rhs += lhs;
  }

  inline constexpr friend Self make_stride_end_iterator(ConstSelfRef first,
                                                        const BaseIt &last) {
    const difference_type dist = std::distance(first.m_base, last);
    const auto strides = dist / first.m_step;
    const StrideIterator<BaseIt> stride_last(
        std::next(first.m_base, first.m_step * strides), first.m_step);
    return stride_last;
  }

private:
  inline constexpr bool is_comparable_with(ConstSelfRef rhs) const {
    return ((m_step == rhs.m_step) &&
            (std::distance(m_base, rhs.m_base) % m_step == 0));
  }

  inline constexpr void assert_comparability(ConstSelfRef rhs) const {
    assert(is_comparable_with(rhs));
  }

private:
  BaseIt m_base{nullptr};
  difference_type m_step{1};
};

static_assert(std::random_access_iterator<
              StrideIterator<typename std::vector<int>::iterator>>);
