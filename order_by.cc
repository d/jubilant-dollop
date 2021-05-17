#include "order_by.h"

#include <algorithm>
#include <utility>

namespace ranges = std::ranges;

namespace csv_query {
OrderBy::OrderBy(const RecordSet& child, std::string order_key)
    : child_(child), order_key_(std::move(order_key)) {}

std::vector<std::string_view> OrderBy::AttributeNames() const {
  return child_.AttributeNames();
}

std::vector<Record> OrderBy::Records() const {
  auto ret = child_.Records();
  auto attrs = child_.AttributeNames();
  auto i = ranges::find(attrs, order_key_) - attrs.begin();

  ranges::sort(ret, std::greater{},
               [i](const Record& r) { return std::stoi(r[i]); });
  return ret;
}
}  // namespace csv_query
