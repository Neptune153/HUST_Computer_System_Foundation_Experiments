.686P
.model flat, c
printf proto c :ptr sbyte, :vararg
includelib  libcmt.lib
includelib  legacy_stdio_definitions.lib 

student  struct
    sname   db   8 dup(0)      ; 学生姓名，8字节
    sid     db   11 dup(0)     ; 学号，11字节
    scores  dw   8 dup(0)      ; 8门课的成绩，每个成绩占2字节
    average dw   0             ; 平均成绩，占2字节
student   ends

.code
; 计算平均成绩
; sptr 学生数组的首地址
; num  学生人数
computeAverageScore proc sptr: dword, num:dword
    push esi
    push edi
    mov esi, [sptr]         ; 学生数组地址
    mov ecx, [num]          ; 学生数量

loop_students:
    xor eax, eax            ; 总分清零
    lea edi, [esi].student.scores+1 ; scores数组地址
    mov edx, 8              ; 循环计数器

score_loop:
    add ax, word ptr [edi]  ; 累加分数
    add edi, 2              ; 移动到下一个分数
    dec edx
    jnz score_loop

    
    xor edx, edx            ; 清零DX，确保被除数为DX:AX = 0:sum
    mov bx, 8               ; 除数
    div bx                  ; ax = sum / 8，余数在DX

    mov [esi].student.average+1, ax ; 存储平均分
    add esi, 38             ; 移动到下一个学生（每个学生38字节）
    dec ecx
    jnz loop_students

    pop edi
    pop esi
    ret
computeAverageScore endp
end