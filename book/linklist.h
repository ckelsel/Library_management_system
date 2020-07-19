#pragma once

#define TRUE 1
#define FALSE 0

#define MAX_LENGTH 128

struct linklist_t {
    // 书名
    char name[MAX_LENGTH];

    // 作者
    char author[MAX_LENGTH];

	struct linklist_t* next;
};


// 创建一个带头结点的链表
struct linklist_t* linklist_init();


// 添加节点
void linklist_add(struct linklist_t *head, char *book_name, char *book_author);

// 删除节点
void linklist_del(struct linklist_t *head, char *book_name, char *book_author);