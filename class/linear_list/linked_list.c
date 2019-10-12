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
  head->data = 'h';
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
linked_list *insert(linked_list *p, type data) {
  linked_list *q = (linked_list *)malloc(sizeof(linked_list));
  q->data = data;
  q->next = p->next;
  p->next = q;
  return q;
}

/**
 * 打印链表的所有值
 * @param list 链表头结点地址
 */
void print(linked_list *list) {
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
void delete_next(linked_list *p) {
  linked_list *q = p->next;
  p->next = q->next;
  free(q);
}

/**
 * 按照数值查找节点 /          地址运算(只能向右)
 * @param  loc 头结点的位置 /  当前节点位置
 * @param  i   索引(head为0)/  与loc的相对位置
 * @return     要查找的指针地址
 */
linked_list *iloc(linked_list *loc, size_t i) {
  while (i--) {
    if (!loc->next) { return NULL; }
    loc = loc->next;
  }
  return loc;
}

/**
 * 求表长
 * @param  head 头结点位置
 * @return      长度
 */
size_t len(linked_list *head) {
  size_t len;
  for (len = 0; head->next; head = head->next) { ++len; }
  return len;
}

/**
 * 反转链表
 * @param  head 链表的头结点地址
 */
void reverse(linked_list *head) {
  linked_list *pre = NULL, *cur = head->next, *next;
  while (cur) {
    next = cur->next;
    cur->next = pre;
    pre = cur;
    cur = next;
  }
  // pre -> next = NULL; // 最后的节点无后继
  head->next = pre;
}

/**
 * 判断空链表
 * @param  head 头结点位置
 * @return      空为 1, 否则为 0.
 */
int is_empty(linked_list *head) { return (head->next == NULL); }

/**
 * 按值查找
 * @param  loc  查找的开始位置
 * @param  data 要查找的数据
 * @return      找到的节点
 */
linked_list *search(linked_list *loc, type data) {
  while (loc->data != data) {
    if ((loc = loc->next) == NULL) { return NULL; };
  }
  return loc;
}

// 测试函数
int main(int argc, char const *argv[]) {
  // 测试初始化函数
  linked_list *head = init();
  creat_char_list(head);
  printf("After init:\n");
  print(head);

  // 测试查找函数
  linked_list *find = iloc(head, 1);
  printf("\nFind head[1]\n");
  printf("%c\n", find->data);

  // 测试表长
  printf("\nThe length of linked list is %d\n", len(head));

  // 测试查找
  char to_search = 'a';
  printf("%c\n", search(head, to_search)->data);

  // 测试插入函数
  insert(head, '5');
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

  // 测试空链表
  linked_list *empty = init();
  if (is_empty(empty)) { printf("\nInit a empty list\n"); }

  return 0;
}
// 1 2 3 a
// $
// After init:
// h 1 2 3 a
//
// find head[1]
// 1
//
// The length of linked list is 4
// a
//
// After insert:
// h 5 1 2 3 a
//
// After delete
// h 1 2 3 a
//
// After reverse
// h a 3 2 1
//
// init a empty list
