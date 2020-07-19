#include "pch.h"

#include "../book/linklist.h"
#include "../book/database.h"

TEST(LinkList, init) {
    // nullptr 空指针
    struct linklist_t* linklist;
    linklist = linklist_init();
    // linklist的值不为NULL
    EXPECT_NE(nullptr, linklist);
}



TEST(LinkList, add)
{
    struct linklist_t* head;
    head = linklist_init();

    linklist_add(head, "图书管理系统", "谢昆明");
    linklist_add(head, "一学就会，0基础实现贪吃蛇", "谢昆明");


    // 测试代码
    struct linklist_t* p2;
    struct linklist_t* p3;

    // 指向第二个节点
    p2 = head->next;

    // 指向第三个节点
    p3 = p2->next;

    EXPECT_STREQ("图书管理系统", p2->name);
    EXPECT_STREQ("谢昆明", p2->author);
    EXPECT_NE(nullptr, p2->next);


    EXPECT_STREQ("一学就会，0基础实现贪吃蛇", p3->name);
    EXPECT_STREQ("谢昆明", p3->author);
    EXPECT_EQ(nullptr, p3->next);
}


TEST(LinkList, del)
{
    struct linklist_t* head;
    head = linklist_init();

    linklist_add(head, "visual studio 2019调试入门", "谢昆明");
    linklist_add(head, "visual studio 2019小白快速入门视频教程", "谢昆明");

    // 删掉1个节点
    linklist_del(head, "visual studio 2019调试入门", "谢昆明");

    // 指向第二个节点
    struct linklist_t* p2;

    p2 = head->next;

    EXPECT_STREQ("visual studio 2019小白快速入门视频教程", p2->name);
    EXPECT_STREQ("谢昆明", p2->author);
    EXPECT_EQ(nullptr, p2->next);
}


TEST(LinkList, del_no_in_list)
{
    struct linklist_t* head;
    head = linklist_init();

    linklist_add(head, "visual studio 2019调试入门", "谢昆明");
    linklist_add(head, "visual studio 2019小白快速入门视频教程", "谢昆明");

    // 删掉不存在的节点
    linklist_del(head, "xx", "谢昆明");

    // 测试代码
    struct linklist_t* p2;
    struct linklist_t* p3;

    // 指向第二个节点
    p2 = head->next;

    // 指向第三个节点
    p3 = p2->next;

    EXPECT_STREQ("visual studio 2019调试入门", p2->name);
    EXPECT_STREQ("谢昆明", p2->author);
    EXPECT_NE(nullptr, p2->next);


    EXPECT_STREQ("visual studio 2019小白快速入门视频教程", p3->name);
    EXPECT_STREQ("谢昆明", p3->author);
    EXPECT_EQ(nullptr, p3->next);
}



TEST(LinkList, del_no_in_list2)
{
    struct linklist_t* head;
    head = linklist_init();

    linklist_add(head, "visual studio 2019调试入门", "谢昆明");
    linklist_add(head, "visual studio 2019小白快速入门视频教程", "谢昆明");

    // 删掉不存在的节点
    linklist_del(head, "", "");

    // 测试代码
    struct linklist_t* p2;
    struct linklist_t* p3;

    // 指向第二个节点
    p2 = head->next;

    // 指向第三个节点
    p3 = p2->next;

    EXPECT_STREQ("visual studio 2019调试入门", p2->name);
    EXPECT_STREQ("谢昆明", p2->author);
    EXPECT_NE(nullptr, p2->next);


    EXPECT_STREQ("visual studio 2019小白快速入门视频教程", p3->name);
    EXPECT_STREQ("谢昆明", p3->author);
    EXPECT_EQ(nullptr, p3->next);
}


TEST(Database, write)
{
    struct linklist_t* head;
    head = linklist_init();

    linklist_add(head, "visual studio 2019调试入门", "谢昆明");
    linklist_add(head, "visual studio 2019小白快速入门视频教程", "谢昆明");


    database_write(head);

    const char *right = "visual studio 2019调试入门,谢昆明\nvisual studio 2019小白快速入门视频教程,谢昆明\n";

    // 读取文件内容
    char buffer[1024];
    FILE* fp = NULL;
    fopen_s(&fp, DATABASE_FILE, "r");
    fread(buffer, 1, 1024, fp);
    fclose(fp);

    EXPECT_EQ(memcmp(right, buffer, strlen(right)), 0);
}

