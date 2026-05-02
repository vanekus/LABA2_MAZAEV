#include <iostream>
#include <string>
#include "tests.h"
#include "ArraySequence.h"
#include "ListSequence.h"

void printMenu() {
    std::cout << "\n=== Sequence Tester ===\n";
    std::cout << "1. Create MutableArraySequence\n";
    std::cout << "2. Create ImmutableArraySequence\n";
    std::cout << "3. Create MutableListSequence\n";
    std::cout << "4. Create ImmutableListSequence\n";
    std::cout << "5. Get first\n";
    std::cout << "6. Get last\n";
    std::cout << "7. Get by index\n";
    std::cout << "8. Get length\n";
    std::cout << "9. Get subsequence\n";
    std::cout << "10. Append\n";
    std::cout << "11. Prepend\n";
    std::cout << "12. InsertAt\n";
    std::cout << "13. Concat\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose: ";
}

void printSequence(Sequence<int>* seq, const std::string& name) {
    std::cout << name << " [";
    for (int i = 0; i < seq->GetLength(); ++i) {
        std::cout << seq->Get(i);
        if (i < seq->GetLength() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

void interact() {
    Sequence<int>* current = nullptr;
    int choice;
    bool running = true;
    while (running) {
        printMenu();
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error: please enter a number.\n";
            continue;
        }
        try {
            if (choice == 0) {
                running = false;
                break;
            }
            if (choice >= 1 && choice <= 4) {
                delete current;
                int n;
                std::cout << "Enter number of elements: ";
                std::cin >> n;
                if (n < 0) {
                    std::cout << "Count cannot be negative.\n";
                    continue;
                }
                int* arr = new int[n];
                std::cout << "Enter elements: ";
                for (int i = 0; i < n; ++i) std::cin >> arr[i];
                switch (choice) {
                    case 1: current = new MutableArraySequence<int>(arr, n); break;
                    case 2: current = new ImmutableArraySequence<int>(arr, n); break;
                    case 3: current = new MutableListSequence<int>(arr, n); break;
                    case 4: current = new ImmutableListSequence<int>(arr, n); break;
                }
                delete[] arr;
                printSequence(current, "Created:");
            } else {
                if (!current) {
                    std::cout << "No sequence created yet. Please create one first (1-4).\n";
                    continue;
                }
                switch (choice) {
                    case 5:
                        std::cout << "First: " << current->GetFirst() << "\n";
                        break;
                    case 6:
                        std::cout << "Last: " << current->GetLast() << "\n";
                        break;
                    case 7: {
                        int idx;
                        std::cout << "Index: ";
                        std::cin >> idx;
                        std::cout << "Value: " << current->Get(idx) << "\n";
                        break;
                    }
                    case 8:
                        std::cout << "Length: " << current->GetLength() << "\n";
                        break;
                    case 9: {
                        int s, e;
                        std::cout << "Start, end: ";
                        std::cin >> s >> e;
                        Sequence<int>* sub = current->GetSubsequence(s, e);
                        printSequence(sub, "Subsequence:");
                        delete sub;
                        break;
                    }
                    case 10: {
                        int val;
                        std::cout << "Value: ";
                        std::cin >> val;
                        Sequence<int>* newSeq = current->Append(val);
                        if (newSeq != current) {
                            delete current;
                            current = newSeq;
                        }
                        printSequence(current, "After append:");
                        break;
                    }
                    case 11: {
                        int val;
                        std::cout << "Value: ";
                        std::cin >> val;
                        Sequence<int>* newSeq = current->Prepend(val);
                        if (newSeq != current) {
                            delete current;
                            current = newSeq;
                        }
                        printSequence(current, "After prepend:");
                        break;
                    }
                    case 12: {
                        int val, idx;
                        std::cout << "Value and index: ";
                        std::cin >> val >> idx;
                        Sequence<int>* newSeq = current->InsertAt(val, idx);
                        if (newSeq != current) {
                            delete current;
                            current = newSeq;
                        }
                        printSequence(current, "After insert:");
                        break;
                    }
                    case 13: {
                        std::cout << "Create another sequence to concat:\n";
                        int m;
                        std::cout << "Enter number of elements: ";
                        std::cin >> m;
                        int* arr2 = new int[m];
                        std::cout << "Enter elements: ";
                        for (int i = 0; i < m; ++i) std::cin >> arr2[i];
                        Sequence<int>* other = new MutableArraySequence<int>(arr2, m);
                        Sequence<int>* newSeq = current->Concat(other);
                        if (newSeq != current) {
                            delete current;
                            current = newSeq;
                        }
                        delete other;
                        delete[] arr2;
                        printSequence(current, "After concat:");
                        break;
                    }
                    default:
                        std::cout << "Invalid choice. Please enter a number between 0 and 13.\n";
                        break;
                }
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    delete current;
}

int main() {
    runTests();
    interact();
    return 0;
}