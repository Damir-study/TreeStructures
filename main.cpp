#include <iostream>
#include <sstream>
#include <string>
#include <limits>

#include "include/BinaryTree/BinarySearchTree.hpp"
#include "include/BinaryTree/BalancedTree.hpp"
#include "include/BinaryHeap/BinaryHeap.hpp"
#include "include/Dictionary/Dictionary.hpp"
#include "include/Dictionary/BinaryTreeDictionaryStorage.hpp"
#include "include/Dictionary/BinaryHeapDictionaryStorage.hpp"
#include "include/PriorityQueue/PriorityQueue.hpp"
#include "include/PriorityQueue/BinaryTreeStorage.hpp"
#include "include/PriorityQueue/BinaryHeapStorage.hpp"
#include "include/UI/Input.hpp"
#include "include/UI/Benchmark.hpp"
#include "include/tools/TreeTraversals.hpp"

template <typename T>
std::string to_text(const T& value) {
    std::ostringstream out;
    out << value;
    return out.str();
}

template <typename T>
int reverse_compare(const T& first, const T& second) {
    return default_compare(second, first);
}

template <typename T>
int (*choose_compare())(const T&, const T&) {
    std::cout << "1) По возрастанию\n2) По убыванию\nПорядок: ";
    int choice = get_int();
    if (choice == 1) return default_compare<T>;
    if (choice == 2) return reverse_compare<T>;
    throw std::invalid_argument("Неверный порядок");
}

int choose_storage() {
    std::cout << "1) Куча\n2) Дерево поиска\n3) AVL\nХранилище: ";
    int choice = get_int();
    if (choice < 1 || choice > 3) throw std::invalid_argument("Неверное хранилище");
    return choice;
}

template <typename T>
T transform_value(const T& value) { return -value; }

template <>
int transform_value<int>(const int& value) {
    if (value == std::numeric_limits<int>::min()) throw std::overflow_error("Переполнение");
    return -value;
}

template <>
std::string transform_value<std::string>(const std::string& value) { return value + "!"; }

template <typename T>
bool is_positive(const T& value) { return value > 0; }

template <>
bool is_positive<std::string>(const std::string& value) { return !value.empty(); }

template <typename T>
std::string join_values(const T& value, const std::string& result) {
    return result + (result.empty() ? "" : " ") + to_text(value);
}

template <typename T>
T increment_value(const T& value) { return value + 1; }

template <>
int increment_value<int>(const int& value) {
    if (value == std::numeric_limits<int>::max()) throw std::overflow_error("Переполнение");
    return value + 1;
}

template <>
std::string increment_value<std::string>(const std::string& value) { return value + value; }

template <typename T>
T (*choose_map())(const T&) {
    std::cout << "1) Изменить знак\n2) Прибавить 1\nФункция: ";
    int choice = get_int();
    if (choice == 1) return transform_value<T>;
    if (choice == 2) return increment_value<T>;
    throw std::invalid_argument("Неверная функция");
}

template <>
std::string (*choose_map<std::string>())(const std::string&) {
    std::cout << "1) Добавить !\n2) Повторить строку дважды\nФункция: ";
    int choice = get_int();
    if (choice == 1) return transform_value<std::string>;
    if (choice == 2) return increment_value<std::string>;
    throw std::invalid_argument("Неверная функция");
}

template <typename T>
bool is_negative(const T& value) { return value < 0; }

template <>
bool is_negative<std::string>(const std::string& value) { return value.size() > 3; }

template <typename T>
bool (*choose_where())(const T&) {
    std::cout << "1) Больше нуля\n2) Меньше нуля\nУсловие: ";
    int choice = get_int();
    if (choice == 1) return is_positive<T>;
    if (choice == 2) return is_negative<T>;
    throw std::invalid_argument("Неверное условие");
}

