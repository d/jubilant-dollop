#include "fs_provider.h"
#include "fake_fs.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include "stl_extras.h"

using testing::ElementsAre;

namespace csv_query {
TEST(FsProviderTest, Header) {
  FakeFs fs(R"csv(a,b,c
)csv");

  ASSERT_EQ(fs.Header("foo.txt"), "a,b,c");
}

TEST(FsProviderTest, DataLines) {
  FakeFs fs(R"csv(a,b,c
USA,California,39000000
IND,Kolkata,4399819
)csv");

  ASSERT_THAT(MakeVector(fs.DataLines("foo.txt")),
              ElementsAre("USA,California,39000000", "IND,Kolkata,4399819"));
}
}  // namespace csv_query
