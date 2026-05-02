#include "tests.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include <iostream>
#include <cassert>
#include <string>

void testDynamicArray() {
    std::cout << "Testing DynamicArray...\n";
    int arr[] = {1,2,3};
    DynamicArray<int> da(arr, 3);
    assert(da.Get(1) == 2);
    da.Set(1, 5);
    assert(da.Get(1) == 5);
    da.Resize(5);
    assert(da.GetSize() == 5);
    assert(da.Get(3) == 0);
    
    try {
        da.Get(5);
        assert(false);
    } catch (const IndexOutOfRange&) {}

    da.Resize(2);
    assert(da.GetSize() == 2);
    assert(da.Get(0) == 1);
    assert(da.Get(1) == 5);
    
    try {
        da.Get(2);
        assert(false);
    } catch (const IndexOutOfRange&) {}

    DynamicArray<int> da2(da);
    assert(da2.GetSize() == 2);
    assert(da2.Get(0) == 1);
    da.Set(0, 100);
    assert(da2.Get(0) == 1);

    DynamicArray<int> empty(0);
    assert(empty.GetSize() == 0);
    
    try {
        empty.Get(0);
        assert(false);
    } catch (const IndexOutOfRange&) {}
}

void testLinkedList() {
    std::cout << "Testing LinkedList...\n";
    int arr[] = {1,2,3};
    LinkedList<int> ll(arr, 3);
    assert(ll.GetFirst() == 1);
    assert(ll.GetLast() == 3);
    ll.Append(4);
    assert(ll.GetLength() == 4);
    assert(ll.GetLast() == 4);
    ll.Prepend(0);
    assert(ll.GetFirst() == 0);
    ll.InsertAt(99, 2);

    // Проверка порядка элементов
    assert(ll.Get(0) == 0);
    assert(ll.Get(1) == 1);
    assert(ll.Get(2) == 99);
    assert(ll.Get(3) == 2);
    assert(ll.Get(4) == 3);
    assert(ll.Get(5) == 4);

    LinkedList<int>* sub = ll.GetSubList(1, 3);
    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 1);
    assert(sub->Get(1) == 99);
    assert(sub->Get(2) == 2);
    delete sub;

    try {
        ll.Get(-1);
        assert(false);
    } catch (const IndexOutOfRange&) {}

    try {
        ll.Get(10);
        assert(false);
    } catch (const IndexOutOfRange&) {}

    try {
        ll.InsertAt(5, -1);
        assert(false);
    } catch (const IndexOutOfRange&) {}

    LinkedList<int> empty;
    
    try {
        empty.GetFirst();
        assert(false);
    } catch (const IndexOutOfRange&) {}

    try {
        empty.GetLast();
        assert(false);
    } catch (const IndexOutOfRange&) {}

    int a2[] = {10,20};
    LinkedList<int> ll2(a2,2);
    LinkedList<int>* concat = ll.Concat(&ll2);
    assert(concat->GetLength() == 8);
    assert(concat->Get(6) == 10);
    assert(concat->Get(7) == 20);
    delete concat;
}

void testMutableArraySequence() {
    std::cout << "Testing MutableArraySequence...\n";
    int arr[] = {1,2,3};
    MutableArraySequence<int> mas(arr,3);
    assert(mas.GetLength() == 3);
    mas.Append(4);
    assert(mas.GetLength() == 4);
    assert(mas.GetLast() == 4);
    mas.Prepend(0);
    assert(mas.GetFirst() == 0);
    mas.InsertAt(99, 2);

    // Порядок: [0,1,99,2,3,4]
    assert(mas.Get(0) == 0);
    assert(mas.Get(1) == 1);
    assert(mas.Get(2) == 99);
    assert(mas.Get(3) == 2);
    assert(mas.Get(4) == 3);
    assert(mas.Get(5) == 4);

    mas.Append(5)->Prepend(-1);
    assert(mas.GetFirst() == -1);
    assert(mas.GetLast() == 5);
    assert(mas.GetLength() == 8);
    
    Sequence<int>* sub = mas.GetSubsequence(2, 5);
    assert(sub->GetLength() == 4);
    assert(sub->Get(0) == 1);
    assert(sub->Get(1) == 99);
    assert(sub->Get(2) == 2);
    assert(sub->Get(3) == 3);
    delete sub;

    int arr2[] = {100,200};
    MutableArraySequence<int> mas2(arr2,2);
    mas.Concat(&mas2);
    assert(mas.GetLength() == 10);
    assert(mas.Get(8) == 100);
    assert(mas.Get(9) == 200);
}

