#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Iterator")
{
    TEST_CASE("Empty list begin equals end and no iteration")
    {
        DoublyLinkedList<int> list;
        CHECK(list.begin() == list.end());
        int count = 0;
        for (auto it = list.begin(); it != list.end(); ++it) { ++count; }
        CHECK(count == 0);
    }

    TEST_CASE("Single element iteration yields once")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(5);
        int count = 0;
        for (auto it = list.begin(); it != list.end(); ++it) { CHECK(*it == 5); ++count; }
        CHECK(count == 1);
    }

    TEST_CASE("Pre-increment traverses forward correctly")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        auto it = list.begin();
        CHECK(*it == 1);
        ++it; CHECK(*it == 2);
        ++it; CHECK(*it == 3);
        ++it; CHECK(it == list.end());
    }

    TEST_CASE("Pre-decrement from end goes to last element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        auto it = list.end();
        --it; CHECK(*it == 20);
        --it; CHECK(*it == 10);
        CHECK(it == list.begin());
    }

    TEST_CASE("Modify elements via iterator dereference")
    {
        DoublyLinkedList<int> list;
        for (int i=0;i<3;++i) list.insertAtTail(i);
        for (auto it = list.begin(); it != list.end(); ++it) { *it += 10; }
        int expected[] = {10,11,12};
        int idx=0;
        for (auto it = list.begin(); it != list.end(); ++it) { CHECK(*it == expected[idx++]); }
    }

    TEST_CASE("Range-based for after reverse")
    {
        DoublyLinkedList<int> list;
        for (int i=1;i<=4;++i) list.insertAtTail(i); // [1,2,3,4]
        list.reverse(); // [4,3,2,1]
        int expected[] = {4,3,2,1};
        int idx=0;
        for (int x : list) { CHECK(x == expected[idx++]); }
        CHECK(idx == 4);
    }

    TEST_CASE("Iterator equality and inequality semantics")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        auto a = list.begin();
        auto b = list.begin();
        CHECK(a == b);
        ++b;
        CHECK(a != b);
    }

    TEST_CASE("Iteration after insertAt in middle")
    {
        DoublyLinkedList<int> list; // build [1,3] then insert 2
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1,2);
        int expected[] = {1,2,3};
        int idx=0;
        for (auto it = list.begin(); it != list.end(); ++it) { CHECK(*it == expected[idx++]); }
    }

    TEST_CASE("Iteration after deletions")
    {
        DoublyLinkedList<int> list;
        for (int i=1;i<=5;++i) list.insertAtTail(i); // [1..5]
        list.deleteAt(0); // remove 1
        list.deleteAt(2); // remove 4 -> [2,3,5]
        int expected[] = {2,3,5};
        int idx=0;
        for (auto it = list.begin(); it != list.end(); ++it) { CHECK(*it == expected[idx++]); }
        CHECK(idx==3);
    }

    TEST_CASE("Multiple independent iterators progress independently")
    {
        DoublyLinkedList<int> list;
        for (int i=0;i<3;++i) list.insertAtTail(i);
        auto it1 = list.begin();
        auto it2 = list.begin();
        ++it1; // it1 at 1
        CHECK(*it1 == 1);
        CHECK(*it2 == 0);
        ++it2; ++it2; // it2 at 2
        CHECK(*it2 == 2);
    }

    TEST_CASE("Iterating a list of Points")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1,2));
        list.insertAtTail(Point(3,4));
        int sumX = 0;
        for (auto &p : list) sumX += int(p.getX());
        CHECK(sumX == 4);
    }

    TEST_CASE("Begin then decrement should move to tail-1")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        auto it = list.end();
        --it; CHECK(*it == 2);
    }

    TEST_CASE("Decrementing begin repeatedly should not underflow sentinel access")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        auto it = list.begin();
        CHECK(*it == 5);
        // behavior: one more -- should move to dummy head; we won't deref it after moving past begin
        --it; // do not dereference
        ++it; CHECK(*it == 5); // move back
    }

    TEST_CASE("Iterate after many operations maintains order")
    {
        DoublyLinkedList<int> list;
        for (int i=0;i<10;++i) list.insertAtTail(i);
        list.deleteAt(0);
        list.deleteAt(7-1); // delete what was 8 originally
        list.insertAt(0, -1);
        list.insertAt(5, 99);
    int expected[] = {-1,1,2,3,4,99,5,6,8,9};
        int idx=0;
        for (auto it = list.begin(); it != list.end(); ++it) { CHECK(*it == expected[idx++]); }
        CHECK(idx==10);
    }

    TEST_CASE("Range-for on empty list does nothing")
    {
        DoublyLinkedList<int> list;
        int sum = 0;
        for (int x : list) sum += x;
        CHECK(sum == 0);
    }

    TEST_CASE("Iterating large list counts correctly")
    {
        DoublyLinkedList<int> list;
        for (int i=0;i<100;++i) list.insertAtTail(i);
        int count = 0;
        for (auto it = list.begin(); it != list.end(); ++it) ++count;
        CHECK(count == 100);
    }

    TEST_CASE("Iterator compare across different lists are not equal")
    {
        DoublyLinkedList<int> a, b;
        a.insertAtTail(1);
        b.insertAtTail(1);
        CHECK(a.begin() != b.begin());
    }

    TEST_CASE("Dereference after ++ from last hits end; do not deref end")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        auto it = list.begin();
        CHECK(*it == 1);
        ++it;
        CHECK(it == list.end());
    }

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
