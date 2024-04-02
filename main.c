#define _CRT_SECURE_NO_WARNINGS
#include "student management system.h"

int main() {
    ListNode* head = InitStuList();
    UserList* userList = InitUserList();
    TodoList* todoList = InitTodoList();
    ScoreList* scoreList = InitScoreList();

    AccountMenu(head, userList, todoList, scoreList);

    FreeListNode(head);
    FreeUserList(userList);
    FreeTodoList(todoList);
    FreeScoreList(scoreList);

    return 0;
}

