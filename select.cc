#include "select.h"

#include <algorithm>
#include <functional>
#include <ranges>
#include <utility>
#include "stl_extras.h"

namespace ranges = std::ranges;
namespace views = ranges::views;

namespace csv_query {
Select::Select(const RecordSet& child, std::vector<std::string> attributes)
    : child_(child), attributes_(std::move(attributes)) {}

std::vector<std::string_view> Select::AttributeNames() const {
  return {attributes_.begin(), attributes_.end()};
}

std::vector<Record> Select::Records() const {
  auto indices = MakeVector(views::transform(
      attributes_, [child_attrs = child_.AttributeNames()](const auto& att) {
        return ranges::find(child_attrs, att) - child_attrs.begin();
      }));

  auto Project = [indices = std::move(indices)](const Record& r) {
    return MakeVector(
        views::transform(indices, [&r](auto index) { return r[index]; }));
  };

  std::vector<Record> ret;
  ranges::transform(child_.Records(), std::back_inserter(ret), Project);
  return ret;
}

}  // namespace csv_query
