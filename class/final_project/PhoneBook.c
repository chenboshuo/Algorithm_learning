#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATCH 0

// 链表: 每一条记录
typedef struct node {
  char *phonenumber;
  char *name;
  struct node *next;
} Records;


/**
 * 初始化节点
 * @return 指向结点指针
 */
Records *init() {
  Records *head = (Records *)malloc(sizeof(Records));
  head->next = NULL;
  return head;
}

/**
 * 创建头结点
 * @return 头结点
 */
Records *creat_head(){
  Records *head = init();
  head -> name = (char*)malloc(sizeof(char) * strlen(" name"));
  head -> name = " name";
  head -> phonenumber = (char*)malloc(sizeof(char) * strlen("phone_number"));
  head -> phonenumber = "phone_number";
  return head;
}

/**
 * 插入记录
 * @param  tail 尾指针
 * @return      尾部指针
 */
Records *append(Records *tail, char *name, char *phonenumber) {
  Records *new = init();
  new -> name = (char*)malloc(sizeof(char) * strlen(name));
  new -> name = name;
  new -> phonenumber = (char*)malloc(sizeof(char) * strlen(phonenumber));
  new -> phonenumber = phonenumber;

  tail -> next = new;
  return new;
}

/**
 * 打印链表
 * @param head 头结点
 */
void print(Records* head){
  for(;head;head= head -> next){
    printf("%10s\t%11s\n",head->name, head->phonenumber);
  }
}


/**
 * 顺序查找
 * @param  head   头结点
 * @param  string 要查找的字符串
 * @return        找到的节点的上一个节点
 */
Records *search_pre(Records *head, char* string){
  if(!head->next){ return head;}

  // 由于head不存信息, 故不可能在头结点找到信息
  Records *pre = head;
  head = head -> next;

  for(;head;head= head -> next){
    if(strcmp(string,head->name) == MATCH
       || strcmp(string,head->phonenumber) == MATCH){
      printf("Found:\n"
             "     name   : %s\n"
             "phone_number: %s\n", head->name,head->phonenumber);
      return pre;
    }
    pre = pre-> next;
  }
    return pre;
}

/**
 * 删除节点
 * @param pre 节点地址
 */
void delete(Records *pre){
  Records *to_delete = pre->next;
  pre -> next = to_delete ->next;
  free(to_delete);
}

/**
 * 从文件中输入
 * @param  tail 尾指针
 * @return      新的尾指针
 */
Records *import(Records * tail){
  FILE *fp = fopen("PhoneBook.txt", "r");
  char _[10], __[10];
  fscanf(fp,"%s %s", _, __); // 忽略标题
  while(1){
    char *name = (char*)malloc(sizeof(char)*10);
    char *phonenumber = (char *)malloc(sizeof(char)*11);
    if(fscanf(fp,"%s %s", name, phonenumber) != 2){
      break;
    }
    tail = append(tail, name,phonenumber);
  }
  fclose(fp);
  return tail;
}

/**
 * 程序结束后的链表的导出
 * @param head 头指针
 */
void export(Records *head){
  FILE *fp = fopen("PhoneBook.txt", "w");
  for(;head;head= head -> next){
    fprintf(fp, "%s %s\n",head->name, head->phonenumber);
  }
  fclose(fp);
}

int main(int argc, char const *argv[]) {
  Records *phone_book = creat_head();
  Records *tail = phone_book;
  char name[10];
  char input[10];

  tail = import(tail);
  while(1){

    printf("+---------------------------------------------+\n"
           "|             Phone   Book                    |\n"
           "+---------------------------------------------+\n"
           "|       1: Show all phonenumber               |\n"
           "|       2: Search                             |\n"
           "|       3: Delete a record                    |\n"
           "|       4: Insert a record                    |\n"
           "|       You can press other button to exit    |\n"
           "+---------------------------------------------+\n");
    int flag;
    if(scanf("%d", &flag) != 1){
      export(phone_book);
      exit(0);
    }
    system("cls");

    // 打印函数
    if (flag == 1) {
      print(phone_book);
    }

    // 搜索
    else if(flag == 2){
      printf("To search:\t");
      scanf("%s",input);
      if(search_pre(phone_book,input) == tail){
        printf("Not found\n");
      }
    }

    // 删除
    else if(flag == 3){
      printf("To delete:\t");
      scanf("%s",input);
      Records *pre = search_pre(phone_book,input); // 要删除项的前一项

      // 删除元素
      if( pre != tail){ // 元素是否在链表中
        printf("Continue? (y/n)\t");
        fflush(stdin);  // 不知道为什么要清空缓冲区
        char yn;
        yn = getchar();
        if(yn == 'y') {
          delete(pre);
          printf("done\n");
        }
      }else{
        printf("the item is not found\n");
      };
    }

    // 插入
    else if(flag == 4){
      char *name_ = (char *)malloc(sizeof(char)*10);
      char *number = (char *)malloc(sizeof(char)*11);
      printf("Input the name  :\t");
      scanf("%s",name_);
      printf("Input the number:\t");
      scanf("%s",number);
      tail = append(tail, name_, number);
    }

    // 退出
    else{
      export(phone_book);
      exit(0);
    }
      system("pause");
      system("cls"); // 清空屏幕

  }

  return 0;
}
