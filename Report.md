# Отчет по ИДЗ №2 
### Вариант 16, Асписов Дмитрий Алексеевич БПИ218
 
 
### Код на C на 5 баллов
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void count(char* string, int* digits, int* letters) {
    for (int i = 0; i < strlen(string); i++) 
    {  
        if (string[i] >= '0' && string[i] <= '9') {
            (*digits)++;
        } else if (string[i] >= 'A' && string[i] <= 'Z') {
            (*letters)++;
        } else if (string[i] >= 'a' && string[i] <= 'z') {
            (*letters)++;
        }
    }
}
   
int main()  
{   
    int digits = 0;
    int letters = 0;
    
    char string[10000]; 
    while (fgets(string, 10000, stdin)) {
        count(string, &digits, &letters);
    }
    
    printf("Digits: %d\n", digits);
    printf("Letters: %d", letters);
   
    return 0;  
}  
```

### Компиляция программы без дополнительных опций
```sh
gcc -masm=intel -S main.c -o main1.s
```

### Удаление макросов при помощи флага
```sh
gcc -O0 -Wall -masm=intel -S -fno-asynchronous-unwind-tables -fcf-protection=none main.c -o main2.s
```

### Тестирование

| Входные данные  | main1.s            | main2.s           |
|-----------------|:---------------:|:---------------:|
| hellloworld12345 | Digits: 5 Letters: 11 | Digits: 5 Letters: 11 |
| 1-2     | Digits: 2 Letters: 0   | Digits: 2 Letters: 0   |
| dima+12342   | Digits: 5 Letters: 4 | Digits: 5 Letters: 4 |
| +-=?| Digits: 0 Letters: 0|Digits: 0 Letters: 0|


### Комментарии в asm коде
```assembly
	.file	"main.c"
	.intel_syntax noprefix
	.text
	.globl	count
	.type	count, @function
count:    # вызов функции count с string в rdi, digits в rsi, letters в rdx
	push	rbp
	mov	rbp, rsp
	push	rbx
	sub	rsp, 56
	mov	QWORD PTR -40[rbp], rdi    	# string
	mov	QWORD PTR -48[rbp], rsi		# digits
	mov	QWORD PTR -56[rbp], rdx		# letters
	mov	DWORD PTR -20[rbp], 0		# локальная переменная i
	jmp	.L2
.L6:
	mov	eax, DWORD PTR -20[rbp]
	movsx	rdx, eax
	mov	rax, QWORD PTR -40[rbp]
	add	rax, rdx
	movzx	eax, BYTE PTR [rax]
	cmp	al, 47
	jle	.L3
	mov	eax, DWORD PTR -20[rbp]
	movsx	rdx, eax
	mov	rax, QWORD PTR -40[rbp]
	add	rax, rdx
	movzx	eax, BYTE PTR [rax]
	cmp	al, 57
	jg	.L3
	mov	rax, QWORD PTR -48[rbp]
	mov	eax, DWORD PTR [rax]
	lea	edx, 1[rax]
	mov	rax, QWORD PTR -48[rbp]
	mov	DWORD PTR [rax], edx
	jmp	.L4
.L3:
	mov	eax, DWORD PTR -20[rbp]
	movsx	rdx, eax
	mov	rax, QWORD PTR -40[rbp]
	add	rax, rdx
	movzx	eax, BYTE PTR [rax]
	cmp	al, 64
	jle	.L5
	mov	eax, DWORD PTR -20[rbp]
	movsx	rdx, eax
	mov	rax, QWORD PTR -40[rbp]
	add	rax, rdx
	movzx	eax, BYTE PTR [rax]
	cmp	al, 90
	jg	.L5
	mov	rax, QWORD PTR -56[rbp]
	mov	eax, DWORD PTR [rax]
	lea	edx, 1[rax]
	mov	rax, QWORD PTR -56[rbp]
	mov	DWORD PTR [rax], edx
	jmp	.L4
.L5:
	mov	eax, DWORD PTR -20[rbp]
	movsx	rdx, eax
	mov	rax, QWORD PTR -40[rbp]
	add	rax, rdx
	movzx	eax, BYTE PTR [rax]
	cmp	al, 96
	jle	.L4
	mov	eax, DWORD PTR -20[rbp]
	movsx	rdx, eax
	mov	rax, QWORD PTR -40[rbp]
	add	rax, rdx
	movzx	eax, BYTE PTR [rax]
	cmp	al, 122
	jg	.L4
	mov	rax, QWORD PTR -56[rbp]
	mov	eax, DWORD PTR [rax]
	lea	edx, 1[rax]
	mov	rax, QWORD PTR -56[rbp]
	mov	DWORD PTR [rax], edx
.L4:
	add	DWORD PTR -20[rbp], 1
.L2:
	mov	eax, DWORD PTR -20[rbp]
	movsx	rbx, eax
	mov	rax, QWORD PTR -40[rbp]
	mov	rdi, rax
	call	strlen@PLT
	cmp	rbx, rax
	jb	.L6
	nop
	nop
	mov	rbx, QWORD PTR -8[rbp]
	leave
	ret		# возврат из функции
	.size	count, .-count
	.section	.rodata
.LC0:
	.string	"Digits: %d\n"
.LC1:
	.string	"Letters: %d"
	.text
	.globl	main
	.type	main, @function
main:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 4096
	or	QWORD PTR [rsp], 0
	sub	rsp, 4096
	or	QWORD PTR [rsp], 0
	sub	rsp, 1840
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR -8[rbp], rax
	xor	eax, eax
	mov	DWORD PTR -10024[rbp], 0	# digits
	mov	DWORD PTR -10020[rbp], 0	# letters
	jmp	.L8
.L9:
	lea	rdx, -10020[rbp]
	lea	rcx, -10024[rbp]
	lea	rax, -10016[rbp]	# string
	mov	rsi, rcx
	mov	rdi, rax
	call	count    # вызов функции count с string в rdi, digits в rsi, letters в rdx
.L8:
	mov	rdx, QWORD PTR stdin[rip] # stdin
	lea	rax, -10016[rbp]	# string
	mov	esi, 10000	# 10000
	mov	rdi, rax	# string
	call	fgets@PLT	# вызов функции fgets с string в rdi, 10000 в esi, stdin в rdx
	test	rax, rax	# в rax лежит возвращаемое значение
	jne	.L9
	mov	eax, DWORD PTR -10024[rbp]
	mov	esi, eax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT	# вызов функции printf с digits в esi
	mov	eax, DWORD PTR -10020[rbp]
	mov	esi, eax
	lea	rax, .LC1[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT	# вызов функции printf с letters в esi
	mov	eax, 0
	mov	rdx, QWORD PTR -8[rbp]
	sub	rdx, QWORD PTR fs:40
	je	.L11
	call	__stack_chk_fail@PLT
.L11:
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
	.section	.note.GNU-stack,"",@progbits

```
