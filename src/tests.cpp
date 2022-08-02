#include <gtest/gtest.h>

#include "s21_containers.h"

namespace s21 {

//=========================================================================
// ITERATORS TESTS
//=========================================================================

TEST(list_iterators, iterator_comparison_test) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    list<int> my_list(a);

    list<int>::iterator itr = my_list.begin();
    list<int>::iterator itr2 = my_list.begin();
    EXPECT_TRUE(itr == itr2);
    itr2 = my_list.end();
    --itr2;
    --itr2;
    --itr2;
    ++itr;
    ++itr;
    EXPECT_TRUE(itr == itr2);
    --itr2;
    EXPECT_TRUE(itr != itr2);
}

//=========================================================================
// LIST TESTS
//=========================================================================

TEST(list, default_constructor_test) {
    list<int> my_list;
    int example;
    memset(&example, 0, sizeof(int));
    EXPECT_EQ(my_list.front(), example);
}

TEST(list, parametrized_constructor_test) {
    list<int> my_list(5);
    EXPECT_EQ(my_list.size(), 5);

    int example;
    memset(&example, 0, sizeof(int));
    EXPECT_EQ(my_list.back(), example);

    list<int> my_list2(0);
    EXPECT_EQ((my_list2.size()), 0);
    EXPECT_EQ(my_list2.front(), example);
}

TEST(list, initializer_constructor_test) {
    std::initializer_list<double> a = {1.5, 2.34, 3.789, -0.35, 5};
    list<double> my_list(a);
    list<double>::iterator itr = my_list.begin();
    ++itr;
    ++itr;
    ++itr;
    --itr;
    EXPECT_EQ(*itr, 3.789);
    list<double>::iterator itr2 = my_list.begin();
    ++itr2;
    ++itr2;
    EXPECT_TRUE(itr == itr2);
    list<double>::iterator itr3 = my_list.begin();
    ++itr3;
    EXPECT_TRUE(itr2 != itr3);
    EXPECT_EQ(my_list.size(), 5);
    std::initializer_list<double> b = {};
    list<double> my_list2(b);
    EXPECT_EQ(my_list2.size(), 0);
}

TEST(list, copy_constructor_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    list<int> my_list(a);

    list<int> my_list2(my_list);
    list<int>::iterator itr = my_list2.begin();
    EXPECT_EQ(*itr, 1);
    ++itr;
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 3);
    ++itr;
    EXPECT_EQ(*itr, 4);
    ++itr;
    EXPECT_EQ(*itr, 5);
}
TEST(list, copy_constructor_test_2) {
    std::initializer_list<int> b = {};
    list<int> my_list3(b);
    list<int> my_list4(my_list3);
    int example;
    memset(&example, 0, sizeof(int));
    EXPECT_EQ(my_list4.front(), example);
}

TEST(list, move_constructor_test) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    list<int> my_list(a);
    list<int> my_list2(std::move(my_list));

    list<int>::iterator itr2 = my_list2.end();
    --itr2;
    EXPECT_EQ(*itr2, 5);
    --itr2;
    EXPECT_EQ(*itr2, 4);
    --itr2;
    EXPECT_EQ(*itr2, 3);
    --itr2;
    EXPECT_EQ(*itr2, 2);
    --itr2;
    EXPECT_EQ(*itr2, 1);

    EXPECT_EQ(my_list.size(), 0);
}

TEST(list, asignment_operator_test) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    list<int> my_list(a);
    list<int> my_list2;
    my_list2 = my_list;

    list<int>::iterator itr2 = my_list2.end();
    --itr2;
    EXPECT_EQ(*itr2, 5);
    --itr2;
    EXPECT_EQ(*itr2, 4);
    --itr2;
    EXPECT_EQ(*itr2, 3);
    --itr2;
    EXPECT_EQ(*itr2, 2);
    --itr2;
    EXPECT_EQ(*itr2, 1);

    EXPECT_EQ(my_list.size(), 5);
}

TEST(list, front_and_end_test) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    list<int> my_list(a);
    EXPECT_EQ(my_list.front(), 1);
    EXPECT_EQ(my_list.back(), 5);
    list<int>::iterator itr;
    itr = my_list.end();
    --itr;
    EXPECT_EQ(*itr, 5);
}

TEST(list, empty_test_1) {
    list<long double*> my_list;
    EXPECT_TRUE(my_list.empty());
}
TEST(list, empty_test_2) {
    list<long double*> my_list2(0);
    EXPECT_TRUE(my_list2.empty());
}
TEST(list, empty_test_3) {
    list<long double*> my_list(5);
    EXPECT_FALSE(my_list.empty());
}

TEST(list, max_size_test) {
    list<long double*> my_list;
    EXPECT_EQ(my_list.max_size(), MAX_SIZE);
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    list<int> my_list2(a);
    EXPECT_EQ(my_list2.max_size(), MAX_SIZE);
}

TEST(list, clear_test) {
    list<int> my_list;
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    list<int> my_list2(a);
    my_list2.clear();
    EXPECT_TRUE(my_list == my_list2);
}

TEST(list, erase_test_1) {
    std::initializer_list<int> a = {1, 789, 2, 3, 4};
    list<int> my_list(a);
    list<int>::iterator itr;
    itr = my_list.begin();
    ++itr;
    my_list.erase(itr);
    // EXPECT_EQ(*itr, 789);
    itr = my_list.begin();
    ++itr;
    EXPECT_EQ(*itr, 2);
}
TEST(list, erase_test_2) {
    std::initializer_list<int> b = {};
    list<int> my_list2(b);
    list<int>::iterator itr2;
    itr2 = my_list2.begin();
    --itr2;
    --itr2;
    my_list2.erase(itr2);
    EXPECT_EQ(*itr2, 0);
}

TEST(list, insert_test_1) {
    std::initializer_list<int> a = {1, 3, 4, 5};
    list<int> my_list(a);
    list<int>::iterator itr = my_list.begin();
    ++itr;
    list<int>::iterator return_itr = my_list.insert(itr, 2);
    EXPECT_EQ(*itr, 3);
    EXPECT_EQ(*return_itr, 2);
    list<int>::iterator itr2 = my_list.begin();
    EXPECT_EQ(*itr2, 1);
    ++itr2;
    EXPECT_EQ(*itr2, 2);
    ++itr2;
    EXPECT_EQ(*itr2, 3);
    ++itr2;
    EXPECT_EQ(*itr2, 4);
    ++itr2;
    EXPECT_EQ(*itr2, 5);
}
TEST(list, insert_test_2) {
    std::initializer_list<int> b = {};
    list<int> my_list3(b);
    list<int>::iterator itr3 = my_list3.begin();
    list<int>::iterator return_itr3 = my_list3.insert(itr3, 2);
    EXPECT_EQ(*itr3, 0);
    EXPECT_EQ(*return_itr3, 2);
    list<int>::iterator itr4 = my_list3.begin();
    EXPECT_EQ(*itr4, 2);
}
TEST(list, insert_test_3) {
    std::initializer_list<int> c = {2, 3, 4, 5};
    list<int> my_list5(c);
    list<int>::iterator itr5 = my_list5.begin();
    list<int>::iterator return_itr5 = my_list5.insert(itr5, 1);
    EXPECT_EQ(*itr5, 2);
    EXPECT_EQ(*return_itr5, 1);
    list<int>::iterator itr6 = my_list5.begin();
    EXPECT_EQ(*itr6, 1);
    ++itr6;
    EXPECT_EQ(*itr6, 2);
    ++itr6;
    EXPECT_EQ(*itr6, 3);
    ++itr6;
    EXPECT_EQ(*itr6, 4);
    ++itr6;
    EXPECT_EQ(*itr6, 5);
}

TEST(list, push_front_test_1) {
    std::initializer_list<int> a = {2, 3, 4, 5};
    list<int> my_list(a);
    my_list.push_front(1);
    list<int>::iterator itr2 = my_list.begin();
    EXPECT_EQ(*itr2, 1);
    ++itr2;
    EXPECT_EQ(*itr2, 2);
    ++itr2;
    EXPECT_EQ(*itr2, 3);
    ++itr2;
    EXPECT_EQ(*itr2, 4);
    ++itr2;
    EXPECT_EQ(*itr2, 5);
}
TEST(list, push_front_test_2) {
    std::initializer_list<int> b = {};
    list<int> my_list3(b);
    my_list3.push_front(1);
    list<int>::iterator itr4 = my_list3.begin();
    EXPECT_EQ(*itr4, 1);
}

