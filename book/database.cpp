#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 保存格式
// 书名,作者
void database_write(linklist_t* head)
{
	FILE* fp = NULL;

	fopen_s(&fp, DATABASE_FILE, "w");
	if (fp == NULL)
	{
		return;
	}

	struct linklist_t* p = head;

	while (p->next != NULL)
	{
		p = p->next;

		fprintf(fp, "%s,%s\n", p->name, p->author);
	}

	fclose(fp);
}

