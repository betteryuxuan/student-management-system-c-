
#include "student management system.h"

//�����ʼ��
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

//�˵�����
void DisplayMenu(const char* menuText) {
    system("cls");
    printf("**************************************************************\n");
    printf("***                 \033[33m\033[1m��ӭ����ѧ������ϵͳ\033[0m                   ***\n");
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
        DisplayMenu("***                    \033[33m\033[1m1.��¼    \033[0m                          ***\n"
                    "***                    \033[33m\033[1m2.����ע��\033[0m                          ***\n"
                    "***                    \033[33m\033[1m3.�����޸�\033[0m                          ***\n"
                    "***                    \033[33m\033[1m4.�����һ�\033[0m                          ***\n"
                    "***                    \033[33m\033[1m0.�˳�    \033[0m                          ***\n");

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
            //printf("����������������롣\n");
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
        DisplayMenu("***                    \033[33m\033[1m1.�ɼ���ѯ\033[0m                          ***\n"
                    "***                    \033[33m\033[1m2.����ɼ���ѯ\033[0m                      ***\n"
                    "***                    \033[33m\033[1m3.�ɼ�����\033[0m                          ***\n"
                    "***                    \033[33m\033[1m4.�ɼ�����\033[0m                          ***\n"
                    "***                    \033[33m\033[1m5.������һ��\033[0m                        ***\n"
                    "***                    \033[33m\033[1m0.�˳�\033[0m                              ***\n");
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
            //printf("����������������롣\n");
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
        DisplayMenu("***                    \033[33m\033[1m1.���ѧ����Ϣ\033[0m                      ***\n"
                    "***                    \033[33m\033[1m2.ɾ��ѧ����Ϣ\033[0m                      ***\n"
                    "***                    \033[33m\033[1m3.�޸�ѧ����Ϣ\033[0m                      ***\n"
                    "***                    \033[33m\033[1m4.��ѯѧ����Ϣ\033[0m                      ***\n"
                    "***                    \033[33m\033[1m5.���ѧ����Ϣ\033[0m                      ***\n"
                    "***                    \033[33m\033[1m6.����ѧ����Ϣ\033[0m                      ***\n"
                    "***                    \033[33m\033[1m7.ѧ���ɼ�����\033[0m                      ***\n"
                    "***                    \033[33m\033[1m8.�ɼ�����    \033[0m                      ***\n"
                    "***                    \033[33m\033[1m9.������һ��  \033[0m                      ***\n"
                    "***                    \033[33m\033[1m0.�˳�        \033[0m                      ***\n");
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
            //printf("����������������롣\n");
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
        DisplayMenu("***                    \033[33m\033[1m1. �鿴����            \033[0m             ***\n"
                    "***                    \033[33m\033[1m2. �����ʦ���޸�      \033[0m             ***\n"
                    "***                    \033[33m\033[1m3. �����˺ż�����      \033[0m             ***\n"
                    "***                    \033[33m\033[1m4. ɾ���˻�������      \033[0m             ***\n"
                    "***                    \033[33m\033[1m5. �޸��˻�������      \033[0m             ***\n"
                    "***                    \033[33m\033[1m6. ��ѯ�˻�������      \033[0m             ***\n"
                    "***                    \033[33m\033[1m7. ¼�������˻�������  \033[0m             ***\n"
                    "***                    \033[33m\033[1m8. ��������˻�������  \033[0m             ***\n"
                    "***                    \033[33m\033[1m9. �ֶ�����¼��ѧ����Ϣ\033[0m             ***\n"
                    "***                    \033[33m\033[1m10.������һ��          \033[0m             ***\n"
                    "***                    \033[33m\033[1m0. �˳�                \033[0m             ***\n");
        choice = SafeScanf(0, 10);
        switch (choice) {
        case 1:
            ViewTodo(todoList);
            break;
        case 2:
            system("cls");
            printf("\033[33m\033[1m������(1-5)ѡ��༶������(0)����:\033[0m ");
            char ch;
            scanf(" %c", &ch);
            if (ch >= '1' && ch <= '5') {
                username[0] = '0';
                username[1] = ch;
                username[2] = '\0'; 
            } else {
                printf("\033[33m\033[1m�������\033[0m\n");
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
            //�°༶��ʼ���˻�����
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
            //printf("����������������롣\n");
            break;

        }
    } while (choice);
    WriteUserToFile(userList);
    WriteTodoToFile(todoList);

}
void LoginMenu(ListNode* head, UserList* userList, TodoList* todoList, ScoreList* scoreList, char username[MAX_USERNAME]) {
    int choice = 0;
    system("cls");
    printf("\033[33m\033[1m�������¼�˻�:\033[0m ");
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
    printf("\033[33m\033[1m�����������...\033[0m");
    getch(); 
}
int SafeScanf(int min, int max) {
    wchar_t inputBuffer[100];
    int index = 0;

    while (1) {
        if (index >= sizeof(inputBuffer) / sizeof(wchar_t) - 1) {
            wprintf(L"���������������������� %d �� %d ֮�������:\n", min, max);
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
        wprintf(L"��������� %d �� %d ֮�������:\n", min, max);
        return -1;
    }

    int ret = wcstol(inputBuffer, NULL, 10);

    if (ret < min || ret > max) {
        wprintf(L"��������� %d �� %d ֮�������:\n", min, max);
        return -1;
    }
    else {
        return ret;
    }
}
void SafeFgets(char* buffer, size_t bufferSize) {
    // ��鴫���ָ��ʹ�С�Ƿ���Ч
    if (buffer == NULL || bufferSize == 0) {
        fprintf(stderr, "Invalid buffer or bufferSize provided.\n");
        return;
    }
    if (fgets(buffer, bufferSize, stdin) != NULL) {
        // �Ƴ�ĩβ�Ļ��з�����֤�ַ����Կ��ַ���β
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
    else {
        // ��ȡʧ�ܣ����������Ϣ
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

//�ļ����루���ļ��ж�ȡ��
void ReadStuFromFile(ListNode* head, const char* username) {
    //�����˺�ǰ��λ�򿪶�Ӧ�༶�ļ�
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
        perror("�޷����ļ�");
        return;
    }

    ListNode st;
    ListNode* pre = head;
    memset(&st, 0, sizeof(ListNode));

    while (fscanf(pf, "%s %s %s %d %d %d", st.name, st.id, st.class, &st.score1, &st.score2, &st.score3) == 6) {
        ListNode* cur = (ListNode*)malloc(sizeof(ListNode));
        if (cur == NULL) {
            perror("�ڴ����ʧ��");
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
        perror("�޷����ļ�");
        return; 
    }

    UserList st;
    UserList* pre = userList;

    while (fscanf(pf, "%s %s %c", st.username, st.password, &st.role) == 3) {
        UserList* cur = (UserList*)malloc(sizeof(UserList));
        if (cur == NULL) {
            perror("�ڴ����ʧ��");
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
        perror("�޷����ļ�");
        return;
    }

    TodoList st;
    TodoList* pre = todoList;

    while (fscanf(pf, "%s %499[^\n]", st.username, st.des) == 2) {
        TodoList* cur = (TodoList*)malloc(sizeof(TodoList));
        if (cur == NULL) {
            perror("�ڴ����ʧ��");
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
        perror("�޷����ļ�");
        return;
    }

    ScoreList st;
    ScoreList* pre = scoreList;

    while (fscanf(pf, "%s %d %d %s", st.username, &st.flag, &st.score, st.des) == 4) {
        ScoreList* cur = (ScoreList*)malloc(sizeof(ScoreList));
        if (cur == NULL) {
            perror("�ڴ����ʧ��");
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

//�ļ�д��
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
        perror("�޷����ļ�����д��");
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
        perror("�޷����ļ�����д��");
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
        perror("�޷����ļ�����д��");
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
        perror("�޷����ļ�����д��");
        return;
    }

    ScoreList* cur = scoreList->next;
    while (cur != NULL) {
        fprintf(pf, "%s %d %d %s\n", cur->username, cur->flag, cur->score, cur->des);
        cur = cur->next;
    }

    fclose(pf);
}


//�ڴ��ͷ�
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


//��¼����

    //ʶ�����
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
    printf("\033[33m\033[1m�������¼����: \033[0m");
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
        printf("\033[33m\033[1m�˻�����������⣬��������\033[0m\n");
        Wait();
    }        

    return 0;
}
    //����ע�᣺�˺Ŵ��ڣ��ҵ���ݣ��޸�����
void UpdatePassword(UserList* userList, TodoList* todoList) {
    system("cls");
    if (userList->next == NULL) {
        printf("��������Ϣ��\n");
        Wait();
    }
    printf("�����������˺ţ�");
    UserList* cur = userList->next;
    char username[MAX_USERNAME];
    SafeFgets(username, sizeof(username));
    while (cur != NULL && strcmp(username, cur->username) != 0) {
        cur = cur->next;
    }
    if (cur == NULL) {
        system("cls");
        printf("�Ҳ����û���%s\n", username);
        Wait();
        return;
    }
    if (strcmp(cur->password, "123456") != 0 ) {
        system("cls");
        printf("�����������޸ģ�������ǰ�������һع���\n");
        Wait();
        return;
    }
    char password[MAX_PASSWORD];
    system("cls");
    printf("������������: ");
    HidePasswd(password);
    strcpy(cur->password, password);

    system("cls");
    printf("����ע��ɹ�\n");

    TodoList* cur1 = todoList;
    while (cur1->next != NULL) {
        cur1 = cur1->next;
    }

    TodoList* NewTodo = (TodoList*)malloc(sizeof(TodoList));

    strcpy(NewTodo->username, cur->username);
    sprintf(NewTodo->des, "��������ע��Ϊ:%s", cur->password);

    cur1->next = NewTodo;
    NewTodo->pre = cur1;
    NewTodo->next = NULL;

    Wait();
}
    //�����޸�
void ChangePassword(UserList* userList, TodoList* todoList) {
    system("cls");
    if (userList->next == NULL) {
        printf("��������Ϣ��\n");
        Wait();
        return;
    }

    printf("�����������˺ţ�");
    UserList* cur = userList->next;
    char username[MAX_USERNAME];
    SafeFgets(username, sizeof(username));

    printf("�������������룺");
    char password[MAX_USERNAME];
    HidePasswd(password);

    while (cur != NULL && (strcmp(username, cur->username) != 0 || strcmp(password, cur->password) != 0)) {
        cur = cur->next;
    }
    if (cur == NULL) {
        system("cls");
        printf("�Ҳ��������˻����������\n");
        Wait();
        return;
    }

    printf("����������������: ");
    HidePasswd(password);
    strcpy(cur->password, password);
    system("cls");
    printf("�����޸ĳɹ�\n");

    TodoList* cur1 = todoList;
    while (cur1->next != NULL) {
        cur1 = cur1->next;
    }

    TodoList* NewTodo = (TodoList*)malloc(sizeof(TodoList));

    strcpy(NewTodo->username, cur->username);
    sprintf(NewTodo->des, "���������޸�Ϊ:%s", cur->password);

    cur1->next = NewTodo;
    NewTodo->pre = cur1;
    NewTodo->next = NULL;

    Wait();
}
    //�����һ�
void RecoverPassword(UserList* userList, ListNode* head, TodoList* todoList) {
    system("cls");
    if (userList->next == NULL) {
        printf("��������Ϣ��\n");
        Wait();
        return;
    }
    printf("�����������˺ţ�");
    char username[MAX_USERNAME];
    SafeFgets(username, sizeof(username));;

    printf("����������������");
    char name[MAX_NAME];
    SafeFgets(name, sizeof(name));

    ReadStuFromFile(head, username);
    ListNode* cur1 = head->next;

    while (cur1 != NULL && (strcmp(cur1->id, username) != 0 || strcmp(cur1->name, name) != 0)) {
        cur1 = cur1->next;
    }
    system("cls");
    if (cur1 == NULL) {
        printf("�����˺Ų�ƥ�䣬�����ԡ�\n");
        Wait();
        return;
    }

    UserList* cur = userList->next;
    while (cur != NULL && (strcmp(cur->username, cur1->id) != 0)) {
        cur = cur->next;
    }
    if (cur == NULL) {
        system("cls");
        printf("�Ҳ����û���%s\n", username);
        Wait();
        return;
    }

    char newPassword[MAX_PASSWORD];
    printf("������������: ");
    HidePasswd(newPassword);

    system("cls");

    strcpy(cur->password, newPassword);

    printf("���������óɹ�\n");

    TodoList* cur2 = todoList;
    while (cur2->next != NULL) {
        cur2 = cur2->next;
    }

    TodoList* NewTodo = (TodoList*)malloc(sizeof(TodoList));

    strcpy(NewTodo->username, cur->username);
    sprintf(NewTodo->des, "������������Ϊ:%s", cur->password);

    cur2->next = NewTodo;
    NewTodo->pre = cur1;
    NewTodo->next = NULL;

    Wait();
}


//ѧ����

    //��ѯ���˳ɼ�
void FindStuScore(ListNode* head, char* username) {
    system("cls");
    if (head->next == NULL) {
        printf("�޳ɼ���Ϣ\n");
        return;
    }
    char id[MAX_ID];
    strcpy(id, username);
    ListNode* cur = FindStuById(head, id);
    if (cur != NULL) {
        printf("*************************************************************\n");
        printf("%-5s\t%-5s\t%-5s\t %s %s %s\n", "����", "ѧ��", "�༶", "���ĳɼ�", "��ѧ�ɼ�", "Ӣ��ɼ�");
        printf("%-6s\t%-6s\t%-10s%-6d    %-6d    %-6d\n", cur->name, cur->id, cur->class,
            cur->score1, cur->score2, cur->score3);
        printf("*************************************************************\n");
        Wait();
    } else {
        printf("δ�ҵ�������Ϣ\n");
        Wait();
    }
    return;
}
    //�ɼ�����
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
    printf("\033[34m\033[1m���ĳɼ��������� %d ��\033[0m\n", rank);
    if (rank <= 10) {
        printf("\033[34m\033[1m�ɼ��������������ķ�����ַǳ���ɫ���������ֺóɼ���\033[0m\n");
    }
    else if (rank <= 20) {
        printf("\033[34m\033[1m�ɼ������������ķ�����ֲ�������Ŭ����ߣ�\033[0m\n");
    }
    else {
        printf("\033[34m\033[1m�ɼ������������ķ��滹�������ռ䣬�����ϰ���Ķ���\033[0m\n");
    }

    SelectionSort(head->next, 2, 1);
    rank = ScoreRank(head, username);
    printf("\n\033[34m\033[1m��ѧ�ɼ��������� %d ��\033[0m\n", rank);
    if (rank <= 10) {
        printf("\033[34m\033[1m�ɼ�������������ѧ������ַǳ���ɫ���������ֺóɼ���\033[0m\n");
    }
    else if (rank <= 20) {
        printf("\033[34m\033[1m�ɼ�����������ѧ������ֲ�������Ŭ����ߣ�\033[0m\n");
    }
    else {
        printf("\033[34m\033[1m�ɼ�����������ѧ���滹�������ռ䣬�����ϰ��˼����\033[0m\n");
    }

    SelectionSort(head->next, 3, 1);
    rank = ScoreRank(head, username);
    printf("\n\033[34m\033[1mӢ��ɼ��������� %d ��\033[0m\n", rank);
    if (rank <= 10) {
        printf("\033[34m\033[1m�ɼ�����������Ӣ�﷽����ַǳ���ɫ���������ֺóɼ���\033[0m\n");
    }
    else if (rank <= 20) {
        printf("\033[34m\033[1m�ɼ���������Ӣ�﷽����ֲ�������Ŭ����ߣ�\033[0m\n");
    }
    else {
        printf("\033[34m\033[1m�ɼ���������Ӣ�﷽�滹�������ռ䣬�����ϰ�ͻ��۴ʻ㡣\033[0m\n");
    }

    SelectionSort(head->next, 4, 1);
    rank = ScoreRank(head, username);
    printf("\n\033[34m\033[1m�ܳɼ��������� %d ��\033[0m\n", rank);
    if (rank <= 10) {
        printf("\033[34m\033[1m�ɼ�����������ܳɼ��ǳ����㣬�������ֺóɼ���\033[0m\n\n");
    }
    else if (rank <= 20) {
        printf("\033[34m\033[1m�ɼ��������ܳɼ����ֲ�����������Ŭ����\033[0m\n\n");
    }
    else {
        printf("\033[34m\033[1m�ɼ��������ܳɼ����������ռ䣬�����ϰ��ȫ����ߡ�\033[0m\n\n");
    }

    Wait();
}
    //�ɼ�����
void GradeAppeal(ListNode* head, char* username, ScoreList* scoreList) {
    system("cls");
    ListNode* cur = FindStuById(head, username);
    printf("**************************************************************\n");
    printf("***  \033[33m\033[1m����   ѧ��    �༶    ���ĳɼ�  ��ѧ�ɼ�  Ӣ��ɼ�\033[0m   ***\n");
    printf("***\033[33m\033[1m %-6s  %-6s %-10s  %-6d    %-6d    %-6d \033[0m ***\n",cur->name, cur->id, cur->class,cur->score1, cur->score2, cur->score3);
    printf("**************************************************************\n");
    printf("***         \033[33m\033[1m���ĳɼ����ϣ���ѡ��Ҫ���ߵĿ�Ŀ��\033[0m             ***\n");
    printf("***         \033[33m\033[1m            1.����                \033[0m             ***\n");
    printf("***         \033[33m\033[1m            2.��ѧ                \033[0m             ***\n");
    printf("***         \033[33m\033[1m            3.Ӣ��                \033[0m             ***\n");
    printf("***         \033[33m\033[1m            0.����                \033[0m             ***\n");
    printf("**************************************************************\n");
    printf("**************************************************************\n");

    int choice = 0;
    char buffer[MAX_DES];
    int score = 0;

    choice = SafeScanf(0, 3);

    if (choice != 0 && choice != 1 && choice != 2 && choice != 3) {
        system("cls");
        printf("ѡ�����\n");
        Wait();
        return;
    } else if (choice == 0) {
        return;
    }

    system("cls");    
    printf("\033[33m\033[1m�����������ߺ�ĳɼ���\033[0m");
    scanf("%d", &score);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    system("cls");
    printf("\033[33m\033[1m�����������ߵ�����ԭ��\033[0m");
    SafeFgets(buffer, sizeof(buffer));

    ScoreList* cur1 = scoreList;
    while (cur1->next != NULL) {
        cur1 = cur1->next;
    }

    ScoreList* node = (ScoreList*)malloc(sizeof(ScoreList));
    if (node == NULL) {
        fprintf(stderr, "�ڴ����ʧ��\n");
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
    printf("���߳ɹ�\n");
    Wait();

}
 

//��ʦ��

    //ͨ��ѧ�Ų���
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
    //ͨ����������
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
    //���ѧ����Ϣ
void AddStuInfo(ListNode* head) {
    ListNode* cur = head;
    ListNode* newStudent = (ListNode*)malloc(sizeof(ListNode));

    if (newStudent == NULL) {
        system("cls");
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    system("cls");
    printf("������ѧ������:\n");
    scanf("%s", newStudent->name);
    printf("������ѧ��ѧ��:\n");
    scanf("%s", newStudent->id);
    printf("������༶:\n");
    scanf("%s", newStudent->class);
    printf("������ѧ�����ĳɼ�:\n");
    scanf("%d", &newStudent->score1);
    printf("������ѧ����ѧ�ɼ�:\n");
    scanf("%d", &newStudent->score2);
    printf("������ѧ��Ӣ��ɼ�:\n");
    scanf("%d", &newStudent->score3);

    newStudent->next = cur->next;
    newStudent->pre = cur;
    cur->next = newStudent;

    system("cls");
    printf("����Ϊ %s ��ѧ����Ϣ��¼��\n", newStudent->name);

}
    //ɾ��ѧ����Ϣ
void DelStuInfo(ListNode* head) {
    if (head->next == NULL) {
        system("cls");
        printf("��ѧ����Ϣ\n");
        Wait();
        return;
    }
    int choice = 0;
    if (head->next == NULL) {
        printf("ѧ����Ϣ��ȫ��ɾ��\n");
        return;
    }
    system("cls");
    printf("��ѡ��ɾ����ʽ:\n");
    printf("1.��ѧ��ɾ��\n");
    printf("2.������ɾ��\n");
    printf("0.�˳�\n");
    choice = SafeScanf(0, 2);

    switch (choice) {
    case 1:
        system("cls");
        printf("������Ҫɾ����ѧ��ѧ��: ");
        char id[MAX_ID];
        scanf("%s", id);
        ListNode* cur1 = FindStuById(head, id);
        if (cur1 == NULL) {
            printf("δ�ҵ�ѧ��Ϊ %s ��ѧ��\n", id);
            Wait();
            
        } else if (cur1->next == NULL) {
            cur1->pre->next = NULL;
            free(cur1);
            printf("ѧ��Ϊ %s ��ѧ����ɾ��\n", id);
            Wait();
        } else if (cur1->next != NULL) {
            cur1->pre->next = cur1->next;
            cur1->next->pre = cur1->pre;
            free(cur1);
            printf("ѧ��Ϊ %s ��ѧ����ɾ��\n", id);
            Wait();
        }
        break;

    case 2:
        system("cls");
        printf("������Ҫɾ����ѧ������: ");
        char name[MAX_NAME];
        scanf("%s", name);
        ListNode* cur2 = FindStuByName(head, name);
        if (cur2 == NULL) {
            printf("δ�ҵ�����Ϊ %s ��ѧ��\n", name);
            Wait();
        }
        else if (cur2->next == NULL) {
            cur2->pre->next = NULL;
            free(cur2);
            printf("���� %s ��ѧ����ɾ��\n", name);
            Wait();
        }
        else if(cur2->next != NULL){
                            cur2->pre->next = cur2->next;
            cur2->next->pre = cur2->pre;
            free(cur2);
            printf("����Ϊ %s ��ѧ����ɾ��\n", name);
            Wait();

        }
        break;

    case 0:
        break;
    default:
        printf("�������\n");
        Wait();
        break;
    }
    return;
}
    //�޸�ѧ����Ϣ
void ModifyStuInfo(ListNode* head) {
    if (head->next == NULL) {
        system("cls");
        printf("��ѧ����Ϣ\n");
        Wait();
        return;
    }

    int choice = 1;
    char id[MAX_ID];
    char name[MAX_NAME];
    ListNode* cur = head->next;

    do {
        system("cls");
        printf("��ѡ���ѯ��ʽ:\n");
        printf("1.��ѧ�Ų�ѯ\n");
        printf("2.��������ѯ\n");
        printf("0.�˳�\n");
        choice = SafeScanf(0, 2);

        switch (choice) {
        case 1:
            system("cls");
            printf("������Ҫ�޸ĵ�ѧ��ѧ��:\n");
            scanf("%s", id);
            ListNode* cur1 = FindStuById(head, id);
            if (cur1) {
                Mod(cur1);
            } else {
                system("cls");
                printf("δ�ҵ�ѧ��Ϊ %s ��ѧ��\n", id);
                Wait();
            }
            break;
        case 2:
            system("cls");
            printf("������Ҫ�޸ĵ�ѧ������:\n");
            scanf("%s", name);
            ListNode* cur2 = FindStuByName(head, name);
            if (cur2) {
                Mod(cur2);
            } else {
                system("cls");
                printf("δ�ҵ�����Ϊ %s ��ѧ��\n", name);
                Wait();
            }
            break;
        case 0:
            break;
        default:
            system("cls");
            printf("�����������������\n");
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
        printf(" \033[33m\033[1m%-5s\t%-5s\t%-5s\t %s %s %s\n\033[0m", "����", "ѧ��", "�༶", "���ĳɼ�", "��ѧ�ɼ�", "Ӣ��ɼ�");
        printf("\033[33m\033[1m%-6s\t%-6s\t%-10s%-6d    %-6d    %-6d\033[0m\n", cur->name, cur->id, cur->class,
                                                          cur->score1, cur->score2, cur->score3);
        printf("*************************************************************\n");
        printf("\033[33m\033[1m��ѧ����Ϣ���ϣ���ѡ��Ҫ�޸ĵ���Ϣ\033[0m\n");
        printf("\033[33m\033[1m1.���� 2.ѧ�� 3.�༶ 4.���ĳɼ� 5.��ѧ�ɼ� 6.Ӣ��ɼ� 0.������һ��\033[0m\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        choice = SafeScanf(0, 6);

        switch (choice) {
        case 1:
            system("cls");
            printf("�������µ�������\n");
            scanf("%s", newString);
            strcpy(cur->name, newString);
            system("cls");
            printf("�޸ĳɹ�\n");
            Wait();
            break;
        case 2:
            system("cls");
            printf("�������µ�ѧ�ţ�\n");
            scanf("%s", newString);
            strcpy(cur->id, newString);
            system("cls");
            printf("�޸ĳɹ�\n");
            Wait();
            break;
        case 3:
            system("cls");
            printf("�������µİ༶��\n");
            scanf("%s", newString);
            strcpy(cur->class, newString);
            system("cls");
            printf("�޸ĳɹ�\n");
            Wait();
            break;
        case 4:
            system("cls");
            printf("�������µ����ĳɼ���\n");
            scanf("%d", &new);
            cur->score1 = new;
            system("cls");
            printf("�޸ĳɹ�\n");
            Wait();
            break;
        case 5:
            system("cls");
            printf("�������µ���ѧ�ɼ���\n");
            scanf("%d", &new);
            cur->score2 = new;
            system("cls");
            printf("�޸ĳɹ�\n");
            Wait();
            break;
        case 6:
            system("cls");
            printf("�������µ�Ӣ��ɼ���\n");
            scanf("%d", &new);
            cur->score3 = new;
            system("cls");
            printf("�޸ĳɹ�\n");
            Wait();
            break;
        case 0:
            break;
        default:
            printf("�������\n");
            Wait();
            break;
        }
    }while (choice);
}
    //��ѯѧ����Ϣ
void FindStuInfo(ListNode* head) {
        if (head->next == NULL) {
            printf("��ѧ����Ϣ\n");
            Wait();
            return;
        }
        int choice;
        do {
            system("cls");
            printf("��ѡ���ѯ��ʽ:\n");
            printf("1.��ѧ�Ų�ѯ\n");
            printf("2.��������ѯ\n");
            printf("0.�˳�\n");

            choice = SafeScanf(0, 2);

            switch (choice) {
                case 1:
                    system("cls");
                    printf("������Ҫ��ѯ��ѧ��ѧ��: ");
                    char id[MAX_ID];
                    scanf("%s", id);
                    ListNode* cur1 = FindStuById(head, id);
                    if (cur1 != NULL) {
                        system("cls");
                        printf("*************************************************************\n");
                        printf("\033[33m\033[1m%-5s\t%-5s\t%-5s\t %s %s %s\n\033[0m", "����", "ѧ��", "�༶", "���ĳɼ�", "��ѧ�ɼ�", "Ӣ��ɼ�");
                        printf("\033[33m\033[1m%-6s\t%-6s\t%-10s%-6d    %-6d    %-6d\n\033[0m", cur1->name, cur1->id, cur1->class,
                            cur1->score1, cur1->score2, cur1->score3);
                        printf("*************************************************************\n");
                        Wait();
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                    }
                    else {
                        system("cls");
                        printf("δ�ҵ�ѧ��Ϊ %s ��ѧ��\n", id);
                        Wait();                        
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                    }
                    break;
    
                case 2:
                    system("cls");
                    printf("������Ҫ��ѯ��ѧ������: ");
                    char name[MAX_NAME];
                    scanf("%s", name);
                    ListNode* cur2 = FindStuByName(head, name);
                    if (cur2 != NULL) {
                        system("cls");
                        printf("*************************************************************\n");
                        printf("\033[33m\033[1m%-5s\t%-5s\t%-5s\t %s %s %s\n\033[0m", "����", "ѧ��", "�༶", "���ĳɼ�", "��ѧ�ɼ�", "Ӣ��ɼ�");
                        printf("\033[33m\033[1m%-6s\t%-6s\t%-10s%-6d    %-6d    %-6d\n\033[0m", cur2->name, cur2->id, cur2->class,
                            cur2->score1, cur2->score2, cur2->score3);
                        printf("*************************************************************\n");
                        Wait();
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                    }
                    else {
                        system("cls");
                        printf("δ�ҵ�����Ϊ %s ��ѧ��\n", name);
                        Wait();
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                    }
                    break;
                case 0:
                    break;
                default:
                    system("cls");
                    printf("�����������������\n");
                    Wait();
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    break;
            }
        } while (choice);
        return;
}
    //���ѧ����Ϣ
void DisplayStuInfo(const ListNode* head) {
    system("cls");
    if (head->next == NULL) {
        printf("��ѧ����Ϣ\n");
        Wait();
        return;
    }
    ListNode* cur = head->next;
    printf("**************************************************************\n");
    printf("***                 \033[33m\033[1m��ӭ����ѧ������ϵͳ\033[0m                   ***\n");
    printf("**************************************************************\n");
    printf("**************************************************************\n");
    printf("***  \033[33m\033[1m����   ѧ��    �༶    ���ĳɼ�  ��ѧ�ɼ�  Ӣ��ɼ�\033[0m   ***\n");
    while (cur) {
        printf("*** \033[33m\033[1m%-6s  %-6s %-10s  %-6d    %-6d    %-6d\033[0m  ***\n", cur->name, cur->id, cur->class,
                                                          cur->score1, cur->score2, cur->score3);
        cur = cur->next;
    }
    printf("**************************************************************\n");
    printf("**************************************************************\n");
    Wait();
}
    //����ѧ����Ϣ
void DownloadStuInfo(ListNode* head) {
    system("cls");
    FILE* pf = fopen("student_ingormation.txt", "w");
    if (pf == NULL) {
        perror("�޷����ļ�����д��");
        return;
    }

    ListNode* cur = head->next;
    while (cur != NULL) {
        fprintf(pf, "%s %s %s %d %d %d\n", cur->name, cur->id, cur->class, cur->score1, cur->score2, cur->score3);
        cur = cur->next;
    }
    fclose(pf);
    printf("\033[33m\033[1mѧ����Ϣ�������� 'student_information.txt'\033[0m\n");
    Wait();
}
    //ѧ���ɼ�����
void AverageScores(ListNode* head) {
    if (head == NULL) {
        printf("����Ϊ��\n");
        return;
    }

    double totalChinese = 0, totalMath = 0, totalEnglish = 0;
    int studentCount = 0;

    // ������������ܷ�
    ListNode* current = head;
    while (current != NULL) {
        // ��������ܷ�
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
    printf("\033[32m\033[1m�ɼ�������\033[0m\n\n");

    printf("\033[32m\033[1m����ƽ���֣�%.2lf\033[0m\n", averageChinese);
    if (averageChinese >= 80) {
        printf("\033[32m\033[1m�������ı��ֽϺã��������֣�\n\033[0m\n");
    } else {
        printf("\033[32m\033[1m���������д���ߣ������ǿ�����ϰ��\n\033[0m\n");
    }

    printf("\033[32m\033[1m��ѧƽ���֣�%.2lf\033[0m\n", averageMath);
    if (averageMath >= 80) {
        printf("\033[32m\033[1m������ѧ���ֽϺã��������֣�\033[0m\n\n");
    } else {
        printf("\033[32m\033[1m������ѧ�д���ߣ������ǿ�����ϰ��\033[0m\n\n");
    }

    printf("\033[32m\033[1mӢ��ƽ���֣�%.2lf\033[0m\n", averageEnglish);
    if (averageEnglish >= 80) {
        printf("\033[32m\033[1m����Ӣ����ֽϺã��������֣�\033[0m\n");
    } else {
        printf("\033[32m\033[1m����Ӣ���д���ߣ������ǿ�����ϰ��\033[0m\n");
    }
}
void TeacherScoreAnaly(ListNode* head) {
    system("cls");

    SelectionSort(head->next, 1, 1);
    printf("\033[32m\033[1m���ĳɼ�����ǰʮ��ѧ����\033[0m\n");
    PrintTopStudents(head, 1, 10);
    printf("\n");
    Wait();

    system("cls");
    SelectionSort(head->next, 2, 1);
    printf("\033[32m\033[1m��ѧ�ɼ�����ǰʮ��ѧ����\033[0m\n");
    PrintTopStudents(head, 2, 10);
    printf("\n");
    Wait();

    system("cls");
    SelectionSort(head->next, 3, 1);
    printf("\033[32m\033[1mӢ��ɼ�����ǰʮ��ѧ����\033[0m\n");
    PrintTopStudents(head, 3, 10);
    printf("\n");
    Wait();

    system("cls");
    SelectionSort(head->next, 4, 1);
    printf("\033[32m\033[1m�ܳɼ�����ǰʮ��ѧ����\033[0m\n");
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
            printf("\033[33m\033[1m�� %-2d ��: %-8s    ���ĳɼ�: %d\033[0m\n", rank, cur->name, cur->score1);
        }
        else if (subject == 2) {
            printf("\033[33m\033[1m�� %-2d ��: %-8s    ��ѧ�ɼ�: %d\033[0m\n", rank, cur->name, cur->score2);
        }
        else if (subject == 3) {
            printf("\033[33m\033[1m�� %-2d ��: %-8s    Ӣ��ɼ�: %d\033[0m\n", rank, cur->name, cur->score3);
        }
        else if (subject == 4) {
            printf("\033[33m\033[1m�� %-2d ��: %-8s    �ܳɼ�: %d\033[0m\n", rank, cur->name, cur->score1+ cur->score2 + cur->score3);
        }
        cur = cur->next;
        rank++;
    }
}
    //ѧ���ɼ�����
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
        printf("��ѧ����Ϣ\n");
        Wait();
        return;
    }

    int subjectChoice, orderChoice;
    printf("��ѡ������ʽ\n");
    printf("1. ���ĳɼ�  2. ��ѧ�ɼ�  3. Ӣ��ɼ�  4. �ܷ�\n");
    subjectChoice = SafeScanf(0, 4);

    if (subjectChoice < 1 || subjectChoice > 4) {
        system("cls");
        printf("�������\n");
        Wait();
        return;
    }

    system("cls");

    printf("1. �ɸߵ���  2. �ɵ͵���\n");
    orderChoice = SafeScanf(1, 2);

    if (orderChoice < 1 || orderChoice > 2) {
        system("cls");
        printf("�������\n");
        Wait();
        return;
    }
    SelectionSort(head, subjectChoice, orderChoice);

    system("cls");
    if (head->next == NULL) {
        printf("��ѧ����Ϣ\n");
        Wait();
        return;
    }
    ListNode* cur = head->next;
    printf("**************************************************************\n");
    printf("***                 \033[33m��ӭ����ѧ������ϵͳ\033[0m                   ***\n");
    printf("**************************************************************\n");
    printf("**************************************************************\n");
    printf("***  ����   ѧ��  ���ĳɼ�   ��ѧ�ɼ�   Ӣ��ɼ�   �ܳɼ�  ***\n");
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
    //�ɼ����ߴ���
void DelScore(ScoreList* scoreList, int position) {
    if (scoreList->next == NULL) {
        printf("�����б�Ϊ��\n");
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
        printf("��Ч��ѡ��δ�ҵ���λ�õ����߼�¼\033[0m\n");
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
    printf("\033[33m\033[1m�� %d �����߼�¼�Ѵ������\n", position);
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
        printf("�������\n");
        Wait();
        return;
    }

    system("cls");
    printf("����������������������\n");
    printf("����\033[33m\033[1m�� %d ��\033[0m����\n", count);
    printf("����������������������\n\n");

    printf("\033[33m\033[1m�˺�:%s\033[0m\n", cur->username);
    if (cur->flag == 1) {
        printf("\033[33m\033[1m�������ĳɼ�Ϊ:%d\033[0m\n\n", cur->score);
    }
    else if (cur->flag == 2) {
        printf("\033[33m\033[1m������ѧ�ɼ�Ϊ:%d\033[0m\n\n", cur->score);
    }
    else if (cur->flag == 3) {
        printf("\033[33m\033[1m����Ӣ��ɼ�Ϊ:%d\033[0m\n\n", cur->score);
    }

    printf("\033[33m\033[1m��������:%s\033[0m\n\n", cur->des);

    cur = cur->next;

    int choice = 0;

    printf("\n");
    printf("\033[33m\033[1m��ѡ�������\033[0m\n");
    printf("\033[33m\033[1m1. ͬ��\033[0m\n");
    printf("\033[33m\033[1m2. �ܾ�\033[0m\n");
    printf("\033[33m\033[1m0. ������һ��\033[0m\n");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("���޸�\n");
        DelScore(scoreList, position);
        break;    
    case 2:
        printf("�Ѳ���\n");
        DelScore(scoreList, position);
        break;
    case 0:
        return;
    default:
        printf("��Ч��ѡ��\n");
        break;
    }
}
void GradeUpdate(ScoreList* scoreList) {
    system("cls");
    ScoreList* cur = scoreList->next;

    if (cur == NULL) {
        printf("���������б�Ϊ��\n");
        Wait();
        return;
    }

    int count = 1;

    while (cur != NULL) {
        printf("����������������������\n");
        printf("����\033[33m\033[1m�� %d ��\033[0m����\n", count);
        printf("����������������������\n\n");

        printf("\033[33m\033[1m�˺�:%s\033[0m\n", cur->username);
        if (cur->flag == 1) {
            printf("\033[33m\033[1m�������ĳɼ�Ϊ:%d\033[0m\n", cur->score);
        } else if (cur->flag == 2) {
            printf("\033[33m\033[1m������ѧ�ɼ�Ϊ:%d\033[0m\n", cur->score);
        } else if (cur->flag == 3) {
            printf("\033[33m\033[1m����Ӣ��ɼ�Ϊ:%d\033[0m\n", cur->score);
        }

        printf("\033[33m\033[1m��������:%s\033[0m\n\n", cur->des);

        cur = cur->next;
        count++;
    }

    int position = 0;
    printf("\n");
    printf("\033[33m\033[1m��ѡ��鿴���������(0)�˳�:\033[0m");
    scanf("%d", &position);

    if (position == 0) {
        return;
    }
    HandleScore(scoreList, position);
}


//����Ա
  
    // ����鿴ɾ��
void DelTodo(TodoList* todoList, int position) {
    if (todoList->next == NULL) {
        printf("���������б�Ϊ��\n");
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
        printf("��Ч��ѡ��δ�ҵ���λ�õĴ�������\033[0m\n");
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
    printf("\033[33m\033[1m�� %d �����������Ѵ������\n", position);
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
        printf("�������\n");
        Wait();
        return;
    }
    
    system("cls");
    printf("����������������������\n");
    printf("����\033[33m\033[1m�� %d ��\033[0m����\n", position);
    printf("����������������������\n\n");

    printf("\033[33m\033[1m�˺�:%s\033[0m\n", cur->username);
    printf("\033[33m\033[1m%s\033[0m\n\n", cur->des);

    int choice = 0;

    printf("\n");
    printf("\033[33m\033[1m��ѡ�������\033[0m\n");
    printf("\033[33m\033[1m1. �Ѵ���\033[0m\n");
    printf("\033[33m\033[1m0. �˳�\033[0m\n");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("�����Ѵ������\n");
        DelTodo(todoList, position);
        break;
    case 0:
        break;
    default:
        printf("��Ч��ѡ��\n");
        Wait();
        break;
    }
}
void ViewTodo(TodoList* todoList) {
    system("cls");
    TodoList* cur = todoList->next;

    if (cur == NULL) {
        printf("���������б�Ϊ��\n");
        Wait();
        return;
    }

    int count = 1;

    while (cur != NULL) {
        printf("����������������������\n");
        printf("����\033[33m\033[1m�� %d ��\033[0m����\n", count);
        printf("����������������������\n\n");

        printf("\033[33m\033[1m�˺�:%s\033[0m\n", cur->username);
        printf("\033[33m\033[1m%s\033[0m\n\n", cur->des);
        cur = cur->next;
        count++;
    }

    int position = 0;
    printf("\n");
    printf("\033[33m\033[1m��ѡ��鿴���������(0)�˳�:\033[0m");
    scanf("%d", &position);

    if (position == 0) {
        return;
    }

    HandleTodo(todoList, position);
}
    //���������Ϣ
void AddUserInfo(UserList* userList) {
    UserList* cur = userList;
    UserList* newUser = (UserList*)malloc(sizeof(UserList));

    if (newUser == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // ����������Ϣ
    system("cls");
    printf("�������˺�:\n");
    scanf("%s", newUser->username);
    printf("����������:\n");
    scanf("%s", newUser->password);
    printf("��ѡ����ݣ�ѧ��->'S',��ʦ->'T'������Ա->'A'��:\n");
    scanf(" %c", &(newUser->role));

    // ���½ڵ���뵽����ĩβ
    newUser->next = cur->next;
    newUser->pre = cur;
    cur->next = newUser;

}
    //ɾ��������Ϣ
void DeleteUserInfo(UserList* userList) {
    char targetUsername[MAX_USERNAME];
    system("cls");
    printf("������Ҫɾ�����˺�:\n");
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
        printf("�˺� %s ɾ���ɹ���\n", targetUsername);
        Wait();
    } else {
        system("cls");
        printf("δ�ҵ��û� %s��\n", targetUsername);
        Wait();
    }
}
    //�޸�������Ϣ
void ModifyUserInfo(UserList* userList) {
    char targetUsername[MAX_USERNAME];
    system("cls");
    printf("������Ҫ�޸ĵ��˺�:\n");
    scanf("%s", targetUsername);

    UserList* cur = userList->next;

    // Ѱ��Ҫ�޸ĵĽڵ�
    while (cur != NULL && strcmp(cur->username, targetUsername) != 0) {
        cur = cur->next;
    }

    if (cur != NULL) {
        // ��ʾ�û������µ��˺ź�������Ϣ
        system("cls");
        printf("�������µ��˺�:\n");
        scanf("%s", cur->username);

        printf("�������µ�����:\n");
        scanf("%s", cur->password);

        printf("��ѡ���µ���ݣ�ѧ��->'S', ��ʦ->'T'������Ա->'A'��:\n");
        scanf(" %c", &(cur->role));

        system("cls");
        printf("�û� %s �޸ĳɹ���\n", targetUsername);
        Wait();
    }
    else {
        system("cls");
        printf("δ�ҵ��û� %s��\n", targetUsername);
        Wait();
    }
}
    //����������Ϣ
void FindUserInfo(UserList* userList) {
    char targetUsername[MAX_USERNAME];
    system("cls");
    printf("������Ҫ���ҵ��˺�:\n");
    scanf("%s", targetUsername);

    UserList* cur = userList->next;

    while (cur != NULL && strcmp(cur->username, targetUsername) != 0) {
        cur = cur->next;
    }

    if (cur != NULL) {
        system("cls");
        printf("�û���Ϣ��\n");
        printf("�˺�: %s\n", cur->username);
        printf("����: %s\n", cur->password);
        Wait();
    }
    else {
        system("cls");
        printf("δ�ҵ��û� %s��\n", targetUsername);
        Wait();
    }
}
    //�°༶��ʼ���˻�����
void InitialClassFromFile(ListNode* head, UserList* userList) {
    char username[MAX_USERNAME];
    char ch;
    system("cls");
    printf("�������ʼ���˺�����༶(1-5): ");
    while (1) {
        if (scanf(" %c", &ch) != 1 || (ch < '1' || ch > '5')) {
            printf("��Ч���룬����������(1-5): ");
            while (getchar() != '\n'); 
        }
        else {
            break;
        }
    }
    system("cls");
    printf(" %c ���������Ϣ�ѳ�ʼ��\n", ch);
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
    //���������Ϣ
void DisplayUserInfo(const UserList* userList) {
    system("cls");
    if (userList->next == NULL) {
        printf("��������Ϣ\n");
        Wait();
        return;
    }
    UserList* cur = userList->next;
    printf("*************************************************************\n");
    printf("\033[33m\033[1m%-5s\t%-5s\n\033[0m", "�˻�", "����");

    while (cur) {
        printf("\033[33m\033[1m%-6s\t%-6s\n\033[0m", cur->username, cur->password);
        cur = cur->next;
    }
    printf("*************************************************************\n");
    Wait();
}
    //�ֶ�����¼��ѧ����Ϣ 
void ReEnterStuInfo(ListNode* head) {
    char username[MAX_USERNAME];
    system("cls");
    printf("����������¼��ѧ���༶: ");
    char ch;
    while (1) {
        if (scanf(" %c", &ch) != 1 || (ch < '1' || ch > '5')) {
            printf("��Ч���룬����������(1-5): ");
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