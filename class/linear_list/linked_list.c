#include <stdio.h>
#include <stdlib.h>
typedef char type;

// 正向链表定义
typedef struct node {
  type data;
  struct node *next;
} linked_list;

/**
 * 初始化链表
 * @return 指向头结点指针
 * 算法思路
 * 1.让head指向一个新的重新分配的节点, 指针域为空
 * 2.返回head;
 */
linked_list *init() {
  linked_list *head = (linked_list *)malloc(sizeof(linked_list));
  head->next = NULL;
  return head;
}

/**
 * 创建列表(仅限于char),输入"$"停止
 * @param  head 头指针
 * @return      尾部指针
 */
linked_list *creat_char_list(linked_list *head) {
  linked_list *tail = head, *p;
  type x;
  head -> data = 'h';
  while ((x = getchar()) && x != '$') {
    p = (linked_list *)malloc(sizeof(linked_list));
    p->data = x;
    p->next = NULL;
    tail->next = p;
    tail = p;
    x = getchar();
  }
  return tail;
}

/**
 * 在当前位置之后插入节点
 * @param  p 当前节点位置
 * @param  data 加入的数据
 * @return   插入后节点的位置
 */
linked_list* insert(linked_list* p, type data){
  linked_list*q = (linked_list*)malloc(sizeof(linked_list));
  q -> data = data;
  q -> next = p -> next;
  p -> next = q;
  return q;
}

/**
 * 打印链表的所有值
 * @param list 链表头结点地址
 */
void print(linked_list* list) {
  while (list) {
  printf("%c ", list->data);
  list = list->next;
  }
  printf("\n");
}

/**
 * 删除下一个节点
 * @param p 当前节点的地址
 */
void delete_next(linked_list* p) {
  linked_list*q = p->next;
  p ->next = q -> next;
  free(q);
}

// TODO: 删除当前节点

/**
 * 反转链表
 * @param  head 链表的头结点地址
 */
void reverse(linked_list*head){
  linked_list* pre=NULL, *cur = head->next, *next;
  while (cur) {
    next = cur -> next;
    cur -> next = pre;
    pre = cur;
    cur = next;
  }
  // pre -> next = NULL; // 最后的节点无后继
  head ->next = pre;
}

// 测试函数
int main(int argc, char const *argv[]) {
  // 测试初始化函数
  linked_list *head = init();
  creat_char_list(head);
  printf("After init:\n");
  print(head);

  // 测试插入函数
  insert(head,'5');
  printf("\nAfter insert:\n");
  print(head);

  // 测试删除函数
  delete_next(head);
  printf("\nAfter delete\n");
  print(head);

  // 测试反转函数
  reverse(head);
  printf("\nAfter reverse\n");
  print(head);

  return 0;
}
// a b c $
// After init:
// h a b c
//
// After insert:
// h 5 a b c
//
// After delete
// h a b c
//
// After reverse
// h c b a
