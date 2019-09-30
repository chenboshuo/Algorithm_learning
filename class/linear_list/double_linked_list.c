#include <stdio.h>
#include <stdlib.h>

// 定义存储char的结构体
typedef struct node{
  struct node *prior;
  char data;
  struct node *next;
} double_linked_list;

/**
 * 生成双向链表并返回
 * @return  返回头结点地址
 */
double_linked_list *init(void){
  double_linked_list *head = (double_linked_list *)malloc(sizeof(double_linked_list));
  head -> data = 'h'; // 标记头结点或者异常值
  head->prior = NULL;
  head->next = NULL;
  return head;
}

/**
 * 尾插法建表
 * @param tail 链表末尾
 * @return 末尾节点地址
 */
double_linked_list* creat_list(double_linked_list* tail){
  char input;
  while ((input = getchar()) != '$') {
    double_linked_list *next = init();
    next -> data = input;
    tail -> next = next;
    next -> prior = tail;
    tail = next;
  }
  return tail;
}

/**
 * 打印节点
 * @param node 起始节点
 * @param reverse 正向打印为1,否则为0
 */
void print(double_linked_list* node, int reverse) {
  while (node) {
    printf("%c ", node->data);
    if (!reverse) {
      node = node -> next;
    } else {
      node = node -> prior;
    }
  }
  printf("\n");
}

/**
 * 删除节点
 * @param node 节点地址
 */
void delete(double_linked_list *head,double_linked_list* node) {
  // 检查node是否是表中元素
  while (head && head != node) {
    head = head -> next;
  }
  if (!head) { // 若node不在链表中,head为NULL
    printf("Error with delete\n");
    return;
  }
  double_linked_list *prior = node -> prior;
  double_linked_list *next = node ->next;
  next -> prior = prior;
  prior -> next = next;
  free(node);
}


/**
 * 在当前节点之后插入节点
 * @param  node  节点地址
 * @param  value 插入节点的值
 */
void insert(double_linked_list *node, char value){
  double_linked_list *new = init();
  new -> data = value;
  new -> prior = node;
  new -> next = node->next;
  node -> next = new;
  new -> next -> prior = new;
}

int main(int argc, char const *argv[]){
  // 测试生成双向链表
  printf("Input the value of a list\n");
  double_linked_list *test = init();
  double_linked_list *tail = creat_list(test);
  // Input the value of a list
  // abcdef$


  printf("\nInit a double linked list\n");
  print(test,0);
  print(tail,1);
  // Init a double linked list
  // h a b c d e f
  // f e d c b a h

  // 测试插入
  printf("Test inset\n");
  insert(test->next, 'n');
  print(test,0);
  // Test inset
  // h a n b c d e f

  // 测试删除函数
  printf("\ndelete test->next\n");
  delete(test,test->next);
  print(test,0);
  // delete test->next
  // h n b c d e f

  // 测试非法删除
  printf("\n");
  delete(test,NULL);
  // Error with delete

  return 0;
}
// Input the value of a list
// abcdef$
//
// Init a double linked list
// h a b c d e f
// f e d c b a h
// Test inset
// h a n b c d e f
//
// delete test->next
// h n b c d e f
//
// Error with delete
