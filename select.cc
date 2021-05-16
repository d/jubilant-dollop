#include "select.h"

#include <algorithm>
#include <functional>
#include <utility>

namespace ranges = std::ranges;

namespace csv_query {
Select::Select(const RecordSet& child, std::vector<std::string> attributes)
    : child_(child), attributes_(std::move(attributes)) {}

std::vector<std::string_view> Select::AttributeNames() const {
  return {attributes_.begin(), attributes_.end()};
}

std::vector<Record> Select::Records() const {
  std::vector<Record> ret;
  ranges::transform(child_.Records(), std::back_inserter(ret),
                    [this](const Record& r) { return Project(r); });
  return ret;
}

Record Select::Project(const Record& record) const {
  Record projected;

  auto underlying_attrs = child_.AttributeNames();
  ranges::transform(attributes_, std::back_inserter(projected),
                    [&underlying_attrs, &record](const auto& att) {
                      auto i = ranges::find(underlying_attrs, att) -
                               underlying_attrs.begin();
                      return record[i];
                    });

  return projected;
}
}  // namespace csv_query