TEST(list, push_back_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4};
    list<int> my_list(a);
    my_list.push_back(5);
    list<int>::iterator itr2 = my_list.begin();
    EXPECT_EQ(*itr2, 1);
    ++itr2;
    EXPECT_EQ(*itr2, 2);
    ++itr2;
    EXPECT_EQ(*itr2, 3);
    ++itr2;
    EXPECT_EQ(*itr2, 4);
    ++itr2;
    EXPECT_EQ(*itr2, 5);
}
TEST(list, push_back_test_2) {
    std::initializer_list<int> b = {};
    list<int> my_list3(b);
    my_list3.push_back(1);
    list<int>::iterator itr4 = my_list3.begin();
    EXPECT_EQ(*itr4, 1);
}

TEST(list, swap_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    list<int> my_list(a);
    std::initializer_list<int> b = {6, 7, 8, 9};
    list<int> my_list2(b);
    my_list.swap(my_list2);
    EXPECT_EQ((my_list.size()), 4);
    EXPECT_EQ((my_list2.size()), 5);
    list<int>::iterator itr2 = my_list.begin();
    EXPECT_EQ(*itr2, 6);
    ++itr2;
    EXPECT_EQ(*itr2, 7);
    ++itr2;
    EXPECT_EQ(*itr2, 8);
    ++itr2;
    EXPECT_EQ(*itr2, 9);
    ++itr2;
    ++itr2;
    EXPECT_EQ(*itr2, 6);
    list<int>::iterator itr3 = my_list2.begin();
    EXPECT_EQ(*itr3, 1);
    ++itr3;
    EXPECT_EQ(*itr3, 2);
    ++itr3;
    EXPECT_EQ(*itr3, 3);
    ++itr3;
    EXPECT_EQ(*itr3, 4);
    ++itr3;
    EXPECT_EQ(*itr3, 5);
}
TEST(list, swap_test_2) {
    std::initializer_list<int> c = {};
    list<int> my_list3(c);
    std::initializer_list<int> d = {1};
    list<int> my_list4(d);
    my_list3.swap(my_list4);
    EXPECT_EQ((my_list3.size()), 1);
    EXPECT_EQ((my_list4.size()), 0);
}
TEST(list, swap_test_3) {
    std::initializer_list<int> e = {1, 2, 3};
    list<int> my_list5(e);
    my_list5.swap(my_list5);
    EXPECT_EQ((my_list5.size()), 3);
}

TEST(list, sort_test_1) {
    std::initializer_list<int> a = {1, 4, 2, 5, 3, 3};
    list<int> my_list(a);
    my_list.sort();
    list<int>::iterator itr2 = my_list.begin();
    EXPECT_EQ(*itr2, 1);
    ++itr2;
    EXPECT_EQ(*itr2, 2);
    ++itr2;
    EXPECT_EQ(*itr2, 3);
    ++itr2;
    EXPECT_EQ(*itr2, 3);
    ++itr2;
    EXPECT_EQ(*itr2, 4);
    ++itr2;
    EXPECT_EQ(*itr2, 5);
}
TEST(list, sort_test_2) {
    std::initializer_list<int> a = {1, 1};
    list<int> my_list(a);
    my_list.sort();
    list<int>::iterator itr2 = my_list.begin();
    EXPECT_EQ(*itr2, 1);
    ++itr2;
    EXPECT_EQ(*itr2, 1);
}
TEST(list, sort_test_3) {
    std::initializer_list<int> a = {};
    list<int> my_list(a);
    my_list.sort();
}

TEST(list, merge_test_1) {
    std::initializer_list<int> a = {1, 2, 3};
    std::initializer_list<int> b = {4, 5};
    list<int> my_list(a);
    list<int> my_list2(b);
    my_list.merge(my_list2);
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 1);
    ++itr;
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 3);
    ++itr;
    EXPECT_EQ(*itr, 4);
    ++itr;
    EXPECT_EQ(*itr, 5);
}
TEST(list, merge_test_2) {
    std::initializer_list<int> a = {1, 2, 3};
    std::initializer_list<int> b = {};
    list<int> my_list(a);
    list<int> my_list2(b);
    my_list.merge(my_list2);
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 1);
    ++itr;
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 3);
}
TEST(list, merge_test_3) {
    std::initializer_list<int> a = {};
    std::initializer_list<int> b = {};
    list<int> my_list(a);
    list<int> my_list2(b);
    my_list.merge(my_list2);
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 0);
}

TEST(list, pop_front_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    list<int> my_list(a);
    my_list.pop_front();
    EXPECT_EQ(my_list.size(), 4);
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 3);
    ++itr;
    EXPECT_EQ(*itr, 4);
    ++itr;
    EXPECT_EQ(*itr, 5);
}
TEST(list, pop_front_test_2) {
    std::initializer_list<int> a = {};
    list<int> my_list(a);
    my_list.pop_front();
    EXPECT_EQ(my_list.size(), 0);
}

TEST(list, pop_back_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    list<int> my_list(a);
    my_list.pop_front();
    EXPECT_EQ(my_list.size(), 4);
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 3);
    ++itr;
    EXPECT_EQ(*itr, 4);
    ++itr;
    EXPECT_EQ(*itr, 5);
}
TEST(list, pop_back_test_2) {
    std::initializer_list<int> a = {};
    list<int> my_list(a);
    my_list.pop_back();
    EXPECT_EQ(my_list.size(), 0);
}

TEST(list, splice_test_1) {
    std::initializer_list<int> a = {1, 2, 3};
    std::initializer_list<int> b = {4, 5};
    list<int> my_list(a);
    list<int> my_list2(b);
    list<int>::iterator itr;
    itr = my_list.end();
    my_list.splice(itr, my_list2);
    itr = my_list.begin();
    EXPECT_EQ(*itr, 1);
    ++itr;
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 3);
    ++itr;
    EXPECT_EQ(*itr, 4);
    ++itr;
    EXPECT_EQ(*itr, 5);
}
TEST(list, splice_test_2) {
    std::initializer_list<int> a = {1, 5, 6};
    std::initializer_list<int> b = {2, 3, 4};
    list<int> my_list(a);
    list<int> my_list2(b);
    list<int>::iterator itr;
    itr = my_list.begin();
    ++itr;
    my_list.splice(itr, my_list2);
    itr = my_list.begin();
    EXPECT_EQ(*itr, 1);
    ++itr;
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 3);
    ++itr;
    EXPECT_EQ(*itr, 4);
    ++itr;
    EXPECT_EQ(*itr, 5);
    ++itr;
    EXPECT_EQ(*itr, 6);
}
TEST(list, splice_test_3) {
    std::initializer_list<int> a = {4, 5, 6};
    std::initializer_list<int> b = {1, 2, 3};
    list<int> my_list(a);
    list<int> my_list2(b);
    list<int>::iterator itr;
    itr = my_list.begin();
    my_list.splice(itr, my_list2);
    itr = my_list.begin();
    EXPECT_EQ(*itr, 1);
    ++itr;
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 3);
    ++itr;
    EXPECT_EQ(*itr, 4);
    ++itr;
    EXPECT_EQ(*itr, 5);
    ++itr;
    EXPECT_EQ(*itr, 6);
}
TEST(list, splice_test_4) {
    std::initializer_list<int> a = {};
    std::initializer_list<int> b = {1, 2, 3};
    list<int> my_list(a);
    list<int> my_list2(b);
    list<int>::iterator itr;
    itr = my_list.begin();
    ++itr;
    my_list.splice(itr, my_list2);
    itr = my_list.begin();
    EXPECT_EQ(*itr, 1);
    ++itr;
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 3);
}
TEST(list, splice_test_5) {
    std::initializer_list<int> a = {};
    std::initializer_list<int> b = {};
    list<int> my_list(a);
    list<int> my_list2(b);
    EXPECT_EQ(my_list.size(), 0);
}

