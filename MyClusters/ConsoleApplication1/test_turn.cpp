#include "Queue.h"
#include <gtest.h>


TEST(Queue, can_create_queue_with_positive_length)
{
	ASSERT_NO_THROW(Queue<int> q(5));
}

TEST(Queue, cant_create_too_large_queue)
{
	ASSERT_ANY_THROW(Queue<int> q(MaxQueueSize + 1));
}

TEST(Queue, throws_when_queue_vector_with_negative_length)
{
	ASSERT_ANY_THROW(Queue<int> q(-5));
}

TEST(Queue, can_get_size)
{
	Queue<int> q(4);
	EXPECT_EQ(4, q.GetSize());
}

TEST(Queue, can_get_count_element_in_queue)
{
	Queue<int> q(5);
	for (int i = 0; i < 4; i++)
		q.Put(i);
	EXPECT_EQ(4, q.Cardinality());
}

TEST(Queue, can_view_the_first_element)
{
	Queue<int> q(5);
	for (int i = 0; i < 4; i++)
		q.Put(i);
	EXPECT_EQ(0, q.ViewTheFirst());
}

TEST(Queue, can_put_element_the_first_option)
{
	int size = 4;
	Queue<int> q(size);
	ASSERT_NO_THROW(q.Put(size));
	EXPECT_EQ(1, q.Cardinality());
	EXPECT_EQ(size, q.ViewTheFirst());
}

TEST(Queue, can_put_element_the_second_option)
{
	Queue<int> q(4);
	int i;
	for (i = 0; i < 4; i++)
		q.Put(i);
	q.Get();
	ASSERT_NO_THROW(q.Put(i));
	EXPECT_EQ(4, q.Cardinality());
	EXPECT_EQ(1, q.ViewTheFirst());
}


TEST(Queue, can_get_first_element)
{
	Queue<int> q(4);
	for (int i = 0; i < 4; i++)
		q.Put(i);
	ASSERT_NO_THROW(q.Get());
	EXPECT_EQ(3, q.Cardinality());
	EXPECT_EQ(1, q.ViewTheFirst());
}

TEST(Queue, true_when_queue_is_empty)//проверка на пустату очереди
{
	Queue<int> q(3);
	EXPECT_EQ(true, q.IsEmpty());
}

TEST(Queue, throws_when_put_element_in_full_queue)//исключение, при добавлении элемента в полную очередь
{
	Queue<int> q(4);
	int i = 0;
	for (i = 0; i < 4; i++)
		q.Put(i);
	ASSERT_ANY_THROW(q.Put(i));
}

TEST(Queue, true_when_queue_is_full)//проверка на полноту очереди
{
	Queue<int> q(4);
	for (int i = 0; i < 4; i++)
		q.Put(i);
	EXPECT_EQ(true, q.IsFull());
}

TEST(Queue, throws_when_return_element_from_empty_queue)
{
	Queue<int> q(3);
	ASSERT_ANY_THROW(q.Get());
