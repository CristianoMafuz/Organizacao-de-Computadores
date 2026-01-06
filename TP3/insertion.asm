.data
 	vetor:
		.alig 2 #alocando um vetor de inteiros, portanto o código de alig é 2
    	.space 40 #tamanho do vetor (10 x 4 bytes = 40 bytes) 
 	msg_de_entrada: .asciiz "Digite os 10 valores do vetor: "

.text
  	declaracoes_vetor:
    	move $t0 $zero #$t0 = i
    	li $t2 40 #tamanho do vetor	
    	li $v0 4 #carregando o registrador $v0 com 4, que imprime uma string
    	la $a0 msg_de_entrada #imprimir mensagem de entrada de dados
    	syscall #chamada da funcao de operacao

  	entrada_de_dados:
    	beq $t0 $t2 main #se i == 40(décima iteração) ir para main
    	li $v0 5 #carregando o registrador $v0 com 5, que realiza a leitura de dados
    	syscall 
    	sw $v0 vetor($t0) #vet[i] = $v0(numero digitado pelo usuario)
    	addi $t0 $t0 4 #i += 4 
    	#a contagem acontece de 4 em 4 pois os endereços de memoria são dispostos de 4 em 4.
    	j entrada_de_dados #reinicia o loop
	

  	main:
    	li $t1 4 #$t1 = contador do loop externo - i
    	li $t2 0 #$t2 = contador do loop interno - j
    	li $t3 0 #$t3 = key(variável que servirá como auxiliar)
    	li $t4 40 #$t4 = tamanho do vetor
    	li $t5 4 #$t5 = j+4
    	li $s0 0 #s0 = registrador que irá carregar um valor da memoria 
    	li $s1 0 #s1 = outro registrador que irá carregar um valor da memoria 

		#medição do tempo - inicio
		li $v0 30
		syscall
		move $s5 $a0 #s5 = marca o tempo inicial naquele instante 

	for:
      	beq $t1 $t4 fim_programa #se i == tamanho do vetor, sair do for externo

      	lw $t3 vetor($t1) #key = vetor[i]
      
      	#j = i-4
      	move $t2 $t1 #j = i
      	subi $t2 $t2 4 #j -= 4

      	while:

        	blt $t2 $zero fim_while #se j < 0 encerra o while
        
        	lw $s0 vetor($t2) #$s0 = vetor[j]
        	ble $s0 $t3 fim_while #se vetor[j] <= key encerra o while

        	#$t5 = j+4
        	move $t5 $t2 #$t5 = j
        	addi $t5 $t5 4 #$t5 += 4

        	#vetor[j+4] = vetor[j]
        	sw $s0 vetor($t5)
        
        	subi $t2 $t2 4 #indice do vetor j -= 4
        	j while #reinicia o loop interno

		fim_while:
	
	  	#$t5 = j+4
      	move $t5 $t2 #$t5 = j
      	addi $t5 $t5 4 #$t5 += 4
      
      	sw $t3 vetor($t5) #vetor[j+4] = key

		proxima_iteracao_for:
    	addi $t1 $t1 4 #indice do vetor i+=4
    	j for #reinicia o loop externo

	fim_programa:
		#medição do tempo - fim
		li $v0 30
		syscall
		
		sub $s5 $a0 $s5 #s5 = tempo final decorrido 
    	
    	#encerrando o programa
    	li $v0 10 #carregando $v0 com 10, que encerra o programa
    	syscall