TEST(list, reverse_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    list<int> my_list(a);
    my_list.reverse();
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 5);
    ++itr;
    EXPECT_EQ(*itr, 4);
    ++itr;
    EXPECT_EQ(*itr, 3);
    ++itr;
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 1);
}
TEST(list, reverse_test_2) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5, 6};
    list<int> my_list(a);
    my_list.reverse();
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 6);
    ++itr;
    EXPECT_EQ(*itr, 5);
    ++itr;
    EXPECT_EQ(*itr, 4);
    ++itr;
    EXPECT_EQ(*itr, 3);
    ++itr;
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 1);
}
TEST(list, reverse_test_3) {
    std::initializer_list<int> a = {1, 2};
    list<int> my_list(a);
    my_list.reverse();
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 1);
}
TEST(list, reverse_test_4) {
    std::initializer_list<int> a = {1};
    list<int> my_list(a);
    my_list.reverse();
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 1);
    EXPECT_EQ(my_list.size(), 1);
}
TEST(list, reverse_test_5) {
    std::initializer_list<int> a = {};
    list<int> my_list(a);
    my_list.reverse();
    EXPECT_EQ(my_list.size(), 0);
}

TEST(list, unique_test_1) {
    std::initializer_list<int> a = {1, 2, 2, 3, 4, 4, 4, 5};
    list<int> my_list(a);
    my_list.unique();
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 1);
    ++itr;
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 3);
    ++itr;
    EXPECT_EQ(*itr, 4);
    ++itr;
    EXPECT_EQ(*itr, 5);
}
TEST(list, unique_test_2) {
    std::initializer_list<int> a = {1, 2, 3};
    list<int> my_list(a);
    my_list.unique();
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 1);
    ++itr;
    EXPECT_EQ(*itr, 2);
    ++itr;
    EXPECT_EQ(*itr, 3);
}
TEST(list, unique_test_3) {
    std::initializer_list<int> a = {1, 1};
    list<int> my_list(a);
    my_list.unique();
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 1);
    EXPECT_EQ(my_list.size(), 1);
}
TEST(list, unique_test_4) {
    std::initializer_list<int> a = {};
    list<int> my_list(a);
    my_list.unique();
    list<int>::iterator itr;
    itr = my_list.begin();
    EXPECT_EQ(*itr, 0);
    EXPECT_EQ(my_list.size(), 0);
}

TEST(list, emplace_test_1) {
    struct structure {
        int x_;
        long double y_;
        char z_;
        bool operator==(const structure& other) const {
            return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
        }
        structure() {
            x_ = 0;
            y_ = 0;
            z_ = 0;
        }
        structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
    };
    structure elem1 = {1, 2., '3'};
    structure elem2 = {7, 8., '9'};
    structure expecting_result = {6, 7., '8'};
    std::initializer_list<structure> a = {elem1, elem2};
    list<structure> my_list(a);
    list<structure>::iterator itr = my_list.begin();
    ++itr;
    list<structure>::iterator return_itr = my_list.emplace(itr, 6, 7., '8');
    EXPECT_TRUE(*return_itr == expecting_result);
    EXPECT_TRUE(*itr == elem2);
    --itr;
    --itr;
    EXPECT_TRUE(*itr == elem1);
}
TEST(list, emplace_test_2) {
    struct structure {
        int x_;
        long double y_;
        char z_;
        bool operator==(const structure& other) const {
            return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
        }
        structure() {
            x_ = 0;
            y_ = 0;
            z_ = 0;
        }
        structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
    };
    structure expecting_result = {6, 7., '8'};
    std::initializer_list<structure> a;
    list<structure> my_list(a);
    list<structure>::iterator itr = my_list.begin();
    list<structure>::iterator return_itr = my_list.emplace(itr, 6, 7., '8');
    EXPECT_TRUE(*return_itr == expecting_result);
    EXPECT_TRUE(*(my_list.begin()) == expecting_result);
}
TEST(list, emplace_test_3) {
    list<int> my_list;
    list<int>::iterator itr = my_list.begin();
    list<int>::iterator return_itr = my_list.emplace(itr, 6);
    EXPECT_EQ(*return_itr, 6);
}

TEST(list, emplace_back_test) {
    struct structure {
        int x_;
        long double y_;
        char z_;
        bool operator==(const structure& other) const {
            return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
        }
        structure() {
            x_ = 0;
            y_ = 0;
            z_ = 0;
        }
        structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
    };
    structure elem1 = {1, 2., '3'};
    structure elem2 = {6, 7., '8'};
    structure expecting_result = {7, 8., '9'};
    std::initializer_list<structure> a = {elem1, elem2};
    list<structure> my_list(a);
    list<structure>::iterator itr = my_list.begin();
    my_list.emplace_back(7, 8., '9');
    EXPECT_TRUE(*itr == elem1);
    ++itr;
    EXPECT_TRUE(*itr == elem2);
    ++itr;
    EXPECT_TRUE(*itr == expecting_result);
}

TEST(list, emplace_front_test) {
    struct structure {
        int x_;
        long double y_;
        char z_;
        bool operator==(const structure& other) {
            return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
        }
        structure() {
            x_ = 0;
            y_ = 0;
            z_ = 0;
        }
        structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
    };
    structure elem1 = {6, 7., '8'};
    structure elem2 = {7, 8., '9'};
    structure expecting_result = {1, 2., '3'};
    std::initializer_list<structure> a = {elem1, elem2};
    list<structure> my_list(a);
    my_list.emplace_front(1, 2., '3');
    list<structure>::iterator itr = my_list.begin();
    EXPECT_TRUE(*itr == expecting_result);
    ++itr;
    EXPECT_TRUE(*itr == elem1);
    ++itr;
    EXPECT_TRUE(*itr == elem2);
}

//=========================================================================
// STACK TESTS
//=========================================================================

TEST(stack, top_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    stack<int> my_stack(a);
    EXPECT_EQ(my_stack.top(), 5);
}
TEST(stack, top_test_2) {
    std::initializer_list<int> a = {};
    stack<int> my_stack(a);
    EXPECT_EQ(my_stack.top(), 0);
}

TEST(stack, empty_test_1) {
    std::initializer_list<int> a = {};
    stack<int> my_stack(a);
    EXPECT_TRUE(my_stack.empty());
}
TEST(stack, empty_test_2) {
    std::initializer_list<int> a = {1, 2, 3};
    stack<int> my_stack(a);
    EXPECT_FALSE(my_stack.empty());
}

TEST(stack, size_test_1) {
    stack<int> my_stack(5);
    EXPECT_EQ((my_stack.size()), 5);
}
TEST(stack, size_test_2) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    stack<int> my_stack(a);
    EXPECT_EQ((my_stack.size()), 5);
}
TEST(stack, size_test_3) {
    stack<int> my_stack;
    EXPECT_EQ((my_stack.size()), 0);
}

TEST(stack, push_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4};
    stack<int> my_stack(a);
    my_stack.push(5);
    EXPECT_EQ(my_stack.top(), 5);
}
TEST(stack, push_test_2) {
    std::initializer_list<int> a = {};
    stack<int> my_stack(a);
    my_stack.push(1);
    EXPECT_EQ(my_stack.top(), 1);
}

TEST(stack, pop_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    stack<int> my_stack(a);
    my_stack.pop();
    EXPECT_EQ(my_stack.top(), 4);
    my_stack.pop();
    EXPECT_EQ(my_stack.top(), 3);
}
TEST(stack, pop_test_2) {
    std::initializer_list<int> a = {};
    stack<int> my_stack(a);
    my_stack.pop();
}

