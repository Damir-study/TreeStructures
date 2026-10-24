#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP

template <typename T>
int default_compare(const T& first, const T& second) {
    if (first > second) return 1;
    if (first < second) return -1;
    return 0;
}


#endif // COMPARATOR_HPP