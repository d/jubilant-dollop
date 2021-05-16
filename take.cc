#include "take.h"

namespace csv_query {
Take::Take(const RecordSet& child, size_t limit)
    : child_(child), limit_(limit) {}

std::vector<std::string_view> Take::AttributeNames() const {
  return child_.AttributeNames();
}

std::vector<Record> Take::Records() const {
  auto r = child_.Records();
  if (r.size() > limit_) {
    r.resize(limit_);
  }
  return r;
}

}  // namespace csv_query
