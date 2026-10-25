#include "../../include/UI/Benchmark.hpp"
#include "../../include/BinaryTree/BinarySearchTree.hpp"
#include "../../include/BinaryTree/BalancedTree.hpp"
#include "../../include/BinaryHeap/BinaryHeap.hpp"
#include "../../include/Dictionary/Dictionary.hpp"
#include "../../include/Dictionary/BinaryTreeDictionaryStorage.hpp"
#include "../../include/Dictionary/BinaryHeapDictionaryStorage.hpp"
#include "../../include/PriorityQueue/PriorityQueue.hpp"
#include "../../include/PriorityQueue/BinaryTreeStorage.hpp"
#include "../../include/PriorityQueue/BinaryHeapStorage.hpp"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <limits>
#include <random>
#include "../../external/mutable_array_sequence.h"
#include <filesystem>

using Clock = std::chrono::steady_clock;

double elapsed_ms(Clock::time_point start) {
    return std::chrono::duration<double, std::milli>(Clock::now() - start).count();
}

template <typename C> void add(C& c, int x) { c.add(x); }
void add(PriorityQueue<int>& c, int x) { c.push(x); }
void add(Dictionary<int, int>& c, int x) { c.add(x, x); }
template <typename C> bool find(const C& c, int x) { return c.contains(x); }
bool find(const Dictionary<int, int>& c, int x) { return c.contains_key(x); }
template <typename C> void remove(C& c, int x) { c.remove(x); }
void remove(PriorityQueue<int>& c, int) { c.pop(); }

template <typename C>
void measure(C& current, const mutable_array_sequence<int>& data, std::ofstream& file) {
    const int operations = 100;

    auto start = Clock::now();
    for (int i = 0; i < data.get_length(); ++i) add(current, data[i]);
    double add_time = elapsed_ms(start);

    start = Clock::now();
    for (int i = 0; i < operations; ++i) {
        int value = data[i * data.get_length() / operations];
        if (!find(current, value)) throw std::runtime_error("Элемент не найден");
    }
    double find_time = elapsed_ms(start);

    start = Clock::now();
    for (int i = 0; i < operations; ++i) {
        remove(current, data[i * data.get_length() / operations]);
    }
    double remove_time = elapsed_ms(start);

    std::cout << data.get_length() << " | " << add_time << " | " << find_time
              << " | " << remove_time << std::endl;
    file << data.get_length() << ',' << add_time << ',' << find_time << ',' << remove_time << '\n';
    if (!file) throw std::runtime_error("Не удалось записать результаты");
}

void run_measurement(int kind, const mutable_array_sequence<int>& data, std::ofstream& file) {
    switch (kind) {
        case 1: { BinarySearchTree<int> c; measure(c, data, file); break; }
        case 2: { BalancedTree<int> c; measure(c, data, file); break; }
        case 3: { BinaryHeap<int> c; measure(c, data, file); break; }
        case 4: {
            Dictionary<int, int> c(new BinaryHeapDictionaryStorage<int, int>);
            measure(c, data, file); break;
        }
        case 5: {
            Dictionary<int, int> c(new BinaryTreeDictionaryStorage<int, int>(
                new BinarySearchTree<DictionaryPair<int, int>>));
            measure(c, data, file); break;
        }
        case 6: {
            Dictionary<int, int> c(new BinaryTreeDictionaryStorage<int, int>(
                new BalancedTree<DictionaryPair<int, int>>));
            measure(c, data, file); break;
        }
        case 7: { PriorityQueue<int> c(new BinaryHeapStorage<int>); measure(c, data, file); break; }
        case 8: {
            PriorityQueue<int> c(new BinaryTreeStorage<int>(new BinarySearchTree<int>));
            measure(c, data, file); break;
        }
        default: {
            PriorityQueue<int> c(new BinaryTreeStorage<int>(new BalancedTree<int>));
            measure(c, data, file); break;
        }
    }
}

void run_benchmarks() {
    const char* names[] = {"BST", "AVL", "Heap", "DictionaryHeap", "DictionaryBST",
                          "DictionaryAVL", "QueueHeap", "QueueBST", "QueueAVL"};
    std::cout << "1) BST\n2) AVL\n3) Куча\n4) Словарь / куча\n5) Словарь / BST\n"
              << "6) Словарь / AVL\n7) Очередь / куча\n8) Очередь / BST\n9) Очередь / AVL\nСтруктура: ";
    int kind;
    if (!(std::cin >> kind)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Нужно ввести номер структуры");
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (kind < 1 || kind > 9) throw std::invalid_argument("Неверная структура");

    std::filesystem::create_directories("benchmark_results");
    std::string path = std::string("benchmark_results/") + names[kind - 1] + ".csv";
    std::ofstream file(path);
    if (!file) throw std::runtime_error("Не удалось открыть файл результатов");
    file << "count,add_ms,find_ms,remove_ms\n";

    std::cout << "Добавление всех элементов, затем 100 поисков и 100 удалений.\n"
              << "Для очереди удаление — pop(). Значения элементов — int.\n"
              << "N | Добавление, мс | Поиск, мс | Удаление, мс\n";
    const int sizes[] = {10000, 100000, 1000000};
    for (int count : sizes) {
        mutable_array_sequence<int> data;
        for (int i = 0; i < count; ++i) data.append(i);
        std::mt19937 random(42);
        for (int i = count - 1; i > 0; --i) {
            std::uniform_int_distribution<int> index(0, i);
            std::swap(data[i], data[index(random)]);
        }
        run_measurement(kind, data, file);
    }
    std::cout << "Результаты сохранены в " << path << '\n';
}
