#ifndef CSVQUERY__TAKE_H_
#define CSVQUERY__TAKE_H_

#include <ranges>
#include "record_set.h"

namespace csv_query {
class Take : public RecordSet {
 public:
  Take(const RecordSet& child, size_t limit);
  std::vector<std::string_view> AttributeNames() const override;
  std::vector<Record> Records() const override;

 private:
  const RecordSet& child_;
  size_t limit_;
};
}  // namespace csv_query

#endif  // CSVQUERY__TAKE_H_
