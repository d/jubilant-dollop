#ifndef CSVQUERY__QUERY_H_
#define CSVQUERY__QUERY_H_

#include <memory>
#include <sstream>
#include <vector>

#include "operator_factory.h"

namespace csv_query {
class Query {
  FsProvider& fs_provider_;
  OperatorFactory& factory_;
  std::istringstream query_;
  std::vector<std::unique_ptr<RecordSet>> ops_;

 public:
  Query(FsProvider& fs_provider,
        OperatorFactory& factory,
        const std::string& query);

  RecordSet* Parse();
};
}  // namespace csv_query

#endif  // CSVQUERY__QUERY_H_
