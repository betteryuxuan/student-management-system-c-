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

//学生信息
typedef struct ListNode {
    char name[MAX_NAME];
    char id[MAX_ID];
    char class[MAX_CLASS];
    int score1, score2, score3;
    struct ListNode* pre;
    struct ListNode* next;
}ListNode;

//学生账户密码
typedef struct UserList {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role;
    struct UserList* pre;
    struct UserList* next;
}UserList;

//待办事项
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

//初始化学生信息链表
ListNode* InitStuList();
UserList* InitUserList();
TodoList* InitTodoList();
ScoreList* InitScoreList();

//菜单界面
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
//文件输入（从文件中读取）
void ReadStuFromFile(ListNode* head, const char* username);
void ReadUserFromFile(UserList* userList);
void ReadTodoListFromFile(TodoList* todoList);
void ReadScoreListFromFile(ScoreList* scoreList);

//文件写入
void WriteStuToFile(ListNode* head, const char* username);
void WriteUserToFile(UserList* userList);
void WriteTodoToFile(TodoList* todoList);
void WriteScoreToFile(ScoreList* scoreList);

//内存释放
void FreeListNode(ListNode* head);
void FreeUserList(UserList* userList);
void FreeTodoList(TodoList* todoList); 
void FreeScoreList(ScoreList* scoreList);

//登陆操作

    //用户账户识别验证
int Authenticate(const char* username, const char* password, char* role);
int UserLog(ListNode* head, const char* username);
    //密码注册
void UpdatePassword(UserList* userList, TodoList* todoList);
    //密码修改
void ChangePassword(UserList* userList, TodoList* todoList);
    //密码找回
void RecoverPassword(UserList* userList, ListNode* head, TodoList* todoList);

//学生端

    //查询个人成绩
void FindStuScore(ListNode* head, char* username);
    // 成绩分析
int ScoreRank(ListNode* head, char* username);
void ScoreAnaly(ListNode* head, char* username);
    //成绩申诉
void GradeAppeal(ListNode* head, char* username, ScoreList* scoreList);


//教师端链表对应操作

    //通过姓名查找 
ListNode* FindStuByName(ListNode* head, const char* name);
    //通过学号查找 
ListNode* FindStuById(ListNode* head, const char* id);
    //添加学生信息
void AddStuInfo(ListNode* head);
    //删除学生信息
void DelStuInfo(ListNode* head);
    //修改学生信息
void ModifyStuInfo(ListNode* head);
void Mod(ListNode* cur);
    //查询学生信息
void FindStuInfo(ListNode* head);
    //输出学生信息
void DisplayStuInfo(const ListNode* head);
    //下载学生信息
void DownloadStuInfo(ListNode* head);
    //学生成绩分析
void AverageScores(ListNode* head);
void TeacherScoreAnaly(ListNode* head);
void PrintTopStudents(ListNode* head, int subject, int count);
    //学生成绩排序
bool CompareNodes(const ListNode* a, const ListNode* b, int subjectChoice);
void SwapNodes(ListNode* node1, ListNode* node2);
void SelectionSort(ListNode* head, int subjectChoice, int orderChoice);
void SortStuInfo(ListNode* head);
    //成绩申诉处理
void DelScore(ScoreList* scoreList, int position);
void HandleScore(ScoreList* scoreList, int position);
void GradeUpdate(ScoreList* scoreList);


//管理员  
  
    //代办查看删除
void DelTodo(TodoList* todoList, int position);
void HandleTodo(TodoList* todoList, int position);
void ViewTodo(TodoList* todoList);
    //添加账密信息
void AddUserInfo(UserList* userList);
    //删除账密信息
void DeleteUserInfo(UserList* userList);
    //修改账密信息
void ModifyUserInfo(UserList* userList);
    //查找账密信息
void FindUserInfo(UserList* userList);
    //新班级初始化账户密码
void InitialClassFromFile(ListNode* head, UserList* userList);
    //输出账密信息
void DisplayUserInfo(const UserList* userList);
    //手动重新录入学生信息 
void ReEnterStuInfo(ListNode* head);


#endif //STUDENT_MANAGEMENT_SYSTEM_STUDENT_MANAGEMENT_SYSTEM_H
