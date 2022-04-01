#include "pub.h"
#include <crtdbg.h>

void swap(int& lhs, int& rhs) {
  lhs = lhs + rhs;
  rhs = lhs - rhs;
  lhs = lhs - rhs;
}

void BubbleSort(int array[], int length) {
  auto start = std::chrono::steady_clock::now();

  for (int i = 0; i < length - 1; ++i) {
    for (int j = 0; j < length - i - 1; ++j) {
      if (array[j] > array[j + 1]) {
        swap(array[j], array[j + 1]);
      }
    }
  }

  auto end = std::chrono::steady_clock::now();
  print_duration(start, end);
}

void BubbleSort1(int array[], int length) {
  auto start = std::chrono::steady_clock::now();

  for (int i = 0; i < length - 1; ++i) {
    bool is_sorted = true;
    for (int j = 0; j < length - i - 1; ++j) {
      if (array[j] > array[j + 1]) {
        swap(array[j], array[j + 1]);
        is_sorted = false;
      }
    }
    if (is_sorted) {
      break;
    }
  }

  auto end = std::chrono::steady_clock::now();
  print_duration(start, end);
}

void BubbleSort2(int array[], int length) {
  auto start = std::chrono::steady_clock::now();

  int last_exchang_index = 0;
  int sort_border = length - 1;
  for (int i = 0; i < length - 1; ++i) {
    bool is_sorted = true;
    for (int j = 0; j < sort_border; ++j) {
      if (array[j] > array[j + 1]) {
        swap(array[j], array[j + 1]);
        is_sorted = false;
        last_exchang_index = j;
      }
    }
    sort_border = last_exchang_index;
    if (is_sorted) {
      break;
    }
  }

  auto end = std::chrono::steady_clock::now();
  print_duration(start, end);
}

void printarr(int arr[], int length) {
  for (int i = 0; i < length; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  int arr[] = {11, 1, 31, 14, 13, 35, 23, 54, 15, 16,
               13, 14, 15, 16, 17, 18, 19, 20, 21, 20,
               32, 23, 234, 125, 226, 26, 310, 233, 136, 646,
               415, 628, 22, 33, 44, 55, 66, 77, 90, 11,
               111, 112, 113, 114, 115, 116, 117, 19, 20, 11};
  int arr1[] = {11,  1,   31,  14,  13,  35,  23,  54,  15, 16,  13,  14,  15,
               16,  17,  18,  19,  20,  21,  20,  32,  23, 234, 125, 226, 26,
               310, 233, 136, 646, 415, 628, 22,  33,  44, 55,  66,  77,  90,
               11,  111, 112, 113, 114, 115, 116, 117, 19, 20,  11};
  int arr2[] = {11,  1,   31,  14,  13,  35,  23,  54,  15, 16,  13,  14,  15,
               16,  17,  18,  19,  20,  21,  20,  32,  23, 234, 125, 226, 26,
               310, 233, 136, 646, 415, 628, 22,  33,  44, 55,  66,  77,  90,
               11,  111, 112, 113, 114, 115, 116, 117, 19, 20,  11};

  BubbleSort(arr, 50);
  //printarr(arr, 50);
  BubbleSort1(arr1, 50);
  //printarr(arr1, 50);
  BubbleSort2(arr2, 50);
  //printarr(arr2, 50);
  int* c = new int[10];

  //_CrtDumpMemoryLeaks();
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  std::cout << "Hello World!\n";
}