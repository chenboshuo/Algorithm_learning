#include <stdio.h>

enum thread { FALSE, TRUE };

typedef char type;
typedef struct node {
  type value;
  struct node *left;
  enum thread left_thread; // 左边是否为线索
  struct node *right;
  enum thread right_thread; // 左边是否为线索

} binary_tree;

binary_tree *pre = NULL;


/**
 * 初始化二叉树节点
 * @param  value 值得地址
 * @return       生成节点地址
 */
binary_tree* init(type* value){
  binary_tree* root = (binary_tree*)malloc(sizeof(binary_tree));
  root->left_thread = FALSE;
  root->right_thread = FALSE;
  root->left = NULL;
  root->right = NULL;
  if (value) { root->value = *value; }
  return root;
}

/**
 * 线索化二叉树
 * @param node 节点地址
 */
void cue(binary_tree *node){
  if (node == NULL) { return; }


  cue(node->left);

  if (!node->left) { node->left_thread = TRUE; }
  if (!node->right) { node->right_thread = TRUE; }

  if (node->left_thread) { node->right = pre; }
  if (pre && pre->right_thread) { pre->right = node; }

  cue(node->right);

}

/**
 * 获得线索化中序二叉树的下一个节点地址
 * @param  node 节点地址
 * @return      下一个节点地址
 */
binary_tree *__next__(binary_tree * node){
  binary_tree *q;
  if (!node) {
    printf("error");
    return NULL;
  }
  if (node->right_thread) {
    return node->right;
  }
    q = node-> right;
    while (!q->left_thread) {
      q = q->left;
    }
    return q;
}


/**
 * 中序打印线索化的二叉树
 * @param node 起始打印节点
 */
void print_threaded(binary_tree *node){
  binary_tree * p = node;
  if(p){
    while(!p->left_thread){
      p = p-> left;
    }
    while(p){
      printf("%c", p->value);
      p = __next__(p);
    }
  }
}
