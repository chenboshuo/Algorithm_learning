#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NODESIZE 100  // 节点的最大数量
bool thread = false;

typedef char type;
typedef struct node {
  type value;
  struct node *left;
  bool left_thread; // 左边是否为线索
  struct node *right;
  bool right_thread; // 右边是否为线索
} BinaryTree;

/**
 * 初始化二叉树节点
 * @param  value 值得地址
 * @return       生成节点地址
 */
BinaryTree* init(type* value){
  BinaryTree* root = (BinaryTree*)malloc(sizeof(BinaryTree));
  root->left_thread = false; // 初始状态无左右线索
  root->right_thread = false;
  root->left = NULL;
  root->right = NULL;
  if (value) { root->value = *value; }
  return root;
}

/**
 * (内部函数)中序线索化二叉树
 * @param node 节点地址
 */
BinaryTree *pre = NULL;
void _cue(BinaryTree *node){
  // 递归调用建立左子树索引
  if(node -> left && !node->left_thread) {
    _cue(node->left);
  }

  if (pre && !pre->right) { // 没有右孩子, 将右指针作为线索
    pre->right_thread = true;
    pre->right = node;
    pre = node;
  }

  if (!node->left) { // 没有左孩子, 将左指针作为线索
    node->left_thread = true;
    node->left = pre;
    pre = node; // 移动pre指针到当前位置

  }

  // 递归调用建立右子树索引
  if(node->right && !node->right_thread) {
    _cue(node->right);
  }

}

/**
 * (内部函数)获得线索化中序二叉树的下一个节点地址
 * @param  node 节点地址
 * @return      下一个节点地址
 */
BinaryTree *_next(BinaryTree * node){
  if (!node) {
    printf("error");
    return NULL;
  }
  if (node->right_thread) {
    return node->right;
  }
  node = node-> right;
  while (node && !node->left_thread) {
    node = node->left;
  }
  return node;
}


/**
 * (内部函数)中序打印线索化的二叉树
 * @param node 起始打印节点
 */
void _print_threaded(BinaryTree *node){
  if (!node) { return; }
  while (node->left && !node->left_thread) { node = node->left; }
  while (node) {
    printf("%c ", node->value);
    node = _next(node);
  }
}

void in_order_print(BinaryTree *node){
  if (!thread) { // 没有线索,则线索化二叉树
    _cue(node);
    thread = true;
  }
  _print_threaded(node);
  printf("\n");
}


/**
 * 根据表达式建立二叉树
 * 表达式形式为" 节点(左子树, 右子树)"
 * 可以缩进与空格
 * @param  expression 表达式
 * @return            根节点
 */
BinaryTree *create_tree(char *expression) {
  enum child { LEFT, RIGHT };
  BinaryTree *loc[NODESIZE];  // 记录节点的地址
  int ptr_loc = 0;
  BinaryTree *node[2];    // 存储左右子树
  enum child flag = LEFT;  // 左子树或右子树的标志

  while (*expression) {
    switch (*expression) {
      case ' ':
      case '\t':
      case '\n':
        break;  // 跳过空格
      case '(':
        // 让'(' 前的地址入栈
        loc[ptr_loc++] = node[flag];

        // 将当前node的信息清空
        node[LEFT] = NULL;
        node[RIGHT] = NULL;
        flag = LEFT;
        break;
      case ',':
        flag = RIGHT;
        break;   // 切换为右子树
      case ')':  // 检测到')'
        node[flag] = loc[--ptr_loc];
        break;
      default:
        node[flag] = init(expression);
        if ((ptr_loc > 0) && (loc[ptr_loc - 1])) {
          if (flag == LEFT) {
            loc[ptr_loc - 1]->left = node[flag];
          } else {
            loc[ptr_loc - 1]->right = node[flag];
          }
        }
    }
    ++expression;
  };
  thread = false;
  return node[flag];
}


int main(int argc, char const *argv[]) {
  char *exp1 = "A()";
  BinaryTree *test1 = create_tree(exp1);
  printf("\nCase 1: \n%s\n", exp1);
  in_order_print(test1);

  char *exp2 = "A(B,C)";
  BinaryTree *test2 = create_tree(exp2);
  printf("\nCase 2: \n%s\n", exp2);
  in_order_print(test2);

  char *exp3 = "A(\n  B(,D),\n  C(E,)\n)";
  BinaryTree *test3 = create_tree(exp3);
  printf("\nCase 3:\n%s\n", exp3);
  in_order_print(test3);

  char *exp4 = "A(\n  ,\n  C(\n    F,\n  )\n)";
  BinaryTree *test4 = create_tree(exp4);
  printf("\nCase 4:\n%s\n", exp4);
  in_order_print(test4);

  char *exp5 = "A(\n  ,\n  C(\n    F(G,),\n  )\n)";
  BinaryTree *test5 = create_tree(exp5);
  printf("\nCase 5:\n%s\n", exp5);
  in_order_print(test5);

  char *exp6 = "A(\n  B(,D),\n  C(E,)\n)";
  BinaryTree *test6 = create_tree(exp6);
  printf("\nCase 6:\n%s\n", exp6);
  in_order_print(test6);

  char *exp7 = "A(\n  B(\n    ,E\n  ),\n  C(\n    F(\n      G(,H),\n    ),\n  )\n)";
  BinaryTree *test7 = create_tree(exp7);
  printf("\nCase 6:\n%s\n", exp7);
  in_order_print(test7);

  return 0;
}