TEST(stack, swap_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    stack<int> my_stack(a);
    std::initializer_list<int> b = {6, 7, 8, 9};
    stack<int> my_stack2(b);
    my_stack.swap(my_stack2);
    EXPECT_EQ((my_stack.size()), 4);
    EXPECT_EQ((my_stack2.size()), 5);
    EXPECT_EQ(my_stack.top(), 9);
    my_stack.pop();
    EXPECT_EQ(my_stack.top(), 8);
    my_stack.pop();
    EXPECT_EQ(my_stack.top(), 7);
    my_stack.pop();
    EXPECT_EQ(my_stack.top(), 6);

    EXPECT_EQ(my_stack2.top(), 5);
    my_stack2.pop();
    EXPECT_EQ(my_stack2.top(), 4);
    my_stack2.pop();
    EXPECT_EQ(my_stack2.top(), 3);
    my_stack2.pop();
    EXPECT_EQ(my_stack2.top(), 2);
    my_stack2.pop();
    EXPECT_EQ(my_stack2.top(), 1);
}
TEST(stack, swap_test_2) {
    std::initializer_list<int> c = {};
    stack<int> my_stack3(c);
    std::initializer_list<int> d = {1};
    stack<int> my_stack4(d);
    my_stack3.swap(my_stack4);
    EXPECT_EQ((my_stack3.size()), 1);
    EXPECT_EQ((my_stack4.size()), 0);
}
TEST(stack, swap_test_3) {
    std::initializer_list<int> e = {1, 2, 3};
    stack<int> my_stack5(e);
    my_stack5.swap(my_stack5);
    EXPECT_EQ((my_stack5.size()), 3);
}

TEST(stack, emplace_front_test) {
    struct structure {
        int x_;
        long double y_;
        char z_;
        bool operator==(const structure& other) const {
            return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
        }
        structure() {
            x_ = 0;
            y_ = 0;
            z_ = 0;
        }
        structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
    };
    const structure elem1 = {6, 7., '8'};
    const structure elem2 = {7, 8., '9'};
    const structure expecting_result = {1, 2., '3'};
    std::initializer_list<structure> a = {elem1, elem2};
    stack<structure> my_stack(a);
    my_stack.emplace_front(1, 2., '3');
    EXPECT_TRUE(my_stack.top() == elem2);
    my_stack.pop();
    EXPECT_TRUE(my_stack.top() == elem1);
    my_stack.pop();
    EXPECT_TRUE(my_stack.top() == expecting_result);
}

//=========================================================================
// QUEUE TESTS
//=========================================================================

TEST(queue, front_and_end_queue_test) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    queue<int> my_queue(a);
    EXPECT_EQ(my_queue.front(), 1);
    EXPECT_EQ(my_queue.back(), 5);
}

TEST(queue, empty_queue_test_1) {
    std::initializer_list<int> a = {};
    queue<int> my_queue(a);
    EXPECT_TRUE(my_queue.empty());
}
TEST(queue, empty_queue_test_2) {
    std::initializer_list<int> a = {1, 2, 3};
    queue<int> my_queue(a);
    EXPECT_FALSE(my_queue.empty());
}

TEST(queue, size_queue_test_1) {
    queue<int> my_queue(5);
    EXPECT_EQ((my_queue.size()), 5);
}
TEST(queue, size_queue_test_2) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    queue<int> my_queue(a);
    EXPECT_EQ((my_queue.size()), 5);
}
TEST(queue, size_queue_test_3) {
    queue<int> my_queue;
    EXPECT_EQ((my_queue.size()), 0);
}

TEST(queue, push_queue_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4};
    queue<int> my_queue(a);
    my_queue.push(5);
    EXPECT_EQ(my_queue.back(), 5);
}
TEST(queue, push_queue_test_2) {
    std::initializer_list<int> a = {};
    queue<int> my_queue(a);
    my_queue.push(1);
    EXPECT_EQ(my_queue.front(), 1);
}

TEST(queue, pop_queue_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    queue<int> my_queue(a);
    my_queue.pop();
    my_queue.pop();
    EXPECT_EQ(my_queue.front(), 3);
}
TEST(queue, pop_queue_test_2) {
    std::initializer_list<int> a = {};
    queue<int> my_queue(a);
    my_queue.pop();
}

TEST(queue, swap_queue_test_1) {
    std::initializer_list<int> a = {1, 2, 3, 4, 5};
    queue<int> my_queue(a);
    std::initializer_list<int> b = {6, 7, 8, 9};
    queue<int> my_queue2(b);
    my_queue.swap(my_queue2);
    EXPECT_EQ((my_queue.size()), 4);
    EXPECT_EQ((my_queue2.size()), 5);
    EXPECT_EQ(my_queue.front(), 6);
    my_queue.pop();
    EXPECT_EQ(my_queue.front(), 7);
    my_queue.pop();
    EXPECT_EQ(my_queue.front(), 8);
    my_queue.pop();
    EXPECT_EQ(my_queue.front(), 9);

    EXPECT_EQ(my_queue2.front(), 1);
    my_queue2.pop();
    EXPECT_EQ(my_queue2.front(), 2);
    my_queue2.pop();
    EXPECT_EQ(my_queue2.front(), 3);
    my_queue2.pop();
    EXPECT_EQ(my_queue2.front(), 4);
    my_queue2.pop();
    EXPECT_EQ(my_queue2.front(), 5);
}
TEST(queue, swap_queue_test_2) {
    std::initializer_list<int> c = {};
    queue<int> my_queue3(c);
    std::initializer_list<int> d = {1};
    queue<int> my_queue4(d);
    my_queue3.swap(my_queue4);
    EXPECT_EQ((my_queue3.size()), 1);
    EXPECT_EQ((my_queue4.size()), 0);
}
TEST(queue, swap_queue_test_3) {
    std::initializer_list<int> e = {1, 2, 3};
    queue<int> my_queue5(e);
    my_queue5.swap(my_queue5);
    EXPECT_EQ((my_queue5.size()), 3);
}

TEST(queue, emplace_back_queue_test) {
    struct structure {
        int x_;
        long double y_;
        char z_;
        bool operator==(const structure& other) const {
            return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
        }
        structure() {
            x_ = 0;
            y_ = 0;
            z_ = 0;
        }
        structure(int x, long double y, char z) : x_(x), y_(y), z_(z) {}
    };
    structure elem1 = {1, 2., '3'};
    structure elem2 = {6, 7., '8'};
    structure expecting_result = {7, 8., '9'};
    std::initializer_list<structure> a = {elem1, elem2};
    queue<structure> my_queue(a);
    my_queue.emplace_back(7, 8., '9');
    EXPECT_TRUE(my_queue.front() == elem1);
    my_queue.pop();
    EXPECT_TRUE(my_queue.front() == elem2);
    my_queue.pop();
    EXPECT_TRUE(my_queue.front() == expecting_result);
}

TEST(map, constructors_tests) {
    std::initializer_list<std::pair<int, char>> data = {
        {4, 'X'}, {2, 'B'}, {5, 'E'}, {3, 'S'}, {1, 'W'}};
    map<int, char> map1(data), map2, map3(map1);
    map<int, char>::iterator it = map1.begin();
    EXPECT_EQ((*it).first, 1);
    EXPECT_EQ((*it).second, 'W');
    it--;
    it--;
    EXPECT_EQ((*it).first, 1);
    EXPECT_EQ((*it).second, 'W');
    it++;
    it++;
    it++;
    EXPECT_EQ((*it).first, 4);
    EXPECT_EQ((*it).second, 'X');
    it = map1.end();
    EXPECT_EQ((*it).first, 0);
    EXPECT_EQ((*it).second, '\0');
    it++;
    EXPECT_EQ((*it).first, 5);
    EXPECT_EQ((*it).second, 'E');
    it++;
    EXPECT_EQ((*it).first, 0);
    EXPECT_EQ((*it).second, '\0');

    map<int, char>::iterator it2 = map2.begin();
    EXPECT_EQ((*it2).first, 0);
    EXPECT_EQ((*it2).second, '\0');
    it2++;
    EXPECT_EQ((*it).first, 0);
    EXPECT_EQ((*it).second, '\0');
    it2--;
    it2--;
    EXPECT_EQ((*it).first, 0);
    EXPECT_EQ((*it).second, '\0');
    it2 = map2.end();
    EXPECT_EQ((*it).first, 0);
    EXPECT_EQ((*it).second, '\0');
    it2--;
    EXPECT_EQ((*it).first, 0);
    EXPECT_EQ((*it).second, '\0');
    it2++;
    it2++;
    EXPECT_EQ((*it).first, 0);
    EXPECT_EQ((*it).second, '\0');

    EXPECT_EQ((*(map1.begin())).first, (*(map3.begin())).first);
    EXPECT_EQ((*(map1.begin())).second, (*(map3.begin())).second);
    EXPECT_TRUE(map1 == map3);

    map<int, char> map4 = map1;
    EXPECT_EQ(map4.size(), map1.size());

    map<int, char> map5 = map2;
    EXPECT_EQ(map5.empty(), map2.empty());

    map<int, char> map6(std::move(map1));
    EXPECT_TRUE(map1.empty());
    EXPECT_EQ(map6.size(), 5);

    map<int, char> map7;
    EXPECT_TRUE(map7.empty());
    map7 = std::move(map4);
    EXPECT_TRUE(map4.empty());
    EXPECT_EQ(map7.size(), 5);
    EXPECT_EQ(MAX_SIZE, map7.max_size());

    map<int, char> map_one(data), map_two(data);
    EXPECT_TRUE(map_one == map_two);
    map_one.insert({21, 'S'});
    EXPECT_FALSE(map_one == map_two);
    EXPECT_TRUE(map_one != map_two);
}

