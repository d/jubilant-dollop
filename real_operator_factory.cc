#include "real_operator_factory.h"
#include "count_by.h"
#include "from.h"
#include "join.h"
#include "order_by.h"
#include "select.h"
#include "take.h"

namespace csv_query {
RecordSet* RealOperatorFactory::DoFrom(std::string name,
                                       FsProvider& fs_provider) {
  return new class From(std::move(name), fs_provider);
}

RecordSet* RealOperatorFactory::DoSelect(const RecordSet& child,
                                         std::string attribute) {
  return new class Select(child, std::move(attribute));
}

RecordSet* RealOperatorFactory::DoTake(const RecordSet& child, size_t limit) {
  return new class Take(child, limit);
}

RecordSet* RealOperatorFactory::DoOrderBy(const RecordSet& child,
                                          std::string order_key) {
  return new class OrderBy(child, std::move(order_key));
}

RecordSet* RealOperatorFactory::DoCountBy(const RecordSet& child,
                                          std::string group_key) {
  return new class CountBy(child, std::move(group_key));
}

RecordSet* RealOperatorFactory::DoJoin(const RecordSet& lhs,
                                       const RecordSet& rhs,
                                       std::string join_key) {
  return new class Join(lhs, rhs, std::move(join_key));
}

RealOperatorFactory::RealOperatorFactory(FsProvider& fs) : fs_(fs) {}
}  // namespace csv_query
