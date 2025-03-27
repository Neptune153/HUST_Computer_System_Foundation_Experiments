#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define STUDENTS_NUM  10

typedef struct temp {
    char  sname[8];
    char  sid[11];    //  如U202315123
    short  scores[8]; //  8门课的分数
    short  average;   //  平均分
}student;



void display(student* s, int num) {
    for (int i = 0; i < num; i++) {
        printf("学生%d: %s %s 各科成绩：", i, s[i].sname, s[i].sid);
        for (int j = 0; j < 8; j++) {
            printf("%d ", s[i].scores[j]);
        }
        printf("平均分：%d\n", s[i].average);
    }
}

void initStudents(student* s, int num) {
    strcpy(s[0].sname, "czh");
    strcpy(s[0].sid, "U202315513");
    for (int i = 0; i < 8; i++) {
        s[0].scores[i] = 75;
    }

    strcpy(s[1].sname, "aaa");
    strcpy(s[1].sid, "U202311111");
    for (int i = 0; i < 8; i++) {
        s[1].scores[i] = 77;
    }

    strcpy(s[2].sname, "bbb");
    strcpy(s[2].sid, "U202311177");
    for (int i = 0; i < 8; i++) {
        s[2].scores[i] = 60;
    }

    strcpy(s[3].sname, "ccc");
    strcpy(s[3].sid, "U202311122");
    for (int i = 0; i < 8; i++) {
        s[3].scores[i] = 80;
    }

    strcpy(s[4].sname, "ddd");
    strcpy(s[4].sid, "U202311199");
    for (int i = 0; i < 8; i++) {
        s[4].scores[i] = 90;
    }

    strcpy(s[5].sname, "eee");
    strcpy(s[5].sid, "U202311188");
    for (int i = 0; i < 8; i++) {
        s[5].scores[i] = 88;
    }

    strcpy(s[6].sname, "fff");
    strcpy(s[6].sid, "U202311133");
    for (int i = 0; i < 8; i++) {
        s[6].scores[i] = 70;
    }

    strcpy(s[7].sname, "ggg");
    strcpy(s[7].sid, "U202311144");
    for (int i = 0; i < 8; i++) {
        s[7].scores[i] = 66;
    }

    strcpy(s[8].sname, "hhh");
    strcpy(s[8].sid, "U202311155");
    for (int i = 0; i < 8; i++) {
        s[8].scores[i] = 69;
    }

    strcpy(s[9].sname, "iii");
    strcpy(s[9].sid, "U202311166");
    for (int i = 0; i < 8; i++) {
        s[9].scores[i] = 72;
    }

    for (int i = 0; i < num; i++) {
        s[i].average = 0;
    }
}

extern void computeAverageScore(student* s, int num);

/*
void computeAverageScore(student* s, int num) {
    for (int i = 0; i < num; i++) {
        int sum = 0;
        for (int j = 0; j < 8; j++) {
            sum += s[i].scores[j];
        }
        s[i].average = sum / 8;
    }
}
*/

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

/*
void sortStudentsByAverage(student* s, int low, int high){
    if(low < high){
        float pivot = s[high].average;
        int i = low - 1;
        for(int j=low; j<high; j++){
            if(s[j].average > pivot){
                i++;
                student temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
        student temp = s[i+1];
        s[i+1] = s[high];
        s[high] = temp;

        int pi = i+1;
        quickSort(s, low, pi-1);
        quickSort(s, pi+1, high);
    }
}
*/
int main()
{
    student s[STUDENTS_NUM];
    LARGE_INTEGER freq, start, end;
    double time;
    //printf("%d %0x\n", sizeof(student),&s);
    initStudents(s, STUDENTS_NUM);         // 初始化学生信息
    display(s, STUDENTS_NUM);


    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    computeAverageScore(s, STUDENTS_NUM);
    QueryPerformanceCounter(&end);
    time = (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    printf("计算平均成绩用时：%.3f ms\n", time);
    display(s, STUDENTS_NUM);


    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    computeAverageScore(s, STUDENTS_NUM);
    sortStudentsByAverage(s, STUDENTS_NUM);
    //sortStudentsByAverage(s, 0, STUDENTS_NUM-1);
    //time = (end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    printf("排序学生用时：%.3f ms\n", time);
    display(s, STUDENTS_NUM);

    return 0;


    /*

    */
}