TEST(map, iterator_tests) {
    std::initializer_list<std::pair<int, std::string>> data = {
        {4, "XXX"}, {2, "BBB"}, {5, "EEE"}, {3, "SSS"}, {1, "WWW"}};
    s21::map<int, std::string> m1(data);
    std::pair<int, std::string> result_arr[] = {
        {1, "WWW"}, {2, "BBB"}, {3, "SSS"}, {4, "XXX"}, {5, "EEE"}};
    int i = 0;
    for (auto it = m1.begin(); it != m1.end(); it++) {
        EXPECT_EQ(*it, result_arr[i]);
        i++;
    }
    map<int, std::string> map_str;
    map_str.insert({1, "string"});
    EXPECT_EQ((*map_str.begin()).second, "string");

    map_str.insert({-1, "minus"});
    EXPECT_EQ((*map_str.begin()).second, "minus");
    map<int, std::string>::iterator it1(m1.begin());
    it1++;
    it1++;
    EXPECT_EQ((*it1).second, "SSS");
    EXPECT_TRUE(it1 == m1.find(3));
    EXPECT_TRUE(it1 != m1.find(4));
    map<int, std::string> m2(data);
    EXPECT_TRUE(m2.find(5) != m1.find(5));
    map<int, std::string>::iterator it, it2(m2.begin());
    EXPECT_FALSE(it == it2);

    map<int, std::string>::const_iterator const_it = m1.find(4), const_it2;
    EXPECT_EQ((*const_it).second, "XXX");
    const_it2 = m1.end();
    EXPECT_EQ((*const_it2).first, 0);
}

TEST(map, clear_test) {
    std::initializer_list<std::pair<int, char>> data = {
        {4, 'X'}, {2, 'B'}, {5, 'E'}, {3, 'S'}, {1, 'W'}};
    map<int, char> map1(data), map2;
    map1.clear();
    EXPECT_TRUE(map1.empty());
    map2.clear();
    EXPECT_TRUE(map2.empty());
}

TEST(map, insert_test) {
    std::initializer_list<std::pair<int, char>> data = {
        {4, 'X'}, {2, 'B'}, {5, 'E'}, {3, 'S'}, {1, 'W'}};
    map<int, char> map1(data);
    std::pair<map<int, char>::iterator, bool> i1 = map1.insert({8, 'A'});
    EXPECT_TRUE(i1.second);
    EXPECT_EQ((*(i1.first)).second, 'A');
    EXPECT_EQ(map1.size(), 6);

    std::pair<map<int, char>::iterator, bool> i2 = map1.insert({4, '\n'});
    EXPECT_FALSE(i2.second);
    EXPECT_EQ((*(i2.first)).second, 'X');
    EXPECT_EQ(map1.size(), 6);
}

TEST(map, erase_test) {
    std::initializer_list<std::pair<int, char>> data = {
        {4, 'X'}, {2, 'B'}, {5, 'E'}, {3, 'S'}, {1, 'W'}};
    map<int, char> m1(data);
    map<int, char>::iterator it = m1.end();
    m1.erase(it);
    EXPECT_EQ((*it).first, 0);
    EXPECT_EQ((*it).second, '\0');
    it--;
    EXPECT_EQ((*it).second, 'E');
    m1.erase(it);
    EXPECT_EQ((*it).first, 0);
    EXPECT_EQ((*it).second, '\0');
    it = m1.find(2);
    m1.erase(it);
    EXPECT_EQ((*it).first, 3);
    EXPECT_EQ((*it).second, 'S');
    it--;
    EXPECT_EQ((*it).first, 1);
    EXPECT_EQ((*it).second, 'W');
    it++;
    it++;
    EXPECT_EQ((*it).first, 4);
    EXPECT_EQ((*it).second, 'X');
    for (auto iter = m1.begin(); iter != m1.end();) m1.erase(iter);
    EXPECT_TRUE(m1.empty());
}

TEST(map, swap_test) {
    std::initializer_list<std::pair<int, char>> data1 = {
        {4, 'X'}, {2, 'B'}, {5, 'E'}, {3, 'S'}, {1, 'W'}};
    std::initializer_list<std::pair<int, char>> data2 = {
        {6, 'x'}, {10, 'b'}, {7, 'e'}, {9, 's'}, {8, 'w'}};
    map<int, char> m1(data1), m2(data2), m3, m4, m5;
    m1.swap(m2);
    EXPECT_EQ((*m1.begin()).first, 6);
    EXPECT_EQ((*m1.begin()).second, 'x');
    EXPECT_EQ((*m2.begin()).first, 1);
    EXPECT_EQ((*m2.begin()).second, 'W');
    m3.swap(m1);
    EXPECT_TRUE(m1.empty());
    EXPECT_EQ(m3.size(), 5);
    m4.swap(m5);
    EXPECT_TRUE(m4.empty());
    EXPECT_TRUE(m5.empty());
}

TEST(map, merge_test) {
    std::initializer_list<std::pair<int, char>> data1 = {
        {4, 'X'}, {2, 'B'}, {5, 'E'}, {3, 'S'}, {1, 'W'}};
    std::initializer_list<std::pair<int, char>> data2 = {
        {6, 'x'}, {10, 'b'}, {7, 'e'}, {9, 's'}, {8, 'w'}};
    map<int, char> m1(data1), m2(data2), m3;
    m1.merge(m2);
    EXPECT_EQ(m1.size(), 10);
    EXPECT_EQ((*(--m1.end())).first, 10);
    m2.merge(m2);
    EXPECT_EQ(m2.size(), 5);
    m3.merge(m1);
    EXPECT_EQ(m3.size(), 10);

    std::initializer_list<std::pair<int, char>> data3 = {
        {4, 'X'}, {2, 'B'}, {5, 'E'}, {42, 'n'}, {21, 'm'}};
    map<int, char> m4(data3);
    m1.merge(m4);
    EXPECT_EQ(m1.size(), 12);
    EXPECT_TRUE(m1.contains(21));
    EXPECT_FALSE(m4.contains(-21));
}

TEST(map, element_access_test) {
    std::initializer_list<std::pair<int, std::string>> data = {
        {4, "XXX"}, {2, "BBB"}, {5, "EEE"}};
    map<int, std::string> m1(data);
    m1[4] = "HI";
    EXPECT_EQ(m1.at(4), "HI");
    m1.at(2) = "second";
    EXPECT_EQ(m1[2], "second");
    EXPECT_ANY_THROW(m1[21]);
    std::initializer_list<std::pair<int, char>> data2 = {
        {3, 'A'}, {2, 'b'}, {1, 'c'}};
    map<int, char> m2(data2);
    EXPECT_EQ(m2[21], '\0');
    m2.at(21) = 'X';
    EXPECT_EQ(m2[21], 'X');
    EXPECT_ANY_THROW(m2.at(42));
}

