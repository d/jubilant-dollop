#include "fstream_fs.h"

namespace csv_query {
std::istream& FstreamFs::DoOpen(const std::string& name) {
  fs_.open(name);
  return fs_;
}
}  // namespace csv_query
