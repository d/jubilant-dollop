#ifndef CSVQUERY__REAL_FS_H_
#define CSVQUERY__REAL_FS_H_

#include "fs_provider.h"

#include <fstream>

namespace csv_query {
class RealFs final : public FsProvider {
  std::istream& DoOpen(const std::string& name) override;
  std::ifstream fs_;
};
}  // namespace csv_query

#endif  // CSVQUERY__REAL_FS_H_
