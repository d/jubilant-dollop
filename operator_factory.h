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
  virtual RecordSet* DoTake(const RecordSet& child, size_t limit) = 0;
  virtual RecordSet* DoOrderBy(const RecordSet& child,
                               std::string order_key) = 0;
  virtual RecordSet* DoCountBy(const RecordSet& child,
                               std::string group_key) = 0;
  virtual RecordSet* DoJoin(const RecordSet& lhs,
                            const RecordSet& rhs,
                            std::string join_key) = 0;

 public:
  auto From(std::string name, FsProvider& fs_provider) {
    return std::unique_ptr<RecordSet>{DoFrom(std::move(name), fs_provider)};
  }

  auto Select(const RecordSet& child, std::string attribute) {
    return std::unique_ptr<RecordSet>{DoSelect(child, std::move(attribute))};
  }

  auto Take(const RecordSet& child, size_t limit) {
    return std::unique_ptr<RecordSet>{DoTake(child, limit)};
  }

  auto OrderBy(const RecordSet& child, std::string order_key) {
    return std::unique_ptr<RecordSet>{DoOrderBy(child, std::move(order_key))};
  }

  auto CountBy(const RecordSet& child, std::string group_key) {
    return std::unique_ptr<RecordSet>{DoCountBy(child, std::move(group_key))};
  }

  auto Join(const RecordSet& lhs, const RecordSet& rhs, std::string join_key) {
    return std::unique_ptr<RecordSet>{DoJoin(lhs, rhs, std::move(join_key))};
  }
};
}  // namespace csv_query

#endif  // CSVQUERY__OPERATOR_FACTORY_H_
