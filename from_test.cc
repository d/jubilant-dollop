#include "from.h"
#include "fake_fs.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

using testing::ElementsAreArray;

namespace csv_query {
TEST(FromTest, Attributes) {
  FakeFs fs(R"csv(a,b,c
)csv");
  From from("foo.csv", fs);

  ASSERT_THAT(from.AttributeNames(), ElementsAreArray({
                                         "a",
                                         "b",
                                         "c",
                                     }));
}

TEST(FromTest, Records) {
  FakeFs fs(R"csv(a,b,c
USA,California,39000000
IND,Kolkata,4399819
)csv");
  From from("foo.csv", fs);

  ASSERT_THAT(from.Records(), ElementsAreArray(Records{
                                  {
                                      "USA",
                                      "California",
                                      "39000000",
                                  },
                                  {
                                      "IND",
                                      "Kolkata",
                                      "4399819",
                                  },
                              }));
}
}  // namespace csv_query
