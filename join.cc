#include "join.h"

#include <functional>
#include <map>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>
#include <utility>

namespace views = ranges::views;

namespace csv_query {
Join::Join(const RecordSet& lhs, const RecordSet& rhs, std::string join_key)
    : lhs_(lhs),
      rhs_(rhs),
      join_key_(std::move(join_key)),
      lhs_attrs_(lhs_.AttributeNames()),
      rhs_attrs_(rhs_.AttributeNames()),
      join_key_lhs_pos_([&lhs_attrs = lhs_attrs_, &join_key = join_key_]() {
        return ranges::find(lhs_attrs, join_key) - lhs_attrs.begin();
      }()),
      join_key_rhs_pos_([&rhs_attrs = rhs_attrs_, &join_key = join_key_]() {
        return ranges::find(rhs_attrs, join_key) - rhs_attrs.begin();
      }()) {}

std::vector<std::string_view> Join::AttributeNames() const {
  std::vector<std::string_view> ret = lhs_attrs_;
  for (size_t i = 0; i < rhs_attrs_.size(); ++i) {
    if (i == join_key_rhs_pos_) {
      continue;
    }
    ret.push_back(rhs_attrs_[i]);
  }
  return ret;
}

std::vector<Record> Join::Records() const {
  std::multimap<std::string_view, std::reference_wrapper<const Record> >
      lhs_map, rhs_map;
  auto l_records = lhs_.Records();
  auto r_records = rhs_.Records();
  for (const auto& r : l_records) {
    lhs_map.insert({r[join_key_lhs_pos_], r});
  }
  for (const auto& r : r_records) {
    rhs_map.insert({r[join_key_rhs_pos_], r});
  }

  auto Project = [this](const Record& lv, const Record& rv) {
    Record projected = lv;
    for (size_t i = 0; i < rhs_attrs_.size(); ++i) {
      if (i == join_key_rhs_pos_) {
        continue;
      }
      projected.push_back(rv[i]);
    }
    return projected;
  };

  std::vector<Record> ret;
  for (auto lhs_it = lhs_map.begin(), lhs_end = lhs_map.end();
       lhs_it != lhs_end;) {
    auto lhs_next =
        ranges::upper_bound(lhs_it, lhs_end, lhs_it->first, ranges::less{},
                            [](const auto& kv) { return kv.first; });
    auto [rhs_it, rhs_next] = rhs_map.equal_range(lhs_it->first);

    for (const auto& lv : ranges::subrange(lhs_it, lhs_next) | views::values) {
      for (const auto& rv :
           ranges::subrange(rhs_it, rhs_next) | views::values) {
        ret.push_back(Project(lv, rv));
      }
    }
    lhs_it = lhs_next;
  }
  return ret;
}
}  // namespace csv_query
