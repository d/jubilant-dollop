#ifndef CSVQUERY__ORDER_BY_H_
#define CSVQUERY__ORDER_BY_H_

#include <string>
#include "record_set.h"

namespace csv_query {
class OrderBy : public RecordSet {
 public:
  OrderBy(const RecordSet& child, std::string order_key);
  std::vector<std::string_view> AttributeNames() const override;
  std::vector<Record> Records() const override;

 private:
  const RecordSet& child_;
  std::string order_key_;
};
}  // namespace csv_query

#endif  // CSVQUERY__ORDER_BY_H_
