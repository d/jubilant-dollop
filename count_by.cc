#include "count_by.h"

#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>
#include <unordered_map>
#include <utility>
#include "stl_extras.h"

namespace views = ranges::views;

namespace csv_query {
CountBy::CountBy(const RecordSet& child, std::string group_key)
    : child_(child), group_key_(std::move(group_key)) {}

std::vector<std::string_view> CountBy::AttributeNames() const {
  return {group_key_, kCount};
}

std::vector<Record> CountBy::Records() const {
  auto records = child_.Records();
  std::unordered_map<std::string_view, size_t> m;
  auto index = [base_attrs = child_.AttributeNames(),
                &group_key = group_key_]() {
    return ranges::find(base_attrs, group_key) - base_attrs.begin();
  }();
  auto ProjectKey = [index](const Record& r) -> std::string_view {
    return r[index];
  };
  for (auto k : records | views::transform(ProjectKey)) {
    ++m[k];
  }
  return MakeVector(
      m | views::transform([](auto& kv) {
        return Record{std::string{kv.first}, std::to_string(kv.second)};
      }));
}
}  // namespace csv_query
