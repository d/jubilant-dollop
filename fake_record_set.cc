#include "fake_record_set.h"

#include <utility>

namespace csv_query {
std::vector<std::string_view> FakeRecordSet::AttributeNames() const {
  return {attribute_names_.begin(), attribute_names_.end()};
}

std::vector<Record> FakeRecordSet::Records() const {
  return records_;
}

FakeRecordSet::FakeRecordSet(std::vector<std::string> attribute_names,
                             std::vector<Record> records)
    : attribute_names_(std::move(attribute_names)),
      records_(std::move(records)) {}
}  // namespace csv_query
