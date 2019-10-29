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

// binary_tree *str2tree(char* str){
//   int rear = 1;
//   int front = 0;
//   binary_tree *root = init(str);
//   binary_tree *node = root;
//   binary_tree *left_child, *right_child;
//   binary_tree (*location)[NODESIZE];
//   while (str[rear] != '\0') {

//     left_child = init(str + rear);
//     node
//     }
// }

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
  if (!node) {
    printf("|- \n");
    return;
  }

  // 递归地打印左子树
  printf("| ");
  in_order_print(node->left);

  // 打印当前节点
  printf("|-%c\n", node->value);

  // 打印右子树
  printf("| ");
  in_order_print(node->right);
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

  // printf("In oreder traversal:\n");
  // in_order_print(test);

  // 测试表达式建立二叉树
  char *exp = "A(B(,E),C(F,))";
  printf("Test the tree using expression \"%s\".\n", exp);
  binary_tree *test2 = create_tree(exp);
  pre_order_print(test2);

  // 表达式 case 2
  char *exp2 = "A(B(,E),C(F(G(,H),),))";
  printf("Test the tree using expression \"%s\".\n", exp2);
  binary_tree *test3 = create_tree(exp2);
  pre_order_print(test3);

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