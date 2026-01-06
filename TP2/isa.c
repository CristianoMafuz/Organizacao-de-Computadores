#include "isa.h"
#include "alu.h"
#include "memoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>


    Banco_reg aloca_registradores(int n)
    {   
        Banco_reg banco;
        banco.registradores = (Registrador*) malloc(n * sizeof(Registrador));
        return banco;
    }

    void desalocaRegistradores(Banco_reg banco)
    {
        free(banco.registradores);
        banco.registradores = NULL;
    }

    void operacao(char *instruction, ALU *alu) 
    {
        char comando[MAX_STR];
        sscanf(instruction, "%s", comando);

        if (!strcmp(comando, "ADD"))
            alu->opcode = 0b0000;

        else if (!strcmp(comando, "ADDI"))
            alu->opcode = 0b0001;

        else if (!strcmp(comando, "SUB"))
            alu->opcode = 0b0010;

        else if (!strcmp(comando, "DIV"))
            alu->opcode = 0b0011;

        else if (!strcmp(comando, "MUL"))
            alu->opcode = 0b0100;

        else if (!strcmp(comando, "REM"))
            alu->opcode = 0b0101;

        else if (!strcmp(comando, "BLT"))
            alu->opcode = 0b0110;

        else if (!strcmp(comando, "BEQ"))
            alu->opcode = 0b0111;

        else if (!strcmp(comando, "J"))
            alu->opcode = 0b1000;

        else if (!strcmp(comando, "DSP"))
            alu->opcode = 0b1001;

        else if (!strcmp(comando, "STI"))
            alu->opcode = 0b1010;

        else if (!strcmp(comando, "STO"))
            alu->opcode = 0b1011;

        else if (!strcmp(comando, "SUBI"))
            alu->opcode = 0b1100;

        else if (!strcmp(comando, "STOM"))
            alu->opcode = 0b1101;

        else if (!strcmp(comando, "DSPM"))
            alu->opcode = 0b1110;

        else
            alu->opcode = 0b1111;
    }


    void operacao_alu(Inst_mem *memoryOfInstructions, Banco_reg *banco, Main_mem *mainMemory, char *instruction, ALU* alu)
    {
        switch(alu->opcode)
        {
            case 0b000: // soma de registradores
                add(memoryOfInstructions, banco, instruction);
                break;

            case 0b001: // soma com valor inteiro
                addi(memoryOfInstructions, banco, instruction);
                break;

            case 0b010: // subtracao de registradores
                sub(memoryOfInstructions, banco, instruction);
                break;

            case 0b011: // divisao de registradores
                divi(memoryOfInstructions, banco, instruction);
                break;

            case 0b100: // multiplicacao de registradores
                mul(memoryOfInstructions, banco, instruction);
                break;

            case 0b101: // resto da divisao de registradores
                rem(memoryOfInstructions, banco, instruction);
                break;

            case 0b110: // condicional de comparacao R1<R2
                blt(memoryOfInstructions, banco, instruction);
                break;

            case 0b111: // condicional de comparacao R1<R2
                beq(memoryOfInstructions, banco, instruction);
                break;

            case 0b1000: // salto incondicional
                jump(memoryOfInstructions, instruction);
                break;

            case 0b1001: // imprimir o acc
                dsp(memoryOfInstructions, banco);
                break;

            case 0b1010: // atribuicao de constante ao registrador
                sti(memoryOfInstructions, banco, instruction);
                break;

            case 0b1011: // atribuicao do acc ao registrador
                sto(memoryOfInstructions, banco, instruction);
                break;

            case 0b1100: // subtracao com valor inteiro
                subi(memoryOfInstructions, banco, instruction);
                break;

            case 0b1101: // armazenar na memoria principal
                stom(memoryOfInstructions, banco, mainMemory);
                break;

            case 0b1110: // imprimir a memoria principal
                dspm(memoryOfInstructions, mainMemory);
                break;

            case 0b1111:
                memoryOfInstructions->linha++;
                break;
        }
    }
