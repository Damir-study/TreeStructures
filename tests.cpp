#include <gtest/gtest.h>
#include <stdexcept>
#include <utility>

#include "include/BinaryTree/BinarySearchTree.hpp"
#include "include/BinaryTree/BalancedTree.hpp"
#include "include/BinaryTreeDictionary/BinaryTreeDictionary.hpp"
#include "include/BinaryTreeDictionary/BalancedTreeDictionary.hpp"

int reverse_compare(const int& first, const int& second) {
    if (first > second) return -1;
    if (second > first) return 1;
    return 0;
}

class TestBalancedTree : public BalancedTree<int> {
public:
    int root_value() const {
        return this->BinarySearchTreeBase<int>::root->data;
    }
};

TEST(binary_search_tree_test, add_and_get) {
    BinarySearchTree<int> tree;

    EXPECT_TRUE(tree.is_empty());
    tree.add(5);
    tree.add(2);
    tree.add(8);

    EXPECT_EQ(tree.get_size(), 3);
    EXPECT_EQ(tree.get(2), 2);
    EXPECT_TRUE(tree.contains(8));
    EXPECT_FALSE(tree.contains(4));
    EXPECT_THROW(tree.add(5), std::runtime_error);
    EXPECT_THROW(tree.get(4), std::runtime_error);
}

TEST(binary_search_tree_test, remove) {
    BinarySearchTree<int> tree;
    for (int value : {8, 4, 12, 2, 6, 10, 14, 5}) tree.add(value);

    tree.remove(2);  // Лист
    tree.remove(6);  // Один ребёнок
    tree.remove(8);  // Два ребёнка
    tree.remove(100);

    EXPECT_EQ(tree.get_size(), 5);
    EXPECT_FALSE(tree.contains(2));
    EXPECT_FALSE(tree.contains(6));
    EXPECT_FALSE(tree.contains(8));
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(10));
}

TEST(binary_search_tree_test, copy_move_and_clear) {
    BinarySearchTree<int> tree;
    tree.add(3);
    tree.add(1);

    BinarySearchTree<int> copy(tree);
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
    EXPECT_TRUE(copy.contains(1));

    BinarySearchTree<int> moved(std::move(copy));
    EXPECT_TRUE(copy.is_empty());
    EXPECT_EQ(moved.get_size(), 2);
}

TEST(balanced_tree_test, rotations) {
    TestBalancedTree ll;
    for (int value : {3, 2, 1}) ll.add(value);
    EXPECT_EQ(ll.root_value(), 2);

    TestBalancedTree rr;
    for (int value : {1, 2, 3}) rr.add(value);
    EXPECT_EQ(rr.root_value(), 2);

    TestBalancedTree lr;
    for (int value : {3, 1, 2}) lr.add(value);
    EXPECT_EQ(lr.root_value(), 2);

    TestBalancedTree rl;
    for (int value : {1, 3, 2}) rl.add(value);
    EXPECT_EQ(rl.root_value(), 2);
}

TEST(balanced_tree_test, remove) {
    BalancedTree<int> tree;
    for (int value : {8, 4, 12, 2, 6, 10, 14, 9, 11}) tree.add(value);

    tree.remove(8);
    tree.remove(2);
    tree.remove(100);

    EXPECT_EQ(tree.get_size(), 7);
    EXPECT_FALSE(tree.contains(8));
    EXPECT_FALSE(tree.contains(2));
    EXPECT_TRUE(tree.contains(9));
    EXPECT_TRUE(tree.contains(14));
}

TEST(binary_tree_dictionary_test, add_get_and_remove) {
    BinaryTreeDictionary<int, int> dictionary;
    dictionary.add(2, 20);
    dictionary.add(1, 10);

    EXPECT_EQ(dictionary.get(2), 20);
    EXPECT_EQ(dictionary.get_size(), 2);
    EXPECT_THROW(dictionary.add(2, 30), std::runtime_error);

    dictionary.remove(2);
    EXPECT_FALSE(dictionary.contains_key(2));
    EXPECT_TRUE(dictionary.contains_key(1));
}

TEST(balanced_tree_dictionary_test, custom_comparator) {
    BalancedTreeDictionary<int, int> dictionary(reverse_compare);
    dictionary.add(1, 10);
    dictionary.add(2, 20);
    dictionary.add(3, 30);

    EXPECT_EQ(dictionary.get(2), 20);
    EXPECT_EQ(dictionary.get_size(), 3);

    dictionary.remove(2);
    EXPECT_FALSE(dictionary.contains_key(2));
    dictionary.clear();
    EXPECT_TRUE(dictionary.is_empty());
}
