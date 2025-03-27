#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define STUDENTS_NUM 10000  

typedef struct temp {
    char  sname[8];
    char  sid[11];    //  如U202315123
    short  scores[8]; //  8门课的分数
    short  average;   //  平均分
}student;

void initStudents(student* s, int num) {
    srand((unsigned int)time(NULL));

    sprintf(s[0].sname, "S0xxx");
    sprintf(s[0].sid, "U202xxxxxx");
    for (int j = 0; j < 8; j++) {
        s[0].scores[j] = rand() % 80 + 20;
    }
    s[0].average = 0;

    for (int i = 1; i < num; i++) {

        sprintf(s[i].sname, "S%04d", i);
        sprintf(s[i].sid, "U0000%05d", i);
        for (int j = 0; j < 8; j++) {
            s[i].scores[j] = rand() % 80 + 20;
        }
        s[i].average = 0;
    }
}

void display(student* s, int num) {
    printf("前五位：\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\t %s\t各科成绩：", s[i].sname, s[i].sid);
        for (int j = 0; j < 8; j++) {
            printf("%d ", s[i].scores[j]);
        }
        printf("平均分：%d\n", s[i].average);
    }
    printf("后五位：\n");
    for (int i = num - 5; i < num; i++) {
        printf("%s\t %s\t各科成绩：", s[i].sname, s[i].sid);
        for (int j = 0; j < 8; j++) {
            printf("%d ", s[i].scores[j]);
        }
        printf("平均分：%d\n", s[i].average);
    }
}

extern void computeAverageScore(student* s, int num);


/*
void sortStudentsByAverage(student* s, int num) {
    for (int i = 0; i < num - 1; i++) {
        for (int j = 0; j < num - i - 1; j++) {
            if (s[j].average < s[j + 1].average) {
                student temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}
*/

void sortStudentsByAverage(student* s, int low, int high) {
    if (low < high) {
        float pivot = s[high].average;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (s[j].average > pivot) {
                i++;
                student temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
        student temp = s[i + 1];
        s[i + 1] = s[high];
        s[high] = temp;

        int pi = i + 1;
        sortStudentsByAverage(s, low, pi - 1);
        sortStudentsByAverage(s, pi + 1, high);
    }
}

int main() {
    student* s = malloc(STUDENTS_NUM * sizeof(student));
    initStudents(s, STUDENTS_NUM);
    display(s, STUDENTS_NUM);
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    // 测试计算平均分性能
    QueryPerformanceCounter(&start);
    computeAverageScore(s, STUDENTS_NUM);
    QueryPerformanceCounter(&end);

    double compute_time = (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    printf("\n计算平均分用时：%.2f ms\n", compute_time);
    display(s, STUDENTS_NUM);

    // 测试排序性能
    QueryPerformanceCounter(&start);
    //sortStudentsByAverage(s, STUDENTS_NUM);
    sortStudentsByAverage(s, 0, STUDENTS_NUM - 1);
    QueryPerformanceCounter(&end);

    double sort_time = (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    printf("\n排序用时：%.2f ms\n", sort_time);
    display(s, STUDENTS_NUM);

    free(s);
    return 0;
}

