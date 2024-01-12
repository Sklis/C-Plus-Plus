#include <gtest/gtest.h>

#include "../../stack/s21_stack.h"
#include "../item.h"
#include "../stack_helpers.h"

// GCOVR_EXCL_START

namespace {

TEST(Stack, T00CopyConstructor) {
  s21::Stack<Item> q1 = {Item(11), Item(22), Item(33)};
  s21::Stack<Item> q2 = q1;
  EXPECT_EQ(q2, q1);
  q1.print();
  q2.print();
}

TEST(Stack, T0CopyConstructor) {
  s21::Stack<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> rq = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> q2 = q1;

  EXPECT_EQ(q2, rq);
  EXPECT_EQ(q1, rq);
  q1.print();
  q2.print();
}

TEST(Stack, T1CopyConstructor) {
  s21::Stack<Item> q1;
  s21::Stack<Item> q2 = q1;
  EXPECT_TRUE(q2.empty());
  EXPECT_EQ(q2, q1);
}

TEST(Stack, T2CopyConstructor) {
  s21::Stack<Item> q1 = {Item(1)};
  q1.pop();
  s21::Stack<Item> q2 = q1;
  EXPECT_TRUE(q2.empty());
  EXPECT_EQ(q2, q1);
}

TEST(Stack, T0MoveConstructor) {
  s21::Stack<Item> q = {Item(11), Item(22), Item(33)};
  s21::Stack<Item> rq = {Item(11), Item(22), Item(33)};
  s21::Stack<Item> mq(std::move(q));
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(rq, mq);
}

TEST(Stack, T1MoveConstructor) {
  s21::Stack<Item> q;
  s21::Stack<Item> mq(std::move(q));
  EXPECT_TRUE(q.empty());
  EXPECT_TRUE(mq.empty());
  EXPECT_EQ(q, mq);
}

TEST(Stack, T1InitializedPush) {
  s21::Stack<Item> q1 = {Item(11), Item(22), Item(33)};
  s21::Stack<Item> q2;
  q2.push(Item(11));
  q2.push(Item(22));
  q2.push(Item(33));

  EXPECT_EQ(q1, q2);
}

TEST(Stack, T2Pop) {
  s21::Stack<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> q2;
  q2.push(Item(11));
  q2.push(Item(22));
  q2.push(Item(33));
  q2.push(Item(44));

  q1.pop();
  q2.pop();

  EXPECT_EQ(q1, q2);
}

TEST(Stack, T3Pop) {
  s21::Stack<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> q2;
  q1.push(Item(55));
  q2.push(Item(11));
  q2.push(Item(22));
  q2.push(Item(33));
  q2.push(Item(44));
  q2.push(Item(55));

  q1.pop();

  EXPECT_NE(q1, q2);
}

TEST(Stack, T4PopTrow) {
  s21::Stack<Item> s;
  EXPECT_TRUE(s.empty());
  s.pop();
  EXPECT_TRUE(s.empty());
}

TEST(Stack, T5PopTrow) {
  s21::Stack<Item> s = {Item(11), Item(22)};
  s.pop();
  s.pop();
  s.pop();

  EXPECT_TRUE(s.empty());
}

TEST(Stack, T00CopyOperator) {
  s21::Stack<Item> s1 = {Item(11), Item(22), Item(33), Item(44), Item(55)};
  s21::Stack<Item> rs = {Item(11), Item(22), Item(33), Item(44), Item(55)};
  s21::Stack<Item> s2 = {Item(1), Item(242), Item(133), Item(5)};
  s2 = s1;

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s1, rs);
  s1.print();
  s2.print();
}

TEST(Stack, T0CopyOperator) {
  s21::Stack<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> q2 = {Item(11)};
  q2 = q1;

  EXPECT_EQ(q1, q2);
}

TEST(Stack, T1CopyOperator) {
  s21::Stack<Item> q1;
  s21::Stack<Item> q2 = {Item(11)};
  q2 = q1;
  EXPECT_TRUE(q2.empty());
  EXPECT_EQ(q1, q2);
}

TEST(Stack, T3CopyOperator) {
  s21::Stack<Item> q1;
  q1 = q1;
  EXPECT_TRUE(q1.empty());
}

TEST(Stack, T2CopyOperator) {
  s21::Stack<Item> q1 = {Item(11)};
  s21::Stack<Item> q2 = {Item(11)};
  q1 = q1;
  EXPECT_EQ(q1, q2);
}

TEST(Stack, T0MoveOperator) {
  s21::Stack<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> q2 = {Item(11)};
  s21::Stack<Item> rq = {Item(11), Item(22), Item(33), Item(44)};
  q2 = std::move(q1);

  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(rq, q2);
}

