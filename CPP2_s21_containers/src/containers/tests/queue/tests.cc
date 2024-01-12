#include <gtest/gtest.h>

#include "../../queue/s21_queue.h"
#include "../item.h"
#include "../queue_helpers.h"

// GCOVR_EXCL_START

namespace {

TEST(Queue, T0CopyConstructor) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33)};
  s21::Queue<Item> rq = {Item(11), Item(22), Item(33)};
  s21::Queue<Item> q2 = q1;
  EXPECT_EQ(q2, rq);
  EXPECT_EQ(q1, rq);
}

TEST(Queue, T1CopyConstructor) {
  s21::Queue<Item> q1;
  s21::Queue<Item> q2 = q1;
  EXPECT_TRUE(q2.empty());
  EXPECT_EQ(q2, q1);
}

TEST(Queue, T2CopyConstructor) {
  s21::Queue<Item> q1 = {Item(1)};
  q1.pop();
  s21::Queue<Item> q2 = q1;
  EXPECT_TRUE(q2.empty());
  EXPECT_EQ(q2, q1);
}

TEST(Queue, T0MoveConstructor) {
  s21::Queue<Item> q = {Item(11), Item(22), Item(33)};
  s21::Queue<Item> rq = {Item(11), Item(22), Item(33)};
  s21::Queue<Item> mq(std::move(q));
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(rq, mq);
}

TEST(Queue, T1MoveConstructor) {
  s21::Queue<Item> q;
  s21::Queue<Item> mq(std::move(q));
  EXPECT_TRUE(q.empty());
  EXPECT_TRUE(mq.empty());
  EXPECT_EQ(q, mq);
}

TEST(Queue, T0Constructor) {
  s21::Queue<Item> s21_queue;
  std::queue<Item> queue;

  EXPECT_TRUE(s21_queue == queue);
}

TEST(Queue, T1InitializedPush) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33)};
  s21::Queue<Item> q2;
  q2.push(Item(11));
  q2.push(Item(22));
  q2.push(Item(33));

  EXPECT_EQ(q1, q2);
}

TEST(Queue, T2Pop) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> q2;
  q2.push(Item(11));
  q2.push(Item(22));
  q2.push(Item(33));
  q2.push(Item(44));

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1, q2);
}

TEST(Queue, T3Pop) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> q2;
  q1.push(Item(55));
  q2.push(Item(11));
  q2.push(Item(22));
  q2.push(Item(33));
  q2.push(Item(44));
  q2.push(Item(55));

  q1.pop();

  EXPECT_NE(q1, q2);
}

TEST(Queue, T4PopTrow) {
  s21::Queue<Item> q1;

  EXPECT_THROW(q1.pop(), std::out_of_range);
}

TEST(Queue, T5PopTrow) {
  s21::Queue<Item> q1 = {Item(11), Item(22)};
  q1.pop();
  q1.pop();

  EXPECT_THROW(q1.pop(), std::out_of_range);
}

TEST(Queue, T00CopyOperator) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33), Item(44), Item(55)};
  s21::Queue<Item> rq = {Item(11), Item(22), Item(33), Item(44), Item(55)};
  s21::Queue<Item> q2 = {Item(11)};
  q2 = q1;

  EXPECT_EQ(q1, q2);
  EXPECT_EQ(q1, rq);
}

TEST(Queue, T0CopyOperator) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> q2 = {Item(11)};
  q2 = q1;

  EXPECT_EQ(q1, q2);
}

TEST(Queue, T1CopyOperator) {
  s21::Queue<Item> q1;
  s21::Queue<Item> q2 = {Item(11)};
  q2 = q1;
  EXPECT_TRUE(q2.empty());
  EXPECT_EQ(q1, q2);
}

TEST(Queue, T3CopyOperator) {
  s21::Queue<Item> q1;
  q1 = q1;
  EXPECT_TRUE(q1.empty());
}

TEST(Queue, T2CopyOperator) {
  s21::Queue<Item> q1 = {Item(11)};
  s21::Queue<Item> q2 = {Item(11)};
  q1 = q1;
  EXPECT_EQ(q1, q2);
}

TEST(Queue, T0MoveOperator) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> q2 = {Item(11)};
  s21::Queue<Item> rq = {Item(11), Item(22), Item(33), Item(44)};
  q2 = std::move(q1);

  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(rq, q2);
}

TEST(Queue, T1MoveOperator) {
  s21::Queue<Item> q1;
  s21::Queue<Item> q2 = {Item(11)};
  q2 = std::move(q1);
  EXPECT_TRUE(q2.empty());
  EXPECT_EQ(q1, q2);
}

TEST(Queue, T2MoveOperator) {
  s21::Queue<Item> q1;
  q1 = std::move(q1);
  EXPECT_TRUE(q1.empty());
}

