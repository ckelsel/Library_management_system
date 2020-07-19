#pragma once

#define TRUE 1
#define FALSE 0

#define MAX_LENGTH 128

struct linklist_t {
    // ����
    char name[MAX_LENGTH];

    // ����
    char author[MAX_LENGTH];

	struct linklist_t* next;
};


// ����һ����ͷ��������
struct linklist_t* linklist_init();


// ��ӽڵ�
void linklist_add(struct linklist_t *head, char *book_name, char *book_author);

// ɾ���ڵ�
void linklist_del(struct linklist_t *head, char *book_name, char *book_author);