template <>
bool (*choose_where<std::string>())(const std::string&) {
    std::cout << "1) Непустые строки\n2) Длина больше 3\nУсловие: ";
    int choice = get_int();
    if (choice == 1) return is_positive<std::string>;
    if (choice == 2) return is_negative<std::string>;
    throw std::invalid_argument("Неверное условие");
}

template <typename T>
T sum_values(const T& value, const T& result) { return result + value; }

template <>
int sum_values<int>(const int& value, const int& result) {
    long long sum = static_cast<long long>(result) + value;
    if (sum < std::numeric_limits<int>::min() || sum > std::numeric_limits<int>::max())
        throw std::overflow_error("Переполнение");
    return static_cast<int>(sum);
}

template <typename T>
std::size_t count_values(const T&, const std::size_t& result) { return result + 1; }

template <typename T, typename Container>
void print_reduce(const Container& current) {
    std::cout << "1) Сумма / соединение строк без разделителя\n"
              << "2) Собрать в строку через пробел\n3) Количество элементов\nФункция: ";
    int choice = get_int();
    switch (choice) {
        case 1: {
            std::cout << "Начальное значение: ";
            T initial = get_value<T>();
            std::cout << "Результат: " << current.reduce(sum_values<T>, initial) << '\n';
            break;
        }
        case 2: std::cout << "Результат: " << current.reduce(join_values<T>, std::string()) << '\n'; break;
        case 3: std::cout << "Результат: " << current.reduce(count_values<T>, std::size_t(0)) << '\n'; break;
        default: throw std::invalid_argument("Неверная функция");
    }
}

bool replace_current() {
    std::cout << "Заменить текущую структуру результатом? 1) Да 2) Нет\nВыбор: ";
    int choice = get_int();
    if (choice != 1 && choice != 2) throw std::invalid_argument("Неверный выбор");
    return choice == 1;
}

template <typename T>
T generated_value(int index) { return static_cast<T>(index); }

template <>
std::string generated_value<std::string>(int index) { return "item" + std::to_string(index); }

template <typename T>
void add_value(BinarySearchTreeBase<T>& tree, const T& value) { tree.add(value); }
template <typename T>
void add_value(BinaryHeap<T>& heap, const T& value) { heap.add(value); }
template <typename T>
void add_value(PriorityQueue<T>& queue, const T& value) { queue.push(value); }

int get_count() {
    std::cout << "Количество (0..10000): ";
    int count = get_int();
    if (count < 0 || count > 10000) throw std::invalid_argument("Неверное количество");
    return count;
}

template <typename T, typename Container>
void fill(Container& current) {
    std::cout << "1) Вручную\n2) Значения 0, 1, 2... / строки item0, item1...\nСпособ: ";
    int mode = get_int();
    if (mode != 1 && mode != 2) throw std::invalid_argument("Неверный способ");
    int count = get_count();
    for (int i = 0; i < count; ++i) {
        if (mode == 1) std::cout << "Элемент " << i << ": ";
        T value = mode == 1 ? get_value<T>() : generated_value<T>(i);
        try { add_value(current, value); }
        catch (const std::exception& error) { std::cout << error.what() << '\n'; }
    }
}

template <typename T>
void print_tree(const BinarySearchTreeBase<T>& tree) {
    tree.print_structure(std::cout, to_text<T>);
    std::cout << "Элементы: " << tree.to_string(to_text<T>) << '\n';
}

template <typename T>
void print_heap(const BinaryHeap<T>& heap) {
    heap.print_structure(std::cout, to_text<T>);
}

template <typename T>
void print_queue(const PriorityQueue<T>& queue) {
    PriorityQueue<T> copy(queue);
    std::cout << "[ ";
    while (!copy.empty()) std::cout << copy.pop() << ' ';
    std::cout << "]\n";
}

template <typename T>
BinarySearchTreeBase<T>* create_tree(int kind, typename BinarySearchTreeBase<T>::Comparator compare) {
    if (kind == 1) return new BinarySearchTree<T>(compare);
    if (kind == 2) return new BalancedTree<T>(compare);
    throw std::invalid_argument("Неверный тип дерева");
}

