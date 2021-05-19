#include "query.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "fake_record_set.h"
#include "mock_fs.h"
#include "operator_factory.h"

namespace csv_query {
struct MockOperatorFactory : OperatorFactory {
  MOCK_METHOD(RecordSet*,
              DoFrom,
              (std::string name, FsProvider& fs_provider),
              (override));

  MOCK_METHOD(RecordSet*,
              DoSelect,
              (const RecordSet& child, std::string attribute),
              (override));

  MOCK_METHOD(RecordSet*,
              DoTake,
              (const RecordSet& child, size_t limit),
              (override));
};

using testing::ByMove;
using testing::Ref;
using testing::Return;

TEST(QueryTest, From) {
  auto record_set =
      std::unique_ptr<RecordSet>(new FakeRecordSet({"a", "b"}, {}));
  auto* expected_record_set = record_set.get();

  MockFs fs;
  MockOperatorFactory factory;
  Query q(fs, factory, "FROM city.csv");

  EXPECT_CALL(factory, DoFrom("city.csv", Ref(fs)))
      .Times(1)
      .WillOnce([&record_set]() { return record_set.release(); });

  ASSERT_EQ(q.Parse(), expected_record_set);
}

TEST(QueryTest, Select) {
  auto* expected_from_records = new FakeRecordSet({"a", "b"}, {});
  auto from_records = std::unique_ptr<FakeRecordSet>(expected_from_records);
  auto* expected_select_records = new FakeRecordSet({"b"}, {});
  auto select_records = std::unique_ptr<FakeRecordSet>(expected_select_records);

  MockFs fs;
  MockOperatorFactory factory;
  Query q(fs, factory, "FROM city.csv SELECT b");

  EXPECT_CALL(factory, DoFrom("city.csv", Ref(fs)))
      .Times(1)
      .WillOnce([&from_records]() { return from_records.release(); });
  EXPECT_CALL(factory, DoSelect(Ref(*expected_from_records), "b"))
      .WillOnce([&select_records]() { return select_records.release(); });

  ASSERT_EQ(q.Parse(), expected_select_records);
}

TEST(QueryTest, Take) {
  auto* expected_from_records = new FakeRecordSet({"a", "b"}, {});
  auto from_records = std::unique_ptr<FakeRecordSet>(expected_from_records);
  auto* expected_take_records = new FakeRecordSet({"b"}, {});
  auto take_records = std::unique_ptr<FakeRecordSet>(expected_take_records);

  MockFs fs;
  MockOperatorFactory factory;
  Query q(fs, factory, "FROM city.csv TAKE 42");

  EXPECT_CALL(factory, DoFrom("city.csv", Ref(fs)))
      .Times(1)
      .WillOnce([&from_records]() { return from_records.release(); });
  EXPECT_CALL(factory, DoTake(Ref(*expected_from_records), 42))
      .WillOnce([&take_records]() { return take_records.release(); });

  ASSERT_EQ(q.Parse(), expected_take_records);
}

}  // namespace csv_query
