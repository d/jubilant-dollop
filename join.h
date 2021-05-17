#ifndef CSVQUERY__JOIN_H_
#define CSVQUERY__JOIN_H_

#include <string>
#include "record_set.h"

namespace csv_query {
class Join : public RecordSet {
 public:
  Join(const RecordSet& lhs, const RecordSet& rhs, std::string join_key);
  std::vector<std::string_view> AttributeNames() const override;
  std::vector<Record> Records() const override;

 private:
  const RecordSet& lhs_;
  const RecordSet& rhs_;
  std::string join_key_;
  std::vector<std::string_view> lhs_attrs_;
  std::vector<std::string_view> rhs_attrs_;
  size_t join_key_lhs_pos_;
  size_t join_key_rhs_pos_;
};
}  // namespace csv_query

#endif  // CSVQUERY__JOIN_H_
