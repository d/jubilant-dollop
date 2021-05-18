#ifndef CSVQUERY__FROM_H_
#define CSVQUERY__FROM_H_

#include <string>
#include "fs_provider.h"
#include "record_set.h"

namespace csv_query {
class From : public RecordSet {
 public:
  From(std::string name, FsProvider& fs_provider);
  std::vector<std::string_view> AttributeNames() const override;
  std::vector<Record> Records() const override;

 private:
  const std::string name_;
  FsProvider& fs_provider_;
  const Record attributes_;
};
}  // namespace csv_query

#endif  // CSVQUERY__FROM_H_