void testImmutableArraySequence() {
    std::cout << "Testing ImmutableArraySequence...\n";
    int arr[] = {1,2,3};
    ImmutableArraySequence<int> ias(arr,3);
    assert(ias.GetLength() == 3);
    Sequence<int>* ias2 = ias.Append(4);
    assert(ias.GetLength() == 3);
    assert(ias2->GetLength() == 4);
    assert(ias2->GetLast() == 4);
    Sequence<int>* ias3 = ias2->Prepend(0);
    assert(ias2->GetLength() == 4);
    assert(ias3->GetLength() == 5);
    assert(ias3->GetFirst() == 0);
    Sequence<int>* ias4 = ias3->InsertAt(99,2);
    assert(ias4->Get(2) == 99);
    assert(ias4->GetLength() == 6);
    delete ias2;
    delete ias3;
    delete ias4;

    int arr2[] = {10,20};
    ImmutableArraySequence<int> ias5(arr2,2);
    Sequence<int>* concat = ias.Concat(&ias5);
    assert(concat->GetLength() == 5);
    assert(concat->Get(0) == 1);
    assert(concat->Get(1) == 2);
    assert(concat->Get(2) == 3);
    assert(concat->Get(3) == 10);
    assert(concat->Get(4) == 20);
    delete concat;
}

void testMutableListSequence() {
    std::cout << "Testing MutableListSequence...\n";
    int arr[] = {1,2,3};
    MutableListSequence<int> mls(arr,3);
    assert(mls.GetLength() == 3);
    mls.Append(4);
    assert(mls.GetLength() == 4);
    assert(mls.GetLast() == 4);
    mls.Prepend(0);
    assert(mls.GetFirst() == 0);
    mls.InsertAt(99, 2);

    assert(mls.Get(0) == 0);
    assert(mls.Get(1) == 1);
    assert(mls.Get(2) == 99);
    assert(mls.Get(3) == 2);
    assert(mls.Get(4) == 3);
    assert(mls.Get(5) == 4);

    mls.Append(5)->Prepend(-1);
    assert(mls.GetFirst() == -1);
    assert(mls.GetLast() == 5);
    assert(mls.GetLength() == 8);

    int arr2[] = {100,200};
    MutableListSequence<int> mls2(arr2,2);
    mls.Concat(&mls2);
    assert(mls.GetLength() == 10);
    assert(mls.Get(8) == 100);
    assert(mls.Get(9) == 200);
}

void testImmutableListSequence() {
    std::cout << "Testing ImmutableListSequence...\n";
    int arr[] = {1,2,3};
    ImmutableListSequence<int> ils(arr,3);
    assert(ils.GetLength() == 3);
    Sequence<int>* ils2 = ils.Append(4);
    assert(ils.GetLength() == 3);
    assert(ils2->GetLength() == 4);
    assert(ils2->GetLast() == 4);
    Sequence<int>* ils3 = ils2->Prepend(0);
    assert(ils2->GetLength() == 4);
    assert(ils3->GetLength() == 5);
    assert(ils3->GetFirst() == 0);
    Sequence<int>* ils4 = ils3->InsertAt(99,2);
    assert(ils4->Get(2) == 99);
    assert(ils4->GetLength() == 6);
    delete ils2;
    delete ils3;
    delete ils4;

    int arr2[] = {10,20};
    ImmutableListSequence<int> ils5(arr2,2);
    Sequence<int>* concat = ils.Concat(&ils5);
    assert(concat->GetLength() == 5);
    assert(concat->Get(0) == 1);
    assert(concat->Get(1) == 2);
    assert(concat->Get(2) == 3);
    assert(concat->Get(3) == 10);
    assert(concat->Get(4) == 20);
    delete concat;
}

void testPolymorphism() {
    std::cout << "Testing polymorphism via Sequence*...\n";
    int arr[] = {1,2,3};
    Sequence<int>* seq = new MutableArraySequence<int>(arr,3);
    seq->Append(4);
    assert(seq->GetLength() == 4);
    assert(seq->GetLast() == 4);
    delete seq;

    seq = new ImmutableArraySequence<int>(arr,3);
    Sequence<int>* newSeq = seq->Append(4);
    assert(seq->GetLength() == 3);
    assert(newSeq->GetLength() == 4);
    delete seq;
    delete newSeq;

    seq = new MutableListSequence<int>(arr,3);
    seq->Append(4);
    assert(seq->GetLength() == 4);
    delete seq;

    seq = new ImmutableListSequence<int>(arr,3);
    newSeq = seq->Append(4);
    assert(seq->GetLength() == 3);
    assert(newSeq->GetLength() == 4);
    delete seq;
    delete newSeq;
}

void runTests() {
    testDynamicArray();
    testLinkedList();
    testMutableArraySequence();
    testImmutableArraySequence();
    testMutableListSequence();
    testImmutableListSequence();
    testPolymorphism();
    std::cout << "All tests passed!\n";
}