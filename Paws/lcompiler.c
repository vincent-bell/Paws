#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <operations.h>

// expect fe ./paws compile examples/program1.iasm -o examples/outfile.asm

void lcompile_program (tuple *program, char *target_filename) {
    FILE *fptr = fopen(target_filename, "w");
    if (fptr == NULL) {
        fprintf(stderr, "Failed to find the file %s\n", target_filename);
        fflush(stderr);
        exit(1);
    }

    // make parts of this secton included only if the dump fn is included in program {@todo, @later}
    fprintf(fptr, "global _start\n\n");
    fprintf(fptr, "section .text\n\n");
    fprintf(fptr, "dump:\n");
    fprintf(fptr, "   sub rsp, 40\n");
    fprintf(fptr, "   mov ecx, 1\n");
    fprintf(fptr, "   mov r8, -3689348814741910323\n");
    fprintf(fptr, "   mov r10, rsp\n");
    fprintf(fptr, "   mov BYTE [rsp+31], 10\n");
    fprintf(fptr, "   lea r9, [r10+31]\n");
    fprintf(fptr, ".L2:\n");
    fprintf(fptr, "   mov rax, rdi\n");
    fprintf(fptr, "   mov rsi, r9\n");
    fprintf(fptr, "   mul r8\n");
    fprintf(fptr, "   sub rsi, rcx\n");
    fprintf(fptr, "   add rcx, 1\n");
    fprintf(fptr, "   shr rdx, 3\n");
    fprintf(fptr, "   lea rax, [rdx+rdx*4]\n");
    fprintf(fptr, "   add rax, rax\n");
    fprintf(fptr, "   sub rdi, rax\n");
    fprintf(fptr, "   add edi, 48\n");
    fprintf(fptr, "   test rdx, rdx\n");
    fprintf(fptr, "   mov BYTE [rsi], dil\n");
    fprintf(fptr, "   mov rdi, rdx\n");
    fprintf(fptr, "   jne .L2\n");
    fprintf(fptr, "   sub r10, rcx\n");
    fprintf(fptr, "   mov rdx, rcx\n");
    fprintf(fptr, "   mov edi, 1\n");
    fprintf(fptr, "   lea rsi, [r10+32]\n");
    fprintf(fptr, "   mov rax, 1\n");
    fprintf(fptr, "   syscall\n");
    fprintf(fptr, "   add rsp, 40\n");
    fprintf(fptr, "   ret\n");
    fprintf(fptr, "_start\n");

    int i = 0;
    while (program[i].size > 0 && i < 32) {
        signed int operation = program[i].ptr[0];
        i++;
        int lf = i - 1;
        assert(OP_COUNT == 6 && "The number of operations is currently out of sync");
        switch (operation) {
            case LFAST32:
                fprintf(fptr, "   push %d\n", program[lf].ptr[1]);
                free(program[lf].ptr);
                break;
            case S232_PLUS:
                fprintf(fptr, "   pop rax\n");
                fprintf(fptr, "   pop rbx\n");
                fprintf(fptr, "   add rax, rbx\n");
                fprintf(fptr, "   push rax\n");
                free(program[lf].ptr);
                break;
            case S232_MINUS:
                fprintf(fptr, "   pop rax\n");
                fprintf(fptr, "   pop rbx\n");
                fprintf(fptr, "   sub rbx, rax\n");
                fprintf(fptr, "   push rbx\n");
                free(program[lf].ptr);
                break;
            case S232_MULTIPLY:
                fprintf(fptr, "   pop rax\n");
                fprintf(fptr, "   pop rbx\n");
                fprintf(fptr, "   mul rbx\n");
                fprintf(fptr, "   push rax\n");
                free(program[lf].ptr);
                break;
            case DUMP64:
                fprintf(fptr, "   pop rdi\n");
                fprintf(fptr, "   call dump\n");
                free(program[lf].ptr);
                break;
        }
    }

    fprintf(fptr, "   mov rax, 60\n");
    fprintf(fptr, "   mov rdi, 0\n");
    fprintf(fptr, "   syscall\n");
}
