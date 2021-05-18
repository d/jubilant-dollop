#ifndef CSVQUERY__FSTREAM_FS_H_
#define CSVQUERY__FSTREAM_FS_H_

#include <fstream>
#include "fs_provider.h"

namespace csv_query {
class FstreamFs : public FsProvider {
  std::istream& DoOpen(const std::string& name) override;
  std::ifstream fs_;
};
}  // namespace csv_query

#endif  // CSVQUERY__FSTREAM_FS_H_
