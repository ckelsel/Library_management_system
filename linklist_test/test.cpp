#include "pch.h"

#include "../book/linklist.h"
#include "../book/database.h"

TEST(LinkList, init) {
    // nullptr ��ָ��
    struct linklist_t* linklist;
    linklist = linklist_init();
    // linklist��ֵ��ΪNULL
    EXPECT_NE(nullptr, linklist);
}



TEST(LinkList, add)
{
    struct linklist_t* head;
    head = linklist_init();

    linklist_add(head, "ͼ�����ϵͳ", "л����");
    linklist_add(head, "һѧ�ͻᣬ0����ʵ��̰����", "л����");


    // ���Դ���
    struct linklist_t* p2;
    struct linklist_t* p3;

    // ָ��ڶ����ڵ�
    p2 = head->next;

    // ָ��������ڵ�
    p3 = p2->next;

    EXPECT_STREQ("ͼ�����ϵͳ", p2->name);
    EXPECT_STREQ("л����", p2->author);
    EXPECT_NE(nullptr, p2->next);


    EXPECT_STREQ("һѧ�ͻᣬ0����ʵ��̰����", p3->name);
    EXPECT_STREQ("л����", p3->author);
    EXPECT_EQ(nullptr, p3->next);
}


TEST(LinkList, del)
{
    struct linklist_t* head;
    head = linklist_init();

    linklist_add(head, "visual studio 2019��������", "л����");
    linklist_add(head, "visual studio 2019С�׿���������Ƶ�̳�", "л����");

    // ɾ��1���ڵ�
    linklist_del(head, "visual studio 2019��������", "л����");

    // ָ��ڶ����ڵ�
    struct linklist_t* p2;

    p2 = head->next;

    EXPECT_STREQ("visual studio 2019С�׿���������Ƶ�̳�", p2->name);
    EXPECT_STREQ("л����", p2->author);
    EXPECT_EQ(nullptr, p2->next);
}


TEST(LinkList, del_no_in_list)
{
    struct linklist_t* head;
    head = linklist_init();

    linklist_add(head, "visual studio 2019��������", "л����");
    linklist_add(head, "visual studio 2019С�׿���������Ƶ�̳�", "л����");

    // ɾ�������ڵĽڵ�
    linklist_del(head, "xx", "л����");

    // ���Դ���
    struct linklist_t* p2;
    struct linklist_t* p3;

    // ָ��ڶ����ڵ�
    p2 = head->next;

    // ָ��������ڵ�
    p3 = p2->next;

    EXPECT_STREQ("visual studio 2019��������", p2->name);
    EXPECT_STREQ("л����", p2->author);
    EXPECT_NE(nullptr, p2->next);


    EXPECT_STREQ("visual studio 2019С�׿���������Ƶ�̳�", p3->name);
    EXPECT_STREQ("л����", p3->author);
    EXPECT_EQ(nullptr, p3->next);
}



TEST(LinkList, del_no_in_list2)
{
    struct linklist_t* head;
    head = linklist_init();

    linklist_add(head, "visual studio 2019��������", "л����");
    linklist_add(head, "visual studio 2019С�׿���������Ƶ�̳�", "л����");

    // ɾ�������ڵĽڵ�
    linklist_del(head, "", "");

    // ���Դ���
    struct linklist_t* p2;
    struct linklist_t* p3;

    // ָ��ڶ����ڵ�
    p2 = head->next;

    // ָ��������ڵ�
    p3 = p2->next;

    EXPECT_STREQ("visual studio 2019��������", p2->name);
    EXPECT_STREQ("л����", p2->author);
    EXPECT_NE(nullptr, p2->next);


    EXPECT_STREQ("visual studio 2019С�׿���������Ƶ�̳�", p3->name);
    EXPECT_STREQ("л����", p3->author);
    EXPECT_EQ(nullptr, p3->next);
}


TEST(Database, write)
{
    struct linklist_t* head;
    head = linklist_init();

    linklist_add(head, "visual studio 2019��������", "л����");
    linklist_add(head, "visual studio 2019С�׿���������Ƶ�̳�", "л����");


    database_write(head);

    const char *right = "visual studio 2019��������,л����\nvisual studio 2019С�׿���������Ƶ�̳�,л����\n";

    // ��ȡ�ļ�����
    char buffer[1024];
    FILE* fp = NULL;
    fopen_s(&fp, DATABASE_FILE, "r");
    fread(buffer, 1, 1024, fp);
    fclose(fp);

    EXPECT_EQ(memcmp(right, buffer, strlen(right)), 0);
}

