// quick_sort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <functional>

int partition(int array[], int startIndex, int endIndex) {
  //取第一个位置的元素为基准元素【更好的方法是取随机位置的元素为基准元素】
  int pivot = array[startIndex];
  int left = startIndex;
  int right = endIndex;

  while (left != right) {
    //控制right指针比较并左移
    while (left < right && array[right] > pivot) {
      right--;
    }
    //控制left指针比较并右移
    while (left < right && array[left] <= pivot) {
      left++;
    }
    //交换left指针和right指针所指向的元素
    if (left < right) {
      int temp = array[left];
      array[left] = array[right];
      array[right] = temp;
    }
  }
  //基准元素和指针重合点交换
  array[startIndex] = array[left];
  array[left] = pivot;
  return left;
}

void QuickSort(int array[], int startIndex, int endIndex) {
  //递归结束条件
  if (startIndex >= endIndex)
    return;
  //得到基准元素
  int pivotIndex = partition(array, startIndex, endIndex);
  //根据基准元素，分成两部分进行递归排序
  QuickSort(array, startIndex, pivotIndex - 1);
  QuickSort(array, pivotIndex + 1, endIndex);
}

int main()
{
  int a[] = {5,6,3,1,2,8,9,10};
  QuickSort(a, 0, 7);

  std::cout << "sss" << std::endl;
  std::bind();
  return 0;
}
