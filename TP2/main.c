#include "isa.h"
#include "alu.h"
#include "memoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>


int main() 
{
    ALU alu;
    Banco_reg banco;    
    Main_mem memoria_principal;
    Inst_mem memoria_instrucoes;
    int num_linhas;

    //alocacao das variaveis
    banco = aloca_registradores(16);
    iniciarMemoria(&memoria_instrucoes, &memoria_principal);

    //carregando a memoria de instrucoes
    num_linhas = carregarMemoria(&memoria_instrucoes, "texto.txt");

    //execucao do algoritmo
    executarInstrucoes(&memoria_instrucoes, &memoria_principal, &alu, &banco, num_linhas);

    //desalocacao das variaveis
    desalocaRegistradores(banco);
    desalocarMemoria(&memoria_instrucoes, &memoria_principal);


    return 0;
}
