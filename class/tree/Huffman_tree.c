#include <limits.h>  // INT_MAX 定义
#include <stdio.h>
#include <stdlib.h>

#define MAXLEAF 20               // 最多叶节点的值
#define MAXNODE MAXLEAF * 2 - 1  // 最多节点

// Huffman tree definition
typedef struct node {
  int weight;  // 记录节点的权
  int parent;  // parent 节点索引
  int left;
  int right;
} HuffmanTree;

HuffmanTree *createHuffmanTree(int *weight, size_t length) {
  // 初始化节点
  HuffmanTree *node =
      (HuffmanTree *)malloc(sizeof(HuffmanTree) * (2 * length - 1));
  size_t parent_index;
  for (size_t i = 0; i < 2 * length - 1; ++i) {
    if (i < length) {  // 如果是带权的节点, 直接加权
      node[i].weight = weight[i];
    } else {  // 其他节点用0标记
      node[i].weight = 0;
    }
    node[i].parent = -1;
    node[i].left = -1;
    node[i].right = -1;
  }

  for (parent_index = length; parent_index < 2 * length - 1; ++parent_index) {
    int min1 = INT_MAX, min2 = INT_MAX;  // 记录两个最小元素值
    int min1_index = 0, min2_index = 0;  // 记录最小两个元素的位置

    // 寻找最小的两个节点
    for (size_t i = 0; i < parent_index; ++i) {
      if (node[i].parent == -1 &&
          node[i].weight < min1) {  // 节点为根节点且权小于最小
        min2 = min1;
        min2_index = min1_index;
        min1 = node[i].weight;
        min1_index = i;
      } else if (node[i].parent == -1 &&
                 node[i].weight < min2) {  // 若节点的值只小于min2
        min2 = node[i].weight;
        min2_index = i;
      }
    }
      // 创建两个最小节点的 parent node
      node[min1_index].parent = parent_index;
      node[min2_index].parent = parent_index;
      node[parent_index].weight =
          node[min1_index].weight + node[min2_index].weight;
      node[parent_index].left = min1_index;
      node[parent_index].right = min2_index;
  }
  return node;
}

void _print(HuffmanTree *node, size_t index, int depth) {
  for (size_t i = 0; i < depth; ++i) {
    printf("|  ");
  }
  printf("|- %d\n", node[index].weight);

  if (node[index].left != -1) {
    _print(node, node[index].left, depth + 1);
  }
  if (node[index].right != -1) {
    _print(node, node[index].right, depth + 1);
  }
}

void print(HuffmanTree *node) {
  size_t root_index = 0;  // 假设一开始的节点是根节点
  while (node[root_index].parent != -1) {
    root_index = node[root_index].parent;
  }
  _print(node, root_index, 0);
}

int main(int argc, char const *argv[]) {
  // 对HuffmanTree的创建的测试
  // Case 1
  int w1[2] = {0, 1};
  HuffmanTree *test1 = createHuffmanTree(w1, 2);
  printf("\nCase 1\n");
  print(test1);

  // Case 2
  int w2[1] = {1};
  HuffmanTree *test2 = createHuffmanTree(w2, 1);
  printf("\nCase 2\n");
  print(test2);

  // Case 3
  int w3[3] = {9,9,6};
  HuffmanTree *test3 = createHuffmanTree(w3, 3);
  printf("\nCase 3\n");
  print(test3);

  // Case 4
  int w4[4] = {2,5,3,6};
  HuffmanTree *test4 = createHuffmanTree(w4, 4);
  printf("\nCase 4\n");
  print(test4);

  // Case 5
  int w5[9] = {2,5,3,6,8,1,4,8,9};
  HuffmanTree *test5 = createHuffmanTree(w5, 9);
  printf("\nCase 5\n");
  print(test5);

  return 0;
}