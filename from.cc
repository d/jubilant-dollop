#include "from.h"

#include <range/v3/view.hpp>
#include <utility>
#include "stl_extras.h"

namespace views = ranges::views;

namespace csv_query {
static Record FromLine(const std::string& line) {
  return MakeVector(line | views::split(',') | views::transform(MakeString));
}

From::From(std::string name, FsProvider& fs_provider)
    : name_(std::move(name)),
      fs_provider_(fs_provider),
      attributes_(FromLine(fs_provider_.Header(name_))) {}

std::vector<std::string_view> From::AttributeNames() const {
  return {attributes_.begin(), attributes_.end()};
}

std::vector<Record> From::Records() const {
  return MakeVector(fs_provider_.DataLines(name_) | views::transform(FromLine));
}
}  // namespace csv_query
