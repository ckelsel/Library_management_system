// book.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "linklist.h"
#include <string.h>
#include "database.h"



void list_menu(int pause);

struct linklist_t* g_book;

struct list_menu_page {
    // 书名
    char name[MAX_LENGTH];

    // 作者
    char author[MAX_LENGTH];
};

struct list_menu_page g_page[MAX_LENGTH];

void add_menu()
{
    char name[MAX_LENGTH];
    char author[MAX_LENGTH];

    printf("添加图书\n");


    printf("请输入书名:\n");
    scanf_s("%s", name, (unsigned)_countof(name));
    printf("请输入作者:\n");
    scanf_s("%s", author, (unsigned)_countof(author));


    linklist_add(g_book, name, author);
    database_write(g_book);
}

void del_menu()
{
    while (TRUE)
    {
        // 清屏
        system("cls");


        printf("删除图书\n");

        list_menu(FALSE);

        printf("请输入序号删除图书，按ESC返回上级菜单\n");
        int key = _getch();

        // ESC返回
        if (key == 27)
        {
            break;
        }

        // '0' 48
        // '1' 49
        key = key - '0';

        // 数据合法
        if (key > 0 && key < 10) // [1,9]
        {
            linklist_del(g_book, g_page[key].name, g_page[key].author);
        }
    }
}

void modify_menu()
{
    printf("修改图书\n");


    // 列出所有图书
    list_menu(FALSE);

    // 让用户选择图书序号
    printf("请输入序号修改图书，按ESC返回上级菜单\n");

    int key = _getch();
    if (key == 27)
    {
        return;
    }

    key = key - '0';

    // g_book删除旧的图书信息
    if (key > 0 && key < 10)
    {
        linklist_del(g_book, g_page[key].name, g_page[key].author);
    }

    // 提示用户输入书名，作者
    char name[MAX_LENGTH];
    char author[MAX_LENGTH];

    printf("请输入书名:\n");
    scanf_s("%s", name, (unsigned)_countof(name));
    printf("请输入作者:\n");
    scanf_s("%s", author, (unsigned)_countof(author));


    // g_book插入新的图书信息

    linklist_add(g_book, name, author);
    database_write(g_book);
}

void query_menu()
{
    printf("查询图书\n");

    // 提示用户输入用户名author查询
    char author[MAX_LENGTH];
    printf("请输入作者查询\n");
    printf("作者:");
    scanf_s("%s", author, (unsigned)_countof(author));

    printf("------------查询结果----------\n");
    printf("序号\t\t书名\t\t作者\n");
    int index = 1;

    // 遍历g_book链表
    struct linklist_t* p = g_book;

    while (p->next != NULL)
    {
        // 指向下一个节点
        p = p->next;

        // 如果author跟g_book的author一样，则显示出来
        if (memcmp(p->author, author, strlen(p->author)) == 0)
        {
            printf("%d\t\t%s\t\t%s\n", index, p->name, p->author);
            index++;
        }
    }

    _getch();
}

void list_menu(int pause)
{
    printf("列出所有图书\n");

    printf("序号\t\t书名\t\t作者\n");

    struct linklist_t* p = g_book;

    memset(g_page, 0, sizeof(g_page));

    int index = 1;
    while (p->next != NULL)
    {
        p = p->next;

        printf("%d\t\t%s\t\t%s\n", index, p->name, p->author);

        memcpy(g_page[index].author, p->author, strlen(p->author) + 1);
        memcpy(g_page[index].name, p->name, strlen(p->name) + 1);

        index++;
    }

    if (pause)
    {
        _getch();
    }
    
}

// 主界面
void mainmenu()
{
    printf("图书管理系统\n");
    printf("\n");
    printf("1. 添加图书\n");
    printf("2. 删除图书\n");
    printf("3. 修改图书\n");
    printf("4. 查询图书\n");
    printf("5. 列出所有图书\n");
    printf("\n");
    printf("请按数字，选择功能\n");
}

void mainloop()
{
    while (true) {
        mainmenu();

        // getchar需要按回车键
        int key = _getch();
        system("cls");
        switch (key) {
        case '1':
            add_menu();
            break;
        case '2':
            del_menu();
            break;
        case '3':
            modify_menu();
            break;
        case '4':
            query_menu();
            break;
        case '5':
            list_menu(TRUE);
            break;
        default:
            break;
        }
        system("cls");
    }
}


int main()
{
    g_book = linklist_init();

    mainloop();
    
    return 0;
}

