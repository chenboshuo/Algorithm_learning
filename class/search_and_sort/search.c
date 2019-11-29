// 顺序查找和二分查找
#include <stdio.h>
#include <stdlib.h>

/**
 * 顺序查找
 * @param  a      数组
 * @param  len    数组长度
 * @param  target 要查找的值
 * @return        找到的元素的下标(未找到返回-1)
 */
int sequential_search(int* a, size_t len, int target){
  for (size_t i = 0; i < len; ++i){
    if (a[i] == target) { return i; }
  }
  return -1;
}

/**
 * 二分查找
 * @param  nums   数组
 * @param  len    数组长度
 * @param  target 目标值
 * @return        找到元素的下标(-1表示未找到)
 */
int binary_search(int *nums, size_t len, int target) {
  size_t low = 0;
  size_t high = len - 1;

  // 若搜索值大于数组最大值, 直接找不到
  if (target > nums[high]) { return -1; }
  while(low <= high){
    int mid = low + ((high-low) >> 1);
    if(target > nums[mid]) {
      low = mid +1;
    }else if(target < nums[mid]){
      high = mid -1;
    }else{
      return mid;
    }
  }
  return -1;
}

int main(int argc, char const *argv[]) {
  // case 1
  int a1[5] = { 1, 2, 3, 4, 5 };
  printf("To find 3 in [1,2,3,4,5]\n");
  printf("Brute force: %d\n", sequential_search(a1, 5, 3));
  printf("To find 0 in [1,2,3,4,5]\n");
  printf("Brute force: %d\n", sequential_search(a1, 5, 0));

  // case 2
  int a2[5] = {3, 4, 5, 2,2};
  printf("To find 3 in [3, 4, 5, 2,2]\n");
  printf("Brute force: %d\n", sequential_search(a2, 5, 3));
  printf("To find 0 in [3, 4, 5, 2,2]\n");
  printf("Brute force: %d\n", sequential_search(a2, 5, 0));

  printf("\nTest binary search\n\n");

  // case 1
  int a3[5] = {0,1,2,3,4};
  printf("To search for 0 in a3 = [0,1,2,3,4]: %d\n", binary_search(a3, 5, 0));
  printf("To search for 2 in a3 = [0,1,2,3,4]: %d\n", binary_search(a3, 5, 2));
  printf("To search for 5 in a3 = [0,1,2,3,4]: %d\n", binary_search(a3, 5, 5));


  // case 2
  int a4[7] = {1,1,2,3,5,8,13};
  printf("\nTo find 1  in a4 = [1,1,2,3,5,8,13]: %d\n", binary_search(a4, 7, 1));
  printf("To find 13 in a4 = [1,1,2,3,5,8,13]: %d\n", binary_search(a4, 7, 13));
  printf("To find 4  in a4 = [1,1,2,3,5,8,13]: %d\n", binary_search(a4, 7, 4));


  return 0;
}
