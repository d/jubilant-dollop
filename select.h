#ifndef CSVQUERY__SELECT_H_
#define CSVQUERY__SELECT_H_

#include "record_set.h"

namespace csv_query {
class Select : public RecordSet {
 public:
  Select(const RecordSet& child, std::string attribute);
  std::vector<std::string_view> AttributeNames() const override;
  std::vector<Record> Records() const override;

 private:
  const RecordSet& child_;
  const std::string attribute_;
};
}  // namespace csv_query

#endif  // CSVQUERY__SELECT_H_
