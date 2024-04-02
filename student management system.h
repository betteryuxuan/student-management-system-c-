#define _CRT_SECURE_NO_WARNINGS
#ifndef STUDENT_MANAGEMENT_SYSTEM_STUDENT_MANAGEMENT_SYSTEM_H
#define STUDENT_MANAGEMENT_SYSTEM_STUDENT_MANAGEMENT_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>

#define MAX_NAME 20
#define MAX_CLASS 20
#define MAX_ID 10
#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_DES 500

//ѧ����Ϣ
typedef struct ListNode {
    char name[MAX_NAME];
    char id[MAX_ID];
    char class[MAX_CLASS];
    int score1, score2, score3;
    struct ListNode* pre;
    struct ListNode* next;
}ListNode;

//ѧ���˻�����
typedef struct UserList {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role;
    struct UserList* pre;
    struct UserList* next;
}UserList;

//��������
typedef struct TodoList {
    char username[MAX_USERNAME];
    char des[MAX_DES];
    struct TodoList* pre;
    struct TodoList* next;
}TodoList;

typedef struct ScoreList {
    char username[MAX_USERNAME];
    int flag;
    int score;    
    char des[MAX_DES];
    struct ScoreList* pre;
    struct ScoreList* next;
}ScoreList;

//��ʼ��ѧ����Ϣ����
ListNode* InitStuList();
UserList* InitUserList();
TodoList* InitTodoList();
ScoreList* InitScoreList();

//�˵�����
void DisplayMenu(const char* menuText);
void AccountMenu(ListNode* head, UserList* userList, TodoList* todoList, ScoreList* scoreList);
void StudentMenu(ListNode* head, char* username, ScoreList* scoreList);
void TeacherMenu(ListNode* head, char* username, ScoreList* scoreList);
void AdminMenu(ListNode* head, UserList* userList, TodoList* todoList,ScoreList* scoreList);
void LoginMenu(ListNode* head, UserList* userList, TodoList* todoList, ScoreList* scoreList, char username[MAX_USERNAME]);

void Wait();
int SafeScanf(int min, int max);
void SafeFgets(char* buffer, size_t bufferSize);
void HidePasswd(char* passwd);
//�ļ����루���ļ��ж�ȡ��
void ReadStuFromFile(ListNode* head, const char* username);
void ReadUserFromFile(UserList* userList);
void ReadTodoListFromFile(TodoList* todoList);
void ReadScoreListFromFile(ScoreList* scoreList);

//�ļ�д��
void WriteStuToFile(ListNode* head, const char* username);
void WriteUserToFile(UserList* userList);
void WriteTodoToFile(TodoList* todoList);
void WriteScoreToFile(ScoreList* scoreList);

//�ڴ��ͷ�
void FreeListNode(ListNode* head);
void FreeUserList(UserList* userList);
void FreeTodoList(TodoList* todoList); 
void FreeScoreList(ScoreList* scoreList);

//��½����

    //�û��˻�ʶ����֤
int Authenticate(const char* username, const char* password, char* role);
int UserLog(ListNode* head, const char* username);
    //����ע��
void UpdatePassword(UserList* userList, TodoList* todoList);
    //�����޸�
void ChangePassword(UserList* userList, TodoList* todoList);
    //�����һ�
void RecoverPassword(UserList* userList, ListNode* head, TodoList* todoList);

//ѧ����

    //��ѯ���˳ɼ�
void FindStuScore(ListNode* head, char* username);
    // �ɼ�����
int ScoreRank(ListNode* head, char* username);
void ScoreAnaly(ListNode* head, char* username);
    //�ɼ�����
void GradeAppeal(ListNode* head, char* username, ScoreList* scoreList);


//��ʦ�������Ӧ����

    //ͨ���������� 
ListNode* FindStuByName(ListNode* head, const char* name);
    //ͨ��ѧ�Ų��� 
ListNode* FindStuById(ListNode* head, const char* id);
    //���ѧ����Ϣ
void AddStuInfo(ListNode* head);
    //ɾ��ѧ����Ϣ
void DelStuInfo(ListNode* head);
    //�޸�ѧ����Ϣ
void ModifyStuInfo(ListNode* head);
void Mod(ListNode* cur);
    //��ѯѧ����Ϣ
void FindStuInfo(ListNode* head);
    //���ѧ����Ϣ
void DisplayStuInfo(const ListNode* head);
    //����ѧ����Ϣ
void DownloadStuInfo(ListNode* head);
    //ѧ���ɼ�����
void AverageScores(ListNode* head);
void TeacherScoreAnaly(ListNode* head);
void PrintTopStudents(ListNode* head, int subject, int count);
    //ѧ���ɼ�����
bool CompareNodes(const ListNode* a, const ListNode* b, int subjectChoice);
void SwapNodes(ListNode* node1, ListNode* node2);
void SelectionSort(ListNode* head, int subjectChoice, int orderChoice);
void SortStuInfo(ListNode* head);
    //�ɼ����ߴ���
void DelScore(ScoreList* scoreList, int position);
void HandleScore(ScoreList* scoreList, int position);
void GradeUpdate(ScoreList* scoreList);


//����Ա  
  
    //����鿴ɾ��
void DelTodo(TodoList* todoList, int position);
void HandleTodo(TodoList* todoList, int position);
void ViewTodo(TodoList* todoList);
    //���������Ϣ
void AddUserInfo(UserList* userList);
    //ɾ��������Ϣ
void DeleteUserInfo(UserList* userList);
    //�޸�������Ϣ
void ModifyUserInfo(UserList* userList);
    //����������Ϣ
void FindUserInfo(UserList* userList);
    //�°༶��ʼ���˻�����
void InitialClassFromFile(ListNode* head, UserList* userList);
    //���������Ϣ
void DisplayUserInfo(const UserList* userList);
    //�ֶ�����¼��ѧ����Ϣ 
void ReEnterStuInfo(ListNode* head);


#endif //STUDENT_MANAGEMENT_SYSTEM_STUDENT_MANAGEMENT_SYSTEM_H
