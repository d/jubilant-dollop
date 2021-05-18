#ifndef CSVQUERY__RECORDSET_H_
#define CSVQUERY__RECORDSET_H_

#include <string>
#include <string_view>
#include <vector>

namespace csv_query {
using Record = std::vector<std::string>;
using Records = std::vector<Record>;

class RecordSet {
 public:
  virtual std::vector<std::string_view> AttributeNames() const = 0;
  virtual std::vector<Record> Records() const = 0;
};
}  // namespace csv_query

#endif  // CSVQUERY__RECORDSET_H_
