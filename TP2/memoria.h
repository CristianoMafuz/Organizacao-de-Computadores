#ifndef MEMORIA_H
#define MEMORIA_H
#include "isa.h"
#include "alu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

    //funcao que aloca e inicia as duas memorias
    void iniciarMemoria(Inst_mem*, Main_mem*);

    //funcao que carrega a memoria de instrucoes
    int carregarMemoria(Inst_mem *, char*);

    //funcao que desaloca e inicia as duas memorias
    void desalocarMemoria(Inst_mem*, Main_mem*);

    //funcao que executa uma instrucao
    void executarInstrucoes(Inst_mem*, Main_mem*, ALU*, Banco_reg*, int);


#endif // MEMORIA_H