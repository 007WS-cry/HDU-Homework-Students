/**
 * 文件名: Students/students.h
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

#ifndef STUDENTS_H
#define STUDENTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

typedef struct Node *pNode, Node;

int getGrade(int score);
void init(int m);
void writeInfo(const char *tmp_name, const char *tmp_number);
void writeScore(char *tmp_number, int tmp_m, double tmp_score);
void deleteNode(const char *tmp_number);
pNode findNodeNumber(const char *tmp_number);
pNode fineNodeName(const char *tmp_name);
void turnInfo(char *tmp_number, int tmp_m, double tmp_score);
double calScore(const char *tmp_number, int tmp_m);
double calTotalScore(const char *tmp_number);
pNode mergeNumber(pNode head);
pNode mergeScore(pNode head, int compare_number);
pNode mergeName(pNode head);
void sortNumber();
void sortScore(int compare_number);
void sortName();
void statusPrint(int tmp_m);
void printInfo();
void writeToFile(char *path);
void readFromFile(char *path);
void SetPos(int x, int y);

#endif //STUDENTS_H
