#ifndef CSVQUERY__OPERATOR_FACTORY_H_
#define CSVQUERY__OPERATOR_FACTORY_H_

#include <memory>
#include <string>
#include "fs_provider.h"
#include "record_set.h"

namespace csv_query {
class OperatorFactory {
  virtual RecordSet* DoFrom(std::string name, FsProvider& fs_provider) = 0;
  virtual RecordSet* DoSelect(const RecordSet& child,
                              std::string attribute) = 0;

 public:
  auto From(std::string name, FsProvider& fs_provider) {
    return std::unique_ptr<RecordSet>{DoFrom(name, fs_provider)};
  }

  auto Select(const RecordSet& child, std::string attribute) {
    return std::unique_ptr<RecordSet>{DoSelect(child, std::move(attribute))};
  }
};
}  // namespace csv_query

#endif  // CSVQUERY__OPERATOR_FACTORY_H_
