
#include "student management system.h"

//链表初始化
ListNode* InitStuList() {
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    if (head == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(head->name, "");
    strcpy(head->class, "");
    strcpy(head->id, "");
    head->score1 = 0;
    head->score2 = 0;
    head->score3 = 0;
    head->pre = NULL;
    head->next = NULL;

    return head;
}
UserList* InitUserList() {
    UserList* head1 = (UserList*)malloc(sizeof(UserList));
    if (head1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(head1->username, "");
    strcpy(head1->password, "");
    head1->role = '\0';
    head1->pre = NULL;
    head1->next = NULL;

    return head1;
}
TodoList* InitTodoList() {
    TodoList* head = (TodoList*)malloc(sizeof(TodoList));
    if (head == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(head->username, "");
    strcpy(head->des, "");

    head->pre = NULL;
    head->next = NULL;

    return head;
}
ScoreList* InitScoreList() {
    ScoreList* head = (ScoreList*)malloc(sizeof(ScoreList));
    if (head == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strcpy(head->username, "");
    head->flag = 0;
    head->score = 0;
    strcpy(head->des, "");

    head->pre = NULL;
    head->next = NULL;

    return head;
}

//菜单界面
void DisplayMenu(const char* menuText) {
    system("cls");
    printf("**************************************************************\n");
    printf("***                 \033[33m\033[1m欢迎进入学生管理系统\033[0m                   ***\n");
    printf("**************************************************************\n");
    printf("**************************************************************\n");
    printf("%s", menuText);
    printf("**************************************************************\n");
    printf("**************************************************************\n");
}
void AccountMenu(ListNode* head, UserList* userList, TodoList* todoList, ScoreList* scoreList) {
    int choice = 0;
    char username[MAX_USERNAME];

    ReadUserFromFile(userList);
    ReadTodoListFromFile(todoList);
    do {
        system("cls");
        DisplayMenu("***                    \033[33m\033[1m1.登录    \033[0m                          ***\n"
                    "***                    \033[33m\033[1m2.密码注册\033[0m                          ***\n"
                    "***                    \033[33m\033[1m3.密码修改\033[0m                          ***\n"
                    "***                    \033[33m\033[1m4.密码找回\033[0m                          ***\n"
                    "***                    \033[33m\033[1m0.退出    \033[0m                          ***\n");

        choice = SafeScanf(0, 4);
        switch (choice) {
        case 1:
            LoginMenu(head, userList, todoList, scoreList, username);
            break;
        case 2:
            UpdatePassword(userList, todoList);
            break;
        case 3:
            ChangePassword(userList, todoList);
            break;
        case 4:
            RecoverPassword(userList, head, todoList);
            break;
        case 0:
            break;
        default:
            //printf("输入错误，请重新输入。\n");
            Wait();
            break;
        }
        WriteUserToFile(userList);
        WriteTodoToFile(todoList);
    } while (choice);
}
void StudentMenu(ListNode* head, char* username, ScoreList* scoreList) {
    //int c;
    //while ((c = getchar()) != '\n' && c != EOF);

    int choice = 0;

    ReadStuFromFile(head, username);
    ReadScoreListFromFile(scoreList);

    do {
        DisplayMenu("***                    \033[33m\033[1m1.成绩查询\033[0m                          ***\n"
                    "***                    \033[33m\033[1m2.本班成绩查询\033[0m                      ***\n"
                    "***                    \033[33m\033[1m3.成绩分析\033[0m                          ***\n"
                    "***                    \033[33m\033[1m4.成绩申诉\033[0m                          ***\n"
                    "***                    \033[33m\033[1m5.返回上一层\033[0m                        ***\n"
                    "***                    \033[33m\033[1m0.退出\033[0m                              ***\n");
        choice = SafeScanf(0, 5);
        switch (choice) {
        case 1:
            FindStuScore(head, username);
            break;
        case 2:
            SortStuInfo(head);
            break;
        case 3:
            ScoreAnaly(head, username);
            break;
        case 4:
            GradeAppeal(head, username, scoreList);
            break;
        case 5:
            choice = 0;
            break;
        case 0:
            WriteStuToFile(head, username);
            WriteScoreToFile(scoreList);
            exit(0);
        default:
            //printf("输入错误，请重新输入。\n");
            Wait();
            break;
        }
    } while (choice);

    WriteStuToFile(head, username);
    WriteScoreToFile(scoreList);

}
void TeacherMenu(ListNode* head, char* username, ScoreList* scoreList) {
    //int c;
    //while ((c = getchar()) != '\n' && c != EOF);

    int choice = 0;
    ReadStuFromFile(head, username);
    ReadScoreListFromFile(scoreList);

    do {
        DisplayMenu("***                    \033[33m\033[1m1.添加学生信息\033[0m                      ***\n"
                    "***                    \033[33m\033[1m2.删除学生信息\033[0m                      ***\n"
                    "***                    \033[33m\033[1m3.修改学生信息\033[0m                      ***\n"
                    "***                    \033[33m\033[1m4.查询学生信息\033[0m                      ***\n"
                    "***                    \033[33m\033[1m5.输出学生信息\033[0m                      ***\n"
                    "***                    \033[33m\033[1m6.下载学生信息\033[0m                      ***\n"
                    "***                    \033[33m\033[1m7.学生成绩分析\033[0m                      ***\n"
                    "***                    \033[33m\033[1m8.成绩申诉    \033[0m                      ***\n"
                    "***                    \033[33m\033[1m9.返回上一层  \033[0m                      ***\n"
                    "***                    \033[33m\033[1m0.退出        \033[0m                      ***\n");
        choice = SafeScanf(0, 9);

        switch (choice) {
        case 1:
            AddStuInfo(head);
            Wait();
            break;
        case 2:
            DelStuInfo(head);
            break;
        case 3:
            ModifyStuInfo(head);
            break;
        case 4:
            FindStuInfo(head);
            break;
        case 5:
            SortStuInfo(head);
            break;
        case 6:
            DownloadStuInfo(head);
            break;
        case 7:
            TeacherScoreAnaly(head);
            break;
        case 8:
            GradeUpdate(scoreList);
            break;
        case 9:
            choice = 0;
            break;
        case 0:
            WriteStuToFile(head, username);
            WriteScoreToFile(scoreList);
            exit(0);
        default:
            //printf("输入错误，请重新输入。\n");
            break;
        }
    } while (choice);
    WriteStuToFile(head, username);
    WriteScoreToFile(scoreList);

}
void AdminMenu(ListNode* head, UserList* userList, TodoList* todoList,ScoreList* scoreList) {
    //int c;
    //while ((c = getchar()) != '\n' && c != EOF);

    int choice = 0;
    char username[MAX_USERNAME];

    ReadTodoListFromFile(todoList);

    do {
        DisplayMenu("***                    \033[33m\033[1m1. 查看代办            \033[0m             ***\n"
                    "***                    \033[33m\033[1m2. 进入教师端修改      \033[0m             ***\n"
                    "***                    \033[33m\033[1m3. 增加账号及密码      \033[0m             ***\n"
                    "***                    \033[33m\033[1m4. 删除账户及密码      \033[0m             ***\n"
                    "***                    \033[33m\033[1m5. 修改账户及密码      \033[0m             ***\n"
                    "***                    \033[33m\033[1m6. 查询账户及密码      \033[0m             ***\n"
                    "***                    \033[33m\033[1m7. 录入所有账户及密码  \033[0m             ***\n"
                    "***                    \033[33m\033[1m8. 输出所有账户及密码  \033[0m             ***\n"
                    "***                    \033[33m\033[1m9. 手动重新录入学生信息\033[0m             ***\n"
                    "***                    \033[33m\033[1m10.返回上一层          \033[0m             ***\n"
                    "***                    \033[33m\033[1m0. 退出                \033[0m             ***\n");
        choice = SafeScanf(0, 10);
        switch (choice) {
        case 1:
            ViewTodo(todoList);
            break;
        case 2:
            system("cls");
            printf("\033[33m\033[1m请输入(1-5)选择班级或输入(0)返回:\033[0m ");
            char ch;
            scanf(" %c", &ch);
            if (ch >= '1' && ch <= '5') {
                username[0] = '0';
                username[1] = ch;
                username[2] = '\0'; 
            } else {
                printf("\033[33m\033[1m输入错误\033[0m\n");
                Wait();
                break;
            }
            TeacherMenu(head, username, todoList);
            break;
        case 3:
            AddUserInfo(userList);
            break;
        case 4:
            DeleteUserInfo(userList);
            break;
        case 5:
            ModifyUserInfo(userList);
            break;
        case 6:
            FindUserInfo(userList);
            break;
        case 7:
            //新班级初始化账户密码
            InitialClassFromFile(head, userList);
            break;
        case 8:
            DisplayUserInfo(userList);
            break;
        case 9:
            ReEnterStuInfo(head);
            break;
        case 10:
            WriteUserToFile(userList);
            WriteTodoToFile(todoList);
            return;
        case 0:
            WriteUserToFile(userList);
            WriteTodoToFile(todoList);
            exit(0);
        default:
            //printf("输入错误，请重新输入。\n");
            break;

        }
    } while (choice);
    WriteUserToFile(userList);
    WriteTodoToFile(todoList);

}
void LoginMenu(ListNode* head, UserList* userList, TodoList* todoList, ScoreList* scoreList, char username[MAX_USERNAME]) {
    int choice = 0;
    system("cls");
    printf("\033[33m\033[1m请输入登录账户:\033[0m ");
    SafeFgets(username, sizeof(username));

    choice = UserLog(head, username);

    switch (choice) {
    case 1:
        StudentMenu(head, username, scoreList);
        break;
    case 2:
        TeacherMenu(head, username, scoreList);
        break;
    case 3:
        AdminMenu(head, userList, todoList, scoreList);
        break;
    default:
        break;
    }
}

void Wait() {
    //Sleep(1000);
    printf("\033[33m\033[1m按任意键继续...\033[0m");
    getch(); 
}
int SafeScanf(int min, int max) {
    wchar_t inputBuffer[100];
    int index = 0;

    while (1) {
        if (index >= sizeof(inputBuffer) / sizeof(wchar_t) - 1) {
            wprintf(L"输入过长，请重新输入介于 %d 到 %d 之间的整数:\n", min, max);
            return -1;
        }

        wint_t ch = getwchar();
        if (ch == L'\n' || ch == L'\r') {
            inputBuffer[index] = L'\0';
            break;
        }
        else {
            inputBuffer[index++] = ch;
        }
    }

    if (!iswdigit(inputBuffer[0]) && inputBuffer[0] != L'-') {
        wprintf(L"请输入介于 %d 到 %d 之间的整数:\n", min, max);
        return -1;
    }

    int ret = wcstol(inputBuffer, NULL, 10);

    if (ret < min || ret > max) {
        wprintf(L"请输入介于 %d 到 %d 之间的整数:\n", min, max);
        return -1;
    }
    else {
        return ret;
    }
}
void SafeFgets(char* buffer, size_t bufferSize) {
    // 检查传入的指针和大小是否有效
    if (buffer == NULL || bufferSize == 0) {
        fprintf(stderr, "Invalid buffer or bufferSize provided.\n");
        return;
    }
    if (fgets(buffer, bufferSize, stdin) != NULL) {
        // 移除末尾的换行符，保证字符串以空字符结尾
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
    else {
        // 读取失败，输出错误信息
        fprintf(stderr, "Error reading input.\n");
    }
}
void HidePasswd(char* passwd) {
    char c;
    int i = 0;
    int maxLength = 15;
    while ((c = _getch()) != '\r') {
        if (isprint(c) && !iswalpha(c) && i < maxLength) {
            passwd[i++] = c;
            putchar('*');
        }
        else if (i > 0 && c == '\b') {
            --i;
            putchar('\b');
            putchar(' ');
            putchar('\b');
        }
    }

    if (i > 0) {
        putchar('\n');
    }

    passwd[i] = '\0';
}

//文件输入（从文件中读取）
void ReadStuFromFile(ListNode* head, const char* username) {
    //根据账号前两位打开对应班级文件
    int flag = username[1];
    char fileName[100];
    switch (flag) {
    case '1':
        strcpy(fileName, "E:\\student management system\\class1.txt");
        break;
    case '2':
        strcpy(fileName, "E:\\student management system\\class2.txt");
        break;
    case '3':
        strcpy(fileName, "E:\\student management system\\class3.txt");
        break;
    case '4':
        strcpy(fileName, "E:\\student management system\\class4.txt");
        break;
    case '5':
        strcpy(fileName, "E:\\student management system\\class5.txt");
        break;
    default:
        fprintf(stderr, "Class recognition error\n");
        return;
    }    
    FILE* pf = fopen(fileName, "r");
    if (pf == NULL) {
        perror("无法打开文件");
        return;
    }

    ListNode st;
    ListNode* pre = head;
    memset(&st, 0, sizeof(ListNode));

    while (fscanf(pf, "%s %s %s %d %d %d", st.name, st.id, st.class, &st.score1, &st.score2, &st.score3) == 6) {
        ListNode* cur = (ListNode*)malloc(sizeof(ListNode));
        if (cur == NULL) {
            perror("内存分配失败");
            fclose(pf);
            return;
        }

        strcpy(cur->name, st.name);
        strcpy(cur->class, st.class);
        strcpy(cur->id, st.id);
        cur->score1 = st.score1;
        cur->score2 = st.score2;
        cur->score3 = st.score3;

        cur->next = NULL;
        cur->pre = pre;

        pre->next = cur;
        pre = cur;
    }
    fclose(pf);
    return;
}
void ReadUserFromFile(UserList* userList) {
    FILE* pf = fopen("AccountInfo.txt", "r");
    if (pf == NULL) {
        perror("无法打开文件");
        return; 
    }

    UserList st;
    UserList* pre = userList;

    while (fscanf(pf, "%s %s %c", st.username, st.password, &st.role) == 3) {
        UserList* cur = (UserList*)malloc(sizeof(UserList));
        if (cur == NULL) {
            perror("内存分配失败");
            fclose(pf);
            return; 
        }
        strcpy(cur->username, st.username);
        strcpy(cur->password, st.password);
        cur->role = st.role;

        cur->next = NULL;
        cur->pre = pre;

        pre->next = cur;
        pre = cur;
    }

    fclose(pf);
    return;
}
void ReadTodoListFromFile(TodoList* todoList) {
    FILE* pf = fopen("TodoInfo.txt", "r");
    if (pf == NULL) {
        perror("无法打开文件");
        return;
    }

    TodoList st;
    TodoList* pre = todoList;

    while (fscanf(pf, "%s %499[^\n]", st.username, st.des) == 2) {
        TodoList* cur = (TodoList*)malloc(sizeof(TodoList));
        if (cur == NULL) {
            perror("内存分配失败");
            fclose(pf);
            return;
        }

        strcpy(cur->username, st.username);
        strcpy(cur->des, st.des);

        cur->next = NULL;
        cur->pre = pre;

        pre->next = cur;
        pre = cur;
    }

    fclose(pf);
}
void ReadScoreListFromFile(ScoreList* scoreList) {
    FILE* pf = fopen("ScoreInfo.txt", "r");
    if (pf == NULL) {
        perror("无法打开文件");
        return;
    }

    ScoreList st;
    ScoreList* pre = scoreList;

    while (fscanf(pf, "%s %d %d %s", st.username, &st.flag, &st.score, st.des) == 4) {
        ScoreList* cur = (ScoreList*)malloc(sizeof(ScoreList));
        if (cur == NULL) {
            perror("内存分配失败");
            fclose(pf);
            return;
        }

        strcpy(cur->username, st.username);
        cur->flag = st.flag;
        cur->score = st.score;
        strcpy(cur->des, st.des);

        cur->next = NULL;
        cur->pre = pre;

        pre->next = cur;
        pre = cur;
    }

    fclose(pf);
}

//文件写入
void WriteStuToFile(ListNode* head, const char* username) {
    int flag = username[1];
    char fileName[100];
    switch (flag) {
    case '1':
        strcpy(fileName, "E:\\student management system\\class1.txt");
        break;
    case '2':
        strcpy(fileName, "E:\\student management system\\class2.txt");
        break;
    case '3':
        strcpy(fileName, "E:\\student management system\\class3.txt");
        break;
    case '4':
        strcpy(fileName, "E:\\student management system\\class4.txt");
        break;
    case '5':
        strcpy(fileName, "E:\\student management system\\class5.txt");
        break;
    default:
        fprintf(stderr, "Class recognition error\n");
        return;
    }

    FILE* pf = fopen(fileName, "w");
    if (pf == NULL) {
        perror("无法打开文件进行写入");
        return;
    }

    ListNode* cur = head->next;
    while (cur != NULL) {
        fprintf(pf, "%s %s %s %d %d %d\n", cur->name, cur->id, cur->class, cur->score1, cur->score2, cur->score3);
        cur = cur->next;
    }

    fclose(pf);
}
void WriteUserToFile(UserList* userList) {
    FILE* pf = fopen("AccountInfo.txt", "w");
    if (pf == NULL) {
        perror("无法打开文件进行写入");
        return;
    }

    UserList* cur = userList->next;
    while (cur != NULL) {
        fprintf(pf, "%s %s %c\n", cur->username, cur->password, cur->role);
        cur = cur->next;
    }

    fclose(pf);
}
void WriteTodoToFile(TodoList* todoList) {
    FILE* pf = fopen("TodoInfo.txt", "w");
    if (pf == NULL) {
        perror("无法打开文件进行写入");
        return;
    }

    TodoList* cur = todoList->next;
    while (cur != NULL) {
        fprintf(pf, "%s %s\n", cur->username, cur->des);
        cur = cur->next;
    }

    fclose(pf);
}
void WriteScoreToFile(ScoreList* scoreList) {
    FILE* pf = fopen("ScoreInfo.txt", "w");
    if (pf == NULL) {
        perror("无法打开文件进行写入");
        return;
    }

    ScoreList* cur = scoreList->next;
    while (cur != NULL) {
        fprintf(pf, "%s %d %d %s\n", cur->username, cur->flag, cur->score, cur->des);
        cur = cur->next;
    }

    fclose(pf);
}


//内存释放
void FreeListNode(ListNode* head) {
    ListNode* current = head->next;
    ListNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    head->next = NULL;
}
void FreeUserList(UserList* userList) {
    UserList* current = userList->next;
    UserList* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    userList->next = NULL;
}
void FreeTodoList(TodoList* todoList) {
    TodoList* current = todoList->next;
    TodoList* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    todoList->next = NULL;
}
void FreeScoreList(ScoreList* scoreList) {
    ScoreList* cur = scoreList->next;
    ScoreList* next;

    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }

    scoreList->next = NULL;
}


//登录操作

    //识别身份
int Authenticate(const char* username, const char* password, char* role) {
    FILE* file = fopen("AccountInfo.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0; 
    }

    char fileUsername[MAX_USERNAME];
    char filePassword[MAX_PASSWORD];
    while (fscanf(file, "%s %s %c", fileUsername, filePassword, role) == 3) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
int UserLog(ListNode* head, const char* username) {
    char password[MAX_PASSWORD];
    printf("\033[33m\033[1m请输入登录密码: \033[0m");
    HidePasswd(password);
    char role;
    int flag = Authenticate(username, password, &role);

    if (flag) {
        if (role == 'S') {
;            return 1;
        } else if (role == 'T') {
            return 2;
        } else if (role == 'A') {
            return 3;
        }
    } else {
        system("cls");
        printf("\033[33m\033[1m账户密码存在问题，请检查重试\033[0m\n");
        Wait();
    }        

    return 0;
}
    //密码注册：账号存在，找到身份，修改密码
void UpdatePassword(UserList* userList, TodoList* todoList) {
    system("cls");
    if (userList->next == NULL) {
        printf("无账密信息。\n");
        Wait();
    }
    printf("请输入您的账号：");
    UserList* cur = userList->next;
    char username[MAX_USERNAME];
    SafeFgets(username, sizeof(username));
    while (cur != NULL && strcmp(username, cur->username) != 0) {
        cur = cur->next;
    }
    if (cur == NULL) {
        system("cls");
        printf("找不到用户：%s\n", username);
        Wait();
        return;
    }
    if (strcmp(cur->password, "123456") != 0 ) {
        system("cls");
        printf("您的密码已修改，忘记请前往密码找回功能\n");
        Wait();
        return;
    }
    char password[MAX_PASSWORD];
    system("cls");
    printf("请输入新密码: ");
    HidePasswd(password);
    strcpy(cur->password, password);

    system("cls");
    printf("密码注册成功\n");

    TodoList* cur1 = todoList;
    while (cur1->next != NULL) {
        cur1 = cur1->next;
    }

    TodoList* NewTodo = (TodoList*)malloc(sizeof(TodoList));

    strcpy(NewTodo->username, cur->username);
    sprintf(NewTodo->des, "申请密码注册为:%s", cur->password);

    cur1->next = NewTodo;
    NewTodo->pre = cur1;
    NewTodo->next = NULL;

    Wait();
}
    //密码修改
void ChangePassword(UserList* userList, TodoList* todoList) {
    system("cls");
    if (userList->next == NULL) {
        printf("无账密信息。\n");
        Wait();
        return;
    }

    printf("请输入您的账号：");
    UserList* cur = userList->next;
    char username[MAX_USERNAME];
    SafeFgets(username, sizeof(username));

    printf("请输入您的密码：");
    char password[MAX_USERNAME];
    HidePasswd(password);

    while (cur != NULL && (strcmp(username, cur->username) != 0 || strcmp(password, cur->password) != 0)) {
        cur = cur->next;
    }
    if (cur == NULL) {
        system("cls");
        printf("找不到您的账户或密码错误\n");
        Wait();
        return;
    }

    printf("请输入您的新密码: ");
    HidePasswd(password);
    strcpy(cur->password, password);
    system("cls");
    printf("密码修改成功\n");

    TodoList* cur1 = todoList;
    while (cur1->next != NULL) {
        cur1 = cur1->next;
    }

    TodoList* NewTodo = (TodoList*)malloc(sizeof(TodoList));

    strcpy(NewTodo->username, cur->username);
    sprintf(NewTodo->des, "申请密码修改为:%s", cur->password);

    cur1->next = NewTodo;
    NewTodo->pre = cur1;
    NewTodo->next = NULL;

    Wait();
}
    //密码找回
void RecoverPassword(UserList* userList, ListNode* head, TodoList* todoList) {
    system("cls");
    if (userList->next == NULL) {
        printf("无账密信息。\n");
        Wait();
        return;
    }
    printf("请输入您的账号：");
    char username[MAX_USERNAME];
    SafeFgets(username, sizeof(username));;

    printf("请输入您的姓名：");
    char name[MAX_NAME];
    SafeFgets(name, sizeof(name));

    ReadStuFromFile(head, username);
    ListNode* cur1 = head->next;

    while (cur1 != NULL && (strcmp(cur1->id, username) != 0 || strcmp(cur1->name, name) != 0)) {
        cur1 = cur1->next;
    }
    system("cls");
    if (cur1 == NULL) {
        printf("姓名账号不匹配，请重试。\n");
        Wait();
        return;
    }

    UserList* cur = userList->next;
    while (cur != NULL && (strcmp(cur->username, cur1->id) != 0)) {
        cur = cur->next;
    }
    if (cur == NULL) {
        system("cls");
        printf("找不到用户：%s\n", username);
        Wait();
        return;
    }

    char newPassword[MAX_PASSWORD];
    printf("请输入新密码: ");
    HidePasswd(newPassword);

    system("cls");

    strcpy(cur->password, newPassword);

    printf("密码已重置成功\n");

    TodoList* cur2 = todoList;
    while (cur2->next != NULL) {
        cur2 = cur2->next;
    }

    TodoList* NewTodo = (TodoList*)malloc(sizeof(TodoList));

    strcpy(NewTodo->username, cur->username);
    sprintf(NewTodo->des, "申请密码重置为:%s", cur->password);

    cur2->next = NewTodo;
    NewTodo->pre = cur1;
    NewTodo->next = NULL;

    Wait();
}


//学生端

    //查询个人成绩
void FindStuScore(ListNode* head, char* username) {
    system("cls");
    if (head->next == NULL) {
        printf("无成绩信息\n");
        return;
    }
    char id[MAX_ID];
    strcpy(id, username);
    ListNode* cur = FindStuById(head, id);
    if (cur != NULL) {
        printf("*************************************************************\n");
        printf("%-5s\t%-5s\t%-5s\t %s %s %s\n", "姓名", "学号", "班级", "语文成绩", "数学成绩", "英语成绩");
        printf("%-6s\t%-6s\t%-10s%-6d    %-6d    %-6d\n", cur->name, cur->id, cur->class,
            cur->score1, cur->score2, cur->score3);
        printf("*************************************************************\n");
        Wait();
    } else {
        printf("未找到您的信息\n");
        Wait();
    }
    return;
}
    //成绩分析
int ScoreRank(ListNode* head, char* username) {
    int rank = 1; 

    ListNode* cur = head->next; 
    while (cur != NULL) {
        if (strcmp(cur->id, username) == 0) {
            return rank;
        }
        cur = cur->next;
        rank++;
    }

    return -1;
}
void ScoreAnaly(ListNode* head, char* username) {
    int rank = 1;
    system("cls");

    SelectionSort(head->next, 1, 1);
    rank = ScoreRank(head, username);
    printf("\033[34m\033[1m语文成绩排名：第 %d 名\033[0m\n", rank);
    if (rank <= 10) {
        printf("\033[34m\033[1m成绩分析：你在语文方面表现非常出色，继续保持好成绩！\033[0m\n");
    }
    else if (rank <= 20) {
        printf("\033[34m\033[1m成绩分析：在语文方面表现不错，继续努力提高！\033[0m\n");
    }
    else {
        printf("\033[34m\033[1m成绩分析：在语文方面还有提升空间，多加练习和阅读。\033[0m\n");
    }

    SelectionSort(head->next, 2, 1);
    rank = ScoreRank(head, username);
    printf("\n\033[34m\033[1m数学成绩排名：第 %d 名\033[0m\n", rank);
    if (rank <= 10) {
        printf("\033[34m\033[1m成绩分析：你在数学方面表现非常出色，继续保持好成绩！\033[0m\n");
    }
    else if (rank <= 20) {
        printf("\033[34m\033[1m成绩分析：在数学方面表现不错，继续努力提高！\033[0m\n");
    }
    else {
        printf("\033[34m\033[1m成绩分析：在数学方面还有提升空间，多加练习和思考。\033[0m\n");
    }

    SelectionSort(head->next, 3, 1);
    rank = ScoreRank(head, username);
    printf("\n\033[34m\033[1m英语成绩排名：第 %d 名\033[0m\n", rank);
    if (rank <= 10) {
        printf("\033[34m\033[1m成绩分析：你在英语方面表现非常出色，继续保持好成绩！\033[0m\n");
    }
    else if (rank <= 20) {
        printf("\033[34m\033[1m成绩分析：在英语方面表现不错，继续努力提高！\033[0m\n");
    }
    else {
        printf("\033[34m\033[1m成绩分析：在英语方面还有提升空间，多加练习和积累词汇。\033[0m\n");
    }

    SelectionSort(head->next, 4, 1);
    rank = ScoreRank(head, username);
    printf("\n\033[34m\033[1m总成绩排名：第 %d 名\033[0m\n", rank);
    if (rank <= 10) {
        printf("\033[34m\033[1m成绩分析：你的总成绩非常优秀，继续保持好成绩！\033[0m\n\n");
    }
    else if (rank <= 20) {
        printf("\033[34m\033[1m成绩分析：总成绩表现不错，继续保持努力！\033[0m\n\n");
    }
    else {
        printf("\033[34m\033[1m成绩分析：总成绩还有提升空间，多加练习和全面提高。\033[0m\n\n");
    }

    Wait();
}
    //成绩申诉
void GradeAppeal(ListNode* head, char* username, ScoreList* scoreList) {
    system("cls");
    ListNode* cur = FindStuById(head, username);
    printf("**************************************************************\n");
    printf("***  \033[33m\033[1m姓名   学号    班级    语文成绩  数学成绩  英语成绩\033[0m   ***\n");
    printf("***\033[33m\033[1m %-6s  %-6s %-10s  %-6d    %-6d    %-6d \033[0m ***\n",cur->name, cur->id, cur->class,cur->score1, cur->score2, cur->score3);
    printf("**************************************************************\n");
    printf("***         \033[33m\033[1m您的成绩如上，请选择要申诉的科目：\033[0m             ***\n");
    printf("***         \033[33m\033[1m            1.语文                \033[0m             ***\n");
    printf("***         \033[33m\033[1m            2.数学                \033[0m             ***\n");
    printf("***         \033[33m\033[1m            3.英语                \033[0m             ***\n");
    printf("***         \033[33m\033[1m            0.返回                \033[0m             ***\n");
    printf("**************************************************************\n");
    printf("**************************************************************\n");

    int choice = 0;
    char buffer[MAX_DES];
    int score = 0;

    choice = SafeScanf(0, 3);

    if (choice != 0 && choice != 1 && choice != 2 && choice != 3) {
        system("cls");
        printf("选择错误\n");
        Wait();
        return;
    } else if (choice == 0) {
        return;
    }

    system("cls");    
    printf("\033[33m\033[1m请输入您申诉后的成绩：\033[0m");
    scanf("%d", &score);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    system("cls");
    printf("\033[33m\033[1m请输入您申诉的申诉原因：\033[0m");
    SafeFgets(buffer, sizeof(buffer));

    ScoreList* cur1 = scoreList;
    while (cur1->next != NULL) {
        cur1 = cur1->next;
    }

    ScoreList* node = (ScoreList*)malloc(sizeof(ScoreList));
    if (node == NULL) {
        fprintf(stderr, "内存分配失败\n");
        exit(EXIT_FAILURE);
    }

    strcpy(node->username, username);
    node->flag = choice;
    node->score = score;
    strcpy(node->des, buffer);

    cur1->next = node;
    node->pre = cur1;
    node->next = NULL;


    system("cls");
    printf("申诉成功\n");
    Wait();

}
 

//教师端

    //通过学号查找
ListNode* FindStuById(ListNode* head, const char* id) {
    ListNode* cur = head->next;

    while (cur != NULL) {
        if (strcmp(cur->id, id) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}
    //通过姓名查找
ListNode* FindStuByName(ListNode* head, const char* name) {
    ListNode* cur = head->next;

    while (cur != NULL) {

        if (strcmp(cur->name, name) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}
    //添加学生信息
void AddStuInfo(ListNode* head) {
    ListNode* cur = head;
    ListNode* newStudent = (ListNode*)malloc(sizeof(ListNode));

    if (newStudent == NULL) {
        system("cls");
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    system("cls");
    printf("请输入学生姓名:\n");
    scanf("%s", newStudent->name);
    printf("请输入学生学号:\n");
    scanf("%s", newStudent->id);
    printf("请输入班级:\n");
    scanf("%s", newStudent->class);
    printf("请输入学生语文成绩:\n");
    scanf("%d", &newStudent->score1);
    printf("请输入学生数学成绩:\n");
    scanf("%d", &newStudent->score2);
    printf("请输入学生英语成绩:\n");
    scanf("%d", &newStudent->score3);

    newStudent->next = cur->next;
    newStudent->pre = cur;
    cur->next = newStudent;

    system("cls");
    printf("姓名为 %s 的学生信息已录入\n", newStudent->name);

}
    //删除学生信息
void DelStuInfo(ListNode* head) {
    if (head->next == NULL) {
        system("cls");
        printf("无学生信息\n");
        Wait();
        return;
    }
    int choice = 0;
    if (head->next == NULL) {
        printf("学生信息已全部删除\n");
        return;
    }
    system("cls");
    printf("请选择删除方式:\n");
    printf("1.按学号删除\n");
    printf("2.按姓名删除\n");
    printf("0.退出\n");
    choice = SafeScanf(0, 2);

    switch (choice) {
    case 1:
        system("cls");
        printf("请输入要删除的学生学号: ");
        char id[MAX_ID];
        scanf("%s", id);
        ListNode* cur1 = FindStuById(head, id);
        if (cur1 == NULL) {
            printf("未找到学号为 %s 的学生\n", id);
            Wait();
            
        } else if (cur1->next == NULL) {
            cur1->pre->next = NULL;
            free(cur1);
            printf("学号为 %s 的学生已删除\n", id);
            Wait();
        } else if (cur1->next != NULL) {
            cur1->pre->next = cur1->next;
            cur1->next->pre = cur1->pre;
            free(cur1);
            printf("学号为 %s 的学生已删除\n", id);
            Wait();
        }
        break;

    case 2:
        system("cls");
        printf("请输入要删除的学生姓名: ");
        char name[MAX_NAME];
        scanf("%s", name);
        ListNode* cur2 = FindStuByName(head, name);
        if (cur2 == NULL) {
            printf("未找到姓名为 %s 的学生\n", name);
            Wait();
        }
        else if (cur2->next == NULL) {
            cur2->pre->next = NULL;
            free(cur2);
            printf("姓名 %s 的学生已删除\n", name);
            Wait();
        }
        else if(cur2->next != NULL){
                            cur2->pre->next = cur2->next;
            cur2->next->pre = cur2->pre;
            free(cur2);
            printf("姓名为 %s 的学生已删除\n", name);
            Wait();

        }
        break;

    case 0:
        break;
    default:
        printf("输入错误\n");
        Wait();
        break;
    }
    return;
}
    //修改学生信息
void ModifyStuInfo(ListNode* head) {
    if (head->next == NULL) {
        system("cls");
        printf("无学生信息\n");
        Wait();
        return;
    }

    int choice = 1;
    char id[MAX_ID];
    char name[MAX_NAME];
    ListNode* cur = head->next;

    do {
        system("cls");
        printf("请选择查询方式:\n");
        printf("1.按学号查询\n");
        printf("2.按姓名查询\n");
        printf("0.退出\n");
        choice = SafeScanf(0, 2);

        switch (choice) {
        case 1:
            system("cls");
            printf("请输入要修改的学生学号:\n");
            scanf("%s", id);
            ListNode* cur1 = FindStuById(head, id);
            if (cur1) {
                Mod(cur1);
            } else {
                system("cls");
                printf("未找到学号为 %s 的学生\n", id);
                Wait();
            }
            break;
        case 2:
            system("cls");
            printf("请输入要修改的学生姓名:\n");
            scanf("%s", name);
            ListNode* cur2 = FindStuByName(head, name);
            if (cur2) {
                Mod(cur2);
            } else {
                system("cls");
                printf("未找到姓名为 %s 的学生\n", name);
                Wait();
            }
            break;
        case 0:
            break;
        default:
            system("cls");
            printf("输入错误，请重新输入\n");
            Wait();
            break;
        }
    } while (choice);
    return;     
}
void Mod(ListNode* cur) {
    int choice = 1;
    char newString[MAX_NAME];
    int new = 0;
    do {
        system("cls");
        printf("*************************************************************\n");
        printf(" \033[33m\033[1m%-5s\t%-5s\t%-5s\t %s %s %s\n\033[0m", "姓名", "学号", "班级", "语文成绩", "数学成绩", "英语成绩");
        printf("\033[33m\033[1m%-6s\t%-6s\t%-10s%-6d    %-6d    %-6d\033[0m\n", cur->name, cur->id, cur->class,
                                                          cur->score1, cur->score2, cur->score3);
        printf("*************************************************************\n");
        printf("\033[33m\033[1m该学生信息如上，请选择要修改的信息\033[0m\n");
        printf("\033[33m\033[1m1.姓名 2.学号 3.班级 4.语文成绩 5.数学成绩 6.英语成绩 0.返回上一层\033[0m\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        choice = SafeScanf(0, 6);

        switch (choice) {
        case 1:
            system("cls");
            printf("请输入新的姓名：\n");
            scanf("%s", newString);
            strcpy(cur->name, newString);
            system("cls");
            printf("修改成功\n");
            Wait();
            break;
        case 2:
            system("cls");
            printf("请输入新的学号：\n");
            scanf("%s", newString);
            strcpy(cur->id, newString);
            system("cls");
            printf("修改成功\n");
            Wait();
            break;
        case 3:
            system("cls");
            printf("请输入新的班级：\n");
            scanf("%s", newString);
            strcpy(cur->class, newString);
            system("cls");
            printf("修改成功\n");
            Wait();
            break;
        case 4:
            system("cls");
            printf("请输入新的语文成绩：\n");
            scanf("%d", &new);
            cur->score1 = new;
            system("cls");
            printf("修改成功\n");
            Wait();
            break;
        case 5:
            system("cls");
            printf("请输入新的数学成绩：\n");
            scanf("%d", &new);
            cur->score2 = new;
            system("cls");
            printf("修改成功\n");
            Wait();
            break;
        case 6:
            system("cls");
            printf("请输入新的英语成绩：\n");
            scanf("%d", &new);
            cur->score3 = new;
            system("cls");
            printf("修改成功\n");
            Wait();
            break;
        case 0:
            break;
        default:
            printf("输入错误\n");
            Wait();
            break;
        }
    }while (choice);
}
    //查询学生信息
void FindStuInfo(ListNode* head) {
        if (head->next == NULL) {
            printf("无学生信息\n");
            Wait();
            return;
        }
        int choice;
        do {
            system("cls");
            printf("请选择查询方式:\n");
            printf("1.按学号查询\n");
            printf("2.按姓名查询\n");
            printf("0.退出\n");

            choice = SafeScanf(0, 2);

            switch (choice) {
                case 1:
                    system("cls");
                    printf("请输入要查询的学生学号: ");
                    char id[MAX_ID];
                    scanf("%s", id);
                    ListNode* cur1 = FindStuById(head, id);
                    if (cur1 != NULL) {
                        system("cls");
                        printf("*************************************************************\n");
                        printf("\033[33m\033[1m%-5s\t%-5s\t%-5s\t %s %s %s\n\033[0m", "姓名", "学号", "班级", "语文成绩", "数学成绩", "英语成绩");
                        printf("\033[33m\033[1m%-6s\t%-6s\t%-10s%-6d    %-6d    %-6d\n\033[0m", cur1->name, cur1->id, cur1->class,
                            cur1->score1, cur1->score2, cur1->score3);
                        printf("*************************************************************\n");
                        Wait();
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                    }
                    else {
                        system("cls");
                        printf("未找到学号为 %s 的学生\n", id);
                        Wait();                        
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                    }
                    break;
    
                case 2:
                    system("cls");
                    printf("请输入要查询的学生姓名: ");
                    char name[MAX_NAME];
                    scanf("%s", name);
                    ListNode* cur2 = FindStuByName(head, name);
                    if (cur2 != NULL) {
                        system("cls");
                        printf("*************************************************************\n");
                        printf("\033[33m\033[1m%-5s\t%-5s\t%-5s\t %s %s %s\n\033[0m", "姓名", "学号", "班级", "语文成绩", "数学成绩", "英语成绩");
                        printf("\033[33m\033[1m%-6s\t%-6s\t%-10s%-6d    %-6d    %-6d\n\033[0m", cur2->name, cur2->id, cur2->class,
                            cur2->score1, cur2->score2, cur2->score3);
                        printf("*************************************************************\n");
                        Wait();
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                    }
                    else {
                        system("cls");
                        printf("未找到姓名为 %s 的学生\n", name);
                        Wait();
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                    }
                    break;
                case 0:
                    break;
                default:
                    system("cls");
                    printf("输入错误，请重新输入\n");
                    Wait();
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
            }
        } while (choice);
        return;
}
    //输出学生信息
void DisplayStuInfo(const ListNode* head) {
    system("cls");
    if (head->next == NULL) {
        printf("无学生信息\n");
        Wait();
        return;
    }
    ListNode* cur = head->next;
    printf("**************************************************************\n");
    printf("***                 \033[33m\033[1m欢迎进入学生管理系统\033[0m                   ***\n");
    printf("**************************************************************\n");
    printf("**************************************************************\n");
    printf("***  \033[33m\033[1m姓名   学号    班级    语文成绩  数学成绩  英语成绩\033[0m   ***\n");
    while (cur) {
        printf("*** \033[33m\033[1m%-6s  %-6s %-10s  %-6d    %-6d    %-6d\033[0m  ***\n", cur->name, cur->id, cur->class,
                                                          cur->score1, cur->score2, cur->score3);
        cur = cur->next;
    }
    printf("**************************************************************\n");
    printf("**************************************************************\n");
    Wait();
}
    //下载学生信息
void DownloadStuInfo(ListNode* head) {
    system("cls");
    FILE* pf = fopen("student_ingormation.txt", "w");
    if (pf == NULL) {
        perror("无法打开文件进行写入");
        return;
    }

    ListNode* cur = head->next;
    while (cur != NULL) {
        fprintf(pf, "%s %s %s %d %d %d\n", cur->name, cur->id, cur->class, cur->score1, cur->score2, cur->score3);
        cur = cur->next;
    }
    fclose(pf);
    printf("\033[33m\033[1m学生信息已下载至 'student_information.txt'\033[0m\n");
    Wait();
}
    //学生成绩分析
void AverageScores(ListNode* head) {
    if (head == NULL) {
        printf("链表为空\n");
        return;
    }

    double totalChinese = 0, totalMath = 0, totalEnglish = 0;
    int studentCount = 0;

    // 遍历链表计算总分
    ListNode* current = head;
    while (current != NULL) {
        // 计算各科总分
        totalChinese += current->score1;
        totalMath += current->score2;
        totalEnglish += current->score3;

        studentCount++;

        current = current->next;
    }

    double averageChinese = totalChinese / studentCount;
    double averageMath = totalMath / studentCount;
    double averageEnglish = totalEnglish / studentCount;
    
    system("cls");
    printf("\033[32m\033[1m成绩分析：\033[0m\n\n");

    printf("\033[32m\033[1m语文平均分：%.2lf\033[0m\n", averageChinese);
    if (averageChinese >= 80) {
        printf("\033[32m\033[1m本班语文表现较好，继续保持！\n\033[0m\n");
    } else {
        printf("\033[32m\033[1m本班语文有待提高，建议加强相关练习。\n\033[0m\n");
    }

    printf("\033[32m\033[1m数学平均分：%.2lf\033[0m\n", averageMath);
    if (averageMath >= 80) {
        printf("\033[32m\033[1m本班数学表现较好，继续保持！\033[0m\n\n");
    } else {
        printf("\033[32m\033[1m本班数学有待提高，建议加强相关练习。\033[0m\n\n");
    }

    printf("\033[32m\033[1m英语平均分：%.2lf\033[0m\n", averageEnglish);
    if (averageEnglish >= 80) {
        printf("\033[32m\033[1m本班英语表现较好，继续保持！\033[0m\n");
    } else {
        printf("\033[32m\033[1m本班英语有待提高，建议加强相关练习。\033[0m\n");
    }
}
void TeacherScoreAnaly(ListNode* head) {
    system("cls");

    SelectionSort(head->next, 1, 1);
    printf("\033[32m\033[1m语文成绩排名前十的学生：\033[0m\n");
    PrintTopStudents(head, 1, 10);
    printf("\n");
    Wait();

    system("cls");
    SelectionSort(head->next, 2, 1);
    printf("\033[32m\033[1m数学成绩排名前十的学生：\033[0m\n");
    PrintTopStudents(head, 2, 10);
    printf("\n");
    Wait();

    system("cls");
    SelectionSort(head->next, 3, 1);
    printf("\033[32m\033[1m英语成绩排名前十的学生：\033[0m\n");
    PrintTopStudents(head, 3, 10);
    printf("\n");
    Wait();

    system("cls");
    SelectionSort(head->next, 4, 1);
    printf("\033[32m\033[1m总成绩排名前十的学生：\033[0m\n");
    PrintTopStudents(head, 4, 10);
    printf("\n");
    Wait();

    AverageScores(head);
    printf("\n"); 
    Wait();
}
void PrintTopStudents(ListNode* head, int subject, int count) {
    int rank = 1;

    ListNode* cur = head->next;
    while (cur != NULL && rank <= count) {
        if (subject == 1) {
            printf("\033[33m\033[1m第 %-2d 名: %-8s    语文成绩: %d\033[0m\n", rank, cur->name, cur->score1);
        }
        else if (subject == 2) {
            printf("\033[33m\033[1m第 %-2d 名: %-8s    数学成绩: %d\033[0m\n", rank, cur->name, cur->score2);
        }
        else if (subject == 3) {
            printf("\033[33m\033[1m第 %-2d 名: %-8s    英语成绩: %d\033[0m\n", rank, cur->name, cur->score3);
        }
        else if (subject == 4) {
            printf("\033[33m\033[1m第 %-2d 名: %-8s    总成绩: %d\033[0m\n", rank, cur->name, cur->score1+ cur->score2 + cur->score3);
        }
        cur = cur->next;
        rank++;
    }
}
    //学生成绩排序
bool CompareNodes(const ListNode* a, const ListNode* b, int subjectChoice) {
    int scoreA, scoreB;

    switch (subjectChoice) {
    case 1:
        scoreA = a->score1;
        scoreB = b->score1;
        break;
    case 2:
        scoreA = a->score2;
        scoreB = b->score2;
        break;
    case 3:
        scoreA = a->score3;
        scoreB = b->score3;
        break;    
    case 4:
        scoreA = a->score1 + a->score2 + a->score3;
        scoreB = b->score1 + b->score2 + b->score3;
        break;
    }
    return (scoreA > scoreB);
}
void SwapNodes(ListNode* node1, ListNode* node2) {
    if (node1 == NULL || node2 == NULL) {
        return;
    }

    char tempName[MAX_NAME];
    strcpy(tempName, node1->name);
    strcpy(node1->name, node2->name);
    strcpy(node2->name, tempName);
    
    char tempId[MAX_ID];
    strcpy(tempId, node1->id);
    strcpy(node1->id, node2->id);
    strcpy(node2->id, tempId);

    char tempClass[MAX_CLASS];
    strcpy(tempClass, node1->class);
    strcpy(node1->class, node2->class);
    strcpy(node2->class, tempClass);

    int tempScore1 = node1->score1;
    node1->score1 = node2->score1;
    node2->score1 = tempScore1;

    int tempScore2 = node1->score2;
    node1->score2 = node2->score2;
    node2->score2 = tempScore2;

    int tempScore3 = node1->score3;
    node1->score3 = node2->score3;
    node2->score3 = tempScore3;
}
void SelectionSort(ListNode* head, int subjectChoice, int orderChoice) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    for (ListNode* p = head->next; p != NULL; p = p->next) {
        for (ListNode* q = p; q != NULL; q = q->next) {
            if ((!CompareNodes(p, q, subjectChoice) && orderChoice == 1) || (CompareNodes(p, q, subjectChoice) && orderChoice == 2)) {
                SwapNodes(p, q);
            }
        }
    }
}
void SortStuInfo(ListNode* head) {
    system("cls");

    if (head->next == NULL) {
        printf("无学生信息\n");
        Wait();
        return;
    }

    int subjectChoice, orderChoice;
    printf("请选择排序方式\n");
    printf("1. 语文成绩  2. 数学成绩  3. 英语成绩  4. 总分\n");
    subjectChoice = SafeScanf(0, 4);

    if (subjectChoice < 1 || subjectChoice > 4) {
        system("cls");
        printf("输入错误\n");
        Wait();
        return;
    }

    system("cls");

    printf("1. 由高到低  2. 由低到高\n");
    orderChoice = SafeScanf(1, 2);

    if (orderChoice < 1 || orderChoice > 2) {
        system("cls");
        printf("输入错误\n");
        Wait();
        return;
    }
    SelectionSort(head, subjectChoice, orderChoice);

    system("cls");
    if (head->next == NULL) {
        printf("无学生信息\n");
        Wait();
        return;
    }
    ListNode* cur = head->next;
    printf("**************************************************************\n");
    printf("***                 \033[33m欢迎进入学生管理系统\033[0m                   ***\n");
    printf("**************************************************************\n");
    printf("**************************************************************\n");
    printf("***  姓名   学号  语文成绩   数学成绩   英语成绩   总成绩  ***\n");
    while (cur) {
        printf("*** \033[33m\033[1m%-6s %-6s    %-6d     %-6d    %-6d    %-6d\033[0m ***\n", cur->name, cur->id, cur->score1,
            cur->score2, cur->score3, cur->score1 + cur->score2 + cur->score3);
        cur = cur->next;
    }
    printf("**************************************************************\n");
    printf("**************************************************************\n");
    Wait();

    return;
}
    //成绩申诉处理
void DelScore(ScoreList* scoreList, int position) {
    if (scoreList->next == NULL) {
        printf("申诉列表为空\n");
        return;
    }

    ScoreList* cur = scoreList->next;
    int count = 1;

    while (cur != NULL && count < position) {
        cur = cur->next;
        count++;
    }

    if (cur == NULL) {
        system("cls");
        printf("无效的选择，未找到该位置的申诉记录\033[0m\n");
        Wait();
        return;
    }

    if (cur->pre != NULL) {
        cur->pre->next = cur->next;
    }
    if (cur->next != NULL) {
        cur->next->pre = cur->pre;
    }

    free(cur);
    system("cls");
    printf("\033[33m\033[1m第 %d 条申诉记录已处理完成\n", position);
    Wait();
}
void HandleScore(ScoreList* scoreList, int position) {
    ScoreList* cur = scoreList->next;
    int count = 1;

    while (cur != NULL && count < position) {
        cur = cur->next;
        count++;
    }

    if (cur == NULL) {
        printf("代办出错\n");
        Wait();
        return;
    }

    system("cls");
    printf("———————————\n");
    printf("——\033[33m\033[1m第 %d 条\033[0m——\n", count);
    printf("———————————\n\n");

    printf("\033[33m\033[1m账号:%s\033[0m\n", cur->username);
    if (cur->flag == 1) {
        printf("\033[33m\033[1m申诉语文成绩为:%d\033[0m\n\n", cur->score);
    }
    else if (cur->flag == 2) {
        printf("\033[33m\033[1m申诉数学成绩为:%d\033[0m\n\n", cur->score);
    }
    else if (cur->flag == 3) {
        printf("\033[33m\033[1m申诉英语成绩为:%d\033[0m\n\n", cur->score);
    }

    printf("\033[33m\033[1m申诉理由:%s\033[0m\n\n", cur->des);

    cur = cur->next;

    int choice = 0;

    printf("\n");
    printf("\033[33m\033[1m请选择操作：\033[0m\n");
    printf("\033[33m\033[1m1. 同意\033[0m\n");
    printf("\033[33m\033[1m2. 拒绝\033[0m\n");
    printf("\033[33m\033[1m0. 返回上一层\033[0m\n");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("已修改\n");
        DelScore(scoreList, position);
        break;    
    case 2:
        printf("已驳回\n");
        DelScore(scoreList, position);
        break;
    case 0:
        return;
    default:
        printf("无效的选择\n");
        break;
    }
}
void GradeUpdate(ScoreList* scoreList) {
    system("cls");
    ScoreList* cur = scoreList->next;

    if (cur == NULL) {
        printf("待办事项列表为空\n");
        Wait();
        return;
    }

    int count = 1;

    while (cur != NULL) {
        printf("———————————\n");
        printf("——\033[33m\033[1m第 %d 条\033[0m——\n", count);
        printf("———————————\n\n");

        printf("\033[33m\033[1m账号:%s\033[0m\n", cur->username);
        if (cur->flag == 1) {
            printf("\033[33m\033[1m申诉语文成绩为:%d\033[0m\n", cur->score);
        } else if (cur->flag == 2) {
            printf("\033[33m\033[1m申诉数学成绩为:%d\033[0m\n", cur->score);
        } else if (cur->flag == 3) {
            printf("\033[33m\033[1m申诉英语成绩为:%d\033[0m\n", cur->score);
        }

        printf("\033[33m\033[1m申诉理由:%s\033[0m\n\n", cur->des);

        cur = cur->next;
        count++;
    }

    int position = 0;
    printf("\n");
    printf("\033[33m\033[1m请选择查看代办或输入(0)退出:\033[0m");
    scanf("%d", &position);

    if (position == 0) {
        return;
    }
    HandleScore(scoreList, position);
}


//管理员
  
    // 代办查看删除
void DelTodo(TodoList* todoList, int position) {
    if (todoList->next == NULL) {
        printf("待办事项列表为空\n");
        return;
    }

    TodoList* cur = todoList->next;
    int count = 1;

    while (cur != NULL && count < position) {
        cur = cur->next;
        count++;
    }

    if (cur == NULL) {
        system("cls");
        printf("无效的选择，未找到该位置的待办事项\033[0m\n");
        Wait();
        return;
    }

    if (cur->pre != NULL) {
        cur->pre->next = cur->next;
    }
    if (cur->next != NULL) {
        cur->next->pre = cur->pre;
    }

    free(cur);
    system("cls");
    printf("\033[33m\033[1m第 %d 条待办事项已处理完成\n", position);
    Wait();
}
void HandleTodo(TodoList* todoList, int position) {
    TodoList* cur = todoList->next;
    int count = 1;

    while (cur != NULL && count < position) {
        cur = cur->next;
        count++;
    }

    if (cur == NULL) {
        printf("代办出错\n");
        Wait();
        return;
    }
    
    system("cls");
    printf("———————————\n");
    printf("——\033[33m\033[1m第 %d 条\033[0m——\n", position);
    printf("———————————\n\n");

    printf("\033[33m\033[1m账号:%s\033[0m\n", cur->username);
    printf("\033[33m\033[1m%s\033[0m\n\n", cur->des);

    int choice = 0;

    printf("\n");
    printf("\033[33m\033[1m请选择操作：\033[0m\n");
    printf("\033[33m\033[1m1. 已处理\033[0m\n");
    printf("\033[33m\033[1m0. 退出\033[0m\n");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("代办已处理完成\n");
        DelTodo(todoList, position);
        break;
    case 0:
        break;
    default:
        printf("无效的选择\n");
        Wait();
        break;
    }
}
void ViewTodo(TodoList* todoList) {
    system("cls");
    TodoList* cur = todoList->next;

    if (cur == NULL) {
        printf("待办事项列表为空\n");
        Wait();
        return;
    }

    int count = 1;

    while (cur != NULL) {
        printf("———————————\n");
        printf("——\033[33m\033[1m第 %d 条\033[0m——\n", count);
        printf("———————————\n\n");

        printf("\033[33m\033[1m账号:%s\033[0m\n", cur->username);
        printf("\033[33m\033[1m%s\033[0m\n\n", cur->des);
        cur = cur->next;
        count++;
    }

    int position = 0;
    printf("\n");
    printf("\033[33m\033[1m请选择查看代办或输入(0)退出:\033[0m");
    scanf("%d", &position);

    if (position == 0) {
        return;
    }

    HandleTodo(todoList, position);
}
    //添加账密信息
void AddUserInfo(UserList* userList) {
    UserList* cur = userList;
    UserList* newUser = (UserList*)malloc(sizeof(UserList));

    if (newUser == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // 输入账密信息
    system("cls");
    printf("请输入账号:\n");
    scanf("%s", newUser->username);
    printf("请输入密码:\n");
    scanf("%s", newUser->password);
    printf("请选择身份（学生->'S',教师->'T'，管理员->'A'）:\n");
    scanf(" %c", &(newUser->role));

    // 将新节点插入到链表末尾
    newUser->next = cur->next;
    newUser->pre = cur;
    cur->next = newUser;

}
    //删除账密信息
void DeleteUserInfo(UserList* userList) {
    char targetUsername[MAX_USERNAME];
    system("cls");
    printf("请输入要删除的账号:\n");
    scanf("%s", targetUsername);

    UserList* cur = userList->next;

    while (cur != NULL && strcmp(cur->username, targetUsername) != 0) {
        cur = cur->next;
    }

    if (cur != NULL) {
        cur->pre->next = cur->next;
        if (cur->next != NULL) {
            cur->next->pre = cur->pre;
        }
        free(cur);
        system("cls");
        printf("账号 %s 删除成功。\n", targetUsername);
        Wait();
    } else {
        system("cls");
        printf("未找到用户 %s。\n", targetUsername);
        Wait();
    }
}
    //修改账密信息
void ModifyUserInfo(UserList* userList) {
    char targetUsername[MAX_USERNAME];
    system("cls");
    printf("请输入要修改的账号:\n");
    scanf("%s", targetUsername);

    UserList* cur = userList->next;

    // 寻找要修改的节点
    while (cur != NULL && strcmp(cur->username, targetUsername) != 0) {
        cur = cur->next;
    }

    if (cur != NULL) {
        // 提示用户输入新的账号和密码信息
        system("cls");
        printf("请输入新的账号:\n");
        scanf("%s", cur->username);

        printf("请输入新的密码:\n");
        scanf("%s", cur->password);

        printf("请选择新的身份（学生->'S', 教师->'T'，管理员->'A'）:\n");
        scanf(" %c", &(cur->role));

        system("cls");
        printf("用户 %s 修改成功。\n", targetUsername);
        Wait();
    }
    else {
        system("cls");
        printf("未找到用户 %s。\n", targetUsername);
        Wait();
    }
}
    //查找账密信息
void FindUserInfo(UserList* userList) {
    char targetUsername[MAX_USERNAME];
    system("cls");
    printf("请输入要查找的账号:\n");
    scanf("%s", targetUsername);

    UserList* cur = userList->next;

    while (cur != NULL && strcmp(cur->username, targetUsername) != 0) {
        cur = cur->next;
    }

    if (cur != NULL) {
        system("cls");
        printf("用户信息：\n");
        printf("账号: %s\n", cur->username);
        printf("密码: %s\n", cur->password);
        Wait();
    }
    else {
        system("cls");
        printf("未找到用户 %s。\n", targetUsername);
        Wait();
    }
}
    //新班级初始化账户密码
void InitialClassFromFile(ListNode* head, UserList* userList) {
    char username[MAX_USERNAME];
    char ch;
    system("cls");
    printf("请输入初始化账号密码班级(1-5): ");
    while (1) {
        if (scanf(" %c", &ch) != 1 || (ch < '1' || ch > '5')) {
            printf("无效输入，请重新输入(1-5): ");
            while (getchar() != '\n'); 
        }
        else {
            break;
        }
    }
    system("cls");
    printf(" %c 班的账密信息已初始化\n", ch);
    Wait();
    username[1] = ch;

    ReadStuFromFile(head, username);

    ListNode* stuCur = head->next;
    UserList* userPre = userList;
    while (userPre->next != NULL) {
        userPre = userPre->next;
    }

    while (stuCur) {
        UserList* newUser = (UserList*)malloc(sizeof(UserList));
        if (newUser == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        strcpy(newUser->username, stuCur->id);
        strcpy(newUser->password, "123456");
        newUser->role = 'S';

        newUser->pre = userPre;
        newUser->next = NULL;

        userPre->next = newUser;
        userPre = newUser;

        stuCur = stuCur->next;
    }
}
    //输出账密信息
void DisplayUserInfo(const UserList* userList) {
    system("cls");
    if (userList->next == NULL) {
        printf("无账密信息\n");
        Wait();
        return;
    }
    UserList* cur = userList->next;
    printf("*************************************************************\n");
    printf("\033[33m\033[1m%-5s\t%-5s\n\033[0m", "账户", "密码");

    while (cur) {
        printf("\033[33m\033[1m%-6s\t%-6s\n\033[0m", cur->username, cur->password);
        cur = cur->next;
    }
    printf("*************************************************************\n");
    Wait();
}
    //手动重新录入学生信息 
void ReEnterStuInfo(ListNode* head) {
    char username[MAX_USERNAME];
    system("cls");
    printf("请输入重新录入学生班级: ");
    char ch;
    while (1) {
        if (scanf(" %c", &ch) != 1 || (ch < '1' || ch > '5')) {
            printf("无效输入，请重新输入(1-5): ");
            while (getchar() != '\n');
        }
        else {
            break;
        }
    }
    username[1] = ch;
    ReadStuFromFile(head,username);
    ModifyStuInfo(head);
    WriteStuToFile(head,username);
}