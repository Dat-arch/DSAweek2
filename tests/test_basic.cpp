#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Basic Operations")
{

    TEST_CASE("New list is empty and size is 0")
    {
        DoublyLinkedList<int> list;
        CHECK(list.size() == 0);
    }

    TEST_CASE("get/delete on empty throws")
    {
        DoublyLinkedList<int> list;
        CHECK_THROWS_AS(list.get(0), std::out_of_range);
        CHECK_THROWS_AS(list.deleteAt(0), std::out_of_range);
    }

    TEST_CASE("insertAt at head (index 0) on empty equals insertAtHead")
    {
        DoublyLinkedList<int> a, b;
        a.insertAtHead(42);
        b.insertAt(0, 42);
        CHECK(a.size() == 1);
        CHECK(b.size() == 1);
        CHECK(a.get(0) == 42);
        CHECK(b.get(0) == 42);
    }

    TEST_CASE("insertAt at tail (index size)")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAt(2, 3);
        CHECK(list.size() == 3);
        CHECK(list.get(2) == 3);
    }

    TEST_CASE("insertAt middle shifts elements right")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1, 2); // [1,2,3]
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }

    TEST_CASE("insertAt invalid indices throw")
    {
        DoublyLinkedList<int> list;
        CHECK_THROWS_AS(list.insertAt(-1, 1), std::out_of_range);
        CHECK_THROWS_AS(list.insertAt(1, 1), std::out_of_range);
    }

    TEST_CASE("deleteAt head/tail/middle")
    {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 5; ++i) list.insertAtTail(i); // [1..5]
        list.deleteAt(0); // [2,3,4,5]
        CHECK(list.get(0) == 2);
        list.deleteAt(2); // remove 4 -> [2,3,5]
        CHECK(list.get(2) == 5);
        list.deleteAt(2); // remove 5 -> [2,3]
        CHECK(list.size() == 2);
    }

    TEST_CASE("deleteAt invalid indices throw")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        CHECK_THROWS_AS(list.deleteAt(-1), std::out_of_range);
        CHECK_THROWS_AS(list.deleteAt(1), std::out_of_range);
    }

    TEST_CASE("indexOf returns first occurrence with duplicates")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(7);
        list.insertAtTail(8);
        list.insertAtTail(7);
        CHECK(list.indexOf(7) == 0);
        CHECK(list.indexOf(8) == 1);
        CHECK(list.indexOf(9) == -1);
    }

    TEST_CASE("contains works for present and absent elements")
    {
        DoublyLinkedList<std::string> list;
        list.insertAtTail("a");
        list.insertAtTail("b");
        CHECK(list.contains("a"));
        CHECK_FALSE(list.contains("c"));
    }

    TEST_CASE("reverse empty and single element are stable")
    {
        DoublyLinkedList<int> e;
        e.reverse();
        CHECK(e.size() == 0);
        DoublyLinkedList<int> s;
        s.insertAtHead(5);
        s.reverse();
        CHECK(s.get(0) == 5);
    }

    TEST_CASE("reverse multiple elements")
    {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 4; ++i) list.insertAtTail(i); // [1,2,3,4]
        list.reverse(); // [4,3,2,1]
        CHECK(list.get(0) == 4);
        CHECK(list.get(1) == 3);
        CHECK(list.get(2) == 2);
        CHECK(list.get(3) == 1);
    }

    TEST_CASE("toString default for ints")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        auto s = list.toString();
        CHECK(s.find("10") != std::string::npos);
        CHECK(s.find("20") != std::string::npos);
    }

    TEST_CASE("mutation through get reference")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.get(1) = 99;
        CHECK(list.get(1) == 99);
    }

    TEST_CASE("large insertions maintain size and order")
    {
        DoublyLinkedList<int> list;
        const int N = 100;
        for (int i = 0; i < N; ++i) list.insertAtTail(i);
        CHECK(list.size() == N);
        CHECK(list.get(0) == 0);
        CHECK(list.get(N-1) == N-1);
    }

    TEST_CASE("insertAt alternating head/tail builds correct sequence")
    {
        DoublyLinkedList<int> list; // will build [4,2,0,1,3]
        list.insertAtHead(2);          // [2]
        list.insertAtHead(4);          // [4,2]
        list.insertAtTail(0);          // [4,2,0]
        list.insertAt(3, 3);           // [4,2,0,3]
        list.insertAt(3, 1);           // [4,2,0,1,3]
        CHECK(list.get(0) == 4);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 0);
        CHECK(list.get(3) == 1);
        CHECK(list.get(4) == 3);
    }

    TEST_CASE("get out of range negatives and too large")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        CHECK_THROWS_AS(list.get(-1), std::out_of_range);
        CHECK_THROWS_AS(list.get(1), std::out_of_range);
    }

    TEST_CASE("double list operations")
    {
        DoublyLinkedList<double> list;
        list.insertAtTail(1.5);
        list.insertAtHead(0.5);
        list.insertAt(1, 1.0); // [0.5,1.0,1.5]
        CHECK(list.contains(1.0));
        CHECK(list.indexOf(1.5) == 2);
    }

    TEST_CASE("Point indexOf and contains using operator==")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1,2));
        list.insertAtTail(Point(3,4));
        CHECK(list.contains(Point(1,2)));
        CHECK(list.indexOf(Point(3,4)) == 1);
        CHECK_FALSE(list.contains(Point(9,9)));
    }

    TEST_CASE("toString with converter for Points formatting")
    {
        auto conv = [](Point &p){ return std::to_string(int(p.getX()))+","+std::to_string(int(p.getY())); };
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(9,0));
        list.insertAtTail(Point(8,1));
        auto s = list.toString(conv);
        CHECK(s.find("9,0") != std::string::npos);
        CHECK(s.find("8,1") != std::string::npos);
    }

    TEST_CASE("delete all elements leads to empty list")
    {
        DoublyLinkedList<int> list;
        for (int i=0;i<5;++i) list.insertAtTail(i);
        for (int i=0;i<5;++i) list.deleteAt(0);
        CHECK(list.size()==0);
        CHECK_THROWS_AS(list.get(0), std::out_of_range);
    }

    TEST_CASE("indexOf after reverse")
    {
        DoublyLinkedList<int> list;
        for (int i=1;i<=4;++i) list.insertAtTail(i); // [1,2,3,4]
        list.reverse(); // [4,3,2,1]
        CHECK(list.indexOf(4)==0);
        CHECK(list.indexOf(1)==3);
    }

    TEST_CASE("contains on large list for last element")
    {
        DoublyLinkedList<int> list;
        for (int i=0;i<50;++i) list.insertAtTail(i);
        CHECK(list.contains(49));
        CHECK_FALSE(list.contains(50));
    }

    TEST_CASE("Insert at head and tail")
    {
        DoublyLinkedList<int> list;

        SUBCASE("Insert at head")
        {
            list.insertAtHead(2);
            list.insertAtHead(1);
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
        }

        SUBCASE("Insert at tail")
        {
            list.insertAtTail(1);
            list.insertAtTail(2);
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
        }
    }

    TEST_CASE("Delete and reverse")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3); // [1, 2, 3]

        SUBCASE("Delete middle element")
        {
            list.deleteAt(1); // remove 2
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 3);
        }

        SUBCASE("Reverse list")
        {
            list.reverse(); // should become [3, 2, 1]
            CHECK(list.get(0) == 3);
            CHECK(list.get(2) == 1);
        }
    }
}

TEST_SUITE("DoublyLinkedList<Point> Operations")
{
    std::string pointToString(Point & p)
    {
        return "(" + std::to_string(int(p.getX())) + "," + std::to_string(int(p.getY())) + ")";
    }

    TEST_CASE("Insert and get Point")
    {
        DoublyLinkedList<Point> list;

        SUBCASE("Insert at head")
        {
            list.insertAtHead(Point(1, 2));
            list.insertAtHead(Point(3, 4));
            CHECK(list.size() == 2);
            CHECK(list.get(0) == Point(3, 4));
            CHECK(list.get(1) == Point(1, 2));
        }
    }

    TEST_CASE("To string of list<Point>")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(9, 0));
        list.insertAtTail(Point(8, 1));
        std::string str = list.toString(pointToString);
        CHECK(str == "[(9,0), (8,1)]");
    }
}

// TODO add test case