template <typename T>
void print_traversed_value(const T& value) { std::cout << value << ' '; }

template <typename T>
typename BinarySearchTreeBase<T>::Traversal choose_traversal() {
    std::cout << "1) КЛП 2) КПЛ 3) ПКЛ 4) ПЛК 5) ЛПК 6) ЛКП 7) В ширину\nОбход: ";
    switch (get_int()) {
        case 1: return traverse_klp<T>;
        case 2: return traverse_kpl<T>;
        case 3: return traverse_pkl<T>;
        case 4: return traverse_plk<T>;
        case 5: return traverse_lpk<T>;
        case 6: return traverse_lkp<T>;
        case 7: return breadth_first_traversal<T>;
        default: throw std::invalid_argument("Неверный обход");
    }
}

template <typename T>
void tree_menu() {
    std::cout << "1) Дерево поиска\n2) AVL\nТип дерева: ";
    int kind = get_int();
    auto compare = choose_compare<T>();
    BinarySearchTreeBase<T>* current = create_tree<T>(kind, compare);
    while (std::cin) {
        BinarySearchTreeBase<T>* result = nullptr;
        try {
            std::cout << "\n--- Дерево ---\n";
            print_tree(*current);
            std::cout << "1) Добавить\n2) Удалить\n3) Найти\n4) Размер\n5) Очистить\n"
                      << "6) Map\n7) Where\n"
                      << "8) Reduce\n9) Обход\n10) Поддерево\n"
                      << "11) Вхождение поддерева\n12) Заполнить\n0) Назад\nДействие: ";
            int action = get_int();
            if (action == 0) break;
            switch (action) {
                case 1: std::cout << "Значение: "; current->add(get_value<T>()); break;
                case 2: std::cout << "Значение: "; current->remove(get_value<T>()); break;
                case 3: {
                    std::cout << "Значение: ";
                    T value = get_value<T>();
                    std::cout << (current->contains(value) ? "Найдено\n" : "Не найдено\n");
                    break;
                }
                case 4: std::cout << "Размер: " << current->get_size() << '\n'; break;
                case 5: current->clear(); break;
                case 6: result = current->map(choose_map<T>()); break;
                case 7: result = current->where(choose_where<T>()); break;
                case 8: print_reduce<T>(*current); break;
                case 9: {
                    current->traverse(print_traversed_value<T>, choose_traversal<T>());
                    std::cout << '\n';
                    break;
                }
                case 10: std::cout << "Корень: "; result = current->get_subtree(get_value<T>()); break;
                case 11:
                    result = current->create_empty();
                    fill<T>(*result);
                    std::cout << (current->contains_subtree(*result) ? "Входит\n" : "Не входит\n");
                    break;
                case 12: fill<T>(*current); break;
                default: std::cout << "Неверное действие\n"; break;
            }
            if (result) {
                std::cout << "Результат / образец:\n";
                print_tree(*result);
                if ((action == 6 || action == 7) && replace_current()) {
                    delete current;
                    current = result;
                    result = nullptr;
                }
            }
        } catch (const std::exception& error) { std::cout << "Ошибка: " << error.what() << '\n'; }
        delete result;
    }
    delete current;
}

