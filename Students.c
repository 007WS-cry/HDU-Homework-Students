/**
 * 文件名: Students/students.c
 * 项目名称: Students
 * 文件创建日期: 2025-03-13
 * 作者: 007WS
 * 联系方式: a2901805528@163.com
 *
 * 最后编辑日期: 2025-03-26
 * 最后编辑者: 007WS
 * 最后编辑者联系方式: a2901805528@163.com
 *
 * 文件描述:
 * C语言学生成绩管理系统
 *
 * 许可证:
 * 无
 */

#include "Students.h"

int class_number;
int scoreStatus[30][5];
enum IDENTIFY {TEACHER, STUDENT} identify;
struct Node {
    char _name[50];
    char _number[10];
    double _scores[30];
    double _total_score;
    struct Node *_next;
    struct Node *_prev;
} *phead, *ptail;
char def_password[20] = "admin";

void SetPos(int x, int y) {
    HANDLE tOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD tPos = {x, y};
    SetConsoleCursorPosition(tOut, tPos);
}

void init(int m) {
    class_number = m;
    phead = NULL;
    ptail = NULL;
    system("color 0a");
    system("mode con cols=120 lines=40");
    SetConsoleTitleA("\xD1\xA7\xC9\xFA\xB3\xC9\xBC\xA8\xB9\xDC\xC0\xED\xCF\xB5\xCD\xB3");
    system("pause");
    HANDLE tOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(tOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(tOut, &cursorInfo);
    SetPos(10, 10);
    wprintf(L"输入账号：");
    char account[20];
    scanf("%s", account);
    identify = STUDENT;
    if (strcmp(account, "admin") == 0) {
        SetPos(10, 12);
        wprintf(L"输入密码：");
        char password[20];
        scanf("%s", password);
        if (strcmp(password, def_password) == 0) {
            identify = TEACHER;
        }
    }
    while (1) {
        system("cls");
        SetPos(84, 2);
        wprintf(L"操作：");
        int i = 8;
        while (i <= 42) {
            SetPos(84, i - 4);
            switch (i) {
                case 8:
                    wprintf(L"1.输入学生信息");
                break;
                case 10:
                    wprintf(L"2.增加学生成绩");
                break;
                case 12:
                    wprintf(L"3.删除学生信息");
                break;
                case 14:
                    wprintf(L"4.按学号查找记录");
                break;
                case 16:
                    wprintf(L"5.按姓名查找记录");
                break;
                case 18:
                    wprintf(L"6.修改学生信息");
                break;
                case 20:
                    wprintf(L"7.计算学生成绩");
                break;
                case 22:
                    wprintf(L"8.计算课程成绩");
                break;
                case 24:
                    wprintf(L"9.按学号排序");
                break;
                case 26:
                    wprintf(L"10.按姓名排序");
                break;
                case 28:
                    wprintf(L"11.按总成绩降序排序");
                break;
                case 30:
                    wprintf(L"12.按总成绩升序排序");
                break;
                case 32:
                    wprintf(L"13.学生成绩统计");
                break;
                case 34:
                    wprintf(L"14.打印学生记录");
                break;
                case 36:
                    wprintf(L"15.学生记录存盘");
                break;
                case 38:
                    wprintf(L"16.从磁盘读取学生记录");
                    break;
                case 40:
                    wprintf(L"17.修改密码（仅admin）");
                    break;
                default:
                    wprintf(L"0.退出系统");
                    break;
            }
            i += 2;
        }
        SetPos(0, 2);
        wprintf(L"学生成绩管理系统");
        SetPos(0, 4);
        wprintf(L"请输入操作码：");
        char str[100];
        scanf("%s", str);
        if (strcmp(str, "1") == 0) {
            SetPos(0, 6);
            wprintf(L"请输入学生姓名：");
            char tmp_name[50];
            scanf("%s", tmp_name);
            SetPos(0, 8);
            wprintf(L"请输入学生学号：");
            char tmp_number[10];
            scanf("%s", tmp_number);
            SetPos(0, 10);
            writeInfo(tmp_name, tmp_number);
        }
        else if (strcmp(str, "2") == 0) {
            SetPos(0, 6);
            wprintf(L"请输入学生学号：");
            char tmp_number[10];
            scanf("%s", tmp_number);
            SetPos(0, 8);
            wprintf(L"请输入需要增加的课程成绩数量：");
            int tmp_num;
            scanf("%d", &tmp_num);
            int tmp_m;
            double tmp_score;
            for (int j = 0; j < tmp_num; j++) {
                SetPos(0, 10);
                for (int g = 0; g < 50; g++) {
                    printf(" ");
                }
                SetPos(0, 10);
                wprintf(L"请输入学生课程号与课程成绩（空格分割）：");
                scanf("%d%lf", &tmp_m, &tmp_score);
                SetPos(0, 10);
                writeScore(tmp_number, tmp_m, tmp_score);
            }
        }
        else if (strcmp(str, "3") == 0) {
            SetPos(0, 6);
            wprintf(L"请输入学生学号：");
            char tmp_number[10];
            scanf("%s", tmp_number);
            SetPos(0, 8);
            deleteNode(tmp_number);
        }
        else if (strcmp(str, "4") == 0) {
            SetPos(0, 6);
            wprintf(L"请输入学生学号：");
            char tmp_number[10];
            scanf("%s", tmp_number);
            pNode pts = findNodeNumber(tmp_number);
            SetPos(0, 8);
            if (pts == NULL) {
                wprintf(L"没有找到学生！");
                return;
            }
            wprintf(L"姓名：%hs 学号：%hs 成绩：%.5lf", pts->_name, pts->_number, pts->_total_score);
        }
        else if (strcmp(str, "5") == 0) {
            SetPos(0, 6);
            wprintf(L"请输入学生姓名：");
            char tmp_name[50];
            scanf("%s", tmp_name);
            pNode pts = findNodeNumber(tmp_name);
            SetPos(0, 8);
            if (pts == NULL) {
                wprintf(L"没有找到学生！");
                return;
            }
            wprintf(L"姓名：%hs 学号：%hs 成绩：%.5lf", pts->_name, pts->_number, pts->_total_score);
        }
        else if (strcmp(str, "6") == 0) {
            SetPos(0, 6);
            wprintf(L"请输入学生学号：");
            char tmp_number[10];
            scanf("%s", tmp_number);
            SetPos(0, 8);
            wprintf(L"请输入学生课程号与课程成绩（空格分割）：");
            int tmp_m;
            double tmp_score;
            scanf("%d%lf", &tmp_m, &tmp_score);
            SetPos(0, 10);
            turnInfo(tmp_number, tmp_m, tmp_score);
        }
        else if (strcmp(str, "7") == 0) {
            SetPos(0, 6);
            wprintf(L"请输入学生学号：");
            char tmp_number[10];
            scanf("%s", tmp_number);
            double score = calTotalScore(tmp_number);
            SetPos(0, 8);
            wprintf(L"该学生总成绩为：%.5lf", score);
        }
        else if (strcmp(str, "8") == 0) {
            SetPos(0, 6);
            wprintf(L"请输入学生学号与课程号（空格分割）：");
            char tmp_number[10];
            int tmp_m;
            scanf("%s%d", tmp_number, &tmp_m);
            double score = calScore(tmp_number, tmp_m);
            SetPos(0, 8);
            wprintf(L"该学生该科目的成绩为：%.5lf", score);
        }
        else if (strcmp(str, "9") == 0) {
            SetPos(0, 10);
            sortNumber();
        }
        else if (strcmp(str, "10") == 0) {
            SetPos(0, 10);
            sortName();
        }
        else if (strcmp(str, "11") == 0) {
            SetPos(0, 10);
            sortScore(1);
        }
        else if (strcmp(str, "12") == 0) {
            SetPos(0, 10);
            sortScore(0);
        }
        else if (strcmp(str, "13") == 0) {
            SetPos(0, 6);
            wprintf(L"请输入课程号：");
            int tmp_m;
            scanf("%d", &tmp_m);
            SetPos(0, 8);
            statusPrint(tmp_m);
        }
        else if (strcmp(str, "14") == 0) {
            SetPos(0, 10);
            printInfo();
        }
        else if (strcmp(str, "15") == 0) {
            SetPos(0, 6);
            wprintf(L"请输入文件路径：");
            char path[100];
            scanf("%s", path);
            SetPos(0, 8);
            writeToFile(path);
        }
        else if (strcmp(str, "16") == 0) {
            SetPos(0, 6);
            wprintf(L"请输入文件路径：");
            char path[100];
            scanf("%s", path);
            SetPos(0, 8);
            readFromFile(path);
        }
        else if (strcmp(str, "17") == 0) {
            SetPos(0, 6);
            wprintf(L"输入原密码：");
            char tmp[20];
            scanf("%s", tmp);
            if (strcmp(tmp, def_password) == 0) {
                SetPos(0, 8);
                wprintf(L"请输入新密码：");
                scanf("%s", def_password);
                SetPos(0, 10);
                wprintf(L"密码修改成功！");
            }
            else {
                wprintf(L"密码错误！");
            }
        }
        else if (strcmp(str, "0") == 0) {
            exit(0);
        }
        SetPos(40, 14);
        wprintf(L"操作完成！");
        SetPos(40, 16);
        wprintf(L"是否退出(y/n)");
        char op;
        getchar();
        scanf("%c", &op);
        if (op == 'y' || op == 'Y') {
            exit(0);
        }
    }
}

int getGrade(int score) {
    if (score >= 90) {
        return 0;
    }
    else if (score >= 80) {
        return 1;
    }
    else if (score >= 70) {
        return 2;
    }
    else if (score >= 60) {
        return 3;
    }
    else {
        return 4;
    }
}

void writeInfo(const char *tmp_name, const char *tmp_number) {
    if (identify == STUDENT) {
        wprintf(L"无权限进行此操作！");
        return;
    }
    if (ptail == NULL) {
        phead = malloc(sizeof(Node));
        strcpy(phead->_name, tmp_name);
        strcpy(phead->_number, tmp_number);
        phead->_total_score = 0;
        for (int i = 0; i < class_number; i++) {
            phead->_scores[i] = 0;
        }
        phead->_next = NULL;
        phead->_prev = NULL;
        ptail = phead;
    }
    else {
        pNode pts = malloc(sizeof(Node));
        strcpy(pts->_name, tmp_name);
        strcpy(pts->_number, tmp_number);
        pts->_total_score = 0;
        for (int i = 0; i < class_number; i++) {
            pts->_scores[i] = 0;
        }
        pts->_next = NULL;
        pts->_prev = ptail;
        ptail->_next = pts;
        ptail = pts;
    }
}

void writeScore(char *tmp_number, int tmp_m, double tmp_score) {
    if (identify == STUDENT) {
        wprintf(L"无权限进行此操作！");
        return;
    }
    pNode pts = findNodeNumber(tmp_number);
    if (pts == NULL) {
        wprintf(L"没有找到学生！\n");
        return;
    }
    if (pts->_scores[tmp_m] != 0) {
        wprintf(L"该学生已经存在该科目的成绩，请使用6号操作！\n");
    }
    pts->_scores[tmp_m] = tmp_score;
    pts->_total_score += tmp_score;
    scoreStatus[tmp_m][getGrade(tmp_score)]++;
    SetPos(0, 25);
    wprintf(L"已输入学号为%hs的学生的%02d科目成绩！\n", tmp_number, tmp_m);
}

void deleteNode(const char *tmp_number) {
    if (identify == STUDENT) {
        wprintf(L"无权限进行此操作！");
        return;
    }
    pNode pts = findNodeNumber(tmp_number);
    if (pts == NULL) {
        wprintf(L"没有找到学生！\n");
        return;
    }
    for (int i = 0; i < class_number; i++) {
        scoreStatus[i][getGrade(pts->_scores[i])]--;
    }
    if (pts->_prev == NULL) {
        phead = pts->_next;
    }
    else {
        pts->_prev->_next = pts->_next;
    }
    if (pts->_next == NULL) {
        ptail = pts->_prev;
    }
    else {
        pts->_next->_prev = pts->_prev;
    }
    wprintf(L"删除成功！\n");
}

pNode findNodeNumber(const char *tmp_number) {
    pNode pts = phead;
    while (pts != NULL) {
        if (strcmp(pts->_number, tmp_number) == 0) {
            break;
        }
        pts = pts->_next;
    }
    return pts;
}

pNode findNodeName(const char *tmp_name) {
    pNode pts = phead;
    while (pts != NULL) {
        if (strcmp(pts->_name, tmp_name) == 0) {
            break;
        }
        pts = pts->_next;
    }
    return pts;
}

void turnInfo(char *tmp_number, int tmp_m, double tmp_score) {
    if (identify == STUDENT) {
        wprintf(L"无权限进行此操作！");
        return;
    }
    pNode pts = findNodeNumber(tmp_number);
    if (pts == NULL) {
        wprintf(L"没有找到学生！\n");
        return;
    }
    pts->_total_score -= pts->_scores[tmp_m];
    scoreStatus[tmp_m][getGrade(pts->_scores[tmp_m])]--;
    pts->_scores[tmp_m] = tmp_score;
    scoreStatus[tmp_m][getGrade(tmp_score)]++;
    pts->_total_score += tmp_score;
    wprintf(L"已修改学号为%hs的学生的%02d科目成绩！", tmp_number, tmp_m);
}

double calScore(const char *tmp_number, int tmp_m) {
    pNode pts = findNodeNumber(tmp_number);
    if (pts == NULL) {
        wprintf(L"没有找到学生！\n");
        return -1;
    }
    return pts->_scores[tmp_m];
}

double calTotalScore(const char *tmp_number) {
    pNode pts = findNodeNumber(tmp_number);
    if (pts == NULL) {
        wprintf(L"没有找到学生！\n");
        return -1;
    }
    return pts->_total_score;
}

pNode mergeNumber(pNode head) {
    if (head == NULL || head->_next == NULL) {
        return head;
    }
    pNode slow = head, fast = head->_next;
    while (fast != NULL && fast->_next != NULL) {
        slow = slow->_next;
        fast = fast->_next->_next;
    }
    pNode right = slow->_next;
    slow->_next = NULL;
    pNode left = mergeNumber(head);
    right = mergeNumber(right);
    Node ts;
    pNode pts = &ts;
    ts._next = NULL;
    while (left != NULL && right != NULL) {
        if (strcmp(left->_number, right->_number) < 0) {
            pts->_next = left;
            left = left->_next;
        }
        else {
            pts->_next = right;
            right = right->_next;
        }
        pts = pts->_next;
    }
    if (left == NULL) {
        pts->_next = right;
    }
    else {
        pts->_next = left;
    }
    return ts._next;
}

pNode mergeScore(pNode head, int compare_number) {
    if (head == NULL || head->_next == NULL) {
        return head;
    }
    pNode slow = head, fast = head->_next;
    while (fast != NULL && fast->_next != NULL) {
        slow = slow->_next;
        fast = fast->_next->_next;
    }
    pNode right = slow->_next;
    slow->_next = NULL;
    pNode left = mergeScore(head, compare_number);
    right = mergeScore(right, compare_number);
    Node ts;
    pNode pts = &ts;
    ts._next = NULL;
    while (left != NULL && right != NULL) {
        if (compare_number == 0 ? left->_total_score < right->_total_score : left->_total_score > right->_total_score) {
            pts->_next = left;
            left = left->_next;
        }
        else {
            pts->_next = right;
            right = right->_next;
        }
        pts = pts->_next;
    }
    if (left == NULL) {
        pts->_next = right;
    }
    else {
        pts->_next = left;
    }
    return ts._next;
}

pNode mergeName(pNode head) {
    if (head == NULL || head->_next == NULL) {
        return head;
    }
    pNode slow = head, fast = head->_next;
    while (fast != NULL && fast->_next != NULL) {
        slow = slow->_next;
        fast = fast->_next->_next;
    }
    pNode right = slow->_next;
    slow->_next = NULL;
    pNode left = mergeName(head);
    right = mergeName(right);
    Node ts;
    pNode pts = &ts;
    ts._next = NULL;
    while (left != NULL && right != NULL) {
        if (strcmp(left->_name, right->_name) < 0) {
            pts->_next = left;
            left = left->_next;
        }
        else {
            pts->_next = right;
            right = right->_next;
        }
        pts = pts->_next;
    }
    if (left == NULL) {
        pts->_next = right;
    }
    else {
        pts->_next = left;
    }
    return ts._next;
}

void sortNumber() {
    if (identify == STUDENT) {
        wprintf(L"无权限进行此操作！");
        return;
    }
    mergeNumber(phead);
}

void sortScore(int compare_number) {
    if (identify == STUDENT) {
        wprintf(L"无权限进行此操作！");
        return;
    }
    mergeScore(phead, compare_number);
}

void sortName() {
    if (identify == STUDENT) {
        wprintf(L"无权限进行此操作！");
        return;
    }
    mergeName(phead);
}

void statusPrint(int tmp_m) {
    if (tmp_m < 0 || tmp_m > class_number) {
        wprintf(L"非法课程号！\n");
    }
    wprintf(L"课程%02d信息：\n", tmp_m);
    wprintf(L"90分及以上人数：%03d\n", scoreStatus[tmp_m][0]);
    wprintf(L"80-89分人数：%03d\n", scoreStatus[tmp_m][1]);
    wprintf(L"70-79分人数：%03d\n", scoreStatus[tmp_m][2]);
    wprintf(L"60-69分人数：%03d\n", scoreStatus[tmp_m][3]);
    wprintf(L"60分以下人数：%03d\n", scoreStatus[tmp_m][4]);
    printf("\n");
}

void printInfo() {
    if (identify == STUDENT) {
        wprintf(L"无权限进行此操作！");
        return;
    }
    pNode pts = phead;
    if (pts == NULL) {
        wprintf(L"无学生数据！\n");
        return;
    }
    while (pts != NULL) {
        wprintf(L"姓名：%hs\n", pts->_name);
        wprintf(L"学号：%hs\n", pts->_number);
        wprintf(L"总分：%05lf\n", pts->_total_score);
        printf("\n");
        pts = pts->_next;
    }
}

void writeToFile(char *path) {
    if (identify == STUDENT) {
        wprintf(L"无权限进行此操作！");
        return;
    }
    FILE *fp = fopen(path, "w, ccs = UTF-8");
    if (fp == NULL) {
        wprintf(L"打开文件失败！");
    }
    pNode pts = phead;
    fprintf(fp, "姓名\t学号\t总分\t");
    for (int i = 0; i < class_number; i++) {
        if (i == class_number - 1) {
            fprintf(fp, "%02d\n", i);
        }
        else {
            fprintf(fp, "%02d\t", i);
        }
    }
    while (pts != NULL) {
        fprintf(fp, "%s\t%s\t%05lf\t", pts->_name, pts->_number, pts->_total_score);
        for (int i = 0; i < class_number; i++) {
            if (i == class_number - 1) {
                fprintf(fp, "%05lf\n", pts->_scores[i]);
            }
            else {
                fprintf(fp, "%05lf\t", pts->_scores[i]);
            }
        }
        pts = pts->_next;
    }
    fclose(fp);
    wprintf(L"已将学生信息读入至%hs！\n", path);
}

void readFromFile(char *path) {
    if (identify == STUDENT) {
        wprintf(L"无权限进行此操作！");
        return;
    }
    FILE *fp = fopen(path, "r, ccs = UTF-8");
    if (fp == NULL) {
        wprintf(L"打开文件失败！");
    }
    pNode pts = phead;
    if (pts == NULL) {
        wprintf(L"未初始化链表！\n");
        return;
    }
    char tmp_str[100];
    int tmp_num;
    fscanf(fp, "%s\t%s\t%s\t", tmp_str, tmp_str, tmp_str);
    for (int i = 0; i < class_number; i++) {
        if (i == class_number - 1) {
            fscanf(fp, "%02d\n", &tmp_num);
        }
        else {
            fscanf(fp, "%02d\t", &tmp_num);
        }
    }
    fscanf(fp, "%s\t%s\t%lf\t", pts->_name, pts->_number, &pts->_total_score);
    for (int i = 0; i < class_number; i++) {
        fscanf(fp, "%lf", &pts->_scores[i]);
    }
    char tmp_name[50], tmp_number[50];
    while (fscanf(fp, "%s\t%s\t%lf\t", tmp_name, tmp_number, &tmp_num) != EOF) {
        pNode qts = malloc(sizeof(Node));
        strcpy(qts->_name, tmp_name);
        strcpy(qts->_number, tmp_number);
        qts->_total_score = tmp_num;
        for (int i = 0; i < class_number; i++) {
            fscanf(fp, "%lf", &qts->_scores[i]);
        }
        qts->_next = NULL;
        pts->_next = qts;
        qts->_prev = pts;
        ptail = qts;
        pts = pts->_next;
    }
    fclose(fp);
    wprintf(L"已从%hs文件中读入学生信息！\n", path);
}