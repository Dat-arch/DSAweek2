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
        for (int v : {1, 2, 3, 4}) list.insertAtTail(v);     // [1,2,3,4]

        auto it = list.end();   // tail sentinel
        int expected[] = {4, 3, 2, 1};
        int idx = 0;

        while (it != list.begin())
        {
            --it;                                   // lùi về nút hợp lệ
            CHECK(*it == expected[idx++]);
        }
        CHECK(idx == 4);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Iterator works with <algorithm> utilities")
    {
        DoublyLinkedList<int> list;
        for (int v : {5, 10, 15, 20}) list.insertAtTail(v);

        // accumulate tổng
        int sum = std::accumulate(list.begin(), list.end(), 0);
        CHECK(sum == 50);

        // find phần tử
        auto it = std::find(list.begin(), list.end(), 15);
        CHECK(it != list.end());
        CHECK(*it == 15);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Const list iteration")
    {
        DoublyLinkedList<int> tmp;
        for (int v : {7, 8}) tmp.insertAtTail(v);
        const DoublyLinkedList<int>& list = tmp;    // binding const

        int product = 1;
        for (auto it = list.begin(); it != list.end(); ++it)
            product *= *it;

        CHECK(product == 56);                       // 7*8
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Iterate empty list safely")
    {
        DoublyLinkedList<int> empty;
        CHECK(empty.begin() == empty.end());        // cả hai trỏ đầu giả
        for (int v : empty)
            CHECK(false);                           // không được vào đây
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Iterator validity after external deleteAt")
    {
        DoublyLinkedList<int> list;
        for (int v : {1, 2, 3}) list.insertAtTail(v);   // [1,2,3]

        auto it = list.begin();     // trỏ 1
        list.deleteAt(1);           // xoá phần tử 2 ở giữa

        CHECK(*it == 1);            // iterator vẫn trỏ nút 1 hợp lệ
        ++it;                       // dịch sang nút tiếp (giờ là 3)
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
        CHECK(it1 == it2);          // cùng nút đầu

        ++it2;
        CHECK(it1 != it2);          // khác nút
        --it2;
        CHECK(it1 == it2);          // quay lại nút đầu
    }
}

}