template <typename T>
void heap_menu() {
    auto compare = choose_compare<T>();
    BinaryHeap<T> current(compare);
    while (std::cin) {
        BinaryHeap<T>* result = nullptr;
        try {
            std::cout << "\n--- Куча ---\n";
            print_heap(current);
            std::cout << "1) Добавить\n2) Удалить\n3) Найти\n4) Размер\n5) Очистить\n"
                      << "6) Map\n7) Where\n"
                      << "8) Вершина\n9) Извлечь вершину\n10) Поддерево\n"
                      << "11) Вхождение поддерева\n12) Заполнить\n0) Назад\nДействие: ";
            int action = get_int();
            if (action == 0) break;
            switch (action) {
                case 1: std::cout << "Значение: "; current.add(get_value<T>()); break;
                case 2: std::cout << "Значение: "; current.remove(get_value<T>()); break;
                case 3: {
                    std::cout << "Значение: ";
                    T value = get_value<T>();
                    std::cout << (current.contains(value) ? "Найдено\n" : "Не найдено\n");
                    break;
                }
                case 4: std::cout << "Размер: " << current.get_size() << '\n'; break;
                case 5: current.clear(); break;
                case 6: {
                    BinaryHeap<T> mapped = current.map(choose_map<T>());
                    print_heap(mapped);
                    if (replace_current()) current = mapped;
                    break;
                }
                case 7: {
                    BinaryHeap<T> filtered = current.where(choose_where<T>());
                    print_heap(filtered);
                    if (replace_current()) current = filtered;
                    break;
                }
                case 8: std::cout << "Вершина: " << current.top() << '\n'; break;
                case 9: std::cout << "Извлечено: " << current.extract_top() << '\n'; break;
                case 10: std::cout << "Корень: "; result = current.get_subtree(get_value<T>()); break;
                case 11: {
                    BinaryHeap<T> pattern(compare);
                    fill<T>(pattern);
                    std::cout << (current.contains_subtree(pattern) ? "Входит\n" : "Не входит\n");
                    break;
                }
                case 12: fill<T>(current); break;
                default: std::cout << "Неверное действие\n"; break;
            }
            if (result) { std::cout << "Поддерево:\n"; print_heap(*result); }
        } catch (const std::exception& error) { std::cout << "Ошибка: " << error.what() << '\n'; }
        delete result;
    }
}

template <typename Key, typename Value>
void print_pair(const Key& key, const Value& value) { std::cout << key << ": " << value << '\n'; }

template <typename Key, typename Value>
void dictionary_menu() {
    int kind = choose_storage();
    auto compare = choose_compare<Key>();
    IDictionaryStorage<Key, Value>* storage;
    if (kind == 1) storage = new BinaryHeapDictionaryStorage<Key, Value>(compare);
    else if (kind == 2) storage = new BinaryTreeDictionaryStorage<Key, Value>(
        new BinarySearchTree<DictionaryPair<Key, Value>>, compare);
    else storage = new BinaryTreeDictionaryStorage<Key, Value>(
        new BalancedTree<DictionaryPair<Key, Value>>, compare);
    Dictionary<Key, Value> current(storage);
    while (std::cin) {
        try {
            std::cout << "\n--- Словарь ---\n";
            current.traverse(print_pair<Key, Value>);
            std::cout << "1) Добавить\n2) Удалить\n3) Получить\n4) Размер\n5) Очистить\n"
                      << "6) Изменить значение\n7) Заполнить\n0) Назад\nДействие: ";
            int action = get_int();
            if (action == 0) break;
            switch (action) {
                case 1: case 6: {
                    std::cout << "Ключ: "; Key key = get_value<Key>();
                    std::cout << "Значение: "; Value value = get_value<Value>();
                    if (action == 1) current.add(key, value);
                    else current.get(key) = value;
                    break;
                }
                case 2: std::cout << "Ключ: "; current.remove(get_value<Key>()); break;
                case 3: {
                    std::cout << "Ключ: "; Key key = get_value<Key>();
                    std::cout << "Значение: " << current.get(key) << '\n';
                    break;
                }
                case 4: std::cout << "Размер: " << current.get_size() << '\n'; break;
                case 5: current.clear(); break;
                case 7: {
                    int count = get_count();
                    for (int i = 0; i < count; ++i) {
                        std::cout << "Ключ: "; Key key = get_value<Key>();
                        std::cout << "Значение: "; Value value = get_value<Value>();
                        try { current.add(key, value); }
                        catch (const std::exception& error) { std::cout << error.what() << '\n'; }
                    }
                    break;
                }
                default: std::cout << "Неверное действие\n"; break;
            }
        } catch (const std::exception& error) { std::cout << "Ошибка: " << error.what() << '\n'; }
    }
}

