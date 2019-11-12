#include <limits.h>  // INT_MAX 定义
#include <stdio.h>
#include <stdlib.h>

#define MAXLEAF 20               // 最多叶节点的值
#define MAXNODE MAXLEAF * 2 - 1  // 最多节点
#define EMPTY '_' //

// Huffman tree definition
typedef struct node {
  int value;
  int weight;  // 记录节点的权
  int parent;  // parent 节点索引
  int left;
  int right;
} HuffmanTree;

/**
 * 建立 Huffman 树
 * @param  words  字符
 * @param  weight 字符对应权(保证字符与对应权长度喜爱那个等)
 * @param  length 字符(权) 数组的长度
 * @return        哈夫曼树
 */
HuffmanTree *createHuffmanTree(char* words, int *weight, size_t length) {
  // 初始化节点
  HuffmanTree *node =
      (HuffmanTree *)malloc(sizeof(HuffmanTree) * (2 * length - 1));
  size_t parent_index;
  for (size_t i = 0; i < 2 * length - 1; ++i) {
    if (i < length) {  // 如果是带权的节点, 直接加权,并存储对应字母
      node[i].weight = weight[i];
      node[i].value = words[i];
    } else {  // 其他节点用权重为0, 对应字母为空
      node[i].weight = 0;
      node[i].value = EMPTY;
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

/**
 * (内部函数) 打印节点
 * @param node  Huffman 树头指针
 * @param index 节点的索引
 * @param depth 节点在树中对应深度
 */
void _print(HuffmanTree *node, size_t index, int depth) {
  for (size_t i = 0; i < depth; ++i) {
    printf("|  ");
  }
  printf("|- %c (%d)\n", node[index].value ,node[index].weight);

  if (node[index].left != -1) {
    _print(node, node[index].left, depth + 1);
  }
  if (node[index].right != -1) {
    _print(node, node[index].right, depth + 1);
  }
}

/**
 * 打印 Huffman 树
 * @param node 用来存放 Huffman 树地址的数组
 */
void print(HuffmanTree *node) {
  // 寻找根节点
  size_t root_index = 0;
  while (node[root_index].parent != -1) {
    root_index = node[root_index].parent;
  }
  _print(node, root_index, 0);
}

int main(int argc, char const *argv[]) {
  // 对HuffmanTree的创建的测试
  // Case 1
  int w1[2] = {0, 1};
  char* worlds_1 = "ab";
  HuffmanTree *test1 = createHuffmanTree(worlds_1, w1, 2);
  printf("\nCase 1\n");
  print(test1);

  // Case 2
  int w2[1] = {1};
  char *worlds_2 = "a";
  HuffmanTree *test2 = createHuffmanTree(worlds_2, w2, 1);
  printf("\nCase 2\n");
  print(test2);

  // Case 3
  int w3[3] = {9,9,6};
  char *worlds_3 = "Asp";
  HuffmanTree *test3 = createHuffmanTree(worlds_3, w3, 3);
  printf("\nCase 3\n");
  print(test3);

  // Case 4
  int w4[4] = {2,5,8,6};
  char *worlds_4 = "tfes";
  HuffmanTree *test4 = createHuffmanTree(worlds_4, w4, 4);
  printf("\nCase 4\n");
  print(test4);

  // Case 5
  int w5[9] = {2,5,3,6,8,1,4,8,9};
  char *worlds_5 = "abcdefghi";
  HuffmanTree *test5 = createHuffmanTree(worlds_5, w5, 9);
  printf("\nCase 5\n");
  print(test5);

  return 0;
}
