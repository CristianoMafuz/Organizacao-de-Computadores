#ifndef ISA_H
#define ISA_H
#define MAX_STR 5
#define INSTRUCTION_MEMORY_SIZE 100
#define MAIN_MEMORY_SIZE 1024*1024
#define LINE_LENGTH 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>


    typedef struct {
        uint8_t Reg1 : 4;  // Registrador Fonte 1 (4 bits)
        uint8_t Reg2 : 4;  // Registrador Fonte 2 (4 bits)
    } Instrucao;

    typedef struct 
    {
        uint8_t opcode : 4; // código de operação
    } ALU;

    typedef struct 
    {
        uint16_t *dados; //array com todos os dados da memoria principal
        int endereco; //enedereco do proximo espaco a ser ocupado
    } Main_mem;

    typedef struct 
    {
        char **instrucoes; //vetor de strings para armazenar o texto
        int linha; //armazena a linha atual da leituras
    } Inst_mem;

    typedef struct 
    {
        double valor; //valor que o registrador carrega
    } Registrador;

    typedef struct
    {
        Registrador *registradores; //conjunto dos registradoress
        double acc;
    } Banco_reg;

    //funcao que desaloca todos os registradoes
    void desalocaRegistradores(Banco_reg); 

    //funcao que aloca todos os registradoes
    Banco_reg aloca_registradores(int);

    //funcao que encontra qual operacao a alu deve fazer
    void operacao(char*, ALU *);

    //funcao que executa a operacao da alu 
    void operacao_alu(Inst_mem*, Banco_reg* , Main_mem*, char*, ALU*);

#endif // ARQUIVO_H