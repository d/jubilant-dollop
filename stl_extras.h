#ifndef CSVQUERY__STL_EXTRAS_H_
#define CSVQUERY__STL_EXTRAS_H_

#include <iterator>
#include <numeric>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>
#include <string>
#include <vector>

namespace csv_query {
template <class R, class T>
concept RangeOf = ranges::range<R> && requires(const R& r) {
  { *ranges::begin(r) } -> std::convertible_to<T>;
};

template <class C>
auto MakeVector(C&& c) {
  std::vector<std::remove_reference_t<decltype(*c.begin())>> v;
  ranges::copy(c, std::back_inserter(v));
  return v;
}

namespace internal {
struct MakeStringFn {
  template <RangeOf<char> C>
  std::string operator()(C&& c) const {
    std::string s;
    ranges::copy(std::forward<C>(c), std::back_inserter(s));
    return s;
  }
};
}  // namespace internal

// Construct a string given a range of chars
inline constexpr internal::MakeStringFn MakeString;

auto StrSplit(RangeOf<char> auto s, auto delimiter) {
  namespace views = ranges::views;

  std::vector<std::string> ret;
  return s | views::split(delimiter) | views::transform(MakeString);
}

auto Lines(RangeOf<char> auto r) {
  return StrSplit(r, '\n');
}

std::string StrJoin(RangeOf<std::string_view> auto r,
                    std::string_view separator) {
  std::string ret;
  std::string_view sep;
  for (const auto& s : r) {
    ret.append(sep);
    ret.append(s);
    sep = separator;
  }
  return ret;
}

}  // namespace csv_query

#endif  // CSVQUERY__STL_EXTRAS_H_
