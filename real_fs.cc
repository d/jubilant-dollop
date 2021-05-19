#include "real_fs.h"

namespace csv_query {
std::istream& RealFs::DoOpen(const std::string& name) {
  fs_.close();
  fs_.open(name);
  return fs_;
}
}  // namespace csv_query
