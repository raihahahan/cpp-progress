#include "collections.hpp"
#include <iostream>
#include <numeric> // std::iota

int main() {
    mystd::SimpleVector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "Original vector: " << vec << "\n";

    std::cout << "Reverse iteration: ";
    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    // Test push_back
    vec.push_back(6);
    std::cout << "After push_back(6): " << vec << "\n";

    // Test insert_back with input iterator (e.g., istream iterator or raw ptrs)
    int more[] = {7, 8, 9};
    vec.insert_back(std::begin(more), std::end(more));
    std::cout << "After insert_back(more): " << vec << "\n";

    // Test back_inserter directly
    auto bi = vec.back_inserter();
    bi = 10;
    bi = 11;
    std::cout << "After using back_inserter to add 10 and 11: " << vec << "\n";

    // Test insert_back_5 with forward iterator (vector)
    std::vector<int> extra(3);
    std::iota(extra.begin(), extra.end(), 12); // [12, 13, 14]
    vec.insert_back(extra.begin(), extra.end());
    std::cout << "After insert_back(vector): " << vec << "\n";
}
