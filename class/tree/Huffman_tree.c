#include <limits.h>  // INT_MAX 定义
#include <stdio.h>

#define MAXLEAF 20               // 最多叶节点的值
#define MAXNODE MAXLEAF * 2 - 1  // 最多节点

// Huffman tree definition
typedef struct node {
  int weight;
  int parent;
  int left;
  int right;
} HuffmanTree;

void create_HuffmanTree(HuffmanTree *node, int length) {
  for (size_t i = 0; i < 2 * length - 1; ++i) {
    node[i].weight = 0;
    node[i].parent = -1;
    node[i].left = -1;
    node[i].right = -1;
  }
  for (size_t i = 0; i < length; ++i) {
    scanf("%d", &node[i].weight);
  }
  for (size_t i = 0; i < length - 1; ++i) {
    int min1 = INT_MAX, min2 = INT_MAX;
    int min1_index = 0, min2_index = 0;  // 记录最小两个元素的位置
    for (size_t j = 0; j < length + 1; ++j) {
      if (node[j].parent == -1 &&
          node[j].weight < min1) {  // 节点为根节点且权小于最小
        min2 = min1;
        min2_index = min1_index;
        min1 = node[j].weight;
        min1_index = j;
      } else if (node[j].parent == -1 &&
                 node[j].weight < min2) {  // 若节点的值只小于min2
        min2 = node[j].weight;
        min2_index = j;
      }
      node[min1_index].parent = length + i;
      node[min2_index].parent = length + i;
      node[length + i].weight =
          node[min1_index].weight + node[min2_index].weight;
      node[length + i].left = min1_index;
      node[length + i].right = min2_index;
    }
  }
}