TEST(map, emplace_test) {
    class Dew {
     private:
        int a, b, c;

     public:
        Dew() : a(0), b(0), c(0) {}
        Dew(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}

        bool operator<(const Dew& other) const {
            if (a < other.a) return true;
            if (a == other.a && b < other.b) return true;
            return (a == other.a && b == other.b && c < other.c);
        }

        bool operator==(const Dew& other) const {
            return a == other.a && b == other.b && c == other.c;
        }
    };
    map<int, Dew> map;
    std::pair<int, Dew> pair;
    int counter = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++) {
                Dew current(i, j, k);
                pair = {counter, current};
                map.emplace(pair);
                counter++;
            }

    EXPECT_EQ(map.size(), 125);

    std::pair<typename map<int, Dew>::iterator, bool> insert_ret;
    Dew current2(1, 1, 1);
    pair = {111, current2};
    insert_ret = map.emplace(pair);
    EXPECT_FALSE(insert_ret.second);

    Dew current3(3, 2, 1);
    pair = {999, current3};
    insert_ret = map.emplace(pair);
    EXPECT_TRUE(insert_ret.second);
    EXPECT_EQ(map.size(), 126);
    EXPECT_EQ((*(map.find(999))).second, current3);
}

TEST(multiset, constructors_tests) {
    std::initializer_list<int> data = {4, 6, 5, 2, 3, 1, 21};
    multiset<int> multiset1(data), multiset2, multiset3(multiset1);
    multiset<int>::iterator it = multiset1.begin();
    EXPECT_EQ(*it, 1);
    it--;
    it--;
    EXPECT_EQ(*it, 1);
    it++;
    it++;
    it++;
    EXPECT_EQ(*it, 4);
    it = multiset1.end();
    EXPECT_EQ(*it, 0);
    it++;
    EXPECT_EQ(*it, 21);
    it++;
    EXPECT_EQ(*it, 0);

    multiset<int>::iterator it2 = multiset2.begin();
    EXPECT_EQ(*it2, 0);
    it2++;
    EXPECT_EQ(*it2, 0);
    it2--;
    it2--;
    EXPECT_EQ(*it2, 0);
    it2 = multiset2.end();
    EXPECT_EQ(*it2, 0);
    it2--;
    EXPECT_EQ(*it2, 0);
    it2++;
    it2++;
    EXPECT_EQ(*it2, 0);
    EXPECT_EQ(*(multiset1.begin()), *(multiset3.begin()));

    multiset<int> multiset4 = multiset1;
    EXPECT_EQ(multiset4.size(), multiset1.size());

    multiset<int> multiset5 = multiset2;
    EXPECT_EQ(multiset5.empty(), multiset2.empty());

    multiset<int> multiset6(std::move(multiset1));
    EXPECT_TRUE(multiset1.empty());
    EXPECT_EQ(multiset6.size(), 7);

    std::initializer_list<int> data_empty = {};
    multiset<int> multiset7(data_empty);
    EXPECT_TRUE(multiset7.empty());
    multiset7 = std::move(multiset4);
    EXPECT_TRUE(multiset4.empty());
    EXPECT_EQ(multiset7.size(), 7);
    EXPECT_EQ(MAX_SIZE, multiset7.max_size());

    multiset<int> multiset_one(data), multiset_two(data);
    EXPECT_TRUE(multiset_one == multiset_two);
    multiset_one.insert(42);
    EXPECT_FALSE(multiset_one == multiset_two);
    EXPECT_TRUE(multiset_one != multiset_two);
}

TEST(multiset, iterator_tests) {
    std::initializer_list<int> data = {4, 6, 5, 2, 3, 1, 21};
    s21::multiset<int> selfmade_multiset(data);
    int result_arr[] = {1, 2, 3, 4, 5, 6, 21};
    int i = 0;
    for (auto it = selfmade_multiset.begin(); it != selfmade_multiset.end();
         it++) {
        EXPECT_EQ(*it, result_arr[i]);
        i++;
    }
    std::pair<int, bool> p1(0, false), p2(21, true);
    multiset<std::pair<int, bool>> multiset_pair;
    EXPECT_EQ(*multiset_pair.begin(), p1);

    multiset_pair.insert(p2);
    EXPECT_EQ(*multiset_pair.begin(), p2);
    multiset<int>::iterator it1(selfmade_multiset.begin());
    it1++;
    it1++;
    EXPECT_EQ(*it1, 3);
    EXPECT_TRUE(it1 == selfmade_multiset.find(3));
    EXPECT_TRUE(it1 != selfmade_multiset.find(21));
    multiset<int> second_multiset(data);
    EXPECT_TRUE(second_multiset.find(5) != selfmade_multiset.find(5));
    multiset<int>::iterator it, it2(second_multiset.begin());
    EXPECT_FALSE(it == it2);

    multiset<int>::const_iterator const_it = selfmade_multiset.find(5);
    EXPECT_EQ(*const_it, 5);
}

TEST(multiset, clear_test) {
    std::initializer_list<int> data = {4, 6, 5, 2, 3, 1, 21};
    multiset<int> multiset1(data), multiset2, multiset3(data);
    multiset1.clear();
    EXPECT_TRUE(multiset1.empty());
    multiset2.clear();
    EXPECT_TRUE(multiset2.empty());
}

TEST(multiset, insert_test) {
    std::initializer_list<int> data = {4, 6, 5, 2, 3, 1, 21};
    multiset<int> multiset1(data);
    std::pair<multiset<int>::iterator, bool> p1 = multiset1.insert(8);
    EXPECT_TRUE(p1.second);
    EXPECT_EQ(*(p1.first), 8);
    EXPECT_EQ(multiset1.size(), 8);

    std::pair<multiset<int>::iterator, bool> p2 = multiset1.insert(6);
    EXPECT_TRUE(p2.second);
    EXPECT_EQ(*(p2.first), 6);
    EXPECT_EQ(multiset1.size(), 9);
}

TEST(multiset, erase_test) {
    std::initializer_list<int> data = {4, 6, 5, 2, 3, 1, 21};
    multiset<int> multiset1(data);
    multiset<int>::iterator it = multiset1.end();
    multiset1.erase(it);
    EXPECT_EQ(*multiset1.end(), 0);
    it--;
    EXPECT_EQ(*it, 21);
    multiset1.erase(it);
    EXPECT_EQ(*it, 0);
    it = multiset1.find(2);
    multiset1.erase(it);
    EXPECT_EQ(*it, 3);
    it--;
    EXPECT_EQ(*it, 1);
    it++;
    it++;
    EXPECT_EQ(*it, 4);
    for (auto iter = multiset1.begin(); iter != multiset1.end();)
        multiset1.erase(iter);
    EXPECT_TRUE(multiset1.empty());
}

TEST(multiset, swap_test) {
    std::initializer_list<int> data1 = {5, 4, 3, 2, 1};
    std::initializer_list<int> data2 = {10, 9, 8, 7, 6};
    multiset<int> multiset1(data1), multiset2(data2), multiset3, multiset4,
        multiset5;
    multiset1.swap(multiset2);
    EXPECT_EQ(*multiset1.begin(), 6);
    EXPECT_EQ(*multiset2.begin(), 1);
    multiset3.swap(multiset1);
    EXPECT_TRUE(multiset1.empty());
    EXPECT_EQ(multiset3.size(), 5);
    multiset4.swap(multiset5);
    EXPECT_TRUE(multiset4.empty());
    EXPECT_TRUE(multiset5.empty());
}

TEST(multiset, merge_test) {
    std::initializer_list<int> data1 = {5, 4, 3, 2, 1};
    std::initializer_list<int> data2 = {10, 9, 8, 7, 6};
    multiset<int> multiset1(data1), multiset2(data2), multiset3;
    multiset1.merge(multiset2);
    EXPECT_EQ(multiset1.size(), 10);
    EXPECT_EQ(*(--multiset1.end()), 10);
    multiset2.merge(multiset2);
    EXPECT_EQ(multiset2.size(), 5);
    multiset3.merge(multiset1);
    EXPECT_EQ(multiset3.size(), 10);

    std::initializer_list<int> data3 = {5, 4, 3, 21, 42};
    multiset<int> multiset4(data3);
    multiset1.merge(multiset4);
    EXPECT_EQ(multiset1.size(), 15);
    EXPECT_TRUE(multiset1.contains(21));
    EXPECT_FALSE(multiset4.contains(2));
}

