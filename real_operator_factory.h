#ifndef CSVQUERY__REAL_OPERATOR_FACTORY_H_
#define CSVQUERY__REAL_OPERATOR_FACTORY_H_

#include "fs_provider.h"
#include "operator_factory.h"

namespace csv_query {
class RealOperatorFactory final : public OperatorFactory {
 public:
  explicit RealOperatorFactory(FsProvider& fs);

 private:
  RecordSet* DoFrom(std::string name, FsProvider& fs_provider) override;
  RecordSet* DoSelect(const RecordSet& child, std::string attribute) override;
  RecordSet* DoTake(const RecordSet& child, size_t limit) override;
  RecordSet* DoOrderBy(const RecordSet& child, std::string order_key) override;
  RecordSet* DoCountBy(const RecordSet& child, std::string group_key) override;
  RecordSet* DoJoin(const RecordSet& lhs,
                    const RecordSet& rhs,
                    std::string join_key) override;
  FsProvider& fs_;
};
}  // namespace csv_query

#endif  // CSVQUERY__REAL_OPERATOR_FACTORY_H_
