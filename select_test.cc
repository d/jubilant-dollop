#include "select.h"
#include "fake_record_set.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

using testing::ElementsAre;

namespace csv_query {
TEST(SelectTest, Attributes) {
  FakeRecordSet record_set({"a", "b"}, {{"United_States", "300000000"}});
  Select select(record_set, "b");

  ASSERT_THAT(select.AttributeNames(), ElementsAre("b"));
}

TEST(SelectTest, Projection) {
  FakeRecordSet record_set({"a", "b"}, {{"United_States", "300000000"}});
  Select select(record_set, "b");

  ASSERT_THAT(select.Records(), ElementsAre(Record{"300000000"}));
}

}  // namespace csv_query
