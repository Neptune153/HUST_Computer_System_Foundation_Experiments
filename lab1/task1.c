#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdint.h>

const int N = 5;
char message[1080];
int offset = 0;

typedef struct STUDENT {
    char name[8];
    short age;
    float score;
    char remark[200];
} student;

void init(student* s, int N);
int pack_student_bytebybyte(student* s, int sno, char* buf);
int pack_student_whole(student* s, int sno, char* buf);
int restore_student(char* buf, int len, student* s);
void printInfo(student* s);

int main() {
    student old_s[N];
    student new_s[N];
    int lengthBeforeRestore = sizeof(student) * 5;
    int lengthAfterRestore;

    //初始化
    init(old_s, N);

    printf("The information of the old_s: \n");
    printInfo(old_s);

    //压缩
    pack_student_bytebybyte(old_s, 2, message);
    pack_student_whole(&old_s[2], 3, message);
    lengthAfterRestore = offset;

    //解压缩
    restore_student(message, lengthAfterRestore, new_s);

    printf("The information of the new_s: \n");
    printInfo(new_s);

    printf("The length of the old_s: %d\n", lengthBeforeRestore);
    printf("The length after packed: %d\n", lengthAfterRestore);

    //打印message前40个字节的信息
    printf("\nThe first 40 bytes of message:\n");
    for (int i = 1; i <= 40; i++) {
        printf("%02X", message[i]);
        if(i%8==0)
            printf("\n");
    }
    return 0;
}

void init(student* old_s, int N) {

    // 初始化old_s
    strcpy(old_s[0].name, "xxx");
    old_s[0].age = 19;
    old_s[0].score = 13;
    strcpy(old_s[0].remark, "soso");

    strcpy(old_s[1].name, "aaa");
    old_s[1].age = 20;
    old_s[1].score = 50;
    strcpy(old_s[1].remark, "good");

    strcpy(old_s[2].name, "bbb");
    old_s[2].age = 21;
    old_s[2].score = 55;
    strcpy(old_s[2].remark, "great");

    strcpy(old_s[3].name, "ccc");
    old_s[3].age = 22;
    old_s[3].score = 60;
    strcpy(old_s[3].remark, "excellent");

    strcpy(old_s[4].name, "ddd");
    old_s[4].age = 23;
    old_s[4].score = 65;
    strcpy(old_s[4].remark, "amazing");
}
void printInfo(student* s) {
    for (int i = 0; i < N; i++) {
        printf("Student: %d, name: %s, age: %hd, score: %f , Remark:%s\n", i, s[i].name, s[i].age, s[i].score, s[i].remark);
    }
    printf("\n");
}
int pack_student_bytebybyte(student* s, int sno, char* buf) {
    for (int i = 0; i < sno; i++) {
        //name
        for (int j = 0; s[i].name[j] != '\0'; j++) {
            buf[offset++] = s[i].name[j];
        }
        buf[offset++] = '\0';
        //age
        buf[offset++] = (s[i].age) & 0xFF;
        buf[offset++] = (s[i].age >> 8) & 0xFF;
        //score
        uint32_t f2i = *(uint32_t*)&s[i].score;
        buf[offset++] = (f2i) & 0xFF;
        buf[offset++] = (f2i >> 8) & 0xFF;
        buf[offset++] = (f2i >> 16) & 0xFF;
        buf[offset++] = (f2i >> 24) & 0xFF;
        //remark
        for (int j = 0; s[i].remark[j] != '\0'; j++) {
            buf[offset++] = s[i].remark[j];
        }
        buf[offset++] = '\0';
    }
    return 0;
}
int pack_student_whole(student* s, int sno, char* buf) {
    for (int i = 0; i < sno; i++) {
        //name
        strcpy(&buf[offset], s[i].name);
        while (buf[offset] != '\0') offset++;
        offset++;
        //age
        *(short*)(buf + offset) = s[i].age;
        offset += sizeof(short);
        //score
        *(float*)(buf + offset) = s[i].score;
        offset += sizeof(float);
        //remark
        strcpy(&buf[offset], s[i].remark);
        while (buf[offset] != '\0') offset++;
        offset++;
    }
    return 0;
}
int restore_student(char* buf, int len, student* s) {
    int local_offset = 0;
    int num = 0;
    while (local_offset < len) {
        //name
        int i;
        for (i = 0; buf[local_offset] != '\0'; i++) {
            s[num].name[i] = buf[local_offset++];
        }
        s[num].name[i++] = buf[local_offset++];
        //age      
        s[num].age = *(short*)(buf + local_offset);
        local_offset += sizeof(short);
        //score
        s[num].score = *(float*)(buf + local_offset);
        local_offset += sizeof(float);
        //remark
        for (i = 0; buf[local_offset] != '\0'; i++) {
            s[num].remark[i] = buf[local_offset++];
        }
        s[num].remark[i++] = buf[local_offset++];
        num++;
    }
    return 0;
}
