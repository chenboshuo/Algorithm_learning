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
 * @return 头结点
 * 算法思路
 * 1.让head指向一个新的重新分配的节点, 指针域为空
 * 2.返回head;
 */
linked_list *init() {
  linked_list *head = (linked_list *)malloc(sizeof(linked_list));
  head->next = NULL;
  return head;
}
