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
  linked_list *tail, *p;
  type x;
  x = getchar();
  while (x != '$') {
    p = (linked_list *)malloc(sizeof(linked_list));
    p->data = x;
    p->next = NULL;
    tail->next = p;
    tail = p;
    x = getchar();
  }
  return tail;
}

int main(int argc, char const *argv[]) {
  linked_list *head = init();
  creat_char_list(head);
  return 0;
}
