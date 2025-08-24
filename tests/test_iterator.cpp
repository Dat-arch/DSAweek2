#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Iterator")
{
    TEST_CASE("Iteration over DoublyLinkedList")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        int expected[] = {10, 20, 30};

        SUBCASE("Forward iteration using Iterator")
        {
            int idx = 0;
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                CHECK(*it == expected[idx++]);
            }
            CHECK(idx == 3);
        }

        SUBCASE("Range-based for iteration")
        {
            int idx = 0;
            for (int x : list)
            {
                CHECK(x == expected[idx++]);
            }
            CHECK(idx == 3);
        }
    }

    TEST_CASE("Backward iteration using operator--")
    {
        DoublyLinkedList<int> list;
        int init_vals1[] = {1, 2, 3, 4};
        for (int idx = 0; idx < 4; ++idx) list.insertAtTail(init_vals1[idx]); // [1,2,3,4]

        auto it = list.end();   // tail sentinel
        int expected[] = {4, 3, 2, 1};
        int idx = 0;

        while (it != list.begin())
        {
            --it;                                   // move to valid node
            CHECK(*it == expected[idx++]);
        }
        CHECK(idx == 4);
    }

    TEST_CASE("Iterator manual sum and search")
    {
        DoublyLinkedList<int> list;
        int vals[] = {5, 10, 15, 20};
        for (int idx = 0; idx < 4; ++idx) list.insertAtTail(vals[idx]);

        // manual accumulate
        int sum = 0;
        for (auto it = list.begin(); it != list.end(); ++it) sum += *it;
        CHECK(sum == 50);

        // manual find
        bool found = false;
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            if (*it == 15)
            {
                found = true;
                CHECK(*it == 15);
                break;
            }
        }
        CHECK(found);
    }

    TEST_CASE("Const list iteration")
    {
        DoublyLinkedList<int> tmp;
        int tmp_vals[] = {7, 8};
        for (int idx = 0; idx < 2; ++idx) tmp.insertAtTail(tmp_vals[idx]);
        const DoublyLinkedList<int>& list = tmp;    // binding const

        int product = 1;
        for (auto it = list.begin(); it != list.end(); ++it)
            product *= *it;

        CHECK(product == 56);                       // 7*8
    }

    TEST_CASE("Iterate empty list safely")
    {
        DoublyLinkedList<int> empty;
        CHECK(empty.begin() == empty.end());        // both point to sentinel
        for (int v : empty)
            CHECK(false);                           // should not enter
    }

    TEST_CASE("Iterator validity after external deleteAt")
    {
        DoublyLinkedList<int> list;
        int init_vals2[] = {1, 2, 3};
        for (int idx = 0; idx < 3; ++idx) list.insertAtTail(init_vals2[idx]);   // [1,2,3]

        auto it = list.begin();     // points to 1
        list.deleteAt(1);           // remove element 2

        CHECK(*it == 1);            // iterator still valid on node 1
        ++it;                       // move to next (now 3)
        CHECK(it != list.end());
        CHECK(*it == 3);
    }

    TEST_CASE("Equality & inequality of iterators")
    {
        DoublyLinkedList<char> list;
        list.insertAtTail('A');
        list.insertAtTail('B');

        auto it1 = list.begin();
        auto it2 = list.begin();
        CHECK(it1 == it2);          // same node

        ++it2;
        CHECK(it1 != it2);          // different nodes
        --it2;
        CHECK(it1 == it2);          // back to start
    }
}