template <typename T>
void queue_menu() {
    int kind = choose_storage();
    auto compare = choose_compare<T>();
    IPriorityQueueStorage<T>* storage;
    if (kind == 1) storage = new BinaryHeapStorage<T>(compare);
    else storage = new BinaryTreeStorage<T>(create_tree<T>(kind - 1, compare));
    PriorityQueue<T> current(storage);
    while (std::cin) {
        try {
            std::cout << "\n--- Очередь с приоритетом ---\n";
            print_queue(current);
            std::cout << "1) Добавить\n2) Извлечь\n3) Вершина\n4) Найти\n5) Размер\n"
                      << "6) Очистить\n7) Map\n8) Where\n"
                      << "9) Reduce\n10) Заполнить\n0) Назад\nДействие: ";
            int action = get_int();
            if (action == 0) break;
            switch (action) {
                case 1: std::cout << "Значение: "; current.push(get_value<T>()); break;
                case 2: std::cout << "Извлечено: " << current.pop() << '\n'; break;
                case 3: std::cout << "Вершина: " << current.top() << '\n'; break;
                case 4: {
                    std::cout << "Значение: "; T value = get_value<T>();
                    std::cout << (current.contains(value) ? "Найдено\n" : "Не найдено\n");
                    break;
                }
                case 5: std::cout << "Размер: " << current.get_size() << '\n'; break;
                case 6: current.clear(); break;
                case 7: {
                    PriorityQueue<T> mapped = current.map(choose_map<T>());
                    print_queue(mapped);
                    if (replace_current()) current = mapped;
                    break;
                }
                case 8: {
                    PriorityQueue<T> filtered = current.where(choose_where<T>());
                    print_queue(filtered);
                    if (replace_current()) current = filtered;
                    break;
                }
                case 9: print_reduce<T>(current); break;
                case 10: fill<T>(current); break;
                default: std::cout << "Неверное действие\n"; break;
            }
        } catch (const std::exception& error) { std::cout << "Ошибка: " << error.what() << '\n'; }
    }
}

template <typename Key>
void choose_dictionary_value() {
    std::cout << "Значения: 1) int 2) double 3) string\nТип: ";
    switch (get_int()) {
        case 1: dictionary_menu<Key, int>(); break;
        case 2: dictionary_menu<Key, double>(); break;
        case 3: dictionary_menu<Key, std::string>(); break;
        default: std::cout << "Неверный тип\n"; break;
    }
}

template <typename T>
void run_structure(int kind) {
    if (kind == 1) tree_menu<T>();
    else if (kind == 2) heap_menu<T>();
    else queue_menu<T>();
}

int main() {
    while (std::cin) {
        try {
            std::cout << "\n1) Дерево\n2) Куча\n3) Словарь\n4) Очередь с приоритетом\n"
                      << "5) Подсчёт метрик\n0) Выход\nРаздел: ";
            int kind = get_int();
            if (kind == 0) break;
            if (kind == 5) { run_benchmarks(); continue; }
            if (kind < 1 || kind > 4) { std::cout << "Неверный раздел\n"; continue; }
            std::cout << (kind == 3 ? "Тип ключа" : "Тип элемента") << ": 1) int 2) double 3) string\nТип: ";
            int type = get_int();
            if (kind == 3) {
                if (type == 1) choose_dictionary_value<int>();
                else if (type == 2) choose_dictionary_value<double>();
                else if (type == 3) choose_dictionary_value<std::string>();
                else std::cout << "Неверный тип\n";
            }
            else {
                if (type == 1) run_structure<int>(kind);
                else if (type == 2) run_structure<double>(kind);
                else if (type == 3) run_structure<std::string>(kind);
                else std::cout << "Неверный тип\n";
            }
        } catch (const std::exception& error) { std::cout << "Ошибка: " << error.what() << '\n'; }
    }
    return 0;
}
