#ifndef CSVQUERY__COUNT_BY_H_
#define CSVQUERY__COUNT_BY_H_

#include "record_set.h"

namespace csv_query {
class CountBy : public RecordSet {
 public:
  CountBy(const RecordSet& child, std::string group_key);
  std::vector<std::string_view> AttributeNames() const override;
  std::vector<Record> Records() const override;

 private:
  const RecordSet& child_;
  const std::string group_key_;
  static constexpr std::string_view kCount{"count"};
};
}  // namespace csv_query

#endif  // CSVQUERY__COUNT_BY_H_
