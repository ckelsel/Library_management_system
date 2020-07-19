#include "linklist.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

struct linklist_t* linklist_init()
{
	struct linklist_t* head = (struct linklist_t*)malloc(sizeof(struct linklist_t));

	head->next = NULL;

	return head;
}


void linklist_add(linklist_t* head, char* book_name, char* book_author)
{
	// 1.
	struct linklist_t* p = head;

	// 2.
	while (p->next != NULL)
	{
		p = p->next;
	}


	// 3. 
	// book_name: "abc\0"
	struct linklist_t* node = (struct linklist_t* )malloc(sizeof(struct linklist_t));
	memcpy(node->name, book_name, strlen(book_name) + 1);
	memcpy(node->author, book_author, strlen(book_author) + 1);
	node->next = NULL;

	// 4.
	p->next = node;
}

void linklist_del(linklist_t* head, char* book_name, char* book_author)
{
	// 0.
	struct linklist_t* p = head;

	// 1.
	while (p->next != NULL)
	{
		if (memcmp(p->next->author, book_author, strlen(p->next->author)) == 0 &&
			memcmp(p->next->name, book_name, strlen(p->next->name)) == 0)
		{
			// 2.
			struct linklist_t* del = p->next;

			p->next = del->next;

			// 3.
			free(del);
			break;
		}

		p = p->next;
	}
}


