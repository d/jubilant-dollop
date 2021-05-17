#ifndef CSVQUERY__SELECT_H_
#define CSVQUERY__SELECT_H_

#include "record_set.h"

namespace csv_query {
class Select : public RecordSet {
 public:
  Select(const RecordSet& child, std::vector<std::string> attributes);
  std::vector<std::string_view> AttributeNames() const override;
  std::vector<Record> Records() const override;

 private:
  const RecordSet& child_;
  std::vector<std::string> attributes_;
};
}  // namespace csv_query

#endif  // CSVQUERY__SELECT_H_
