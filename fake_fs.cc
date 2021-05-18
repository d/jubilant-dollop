#include "fake_fs.h"

namespace csv_query {
FakeFs::FakeFs(std::string string) : string_(std::move(string)) {}

std::istream& FakeFs::DoOpen([[gnu::unused]] const std::string& name) {
  stream_.str(string_);
  return stream_;
}
}  // namespace csv_query
