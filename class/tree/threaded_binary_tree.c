#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 

typedef char type;
typedef struct node {
  type value;
  struct node *left;
  bool left_thread; // 左边是否为线索
  struct node *right;
  bool right_thread; // 右边是否为线索

} binary_tree;



/**
 * 初始化二叉树节点
 * @param  value 值得地址
 * @return       生成节点地址
 */
binary_tree* init(type* value){
  binary_tree* root = (binary_tree*)malloc(sizeof(binary_tree));
  root->left_thread = false; // 初始状态无左右线索
  root->right_thread = false;
  root->left = NULL;
  root->right = NULL;
  if (value) { root->value = *value; }
  return root;
}

/**
 * 中序线索化二叉树
 * @param node 节点地址
 */
binary_tree *pre = NULL;
void cue(binary_tree *node){
  if (node == NULL) { return; }

  // 递归调用建立左子树索引
  cue(node->left);

  if (!node->left) { // 没有左孩子, 将左指针作为线索
    node->left_thread = true; 
  }
  if (!node->right) { // 没有右孩子, 将右指针作为线索
    node->right_thread = true; 
  }

  // 寻找线索节点
  if (node->left_thread) { // 将左线索指向pre节点
    node->left = pre; 
    pre = node; // 移动pre指针到当前位置
  }
  if (pre && pre->right_thread) { // 将pre节点的右线索指向当前节点
    pre->right = node; 
  }

  // 递归调用建立右子树索引
  cue(node->right);

}

/**
 * 获得线索化中序二叉树的下一个节点地址
 * @param  node 节点地址
 * @return      下一个节点地址
 */
binary_tree *next(binary_tree * node){
  if (!node) {
    printf("error");
    return NULL;
  }
  if (node->right_thread) {
    return node->right;
  }
    node = node-> right;
    while (!node->left_thread) {
      node = node->left;
    }
    return node;
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
      p = next(p);
    }
  }
}

