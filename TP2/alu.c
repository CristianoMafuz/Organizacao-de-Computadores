#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include "isa.h"
#include "memoria.h"

    //funcao que recebe uma string e encontra um registrador
    int encontra_registrador(char *reg_string)
    {
        uint8_t reg;
        if(strlen(reg_string) == 2)
        {
            reg = reg_string[1] - '0';
            return reg;
        }
        else
        {
            reg = 10 + (reg_string[2] - '0');
            return reg;
        }
    }

    //funcao auxiliar para imprimir a memoria principal
    void printBinary20Bits(int value) {
        for (int i = 19; i >= 0; i--) {
            printf("%d", (value & (1 << i)) ? 1 : 0);
        }
    }

    //funcao que soma dois regsitradores e atribui o resultado ao ACC
    void add(Inst_mem *memoryOfInstructions, Banco_reg *banco, char *instruction)
    {
        char reg_1[MAX_STR], reg_2[MAX_STR];

        sscanf(instruction, "%*s%s%s", reg_1, reg_2);

        Instrucao regs;

        regs.Reg1 = encontra_registrador(reg_1);
        regs.Reg2 = encontra_registrador(reg_2);

        banco->acc = banco->registradores[regs.Reg1].valor + banco->registradores[regs.Reg2].valor;
        memoryOfInstructions->linha++;
    }

    //funcao que subtrai dois regsitradores e atribui o resultado ao ACC
    void sub(Inst_mem *memoryOfInstructions, Banco_reg *banco, char *instruction)
    {
        char reg_1[MAX_STR], reg_2[MAX_STR];

        sscanf(instruction, "%*s%s%s", reg_1, reg_2);

        Instrucao regs;

        regs.Reg1 = encontra_registrador(reg_1);
        regs.Reg2 = encontra_registrador(reg_2);

        banco->acc = banco->registradores[regs.Reg1].valor - banco->registradores[regs.Reg2].valor;
        memoryOfInstructions->linha++;
    }

    //funcao que multiplica dois regsitradores e atribui o resultado ao ACC
    void mul(Inst_mem *memoryOfInstructions, Banco_reg *banco, char *instruction)
    {
        char reg_1[MAX_STR], reg_2[MAX_STR];

        sscanf(instruction, "%*s%s%s", reg_1, reg_2);

        Instrucao regs;

        regs.Reg1 = encontra_registrador(reg_1);
        regs.Reg2 = encontra_registrador(reg_2);

        banco->acc = banco->registradores[regs.Reg1].valor * banco->registradores[regs.Reg2].valor;
        memoryOfInstructions->linha++;
    }

    //funcao que divide o valor de dois regsitradores e atribui o resultado ao ACC
    void divi(Inst_mem *memoryOfInstructions, Banco_reg *banco, char *instruction)
    {
        char reg_1[MAX_STR], reg_2[MAX_STR];

        sscanf(instruction, "%*s%s%s", reg_1, reg_2);

        Instrucao regs;

        regs.Reg1 = encontra_registrador(reg_1);
        regs.Reg2 = encontra_registrador(reg_2);

        banco->acc = banco->registradores[regs.Reg1].valor / banco->registradores[regs.Reg2].valor;
        memoryOfInstructions->linha++;
    }

    //funcao que o resto da divisao de dois regsitradores e atribui o resultado ao ACC
    void rem(Inst_mem *memoryOfInstructions, Banco_reg *banco, char *instruction)
    {
        char reg_1[MAX_STR], reg_2[MAX_STR];

        sscanf(instruction, "%*s%s%s", reg_1, reg_2);

        Instrucao regs;

        regs.Reg1 = encontra_registrador(reg_1);
        regs.Reg2 = encontra_registrador(reg_2);

        banco->acc = (int) banco->registradores[regs.Reg1].valor % (int) banco->registradores[regs.Reg2].valor;
        memoryOfInstructions->linha++;
    }

    //funcao que soma o valor de um registrador a uma constante e atribui o resultado ao proprio registrador e ao ACC
    void addi(Inst_mem *memoryOfInstructions, Banco_reg *banco, char *instruction)
    {
        char reg[MAX_STR];
        uint8_t constante;

        sscanf(instruction, "%*s%s%" SCNu8, reg, &constante);

        uint8_t reg_pos = encontra_registrador(reg);

        banco->registradores[reg_pos].valor += constante;

        banco->acc = banco->registradores[reg_pos].valor;
        memoryOfInstructions->linha++;
    }

    //funcao que subtrai o valor de um registrador a uma constante e atribui o resultado ao proprio registrador e ao ACC
    void subi(Inst_mem *memoryOfInstructions, Banco_reg *banco, char *instruction)
    {
        char reg[MAX_STR];
        uint8_t constante;

        sscanf(instruction, "%*s%s%" SCNu8, reg, &constante);

        uint8_t reg_pos = encontra_registrador(reg);

        banco->registradores[reg_pos].valor -= constante;

        banco->acc = banco->registradores[reg_pos].valor;
        memoryOfInstructions->linha++;
    }

    //funcao que atribui o valor de uma constante a um registrador   
    void sti(Inst_mem *memoryOfInstructions, Banco_reg *banco, char *instruction)
    {
        char reg[MAX_STR];
        double constante;

        sscanf(instruction, "%*s%s%lf", reg, &constante);

        uint8_t reg_pos = encontra_registrador(reg);

        banco->registradores[reg_pos].valor = constante;
        memoryOfInstructions->linha++;
    }

    //funcao que armazena o valor de acc em um registrador
    void sto(Inst_mem *memoryOfInstructions, Banco_reg *banco, char *instruction)
    {
        char reg[MAX_STR];

        sscanf(instruction, "%*s%s", reg);

        uint8_t reg_pos = encontra_registrador(reg);

        banco->registradores[reg_pos].valor = banco->acc;
        memoryOfInstructions->linha++;
    }

    //funcao que armazena o valor de acc na memoria principal
    void stom(Inst_mem *memoryOfInstructions, Banco_reg* banco, Main_mem *mainMemory)
    {
        mainMemory->dados[mainMemory->endereco] = banco->acc;
        mainMemory->endereco++;
        memoryOfInstructions->linha++;
    }

    //funcao que imprime a memoria principal
    void dspm(Inst_mem *memoryOfInstructions, Main_mem *mainMemory)
    {
        for(int i = 0; i < mainMemory->endereco; i++)
        {
            printf("MEMÓRIA PRINCIPAL ");
            printBinary20Bits(i);
            printf(" = %u\n", mainMemory->dados[i]);
        }
        memoryOfInstructions->linha++;
    }

    //funcao que imprime o valor de acc
    void dsp(Inst_mem *memoryOfInstructions, Banco_reg* banco)
    {
        printf("ACC: %lf\n", banco->acc);
        memoryOfInstructions->linha++;
    }

    //funcao que compara se dois registradores possuem o mesmo valor e faz um salto condicional
    void beq(Inst_mem *memoryOfInstructions, Banco_reg *banco, char *instruction)
    {   
        char reg_1[MAX_STR], reg_2[MAX_STR];
        int linha;

        sscanf(instruction, "%*s%s%s%d", reg_1, reg_2, &linha);

        double reg_1_valor, reg_2_valor;
        reg_1_valor = banco->registradores[encontra_registrador(reg_1)].valor;
        reg_2_valor = banco->registradores[encontra_registrador(reg_2)].valor;

        if(reg_1_valor == reg_2_valor)
            memoryOfInstructions->linha = linha-1;
        else
            memoryOfInstructions->linha++;

    }  

     //funcao que verifica se um registrador e menor que outro e faz um salto condicional
    void blt(Inst_mem *memoryOfInstructions, Banco_reg *banco, char *instruction)
    {   
        char reg_1[MAX_STR], reg_2[MAX_STR];
        int linha;

        sscanf(instruction, "%*s%s%s%d", reg_1, reg_2, &linha);

        double reg_1_valor, reg_2_valor;
        reg_1_valor = banco->registradores[encontra_registrador(reg_1)].valor;
        reg_2_valor = banco->registradores[encontra_registrador(reg_2)].valor;

        if(reg_1_valor < reg_2_valor)
            memoryOfInstructions->linha = linha-1;
        else
            memoryOfInstructions->linha++;

    }   

    //funcao de salto incondicional
    void jump(Inst_mem *memoryOfInstructions, char *instruction)
    {
        int linha;

        sscanf(instruction, "%*s%d", &linha);

        memoryOfInstructions->linha = linha-1;
    }    