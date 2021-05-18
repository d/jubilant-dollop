#ifndef CSVQUERY__FAKE_FS_H_
#define CSVQUERY__FAKE_FS_H_

#include <sstream>
#include "fs_provider.h"

namespace csv_query {
class FakeFs : public FsProvider {
 public:
  FakeFs(std::string string);

 private:
  std::istream& DoOpen(const std::string& name) override;

  const std::string string_;
  std::istringstream stream_;
};
}  // namespace csv_query

#endif  // CSVQUERY__FAKE_FS_H_
