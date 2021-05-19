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

  MOCK_METHOD(RecordSet*,
              DoOrderBy,
              (const RecordSet& child, std::string order_key),
              (override));

  MOCK_METHOD(RecordSet*,
              DoCountBy,
              (const RecordSet& child, std::string group_key),
              (override));

  MOCK_METHOD(RecordSet*,
              DoJoin,
              (const RecordSet& lhs,
               const RecordSet& rhs,
               std::string join_key),
              (override));
};

using testing::ByMove;
using testing::NiceMock;
using testing::Ref;
using testing::Return;

class QueryTest : public testing::Test {
 public:
  QueryTest() {
    ON_CALL(factory_, DoFrom("city.csv", Ref(fs_)))
        .WillByDefault(
            [&record_set = record_set_]() { return record_set.release(); });
  }

 protected:
  MockFs fs_;
  NiceMock<MockOperatorFactory> factory_;
  std::unique_ptr<RecordSet> record_set_{new FakeRecordSet({"a", "b"}, {})};
};

TEST_F(QueryTest, From) {
  Query q(fs_, factory_, "FROM city.csv");

  EXPECT_CALL(factory_, DoFrom("city.csv", Ref(fs_)))
      .Times(1)
      .WillOnce([&record_set = record_set_]() { return record_set.release(); });

  auto* expected_from_records = record_set_.get();
  ASSERT_EQ(q.Parse(), expected_from_records);
}

TEST_F(QueryTest, Select) {
  std::unique_ptr<RecordSet> select_records{new FakeRecordSet({"b"}, {})};
  auto* expected_select_records = select_records.get();

  Query q(fs_, factory_, "FROM city.csv SELECT b");

  EXPECT_CALL(factory_, DoSelect(Ref(*record_set_), "b"))
      .WillOnce([&select_records]() { return select_records.release(); });

  ASSERT_EQ(q.Parse(), expected_select_records);
}

TEST_F(QueryTest, Take) {
  std::unique_ptr<RecordSet> take_records{new FakeRecordSet({"a", "b"}, {})};
  auto* expected_take_records = take_records.get();

  Query q(fs_, factory_, "FROM city.csv TAKE 42");

  EXPECT_CALL(factory_, DoTake(Ref(*record_set_), 42))
      .WillOnce([&take_records]() { return take_records.release(); });

  ASSERT_EQ(q.Parse(), expected_take_records);
}

TEST_F(QueryTest, OrderBy) {
  std::unique_ptr<RecordSet> order_by_records{
      new FakeRecordSet({"a", "b"}, {})};
  auto* expected_order_by_records = order_by_records.get();

  Query q(fs_, factory_, "FROM city.csv ORDERBY b");

  EXPECT_CALL(factory_, DoOrderBy(Ref(*record_set_), "b"))
      .WillOnce([&order_by_records]() { return order_by_records.release(); });

  ASSERT_EQ(q.Parse(), expected_order_by_records);
}

TEST_F(QueryTest, CountBy) {
  std::unique_ptr<RecordSet> count_by_records{
      new FakeRecordSet({"b", "count"}, {})};
  auto* expected_count_by_records = count_by_records.get();

  Query q(fs_, factory_, "FROM city.csv COUNTBY b");

  EXPECT_CALL(factory_, DoCountBy(Ref(*record_set_), "b"))
      .WillOnce([&count_by_records]() { return count_by_records.release(); });

  ASSERT_EQ(q.Parse(), expected_count_by_records);
}

TEST_F(QueryTest, Join) {
  std::unique_ptr<RecordSet> rhs{new FakeRecordSet{{"b", "c"}, {}}};
  std::unique_ptr<RecordSet> join_records{
      new FakeRecordSet({"a", "b", "c"}, {})};
  auto* expected_join_records = join_records.get();

  Query q(fs_, factory_, "FROM city.csv JOIN country.csv b");

  EXPECT_CALL(factory_, DoFrom("city.csv", Ref(fs_)));
  EXPECT_CALL(factory_, DoFrom("country.csv", Ref(fs_))).WillOnce([&rhs]() {
    return rhs.release();
  });
  EXPECT_CALL(factory_, DoJoin(Ref(*record_set_), Ref(*rhs), "b"))
      .WillOnce([&join_records]() { return join_records.release(); });

  ASSERT_EQ(q.Parse(), expected_join_records);
}

}  // namespace csv_query
