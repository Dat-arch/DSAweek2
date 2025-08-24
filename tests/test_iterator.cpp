#include "doctest/doctest.h"
#include "include/DoublyLinkedList.h"

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

    /* --------------------------------------------------------------------- */
    TEST_CASE("Backward iteration using operator--")
    {
        DoublyLinkedList<int> list;
        // avoid initializer_list loop to prevent extra headers
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.insertAtTail(4);     // [1,2,3,4]

        auto it = list.end();     // tail sentinel
        int expected[] = {4, 3, 2, 1};
        int idx = 0;

        while (it != list.begin())
        {
            --it;                 // step back onto valid node
            CHECK(*it == expected[idx++]);
        }
        CHECK(idx == 4);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Iterator works without <algorithm>/<numeric>")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(10);
        list.insertAtTail(15);
        list.insertAtTail(20);

        // manual accumulate
        int sum = 0;
        for (auto it = list.begin(); it != list.end(); ++it)
            sum += *it;
        CHECK(sum == 50);

        // manual find
        bool found = false;
        int foundValue = 0;
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            if (*it == 15) { found = true; foundValue = *it; break; }
        }
        CHECK(found);
        CHECK(foundValue == 15);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Const list iteration")
    {
        DoublyLinkedList<int> tmp;
        tmp.insertAtTail(7);
        tmp.insertAtTail(8);
        const DoublyLinkedList<int>& list = tmp;    // bind const

        int product = 1;
        for (auto it = list.begin(); it != list.end(); ++it)
            product *= *it;

        CHECK(product == 56);                       // 7*8
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Iterate empty list safely")
    {
        DoublyLinkedList<int> empty;
        CHECK(empty.begin() == empty.end());        // both at dummy
        int count = 0;
        for (int v : empty) { (void)v; ++count; }
        CHECK(count == 0);                          // loop body never runs
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Iterator validity after external deleteAt")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);   // [1,2,3]

        auto it = list.begin();     // points to 1
        list.deleteAt(1);           // remove middle element (2)

        CHECK(*it == 1);            // still valid at 1
        ++it;                       // now points to 3
        CHECK(it != list.end());
        CHECK(*it == 3);
    }

    /* --------------------------------------------------------------------- */
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
        CHECK(it1 == it2);          // back to first
    }
}
