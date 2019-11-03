#include <stdio.h>
#include <stdlib.h>

#define EMPTY '_'     // 用'_'作为占位符
#define NODESIZE 100  // 节点的最大数量

typedef char type;
typedef struct node {
  type value;
  struct node *left;
  struct node *right;
} binary_tree;

enum child { LEFT, RIGHT };

binary_tree *init(type *value) {
  binary_tree *root = (binary_tree *)malloc(sizeof(binary_tree));
  root->left = NULL;
  root->right = NULL;
  if (value) {
    root->value = *value;
  }
  return root;
}


/**
 * 字符串转化为二叉树,
 * 约定 "_" 代表空节点
 * @param  str 节点
 * @return     根节点
 */
binary_tree *str_to_tree(char* str){
  binary_tree *loc[NODESIZE]; // 存储生成节点地址
  int front = 0, rear = 1;

  // 处理根节点
  binary_tree *root = init(str++);
  loc[0] = root;

  for (; *str; ++str) {
    loc[rear] = (*str != EMPTY) ? init(str) : NULL;

    // 链接节点
    if(rear & 1) { // rear 为奇数, 则该节点为左节点
      loc[front]->left = loc[rear++];
    }else{
      loc[front++]->right = loc[rear++];
    }
  }

  return root;
}

/**
 * (内部函数) 递归先序打印二叉树
 * @param node   节点地址
 * @param indent 缩进层数
 */
void _pre_order_print_r(binary_tree *node, int indent) {
  if (!node) {
    // 打印空格
    for (int i = 0; i < indent; ++i) {
      printf("| ");
    }
    printf("|- \n");
    return;
  }
  // 打印空格
  for (int i = 0; i < indent; ++i) {
    printf("| ");
  }
  printf("|-%c\n", node->value);

  if (!node->left && !node->right) { // 跳过没有孩子的节点
    return;
  }

  // 递归的打印左右子树
  _pre_order_print_r(node->left, indent + 1);
  _pre_order_print_r(node->right, indent + 1);
}

/**
 * 先序打印二叉树
 * @param node 起始打印节点
 */
void pre_order_print(binary_tree *node) { _pre_order_print_r(node, 0); }

/**
 * 中序打印二叉树
 * @param node 起始打印节点
 */
void in_order_print(binary_tree *node) {
  binary_tree *path[NODESIZE];
  int pp = 0; // 指向path的指针
  while(node){
    // 有左子树,入栈,进入左子树
    while(node -> left){
      path[pp++] = node;
      node = node->left;
    }

    // 无左子树,打印
    printf("%c ", node->value);

    // 有右子树,进入,continue
    if(node -> right) {
      node = node -> right ;
      continue;
    }

    // 无右子树, 退栈
    while(!node -> right && pp > 0){
      // 退栈
      node = path[--pp];
      // 打印元素
      printf("%c ", node->value);
    }

    node = node->right;
  }
  printf("\n");
}

/**
 * 根据表达式建立二叉树
 * 表达式形式为" 节点(左子树, 右子树)"
 * 可以缩进与空格
 * @param  expression 表达式
 * @return            根节点
 */
binary_tree *create_tree(char *expression) {
  binary_tree *loc[NODESIZE];  // 记录节点的地址
  int ptr_loc = 0;
  binary_tree *node[2];    // 存储左右子树
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
  return node[flag];
}

int main(int argc, char const *argv[]) {
  // 测试先序,中序打印函数
  binary_tree *test = init("A");
  test->right = init("B");
  // test->right->left = init("C");
  printf("Preorder traversal:\n");
  pre_order_print(test);

  printf("In oreder traversal:\n");
  in_order_print(test);

  // 测试表达式建立二叉树
  char *exp = "A(\n  B(\n    ,E\n  ),\n  C(F,)\n)";
  printf("\nTest to create a binary tree using expression \"\n%s\".\n", exp);
  binary_tree *test2 = create_tree(exp);
  pre_order_print(test2);

  printf("In order traversal:\n");
  in_order_print(test2);

  // 表达式
  /*
    A(
      B(,E),
      C(
        F(
          G(,H),
        ),
      )
    )
  */
  char *exp3 = "A(B(,E),C(F(G(,H),),))";
  printf("\nTest to create a binary using expression \"\n%s\".\n", exp3);
  binary_tree *test3 = create_tree(exp3);
  pre_order_print(test3);

  printf("In order traversal:\n");
  in_order_print(test3);

  // printf("In order traversal:\n");
  // in_order_print(test3);

  // 测试字符串转化
  char *str4 = "ABC_DE";
  binary_tree *test4 = str_to_tree(str4);
  printf("Test to create tree by string('_' symbolize the NULL node): %s\n",
         str4);
  pre_order_print(test4);

  return 0;
}

/* output

  Preorder traversal:
  |-A
  Test the tree using expression "A(B(,E),C(F,))".
  |-A
  | |-B
  | |-C
  | | |-F
  | | |-
  Test the tree using expression "A(B(,E),C(F(G(,H),),))".
  |-A
  | |-B
  | |-C
  | | |-F
  | | | |-G
  | | | |-
  | | |-
*/
