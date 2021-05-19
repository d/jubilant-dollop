#include "query.h"
#include "real_fs.h"
#include "real_operator_factory.h"
#include "stl_extras.h"

#include <iostream>
#include <ranges>
#include <string>

namespace ranges = std::ranges;
namespace views = std::ranges::views;

namespace csv_query {
namespace {
template <RangeOf<std::string_view> RecordLike>
struct RecordFormatter {
  const RecordLike& record;
  // NOLINTNEXTLINE(google-explicit-constructor)
  RecordFormatter(const RecordLike& record) : record(record) {}
  friend std::ostream& operator<<(std::ostream& os,
                                  const RecordFormatter& formatter) {
    return os << StrJoin(formatter.record, ",");
  }
};
}  // namespace

extern "C" int main() {
  RealFs fs;
  RealOperatorFactory factory{fs};

  for (auto chars = ranges::subrange(std::istreambuf_iterator<char>{std::cin},
                                     std::istreambuf_iterator<char>{});
       const auto& s : Lines(chars)) {
    Query q(fs, factory, s);

    RecordSet* records = q.Parse();
    auto header = records->AttributeNames();
    std::cout << RecordFormatter{header} << "\n";
    ranges::copy(
        records->Records(),
        std::ostream_iterator<RecordFormatter<Record>>(std::cout, "\n"));
  }
  return 0;
}
}  // namespace csv_query
