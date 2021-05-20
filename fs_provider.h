#ifndef CSVQUERY__FS_PROVIDER_H_
#define CSVQUERY__FS_PROVIDER_H_

#include <algorithm>
#include <istream>
#include <iterator>
#include <range/v3/view.hpp>
#include <string>
#include "stl_extras.h"

namespace csv_query {
class FsProvider {
 private:
  auto Lines(const std::string& name) {
    return csv_query::Lines(
        ranges::subrange(std::istreambuf_iterator<char>(DoOpen(name)),
                         std::istreambuf_iterator<char>()));
  }

 public:
  // returns a range of string, each representing a line from the file (skipping
  // the header line)
  auto DataLines(const std::string& name) {
    namespace views = ranges::views;
    // drop the header line
    return Lines(name) | views::drop(1);
  }

  std::string Header(const std::string& name) {
    namespace views = ranges::views;
    // extract the header line
    auto header_lines = Lines(name) | views::take(1);
    return *header_lines.begin();
  }

 private:
  virtual std::istream& DoOpen(const std::string& name) = 0;
};
}  // namespace csv_query

#endif  // CSVQUERY__FS_PROVIDER_H_
