#include "take.h"
#include "fake_record_set.h"
#include "gtest/gtest.h"

using testing::ElementsAre;
using testing::ElementsAreArray;

namespace csv_query {
TEST(TakeTest, Attributes) {
  FakeRecordSet record_set({"a", "b"}, {});
  Take take(record_set, 0);

  ASSERT_THAT(take.AttributeNames(), ElementsAre("a", "b"));
}

TEST(TakeTest, RecordsExceedLimit) {
  FakeRecordSet record_set({"a"}, {{"SF"}, {"LA"}, {"San_Buenaventura"}});
  Take take(record_set, 2);

  ASSERT_THAT(take.Records(), ElementsAreArray({
                                  Record{"SF"},
                                  Record{"LA"},
                              }));
}

TEST(TakeTest, RecordsWithinLimit) {
  FakeRecordSet record_set({"a"}, {{"SF"}, {"LA"}, {"San_Buenaventura"}});
  Take take(record_set, 5);

  ASSERT_THAT(take.Records(), ElementsAreArray({
                                  Record{"SF"},
                                  Record{"LA"},
                                  Record{"San_Buenaventura"},
                              }));
}

}  // namespace csv_query
