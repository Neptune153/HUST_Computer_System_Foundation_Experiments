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
    mov esi, [sptr]         ; 学生数组地址
    mov ecx, [num]          ; 学生数量

loop_students:
    xor ax, ax         
    add ax, word ptr [esi + 20]   
    add ax, word ptr [esi + 22]  
    add ax, word ptr [esi + 24]   
    add ax, word ptr [esi + 26]   
    add ax, word ptr [esi + 28]   
    add ax, word ptr [esi + 30]  
    add ax, word ptr [esi + 32]   
    add ax, word ptr [esi + 34]   

    shr ax, 3  
    mov [esi+36], ax  

    add esi, 38             
    dec ecx
    jnz loop_students

    pop esi
    ret  
computeAverageScore endp
end
;减少寄存器使用和简化地址计算