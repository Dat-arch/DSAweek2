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

    auto pointToString = [](Point &p) -> std::string {
        return "(" + std::to_string(static_cast<int>(p.getX())) +
               "," + std::to_string(static_cast<int>(p.getY())) + ")";
    };

    std::string str = list.toString(pointToString);
    CHECK(str == "[(9,0), (8,1)]");
}
}

// TODO add test case
// -----------------------------------------------------------------------------
// Extra tests for DoublyLinkedList
// -----------------------------------------------------------------------------
TEST_SUITE("DoublyLinkedList - Extended Tests")
{
    /* --------------------------------------------------------------------- */
    TEST_CASE("Insert-at index (head, middle, tail) and automatic length")
    {
        DoublyLinkedList<int> list;

        // insert at index 0 on empty list  ⇒  acts like insertAtHead
        list.insertAt(0, 10);                     // [10]
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 10);

        // insert at head again
        list.insertAt(0, 5);                      // [5,10]
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 5);

        // insert in the middle
        list.insertAt(1, 7);                      // [5,7,10]
        CHECK(list.size() == 3);
        CHECK(list.get(1) == 7);

        // insert at tail using index == size()
        list.insertAt(3, 12);                     // [5,7,10,12]
        CHECK(list.size() == 4);
        CHECK(list.get(3) == 12);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("insertAt - out-of-range should throw std::out_of_range")
    {
        DoublyLinkedList<int> list;
        CHECK_THROWS_AS(list.insertAt(1, 42), std::out_of_range);
        list.insertAtHead(1);                     // [1]
        CHECK_THROWS_AS(list.insertAt(3, 99), std::out_of_range);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("deleteAt: head, tail, middle, last-element")
    {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 4; ++i) list.insertAtTail(i); // [1,2,3,4]

        // delete head
        list.deleteAt(0);                          // [2,3,4]
        CHECK(list.get(0) == 2);
        CHECK(list.size() == 3);

        // delete tail
        list.deleteAt(list.size() - 1);            // [2,3]
        CHECK(list.get(1) == 3);
        CHECK(list.size() == 2);

        // delete middle (now index 0)
        list.deleteAt(0);                          // [3]
        CHECK(list.get(0) == 3);
        CHECK(list.size() == 1);

        // deleting the single remaining node empties list
        list.deleteAt(0);                          // []
        CHECK(list.size() == 0);
        CHECK_THROWS_AS(list.get(0), std::out_of_range);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("deleteAt - out-of-range should throw std::out_of_range")
    {
        DoublyLinkedList<int> list;
        CHECK_THROWS_AS(list.deleteAt(0), std::out_of_range);
        list.insertAtHead(11);
        CHECK_THROWS_AS(list.deleteAt(2), std::out_of_range);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("indexOf and contains")
    {
        DoublyLinkedList<char> list;
        for (char c : {'a','b','c','b'}) list.insertAtTail(c); // [a,b,c,b]

        CHECK(list.indexOf('a') == 0);
        CHECK(list.indexOf('c') == 2);
        CHECK(list.indexOf('b') == 1);          // first occurrence
        CHECK(list.indexOf('x') == -1);

        CHECK(list.contains('c') == true);
        CHECK(list.contains('x') == false);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("reverse: even, odd, and empty list")
    {
        // even
        DoublyLinkedList<int> even;
        for (int i : {1,2,3,4}) even.insertAtTail(i);        // [1,2,3,4]
        even.reverse();                                      // [4,3,2,1]
        CHECK(even.get(0) == 4);
        CHECK(even.get(3) == 1);

        // odd
        DoublyLinkedList<int> odd;
        for (int i : {5,6,7}) odd.insertAtTail(i);           // [5,6,7]
        odd.reverse();                                       // [7,6,5]
        CHECK(odd.get(0) == 7);
        CHECK(odd.get(2) == 5);

        // empty
        DoublyLinkedList<int> empty;
        empty.reverse();                                     // still empty
        CHECK(empty.size() == 0);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Iterator: forward & backward traversal")
    {
        DoublyLinkedList<int> list;
        for (int i=1;i<=4;++i) list.insertAtTail(i); // [1,2,3,4]

        // forward
        int expected = 1;
        for (auto it = list.begin(); it != list.end(); ++it, ++expected)
            CHECK(*it == expected);

        // backward using -- over temporary iterator to tail sentinel
        auto it = list.end();   // sentinel
        --it;                   // last real node (4)
        CHECK(*it == 4);
        --it; CHECK(*it == 3);
        --it; CHECK(*it == 2);
        --it; CHECK(*it == 1);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Iterator in range-based for loop")
{
    DoublyLinkedList<int> list;
    list.insertAtTail(8);
    list.insertAtTail(6);
    list.insertAtTail(4);   // [8,6,4]

    // Collect iteration output without std::vector
    std::ostringstream oss;
    bool first = true;
    for (int x : list) {
        if (!first) oss << ',';
        first = false;
        oss << x;
    }
    CHECK(oss.str() == "8,6,4");
}


    /* --------------------------------------------------------------------- */
    TEST_CASE("toString with default convert2str = nullptr")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(3);
        list.insertAtTail(4);
        // default formatter should wrap single values
        CHECK(list.toString() == "[3, 4]");
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Copy constructor and assignment operator (deep copy)")
    {
        DoublyLinkedList<int> src;
        for (int i : {1,2,3}) src.insertAtTail(i);

        // copy-constructor
        DoublyLinkedList<int> copy(src);
        src.deleteAt(0);
        CHECK(copy.size() == 3);
        CHECK(copy.get(0) == 1);

        // copy-assignment
        DoublyLinkedList<int> dst;
        dst = copy;
        copy.deleteAt(1);              // modify copy
        CHECK(dst.size() == 3);
        CHECK(dst.get(1) == 2);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Move constructor and move assignment")
    {
        DoublyLinkedList<int> temp;
        temp.insertAtTail(99);

        // move-constructor
        DoublyLinkedList<int> moved(std::move(temp));
        CHECK(moved.size() == 1);
        CHECK(moved.get(0) == 99);

        // move-assignment
        DoublyLinkedList<int> target;
        target = std::move(moved);
        CHECK(target.size() == 1);
        CHECK(target.get(0) == 99);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Large input stress (1,000 elements)")
    {
        DoublyLinkedList<int> list;
        for (int i=0;i<1'000;++i) list.insertAtTail(i);
        CHECK(list.size() == 1'000);
        CHECK(list.get(999) == 999);

        list.reverse();
        CHECK(list.get(0) == 999);
        CHECK(list.get(999) == 0);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Self-reverse twice returns original order")
    {
        DoublyLinkedList<int> list;
        for (int x : {2,4,6,8}) list.insertAtTail(x);
        auto first = list.toString();

        list.reverse();   // reversed
        list.reverse();   // original
        CHECK(list.toString() == first);
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("contains and indexOf after deletes")
    {
        DoublyLinkedList<int> list;
        for (int i=0;i<5;++i) list.insertAtTail(i); // [0,1,2,3,4]
        list.deleteAt(2);                           // remove 2

        CHECK(list.contains(2) == false);
        CHECK(list.indexOf(3) == 2);                // shifted left
    }

    /* --------------------------------------------------------------------- */
    TEST_CASE("Chained insertAtHead & insertAtTail alternation")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(5);           // [5]
        list.insertAtTail(6);           // [5,6]
        list.insertAtHead(4);           // [4,5,6]
        list.insertAtTail(7);           // [4,5,6,7]

        CHECK(list.get(0) == 4);
        CHECK(list.get(3) == 7);
        CHECK(list.size() == 4);
    }
}
