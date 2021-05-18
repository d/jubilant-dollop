#ifndef CSVQUERY__STL_EXTRAS_H_
#define CSVQUERY__STL_EXTRAS_H_

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

namespace csv_query {
template <class C>
auto MakeVector(C&& c) {
  std::vector<std::remove_reference_t<decltype(*c.begin())>> v;
  std::ranges::copy(c, std::back_inserter(v));
  return v;
}

namespace internal {
struct MakeStringFn {
  std::string operator()(auto&& c) const {
    std::string s;
    std::ranges::copy(c, std::back_inserter(s));
    return s;
  }
};
}  // namespace internal

// Construct a string given a range of chars
inline constexpr internal::MakeStringFn MakeString;

}  // namespace csv_query

#endif  // CSVQUERY__STL_EXTRAS_H_
