#ifndef CSVQUERY__MOCKRECORDSET_H_
#define CSVQUERY__MOCKRECORDSET_H_

#include "gmock/gmock.h"
#include "record_set.h"

namespace csv_query {
class FakeRecordSet : public RecordSet {
  std::vector<std::string> attribute_names_;
  std::vector<Record> records_;

 public:
  FakeRecordSet(std::vector<std::string> attribute_names,
                std::vector<Record> records);
  std::vector<std::string_view> AttributeNames() const override;
  std::vector<Record> Records() const override;
};
}  // namespace csv_query

#endif  // CSVQUERY__MOCKRECORDSET_H_