TEST(Stack, T1MoveOperator) {
  s21::Stack<Item> q1;
  s21::Stack<Item> q2 = {Item(11)};
  q2 = std::move(q1);
  EXPECT_TRUE(q2.empty());
  EXPECT_EQ(q1, q2);
}

TEST(Stack, T2MoveOperator) {
  s21::Stack<Item> q1;
  q1 = std::move(q1);
  EXPECT_TRUE(q1.empty());
}

TEST(Stack, T3MoveOperator) {
  s21::Stack<Item> rq = {Item(11), Item(22)};
  s21::Stack<Item> q = {Item(11), Item(22)};
  q = std::move(q);
  EXPECT_EQ(q, rq);
}

TEST(Stack, T0Top) {
  s21::Stack<Item> s = {Item(11), Item(22), Item(33), Item(44)};

  EXPECT_EQ(s.top(), Item(44));
  EXPECT_EQ(s.top(), Item(44));
}

TEST(Stack, T1Top) {
  s21::Stack<Item> s;
  EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(Stack, T2Top) {
  s21::Stack<Item> s = {Item(11), Item(22), Item(33), Item(44)};
  s.push(Item(55));
  EXPECT_EQ(s.top(), Item(55));
}

TEST(Stack, T3Top) {
  s21::Stack<Item> s = {Item(11), Item(22), Item(33), Item(44)};
  s.push(Item(55));
  s.pop();
  s.pop();
  s.pop();
  s.pop();
  EXPECT_EQ(s.top(), Item(11));
}

TEST(Stack, T4Top) {
  s21::Stack<Item> s = {Item(11), Item(22), Item(33), Item(44)};
  s.push(Item(55));
  EXPECT_EQ(s.top(), Item(55));
  s.pop();
  EXPECT_EQ(s.top(), Item(44));
  s.pop();
  EXPECT_EQ(s.top(), Item(33));
  s.pop();
  EXPECT_EQ(s.top(), Item(22));
  s.pop();
  EXPECT_EQ(s.top(), Item(11));
  s.pop();
  EXPECT_THROW(s.top(), std::out_of_range);
}

TEST(Stack, T5Top) {
  s21::Stack<Item> s1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> s2 = {Item(1), Item(2), Item(3), Item(44)};

  EXPECT_EQ(s1.top(), s2.top());
}

TEST(Stack, T0Other) {
  s21::Stack<Item> s1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> s2 = s1;
  EXPECT_EQ(s1, s2);
  s1.push(Item(55));

  EXPECT_NE(s1, s2);
}

TEST(Stack, T1Other) {
  s21::Stack<Item> s1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> s2 = s1;
  s1.push(Item(55));
  s1.push(Item(66));
  s2.insert_many_front(Item(55), Item(66));

  EXPECT_EQ(s1, s2);
}

TEST(Stack, T2Other) {
  s21::Stack<Item> s1 = {Item(11), Item(22), Item(33), Item(44), Item(55)};
  s21::Stack<Item> s2 = {Item(11), Item(21), Item(33), Item(44), Item(55)};

  EXPECT_NE(s2, s1);
}

TEST(Stack, T0InsertManyFront) {
  s21::Stack<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> q2 = {Item(11)};
  q2.insert_many_front(Item(22), Item(33), Item(44));

  EXPECT_EQ(q1, q2);
}

TEST(Stack, T1InsertManyFront) {
  s21::Stack<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> q2;
  q2.insert_many_front(Item(11), Item(22), Item(33), Item(44));

  EXPECT_EQ(q1, q2);
}

TEST(Stack, T0Swap) {
  s21::Stack<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> q2 = {Item(11)};
  s21::Stack<Item> rq2 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> rq1 = {Item(11)};
  q1.swap(q2);

  EXPECT_EQ(q1, rq1);
  EXPECT_EQ(q2, rq2);
}

TEST(Stack, T1Swap) {
  s21::Stack<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> q2 = {Item(11)};
  s21::Stack<Item> rq2 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> rq1 = {Item(11)};
  q2.swap(q1);

  EXPECT_EQ(q1, rq1);
  EXPECT_EQ(q2, rq2);
}

TEST(Stack, T2Swap) {
  s21::Stack<Item> q1 = {Item(11), Item(22), Item(33), Item(44)};
  s21::Stack<Item> q2 = {Item(11)};
  q2.pop();
  s21::Stack<Item> rq2 = {Item(11), Item(22), Item(33), Item(44)};
  q2.swap(q1);

  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q2, rq2);
}

TEST(Stack, T3Swap) {
  s21::Stack<Item> q1;
  s21::Stack<Item> q2;
  q2.swap(q1);

  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q1, q2);
}

}  // namespace
   // GCOVR_EXCL_STOP
