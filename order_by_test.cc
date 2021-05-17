#include "order_by.h"
#include "fake_record_set.h"
#include "gtest/gtest.h"

using testing::ElementsAre;

namespace csv_query {
TEST(OrderByTest, Attributes) {
  FakeRecordSet record_set({"a", "b"}, {});
  OrderBy order_by(record_set, "a");

  ASSERT_THAT(order_by.AttributeNames(), ElementsAre("a", "b"));
}

TEST(OrderByTest, NumericOrderDesc) {
  FakeRecordSet record_set({"b", "a"}, {{"x", "1"}, {"y", "10"}, {"z", "3"}});
  OrderBy order_by(record_set, "a");

  ASSERT_EQ(order_by.Records(), (Records{
                                    {"y", "10"},
                                    {"z", "3"},
                                    {"x", "1"},
                                }));
}
}  // namespace csv_query