TEST(multiset, emplace_test) {
    class Dew {
     private:
        int a, b, c;

     public:
        Dew() : a(0), b(0), c(0) {}
        Dew(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}

        bool operator<(const Dew& other) const {
            if (a < other.a) return true;
            if (a == other.a && b < other.b) return true;
            return (a == other.a && b == other.b && c < other.c);
        }

        bool operator==(const Dew& other) const {
            return a == other.a && b == other.b && c == other.c;
        }
    };
    multiset<Dew> multi;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++) multi.emplace(i, j, k);
    EXPECT_EQ(multi.size(), 125);

    std::pair<typename multiset<Dew>::iterator, bool> p;
    p = multi.emplace(1, 1, 1);
    EXPECT_TRUE(p.second);
    p = multi.emplace(5, 5, 5);
    EXPECT_TRUE(p.second);
    EXPECT_EQ(multi.size(), 127);
    Dew result(5, 5, 5);
    EXPECT_EQ(*(p.first), result);
}

TEST(set, constructors_tests) {
    std::initializer_list<int> data = {4, 6, 5, 2, 3, 1, 21};
    set<int> set1(data), set2, set3(set1);
    set<int>::iterator it = set1.begin();
    EXPECT_EQ(*it, 1);
    it--;
    it--;
    EXPECT_EQ(*it, 1);
    it++;
    it++;
    it++;
    EXPECT_EQ(*it, 4);
    it = set1.end();
    EXPECT_EQ(*it, 0);
    it++;
    EXPECT_EQ(*it, 21);
    it++;
    EXPECT_EQ(*it, 0);

    set<int>::iterator it2 = set2.begin();
    EXPECT_EQ(*it2, 0);
    it2++;
    EXPECT_EQ(*it2, 0);
    it2--;
    it2--;
    EXPECT_EQ(*it2, 0);
    it2 = set2.end();
    EXPECT_EQ(*it2, 0);
    it2--;
    EXPECT_EQ(*it2, 0);
    it2++;
    it2++;
    EXPECT_EQ(*it2, 0);
    EXPECT_EQ(*(set1.begin()), *(set3.begin()));

    set<int> set4 = set1;
    EXPECT_EQ(set4.size(), set1.size());

    set<int> set5 = set2;
    EXPECT_EQ(set5.empty(), set2.empty());

    set<int> set6(std::move(set1));
    EXPECT_TRUE(set1.empty());
    EXPECT_EQ(set6.size(), 7);

    std::initializer_list<int> data_empty = {};
    set<int> set7(data_empty);
    EXPECT_TRUE(set7.empty());
    set7 = std::move(set4);
    EXPECT_TRUE(set4.empty());
    EXPECT_EQ(set7.size(), 7);
    EXPECT_EQ(MAX_SIZE, set7.max_size());

    set<int> set_one(data), set_two(data);
    EXPECT_TRUE(set_one == set_two);
    set_one.insert(42);
    EXPECT_FALSE(set_one == set_two);
    EXPECT_TRUE(set_one != set_two);
}

TEST(set, iterator_tests) {
    std::initializer_list<int> data = {4, 6, 5, 2, 3, 1, 21};
    s21::set<int> selfmade_set(data);
    int result_arr[] = {1, 2, 3, 4, 5, 6, 21};
    int i = 0;
    for (auto it = selfmade_set.begin(); it != selfmade_set.end(); it++) {
        EXPECT_EQ(*it, result_arr[i]);
        i++;
    }
    std::pair<int, bool> p1(0, false), p2(21, true);
    set<std::pair<int, bool>> set_pair;
    EXPECT_EQ(*set_pair.begin(), p1);

    set_pair.insert(p2);
    EXPECT_EQ(*set_pair.begin(), p2);
    set<int>::iterator it1(selfmade_set.begin());
    it1++;
    it1++;
    EXPECT_EQ(*it1, 3);
    EXPECT_TRUE(it1 == selfmade_set.find(3));
    EXPECT_TRUE(it1 != selfmade_set.find(21));
    set<int> second_set(data);
    EXPECT_TRUE(second_set.find(5) != selfmade_set.find(5));
    set<int>::iterator it, it2(second_set.begin());
    EXPECT_FALSE(it == it2);

    set<int>::const_iterator const_it = selfmade_set.find(5);
    EXPECT_EQ(*const_it, 5);
    const_it = selfmade_set.begin();
    it1 = selfmade_set.cend();
    EXPECT_EQ(*it, 0);
}

TEST(set, clear_test) {
    std::initializer_list<int> data = {4, 6, 5, 2, 3, 1, 21};
    set<int> set1(data), set2, set3(data);
    set1.clear();
    EXPECT_TRUE(set1.empty());
    set2.clear();
    EXPECT_TRUE(set2.empty());
}

TEST(set, insert_test) {
    std::initializer_list<int> data = {4, 6, 5, 2, 3, 1, 21};
    set<int> set1(data);
    std::pair<set<int>::iterator, bool> p1 = set1.insert(8);
    EXPECT_TRUE(p1.second);
    EXPECT_EQ(*(p1.first), 8);
    EXPECT_EQ(set1.size(), 8);

    std::pair<set<int>::iterator, bool> p2 = set1.insert(6);
    EXPECT_FALSE(p2.second);
    EXPECT_EQ(*(p2.first), 6);
    EXPECT_EQ(set1.size(), 8);
}

TEST(set, erase_test) {
    std::initializer_list<int> data = {4, 6, 5, 2, 3, 1, 21};
    set<int> set1(data);
    set<int>::iterator it = set1.end();
    set1.erase(it);
    EXPECT_EQ(*set1.end(), 0);
    it--;
    EXPECT_EQ(*it, 21);
    set1.erase(it);
    EXPECT_EQ(*it, 0);
    it = set1.find(2);
    set1.erase(it);
    EXPECT_EQ(*it, 3);
    it--;
    EXPECT_EQ(*it, 1);
    it++;
    it++;
    EXPECT_EQ(*it, 4);
    for (auto iter = set1.begin(); iter != set1.end();) set1.erase(iter);
    EXPECT_TRUE(set1.empty());
}

TEST(set, swap_test) {
    std::initializer_list<int> data1 = {5, 4, 3, 2, 1};
    std::initializer_list<int> data2 = {10, 9, 8, 7, 6};
    set<int> set1(data1), set2(data2), set3, set4, set5;
    set1.swap(set2);
    EXPECT_EQ(*set1.begin(), 6);
    EXPECT_EQ(*set2.begin(), 1);
    set3.swap(set1);
    EXPECT_TRUE(set1.empty());
    EXPECT_EQ(set3.size(), 5);
    set4.swap(set5);
    EXPECT_TRUE(set4.empty());
    EXPECT_TRUE(set5.empty());
}

TEST(set, merge_test) {
    std::initializer_list<int> data1 = {5, 4, 3, 2, 1};
    std::initializer_list<int> data2 = {10, 9, 8, 7, 6};
    set<int> set1(data1), set2(data2), set3;
    set1.merge(set2);
    EXPECT_EQ(set1.size(), 10);
    EXPECT_EQ(*(--set1.end()), 10);
    set2.merge(set2);
    EXPECT_EQ(set2.size(), 5);
    set3.merge(set1);
    EXPECT_EQ(set3.size(), 10);

    std::initializer_list<int> data3 = {5, 4, 3, 21, 42};
    set<int> set4(data3);
    set1.merge(set4);
    EXPECT_EQ(set1.size(), 12);
    EXPECT_TRUE(set1.contains(21));
    EXPECT_FALSE(set4.contains(2));
}

