#include <stdio.h>
#include <stdbool.h> 

static void exchange(int*a, int*b){
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}

void select_sort(int *nums, int len) { 
  int *p_min = nums;

  for (size_t i = 0; i < len; ++i){
    for(size_t j = i+1; j< len; ++j){
      if(nums[j] < *p_min) {  
        p_min = nums + j;
      }
    }
    if(nums[i] > *p_min){
      exchange(nums + i, p_min);
    }
  }
}

void bubble_sort(int *nums, int len){
  for (size_t i = 0; i < len; ++i) { 
    bool is_order = true;
    for (size_t j = 0; j < len -1- i;++j){
      if (nums[j] > nums[j + 1]) { 
        exchange(nums + j, nums + j + 1);
        is_order = false;
        }
    }
    if (is_order) { return; }
  }
}

void insert_sort(int* nums, int len){
  for (size_t i = 1; i < len; ++i){
    for (size_t j = 0; j < i;++j) {
      if(nums[j] > nums[i]){
        exchange(nums+j, nums+i);
      }
    }
  }
}


int main(int argc, char const *argv[]) {
  // test 1 
  printf("select sort [5,5,3,2,1]\n");
  int test1[5] = { 5, 5, 3, 2, 1 };
  select_sort(test1, 5);
  for (size_t i = 0; i < 5; ++i) { printf("%d ", test1[i]); }

  // test 2
  printf("\n\nselect sort [58,8,3,6,47]\n");
  int test2[5] = {58,8,3,6,47};
  select_sort(test2, 5);
  for (size_t i = 0; i < 5; ++i) { printf("%d ", test2[i]); }

  printf("\n\nbubble sort [58,8,3,6,47]\n");
  int test3[5] = {58,8,3,6,47};
  bubble_sort(test3, 5);
  for (size_t i = 0; i < 5; ++i) { printf("%d ", test3[i]); }

  printf("\n\ninsert sort [58,8,3,6,47]\n");
  int test4[5] = {58,8,3,6,47};
  insert_sort(test4, 5);
  for (size_t i = 0; i < 5; ++i) { printf("%d ", test4[i]); }  return 0;
}