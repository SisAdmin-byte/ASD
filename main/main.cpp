// Copyright 2024 Marina Usova

#include <iostream>
#include <string>
#include <sstream>
#include "HashTable.h"
#include "HeapSort.h"
#include "ITable.h"


int main() {
    TVector<std::pair<std::string, int>> dict1 = {
        {"hash", 10072},
        {"list", 13736},
        {"vector", 16262},
        {"massive", 10626},
        {"table", 10083}
    };


    TVector<std::pair<std::string, int>> dict2 = {
        {"table", 22727},
        {"vector", 20728},
        {"queue", 28282},
        {"stack", 20607},
        {"list", 20618}
    };

    HashTable<int> merged = merge_dict(dict1, dict2);

    std::cout << "Combined Dictionary:\n";
    merged.print(std::cout);

    std::cout << "\nSize: " << merged.size() << std::endl;

    std::cout << "=========== HeapSort ===========" << std::endl;
    TVector<int> arr = { 12, 11, 13, 5, 6, 7, 3, 20, 15 };
    std::cout << "Before sort: ";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    heapSort(arr);

    std::cout << "After sort: ";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}