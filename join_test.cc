#include "join.h"
#include "fake_record_set.h"
#include "gtest/gtest.h"

using testing::ElementsAre;
using testing::UnorderedElementsAreArray;

namespace csv_query {
TEST(JoinTest, Attributes) {
  FakeRecordSet lhs({"a", "b"}, {});
  FakeRecordSet rhs({"c", "b"}, {});
  Join join(lhs, rhs, "b");

  ASSERT_THAT(join.AttributeNames(), ElementsAre("a", "b", "c"));
}

TEST(JoinTest, Join) {
  FakeRecordSet lhs({"a", "b"}, {
                                    {"Kabul", "AFG"},
                                    {"Qandahar", "AFG"},
                                    {"Amsterdam", "NLD"},
                                });
  FakeRecordSet rhs({"b", "c"}, {
                                    {"AFG", "Afghanistan"},
                                    {"NLD", "Netherlands"},
                                });
  Join join(lhs, rhs, "b");

  ASSERT_THAT(join.Records(), UnorderedElementsAreArray(Records{
                                  {"Kabul", "AFG", "Afghanistan"},
                                  {"Qandahar", "AFG", "Afghanistan"},
                                  {"Amsterdam", "NLD", "Netherlands"},
                              }));
}
}  // namespace csv_query
