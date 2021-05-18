#include "query.h"

#include <string_view>

static constexpr std::string_view kFrom = "FROM", kSelect = "SELECT",
                                  kTake = "TAKE", kOrderBy = "ORDERBY",
                                  kJoin = "JOIN", kCountBy = "COUNTBY";

namespace csv_query {
Query::Query(FsProvider& fs_provider,
             OperatorFactory& factory,
             const std::string& query)
    : fs_provider_(fs_provider), factory_(factory), query_(query) {}

RecordSet* Query::Parse() {
  std::string token;
  while (query_ >> token) {
    if (token == kFrom) {
      query_ >> token;
      ops_.push_back(factory_.From(token, fs_provider_));
    } else if (token == kSelect) {
      query_ >> token;
      ops_.push_back(factory_.Select(*ops_.back(), token));
    } else [[unlikely]] {
      return nullptr;
    }
  }
  return ops_.back().get();
}
}  // namespace csv_query
