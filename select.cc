#include "select.h"

#include <algorithm>
#include <functional>
#include <ranges>
#include <utility>
#include "stl_extras.h"

namespace ranges = std::ranges;
namespace views = ranges::views;

namespace csv_query {
Select::Select(const RecordSet& child, std::string attribute)
    : child_(child), attribute_(std::move(attribute)) {}

std::vector<std::string_view> Select::AttributeNames() const {
  return {attribute_};
}

std::vector<Record> Select::Records() const {
  auto index = [child_attrs = child_.AttributeNames(), &att = attribute_]() {
    return ranges::find(child_attrs, att) - child_attrs.begin();
  }();

  auto Project = [index](const Record& r) { return Record{r[index]}; };

  std::vector<Record> ret;
  ranges::transform(child_.Records(), std::back_inserter(ret), Project);
  return ret;
}

}  // namespace csv_query
