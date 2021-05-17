#include "count_by.h"
#include "fake_record_set.h"
#include "gtest/gtest.h"

using testing::ElementsAre;
using testing::UnorderedElementsAre;

namespace csv_query {
TEST(CountByTest, Attributes) {
  FakeRecordSet record_set({"a", "b"}, {});
  CountBy count_by(record_set, "b");

  ASSERT_THAT(count_by.AttributeNames(), ElementsAre("b", "count"));
}

TEST(CountByTest, Count) {
  FakeRecordSet record_set({"a", "b"},
                           {{"NYC", "USA"}, {"LA", "USA"}, {"Hanoi", "VNM"}});
  CountBy count_by(record_set, "b");

  ASSERT_THAT(count_by.Records(),
              UnorderedElementsAre(Record{"USA", "2"}, Record{"VNM", "1"}));
}

}  // namespace csv_query