TEST(set, emplace_test) {
    class Dew {
     private:
        int a, b, c;

     public:
        Dew() : a(0), b(0), c(0) {}
        Dew(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}

        bool operator<(const Dew& other) const {
            if (a < other.a) return true;
            if (a == other.a && b < other.b) return true;
            return (a == other.a && b == other.b && c < other.c);
        }

        bool operator==(const Dew& other) const {
            return a == other.a && b == other.b && c == other.c;
        }
    };
    set<Dew> set;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++) set.emplace(i, j, k);

    EXPECT_EQ(set.size(), 125);
    std::pair<typename set<Dew>::iterator, bool> p;
    p = set.emplace(1, 1, 1);
    EXPECT_FALSE(p.second);
    p = set.emplace(5, 5, 5);
    EXPECT_TRUE(p.second);
    EXPECT_EQ(set.size(), 126);
    Dew result(5, 5, 5);
    EXPECT_EQ(*(p.first), result);
}

class For_tests {
 public:
    vector<int> kek_vec;
    vector<int> empty_vec;

    array<int, 5> kek_arr;
    array<int, 5> empty_arr;
    array<int, 5> kek;

    For_tests() {
        vector<int> new_vec({1, 2, 3, 4, 5});
        kek_vec = std::move(new_vec);
        array<int, 5> new_arr({1, 2, 3, 4, 5});
        kek_arr = std::move(new_arr);
        array<int, 5> tmp_kek({1, 2, 3, 4});
        kek = std::move(tmp_kek);
    }
};

struct wow {
    int a;
    int b;
    int c;

    explicit wow(const int a = 0, const int b = 0, const int c = 0) : a(a), b(b), c(c) {}
};

TEST(Test, Element_Access_Tests) {
    For_tests lol;
    EXPECT_THROW(lol.empty_vec[0], std::out_of_range);
    EXPECT_THROW(lol.kek_vec[10] += 5, std::out_of_range);
    EXPECT_EQ(lol.kek_vec.front(), 1);
    EXPECT_EQ(lol.kek_vec.back(), 5);
    EXPECT_THROW(lol.empty_vec.back(), std::invalid_argument);
    EXPECT_THROW(lol.empty_vec.data(), std::invalid_argument);
    vector<int> fail(std::move(fail));
    lol.empty_vec = std::move(lol.kek_vec);
    EXPECT_EQ(lol.empty_vec.front(), 1);
    EXPECT_EQ(lol.empty_vec[2], 3);
    EXPECT_EQ(lol.empty_vec.capacity(), 5);
    lol.empty_vec = std::move(lol.kek_vec);
    EXPECT_THROW(lol.empty_vec.data(), std::invalid_argument);
    EXPECT_EQ(lol.empty_vec.capacity(), 0);
}

TEST(Test, Iterators_n_Capacity) {
    For_tests lol;
    EXPECT_TRUE(lol.empty_vec.empty());
    EXPECT_EQ(lol.kek_vec.size(), 5);
    EXPECT_TRUE(lol.kek_vec.max_size() == MAX_ALLOCATED / sizeof(int));
    lol.kek_vec.reserve(lol.kek_vec.size() + 1);
    EXPECT_TRUE(lol.kek_vec.capacity() > lol.kek_vec.size());
    lol.kek_vec.shrink_to_fit();
    lol.empty_vec.shrink_to_fit();
    EXPECT_TRUE(lol.kek_vec.capacity() == lol.kek_vec.size());
    bool capacity_realization = false;
    for (int i = 0; i < 20; i++) {
        lol.kek_vec.push_back(i);
        if (lol.kek_vec.capacity() > lol.kek_vec.size()) {
            capacity_realization = true;
            break;
        }
    }
    EXPECT_TRUE(capacity_realization);
}

TEST(Test, Modifiers) {
    For_tests lol;
    vector<int>::const_iterator it_const = lol.kek_vec.end();
    EXPECT_EQ(*it_const, 0);
    it_const--;
    vector<int>::iterator it = it_const;
    EXPECT_EQ(*it, 5);
    it--;
    EXPECT_EQ(*it, 4);
    lol.empty_vec.swap(lol.empty_vec);
    lol.kek_vec.insert(it, 228);
    it = lol.kek_vec.end();
    EXPECT_TRUE(lol.kek_vec[3] == 228 && lol.kek_vec.size() == 6);
    it++;
    EXPECT_THROW(lol.kek_vec.erase(it), std::out_of_range);
    EXPECT_THROW(lol.kek_vec.insert(it, 1337), std::out_of_range);
    vector<int>::iterator it1;
    EXPECT_THROW(it1 = lol.empty_vec.begin(), std::invalid_argument);
    EXPECT_THROW(lol.empty_vec.erase(it), std::invalid_argument);
    EXPECT_THROW(lol.kek_vec.insert(it1, 1337), std::invalid_argument);
    lol.empty_vec.push_back(6);
    it1 = lol.empty_vec.begin();
    EXPECT_EQ(*(++it), 0);
    lol.empty_vec.swap(lol.kek_vec);
    EXPECT_TRUE(lol.empty_vec.size() == 6 && lol.kek_vec.size() == 1);
    lol.empty_vec.swap(lol.kek_vec);
    lol.empty_vec.pop_back();
    EXPECT_EQ(lol.empty_vec.size(), 0);
    lol.empty_vec = std::move(lol.kek_vec);
    EXPECT_TRUE(lol.empty_vec.size() == 6 && lol.kek_vec.size() == 0);
    lol.empty_vec.clear();
    lol.empty_vec.clear();
    EXPECT_EQ(lol.empty_vec.size(), 0);

    For_tests lol1;

    vector<int> wtf(std::move(wtf));
    wtf.push_back(0);
    vector<int>::const_iterator iter = wtf.end();
    wtf.emplace(iter, 21);
    EXPECT_EQ(wtf[1], 21);
    wtf.emplace_back(3);
    EXPECT_EQ(wtf[2], 3);
    vector<int>::iterator last = lol1.kek_vec.end();
    last--;
    lol1.kek_vec.pop_back();
    EXPECT_EQ(*last, 0);
    last--;
    EXPECT_EQ(*last, 4);
    *last = 21;
    EXPECT_EQ(lol1.kek_vec[3], 21);

    vector<wow> wow_s;
    wow_s.emplace_back(1, 228, 64);
    EXPECT_TRUE(wow_s.size() == 1 && wow_s[0].c == 64);
    wow_s.emplace_back(2, 1337, 128);
    EXPECT_TRUE(wow_s[1].b == 1337 && wow_s.size() == 2);
}

TEST(Test, Access_Array) {
    For_tests lol;
    EXPECT_EQ(lol.kek_arr.size(), 5);
    EXPECT_EQ(lol.kek_arr.at(0), 1);
    lol.kek_arr[0] = 228;
    EXPECT_EQ(lol.kek_arr.at(0), 228);
    EXPECT_THROW(lol.kek_arr[12] = 1, std::out_of_range);

    array<int, 5> wat(std::move(wat));
    array<int, 5> uhh(std::move(lol.kek));
    uhh.iter = uhh.end();
    uhh.iter--;
    EXPECT_EQ(*(uhh.end() - 1), 0);
    EXPECT_EQ(uhh[3], 4);
    EXPECT_EQ(lol.kek[0], 0);
    array<int, 5> ohh(uhh);
    EXPECT_EQ(*(ohh.data()), 1);
    try {
        array<int, 0> wtf;
        EXPECT_TRUE(false);
    } catch (std::invalid_argument const&) {
        EXPECT_TRUE(true);
    }
}

TEST(Test, Capacity_Array) {
    For_tests lol;
    EXPECT_FALSE(lol.kek_arr.empty());
    EXPECT_EQ(lol.kek_arr.size(), 5);
    EXPECT_TRUE(lol.kek_arr.max_size() == MAX_ALLOCATED / sizeof(int));
}

TEST(Test, Modifiers_array) {
    For_tests lol;
    lol.empty_arr.swap(lol.kek_arr);
    EXPECT_EQ(lol.empty_arr.front(), *(lol.empty_arr.data()));
    EXPECT_EQ(lol.kek_arr.back(), 0);
    EXPECT_EQ(lol.empty_arr.back(), 5);
    lol.kek_arr.fill(21);
    EXPECT_EQ(lol.kek_arr[4], 21);
}
}  // namespace s21

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
