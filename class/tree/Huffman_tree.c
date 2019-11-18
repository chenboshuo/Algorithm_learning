#include <limits.h>  // INT_MAX 定义
#include <stdio.h>
#include <stdlib.h>

#define MAXLEAF 20               // 最多叶节点的值
#define MAXNODE MAXLEAF * 2 - 1  // 最多节点
#define EMPTY '_' // 存贮没有对应字母的单词
#define CODE_MAX 100  // 编码的最大长度
#define BIT_MAX 10 // 存储单个字母的最大编码长度

// Huffman tree definition
typedef struct node {
  int value;
  int weight;  // 记录节点的权
  int parent;  // parent 节点索引
  int left;
  int right;
} HuffmanTree;

// 字典的定义
// 字典存储了字母与对应 Huffman code
typedef struct{
  char word;
  char bits[BIT_MAX + 1];
  int start;
} Dict;

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

/**
 * 创建字典
 * 字典存储了节点字母与对应的编码
 * @param  tree   Huffman 树的地址
 * @param  length 字典数组的长度
 * @return        字典数组的指针
 */
Dict* create_dict(HuffmanTree* tree, int length){
  // 初始化字典
  Dict *dict = (Dict *)malloc(sizeof(Dict) * length);
  for (size_t i = 0; i < length; ++i) {
    dict[i].start = BIT_MAX;
    dict[i].bits[BIT_MAX] = '\0';
  }

  // 处理节点
  for (size_t node_index = 0; node_index < length; node_index++) {

    // 为字典插入字母
    dict[node_index].word = tree[node_index].value;
    int parent_index = tree[node_index].parent;  // parent 表示节点的parent
    int child_index = node_index;  // 相对的child节点的下标


    //  判断 叶子是parent的左或右子树
    while(parent_index != -1){
      if(tree[parent_index].left == child_index) { // parent 的left 是当前节点的下标
        dict[node_index].bits[--(dict[node_index].start)] = '0';
      }else{
        dict[node_index].bits[--(dict[node_index].start)] = '1';
      }
      child_index = parent_index;
      parent_index = tree[parent_index].parent;
    }
  }
  return dict;
}

/**
 * 打印字典
 * @param d      字典
 * @param length 字典数组的长度
 */
void print_dict(Dict *d, int length){
  for (size_t i = 0; i < length; ++i){
    printf("%c - %s\n", d[i].word, d[i].bits + d[i].start);
  }
}

char *code(char* string, Dict* dict, size_t dict_size){
  char *cipher = (char*)malloc(sizeof(char) * CODE_MAX);
  int index = 0;
  while (*string) {
    // 在字典中检索
    for (size_t i = 0; i < dict_size; ++i){
      if(*string == dict[i].word) {  
        printf("%c", dict[i].word);
        for (size_t j = dict[i].start; j < BIT_MAX; ++j) {  // 延长字符串 
          cipher[index++] = dict[i].bits[j]; 
        }
      }
    }
    ++string;
  }
  cipher[index] = '\0';
  return cipher;
}

int main(int argc, char const *argv[]) {
  // Case 1
  int w1[2] = {2, 3};
  char* worlds_1 = "ab";
  HuffmanTree *test1 = createHuffmanTree(worlds_1, w1, 2);
  printf("\nCase 1\n");
  print(test1);
  Dict *d1 = create_dict(test1, 2);
  printf("\n");
  print_dict(d1, 2);
  char *test_txt1 = "abb";
  char *code_1 = code(test_txt1, d1, 2);
  printf("\n the code of \"%s\":\n %s", test_txt1, code_1);

  // // Case 2 不符合实际,去除测试,约定编码数>1
  // int w2[1] = {1};
  // char *worlds_2 = "a";

  // Case 3
  int w3[3] = {9,9,6};
  char *worlds_3 = "Asp";
  HuffmanTree *test3 = createHuffmanTree(worlds_3, w3, 3);
  printf("\nCase 3\n");
  print(test3);
  Dict *d3 = create_dict(test3, 3);
  printf("\n");
  print_dict(d3, 3);
  char *test_txt3 = "pAss";
  char *code_3 = code(test_txt3, d3, 3);
  printf("\n the code of \"%s\":\n %s", test_txt3, code_3);


  // Case 4
  int w4[4] = {2,5,8,6};
  char *worlds_4 = "rfes";
  HuffmanTree *test4 = createHuffmanTree(worlds_4, w4, 4);
  printf("\nCase 4\n");
  print(test4);
  Dict *d4 = create_dict(test4, 4);
  printf("\n");
  print_dict(d4, 4);
  char *test_txt4 = "frees";
  char *code_4 = code(test_txt4, d4, 4);
  printf("\n the code of \"%s\":\n %s", test_txt4, code_4);


  // Case 5
  int w5[9] = {2,5,3,6,8,1,4,8,9};
  char *worlds_5 = "abcdefght";
  HuffmanTree *test5 = createHuffmanTree(worlds_5, w5, 9);
  printf("\nCase 5\n");
  print(test5);
  Dict *d5 = create_dict(test5, 9);
  printf("\n");
  print_dict(d5, 9);
  char *test_txt5 = "database";
  char *code_5 = code(test_txt5, d5, 9);
  printf("\n the code of \"%s\":\n %s", test_txt5, code_5);


  return 0;
}
