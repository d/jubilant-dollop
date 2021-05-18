#ifndef CSVQUERY__MOCK_FS_H_
#define CSVQUERY__MOCK_FS_H_

#include "fs_provider.h"
#include "gmock/gmock.h"

namespace csv_query {
struct MockFs : FsProvider {
  MOCK_METHOD(std::istream&, DoOpen, (const std::string& name), (override));
};
}  // namespace csv_query

#endif  // CSVQUERY__MOCK_FS_H_
