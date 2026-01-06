#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include "isa.h"
#include "alu.h"

    void iniciarMemoria(Inst_mem *memoryOfInstructions, Main_mem *mainMemory) 
    {
        memoryOfInstructions->instrucoes = malloc(INSTRUCTION_MEMORY_SIZE * sizeof(char *)); // Alocar memória para o array de strings

        if (memoryOfInstructions->instrucoes == NULL) 
        {
            printf("Erro ao alocar memória.\n");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < INSTRUCTION_MEMORY_SIZE; ++i) 
        {
            memoryOfInstructions->instrucoes[i] = malloc(LINE_LENGTH * sizeof(char)); // Alocar memória para cada string

            if (memoryOfInstructions->instrucoes[i] == NULL) 
            {
                printf("Erro ao alocar memória.\n");
                exit(EXIT_FAILURE);
            }

            memoryOfInstructions->instrucoes[i][0] = '\0'; // Inicializar cada string com terminador nulo
        }

        memoryOfInstructions->linha = 0;

        mainMemory->dados = malloc(MAIN_MEMORY_SIZE * sizeof(uint16_t));

        if (mainMemory->dados == NULL) 
        {
            printf("Erro ao alocar memória.\n");
            exit(EXIT_FAILURE);
        }

        mainMemory->endereco = 0;
    }

    void desalocarMemoria(Inst_mem *memoryOfInstructions, Main_mem *mainMemory)
    {
        for (int i = 0; i < INSTRUCTION_MEMORY_SIZE; ++i) 
        {
            free(memoryOfInstructions->instrucoes[i]);
        }
        free(memoryOfInstructions->instrucoes);

        free(mainMemory->dados);
    }


    int carregarMemoria(Inst_mem *memoryOfInstructions, char *nomearquivo) 
    {
        FILE *file = fopen(nomearquivo, "r");
        int i = 0;

        if (file == NULL) 
        {
            printf("Erro ao abrir o arquivo.\n");
            exit(EXIT_FAILURE);
        }

        while (fgets(memoryOfInstructions->instrucoes[i], LINE_LENGTH, file) != NULL)
            i++;

        fclose(file);
        return i;
    }

    void executarInstrucoes(Inst_mem *memoryOfInstructions, Main_mem *mainMemory, ALU *alu, Banco_reg *banco, int num_linhas)
    {
        int i = 0;
        while(i < num_linhas)
        {       
            operacao(memoryOfInstructions->instrucoes[i], alu);
            operacao_alu(memoryOfInstructions, banco, mainMemory, memoryOfInstructions->instrucoes[i], alu);
            i = memoryOfInstructions->linha;
        }
    }
