// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_push_front)
{
    List<int> *l1 = new List<int>();
    l1->push_front(10);
    ASSERT_EQUAL(l1->front(), 10);
    ASSERT_EQUAL(l1->back(), 10);

    l1->push_front(30);
    ASSERT_EQUAL(l1->front(), 30);
    ASSERT_EQUAL(l1->back(), 10);

    l1->push_front(50);
    ASSERT_EQUAL(l1->front(), 50);
    ASSERT_EQUAL(l1->back(), 10);

    delete l1;
}

TEST(test_push_back)
{
    List<int> *l1 = new List<int>();
    l1->push_back(10);
    ASSERT_EQUAL(l1->back(), 10);
    ASSERT_EQUAL(l1->front(), 10);

    l1->push_back(30);
    ASSERT_EQUAL(l1->front(), 10);
    ASSERT_EQUAL(l1->back(), 30);

    l1->push_back(50);
    ASSERT_EQUAL(l1->front(), 10);
    ASSERT_EQUAL(l1->back(), 50);

    delete l1;
}

TEST(test_pop_front)
{
    List<int> *l1 = new List<int>();
    l1->push_back(10);
    l1->push_back(30);
    l1->push_back(50);

    ASSERT_EQUAL(l1->front(), 10);
    ASSERT_EQUAL(l1->back(), 50);

    l1->pop_front();
    ASSERT_EQUAL(l1->front(), 30);

    l1->pop_front();
    ASSERT_EQUAL(l1->front(), 50);

    delete l1;
}

TEST(test_pop_back)
{

    List<int> *l1 = new List<int>();
    l1->push_back(10);
    l1->push_back(30);
    l1->push_back(50);

    ASSERT_EQUAL(l1->front(), 10);
    ASSERT_EQUAL(l1->back(), 50);

    l1->pop_back();
    ASSERT_EQUAL(l1->back(), 30);

    l1->pop_back();
    ASSERT_EQUAL(l1->back(), 10);

    delete l1;
}

TEST(test_size)
{
    List<int> *l1 = new List<int>();
    ASSERT_EQUAL(l1->size(), 0);
    l1->push_back(10);
    l1->push_back(30);
    l1->push_back(50);
    ASSERT_EQUAL(l1->size(), 3);

    delete l1;
}

TEST(test_empty)
{

    List<int> *l1 = new List<int>();
    ASSERT_TRUE(l1->empty());
    l1->push_back(10);
    ASSERT_FALSE(l1->empty());

    delete l1;
}

TEST(test_clear)
{
    List<int> *l1 = new List<int>();
    l1->push_back(10);
    l1->push_back(30);
    l1->push_back(50);
    ASSERT_EQUAL(l1->size(), 3);
    l1->clear();
    ASSERT_EQUAL(l1->size(), 0);

    delete l1;
}

TEST(test_assignment)
{
    cout << "yea" << endl;
    List<int> *l1 = new List<int>();
    l1->push_back(10);
    l1->push_back(30);
    List<int> *l2 = new List<int>();
    l2->push_back(20);
    l2->push_back(40);

    *l2 = *l1;
    ASSERT_EQUAL(l2->front(), 10);
    ASSERT_EQUAL(l2->back(), 30);

    delete l1;
    delete l2;
}

TEST(test_copy)
{
    List<int> *l1 = new List<int>();
    l1->push_back(10);
    l1->push_back(30);

    List<int> *l2 = new List<int>(*l1);

    ASSERT_EQUAL(l2->front(), 10);
    ASSERT_EQUAL(l2->back(), 30);

    delete l1;
    delete l2;
}

TEST(test_begin)
{
    List<int> *l1 = new List<int>();
    l1->push_back(10);
    l1->push_back(10);
    l1->push_back(10);
    l1->push_back(10);
    int count = 0;
    for (List<int>::Iterator i = l1->begin(); i != l1->end(); ++i)
    {
        count++;
    }

    ASSERT_EQUAL(count, 4);

    delete l1;
}

TEST(test_end)
{

    List<int> *l1 = new List<int>();
    l1->push_back(10);
    l1->push_back(10);
    l1->push_back(10);
    l1->push_back(10);
    int count = 0;
    for (List<int>::Iterator i = l1->begin(); i != l1->end(); ++i)
    {
        count++;
    }

    ASSERT_EQUAL(count, 4);

    delete l1;
}

TEST(test_erase)
{
    List<int> *l1 = new List<int>();
    l1->push_back(10);
    List<int>::Iterator it = l1->begin();
    l1->erase(it);
    ASSERT_TRUE(l1->empty());

    l1->push_back(30);
    l1->push_back(50);
    l1->push_back(70);
    it = l1->begin();

    l1->erase(it);
    ASSERT_EQUAL(l1->front(), 50);
    l1->erase(l1->end());
    ASSERT_EQUAL(l1->back(), 50);

    delete l1;
}

TEST(test_insert)
{
    List<int> *l1 = new List<int>();

    l1->push_back(10);
    l1->push_back(30);
    l1->push_back(50);
    l1->push_back(70);

    l1->insert(l1->begin(), 100);
    ASSERT_EQUAL(l1->front(), 100);

    l1->insert(l1->end(), 200);
    ASSERT_EQUAL(l1->back(), 200);

    l1->pop_back();
    ASSERT_EQUAL(l1->back(), 70);

    delete l1;
}

TEST_MAIN()