TEST(Queue, T3MoveOperator) {
  s21::Queue<Item> rq = {Item(11), Item(22)};
  s21::Queue<Item> q = {Item(11), Item(22)};
  q = std::move(q);
  EXPECT_EQ(q, rq);
}

TEST(Queue, T0FrontBackPopEmpty) {
  s21::Queue<Item> q = {Item(11), Item(22), Item(33), Item(44), Item(55)};

  EXPECT_EQ(q.front(), Item(11));
  EXPECT_EQ(q.back(), Item(55));
  q.pop();
  EXPECT_EQ(q.front(), Item(22));
  EXPECT_EQ(q.back(), Item(55));
  q.pop();
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.front(), Item(33));
  EXPECT_EQ(q.back(), Item(55));
  q.pop();
  EXPECT_EQ(q.front(), Item(44));
  EXPECT_EQ(q.back(), Item(55));
  q.pop();
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.front(), Item(55));
  EXPECT_EQ(q.back(), Item(55));
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(Queue, T0FrontBack) {
  s21::Queue<Item> q = {Item(11), Item(22), Item(33), Item(44)};

  EXPECT_EQ(q.front(), Item(11));
  EXPECT_EQ(q.back(), Item(44));
}

TEST(Queue, T1FrontBack) {
  s21::Queue<Item> q = {Item(11), Item(22), Item(33), Item(44)};
  q.pop();

  EXPECT_EQ(q.back(), Item(44));
  EXPECT_EQ(q.front(), Item(22));
}

TEST(Queue, T2FrontBack) {
  s21::Queue<Item> q = {Item(11), Item(22), Item(33), Item(44)};
  q.push(Item(55));

  EXPECT_EQ(q.back(), Item(55));
  EXPECT_EQ(q.front(), Item(11));
}

TEST(Queue, T3FrontBack) {
  s21::Queue<Item> q = {Item(11), Item(22), Item(33), Item(44)};
  q.push(Item(55));
  q.pop();
  q.pop();

  EXPECT_EQ(q.back(), Item(55));
  EXPECT_EQ(q.front(), Item(33));
}

TEST(Queue, T4FrontBack) {
  s21::Queue<Item> q = {Item(11), Item(22), Item(33), Item(44)};
  q.push(Item(55));
  q.pop();
  q.pop();
  q.push(Item(66));

  EXPECT_EQ(q.back(), Item(66));
  EXPECT_EQ(q.front(), Item(33));
}

TEST(Queue, T0Back) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> q2;
  q1.push(Item(55));
  q2.push(Item(11));
  q2.push(Item(44));
  q2.push(Item(55));

  EXPECT_EQ(q1.back(), q2.back());
}

TEST(Queue, T1Back) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> q2 = q1;

  EXPECT_EQ(q1.back(), q2.back());
}

TEST(Queue, T0BackFront) {
  s21::Queue<Item> q1 = {Item(11)};
  s21::Queue<Item> q2;
  q2.push(Item(11));

  EXPECT_EQ(q1.back(), q2.back());
  EXPECT_EQ(q1.back(), q2.front());
  EXPECT_EQ(q1.front(), q2.back());
}

TEST(Queue, T0FrontBackThrow) {
  s21::Queue<Item> q;

  EXPECT_THROW(q.front(), std::out_of_range);
  EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(Queue, T1FrontBackThrow) {
  s21::Queue<Item> q = {Item(1)};
  q.pop();

  EXPECT_THROW(q.front(), std::out_of_range);
  EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(Queue, T0InsertManyBack) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> q2 = {Item(11)};
  q2.insert_many_back(Item(22), Item(33), Item(44));

  EXPECT_EQ(q1, q2);
}

TEST(Queue, T1InsertManyBack) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> q2;
  q2.insert_many_back(Item(11), Item(22), Item(33), Item(44));

  EXPECT_EQ(q1, q2);
}

TEST(Queue, T0Swap) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> q2 = {Item(11)};
  s21::Queue<Item> rq2 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> rq1 = {Item(11)};
  q1.swap(q2);

  EXPECT_EQ(q1, rq1);
  EXPECT_EQ(q2, rq2);
}

TEST(Queue, T1Swap) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> q2 = {Item(11)};
  s21::Queue<Item> rq2 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> rq1 = {Item(11)};
  q2.swap(q1);

  EXPECT_EQ(q1, rq1);
  EXPECT_EQ(q2, rq2);
}

TEST(Queue, T2Swap) {
  s21::Queue<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Queue<Item> q2 = {Item(11)};
  q2.pop();
  s21::Queue<Item> rq2 = {Item(11), Item(22), Item(33), Item(44)};
  q2.swap(q1);

  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q2, rq2);
}

TEST(Queue, T3Swap) {
  s21::Queue<Item> q1;
  s21::Queue<Item> q2;
  q2.swap(q1);

  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q1, q2);
}

}  // namespace
   // GCOVR_EXCL_STOP
