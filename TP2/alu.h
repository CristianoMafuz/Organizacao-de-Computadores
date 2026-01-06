#ifndef ALU_H
#define ALU_H
#include "isa.h"
#include "memoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

    // Função que encontra o numero do registrador dentro da string
    int encontra_registrador(char*);

    // Função para printar números binários de 24 bits
    void printBinary20Bits(int);

    // Função de soma de registradores
    void add(Inst_mem*, Banco_reg*, char*);

    // Função de subtração de registradores
    void sub(Inst_mem*, Banco_reg*, char*);

    // Função de multiplicação de registradores
    void mul(Inst_mem*, Banco_reg*, char*);

    // Função de divisão de registradores
    void divi(Inst_mem*, Banco_reg*, char*);

    // Função de adição imediata
    void addi(Inst_mem*, Banco_reg*, char*);

    // Função de atribuicao imediata
    void sti(Inst_mem*, Banco_reg*, char*);

    // Função que atribui um registrador ao acc
    void sto(Inst_mem*, Banco_reg*, char*);

    // Função de calculo do resto
    void rem(Inst_mem*, Banco_reg*, char*);

    // Função de imprimir
    void dsp(Inst_mem*, Banco_reg*);

    // Função condicional de comparacao R1<R2
    void blt(Inst_mem*, Banco_reg*, char*);

    // Função condicional de comparacao R1==R2
    void beq(Inst_mem*, Banco_reg*, char*);

    //Função de salto incondicional, pode receber tanto um valor inteiro arbitrario quanto o valor armazenado em um registrador
    void jump(Inst_mem*, char*);

    //Função de subtração com inteiro
    void subi(Inst_mem*, Banco_reg*, char*);

    void stom(Inst_mem*, Banco_reg*, Main_mem*);

    void dspm(Inst_mem*, Main_mem*);


#endif // ALU_H