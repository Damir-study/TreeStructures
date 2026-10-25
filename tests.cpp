#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <utility>

#include "include/BinaryTree/BinarySearchTree.hpp"
#include "include/BinaryTree/BalancedTree.hpp"
#include "include/BinaryHeap/BinaryHeap.hpp"
#include "include/Dictionary/Dictionary.hpp"
#include "include/Dictionary/BinaryTreeDictionaryStorage.hpp"
#include "include/Dictionary/BinaryHeapDictionaryStorage.hpp"
#include "include/PriorityQueue/PriorityQueue.hpp"
#include "include/PriorityQueue/BinaryTreeStorage.hpp"
#include "include/PriorityQueue/BinaryHeapStorage.hpp"

int reverse_compare(const int& first, const int& second) {
    if (first > second) return -1;
    if (second > first) return 1;
    return 0;
}

int negate_value(const int& value) { return -value; }
bool is_even(const int& value) { return value % 2 == 0; }
int sum_values(const int& value, const int& result) { return value + result; }
std::string value_to_string(const int& value) { return std::to_string(value); }

class TestBalancedTree : public BalancedTree<int> {
public:
    int root_value() const {
        return this->BinarySearchTreeBase<int>::root->data;
    }
};

TEST(binary_search_tree_test, add_and_get) {
    BinarySearchTree<int> tree;
    EXPECT_TRUE(tree.is_empty());
    for (int value : {5, 2, 8}) tree.add(value);

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
    tree.remove(2);
    tree.remove(6);
    tree.remove(8);
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

TEST(binary_search_tree_test, map_where_and_reduce) {
    BinarySearchTree<int> tree;
    for (int value : {3, 1, 4, 2}) tree.add(value);
    auto* mapped = tree.map(negate_value);
    auto* filtered = tree.where(is_even);

    EXPECT_EQ(mapped->to_string(value_to_string), "-4 -3 -2 -1");
    EXPECT_EQ(filtered->to_string(value_to_string), "2 4");
    EXPECT_EQ(tree.reduce(sum_values, 10), 20);
    EXPECT_EQ(tree.get_size(), 4);
    EXPECT_THROW(tree.where(nullptr), std::invalid_argument);

    delete mapped;
    delete filtered;
}

TEST(binary_search_tree_test, subtree) {
    BinarySearchTree<int> tree;
    for (int value : {8, 4, 12, 2, 6}) tree.add(value);
    auto* subtree = tree.get_subtree(4);

    EXPECT_EQ(subtree->get_size(), 3);
    EXPECT_EQ(subtree->to_string(value_to_string), "2 4 6");
    EXPECT_TRUE(tree.contains_subtree(*subtree));

    subtree->remove(2);
    EXPECT_FALSE(tree.contains_subtree(*subtree));
    EXPECT_TRUE(tree.contains(2));
    EXPECT_THROW(tree.get_subtree(100), std::runtime_error);
    delete subtree;
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

TEST(binary_heap_test, add_get_and_extract) {
    BinaryHeap<int> heap;
    EXPECT_TRUE(heap.is_empty());
    EXPECT_THROW(heap.top(), std::runtime_error);
    EXPECT_THROW(heap.extract_top(), std::runtime_error);

    for (int value : {5, 2, 8, 1, 2}) heap.add(value);
    EXPECT_EQ(heap.get_size(), 5);
    EXPECT_EQ(heap.get(8), 8);
    EXPECT_THROW(heap.get(100), std::runtime_error);
    for (int value : {1, 2, 2, 5, 8}) EXPECT_EQ(heap.extract_top(), value);
    EXPECT_TRUE(heap.is_empty());
}

TEST(binary_heap_test, remove) {
    int first[] = {1, 4, 2, 7, 8, 3};
    BinaryHeap<int> up(first, 6);
    up.remove(7);
    EXPECT_FALSE(up.contains(7));
    for (int value : {1, 2, 3, 4, 8}) EXPECT_EQ(up.extract_top(), value);

    int second[] = {1, 2, 3, 4, 5, 6, 7};
    BinaryHeap<int> down(second, 7);
    down.remove(2);
    down.remove(100);
    for (int value : {1, 3, 4, 5, 6, 7}) EXPECT_EQ(down.extract_top(), value);
}

TEST(binary_heap_test, copy_move_and_clear) {
    BinaryHeap<int> heap;
    for (int value : {3, 1, 2}) heap.add(value);
    BinaryHeap<int> copy(heap);
    copy.add(0);
    EXPECT_EQ(heap.top(), 1);

    BinaryHeap<int> moved(std::move(copy));
    EXPECT_TRUE(copy.is_empty());
    EXPECT_EQ(moved.top(), 0);
    heap.clear();
    EXPECT_TRUE(heap.is_empty());
    EXPECT_EQ(moved.get_size(), 4);
}

TEST(binary_heap_test, map_where_and_subtree) {
    int values[] = {1, 2, 3, 4, 5, 6, 7};
    BinaryHeap<int> heap(values, 7);
    BinaryHeap<int> mapped = heap.map(negate_value);
    BinaryHeap<int> filtered = heap.where(is_even);
    auto* subtree = heap.get_subtree(2);

    EXPECT_EQ(mapped.top(), -7);
    EXPECT_EQ(filtered.get_size(), 3);
    for (int value : {2, 4, 6}) EXPECT_EQ(filtered.extract_top(), value);
    EXPECT_EQ(subtree->get_size(), 3);
    EXPECT_TRUE(heap.contains_subtree(*subtree));
    EXPECT_EQ(heap.get_size(), 7);
    delete subtree;
}

TEST(binary_heap_test, custom_comparator) {
    int values[] = {2, 5, 1, 4, 3};
    BinaryHeap<int> heap(values, 5, reverse_compare);
    for (int value : {5, 4, 3, 2, 1}) EXPECT_EQ(heap.extract_top(), value);
    EXPECT_TRUE(heap.is_empty());
}

TEST(dictionary_test, binary_tree_storage) {
    Dictionary<int, std::string> dictionary(new BinaryTreeDictionaryStorage<int, std::string>(
        new BinarySearchTree<DictionaryPair<int, std::string>>));
    dictionary.add(2, "two");
    dictionary.add(1, "one");

    EXPECT_EQ(dictionary.get(2), "two");
    EXPECT_EQ(dictionary.get_size(), 2);
    EXPECT_THROW(dictionary.add(2, "again"), std::runtime_error);
    dictionary.get(2) = "changed";
    EXPECT_EQ(dictionary.get(2), "changed");

    dictionary.remove(2);
    EXPECT_FALSE(dictionary.contains_key(2));
    EXPECT_THROW(dictionary.get(2), std::runtime_error);
}

TEST(dictionary_test, balanced_tree_storage) {
    Dictionary<std::string, int> dictionary(new BinaryTreeDictionaryStorage<std::string, int>(
        new BalancedTree<DictionaryPair<std::string, int>>));
    dictionary.add("one", 1);
    dictionary.add("two", 2);

    EXPECT_EQ(dictionary.get("two"), 2);
    EXPECT_TRUE(dictionary.contains_key("one"));
    dictionary.remove("one");
    EXPECT_EQ(dictionary.get_size(), 1);
    dictionary.clear();
    EXPECT_TRUE(dictionary.is_empty());
}

TEST(dictionary_test, heap_storage) {
    Dictionary<int, double> dictionary(new BinaryHeapDictionaryStorage<int, double>);
    dictionary.add(1, 1.5);
    dictionary.add(2, 2.5);
    Dictionary<int, double> copy(dictionary);
    copy.get(1) = 10.5;

    EXPECT_EQ(dictionary.get(1), 1.5);
    EXPECT_EQ(copy.get(1), 10.5);
    EXPECT_THROW(dictionary.add(1, 3.5), std::runtime_error);
    dictionary.remove(2);
    EXPECT_FALSE(dictionary.contains_key(2));
    EXPECT_TRUE(copy.contains_key(2));
}

TEST(dictionary_test, copy_and_move_assignment) {
    Dictionary<int, int> dictionary(new BinaryHeapDictionaryStorage<int, int>);
    dictionary.add(1, 10);
    Dictionary<int, int> copy(new BinaryTreeDictionaryStorage<int, int>(
        new BalancedTree<DictionaryPair<int, int>>));
    copy = dictionary;
    dictionary.clear();
    EXPECT_EQ(copy.get(1), 10);

    Dictionary<int, int> moved(std::move(copy));
    EXPECT_TRUE(copy.is_empty());
    EXPECT_EQ(moved.get(1), 10);
}

TEST(priority_queue_test, heap_storage) {
    PriorityQueue<int> queue(new BinaryHeapStorage<int>);
    EXPECT_TRUE(queue.empty());
    EXPECT_THROW(queue.pop(), std::runtime_error);
    for (int value : {5, 2, 1, 2}) queue.push(value);

    EXPECT_EQ(queue.get_size(), 4);
    EXPECT_TRUE(queue.contains(5));
    for (int value : {1, 2, 2, 5}) EXPECT_EQ(queue.pop(), value);
    EXPECT_TRUE(queue.empty());
}

TEST(priority_queue_test, binary_tree_storage) {
    PriorityQueue<int> queue(new BinaryTreeStorage<int>(new BinarySearchTree<int>));
    for (int value : {3, 1, 2}) queue.push(value);
    auto mapped = queue.map(negate_value);
    auto filtered = queue.where(is_even);

    EXPECT_EQ(mapped.pop(), -3);
    EXPECT_EQ(filtered.pop(), 2);
    EXPECT_EQ(queue.reduce(sum_values, 10), 16);
    EXPECT_EQ(queue.get_size(), 3);
    EXPECT_THROW(queue.push(2), std::runtime_error);
}

TEST(priority_queue_test, balanced_tree_storage) {
    PriorityQueue<int> queue(new BinaryTreeStorage<int>(new BalancedTree<int>(reverse_compare)));
    for (int value : {2, 5, 1, 4, 3}) queue.push(value);

    EXPECT_EQ(queue.top(), 5);
    for (int value : {5, 4, 3, 2, 1}) EXPECT_EQ(queue.pop(), value);
    EXPECT_TRUE(queue.empty());
}

TEST(priority_queue_test, copy_move_and_clear) {
    PriorityQueue<int> queue(new BinaryHeapStorage<int>);
    queue.push(2);
    queue.push(3);
    PriorityQueue<int> copy(queue);
    copy.push(1);
    EXPECT_EQ(queue.top(), 2);

    PriorityQueue<int> moved(std::move(copy));
    EXPECT_TRUE(copy.empty());
    EXPECT_EQ(moved.pop(), 1);
    queue.clear();
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(moved.get_size(), 2);
}
