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
	
	troca: #função que realiza a troca de dois valores do vetor
		lw $a0 vetor($t1) #$a0 = num[i]
		lw $a1 vetor($t6) #$s1 = num[min]
		sw $a1 vetor($t1) #num[i] = num[min]
		sw $a0 vetor($t6) #num[min] = aux
		j proxima_iteracao_for1 #volta para onde a função foi chamada
	
	main:
		li $t1 0 #$t1 = = contador do loop externo - i
		li $t2 0 #$t2 = indice do vetor do loop interno - j
		li $t3 40 #$t3 = tamanho do vetor
		li $t4 36 #$t4 = tamanho do vetor - 4
		li $t6 0 #$t6 = indice do menor valor do vetor (min)
		li $s0 0 #s0 = registrador que irá carregar um valor da memoria 
		li $s1 0 #s1 = outro registrador que irá carregar um valor da memoria 
	
	#medição do tempo - inicio
		li $v0 30
		syscall
		move $s5 $a0 #s5 = marca o tempo inicial naquele instante 
	
  	for_externo:
  		beq $t1 $t4 fim_programa #se i == 36 sair do for externo
  		
  		move $t6 $t1 #min = i (atualiza o menor)
  		
  		for_interno:
  			#j = i+4
  			move $t2 $t1 #j = i
  			addi $t2 $t2 4 #j += 4
  			
  			comparacao_for_interno:
  			beq $t2 $t3 fim_for_interno #se j == 40 sair do for interno
  			
  			lw $s0 vetor($t2) #$s0 = num[j]
  			lw $s1 vetor($t6) #$s1 = num[min]
  			bge $s0 $s1 proxima_iteracao_for2 #se num[j] >= num[min], j += 4 
  			move $t6 $t2 #caso contrario, min = j
  			
  			proxima_iteracao_for2:
  			addi $t2 $t2 4 #indice do vetor j += 4
  			j comparacao_for_interno #reinicia o loop interno sem declarar que j = i outra vez
  			
  		fim_for_interno:
  		bne $t1 $t6 troca #se i != min, troca
  		#caso contrario, vai para a proxima iteracao
  		
  		proxima_iteracao_for1:
  		addi $t1 $t1 4 #indice do vetor i+=4
  		j for_externo #reinicia o loop externo
  	
	fim_programa:
		#medição do tempo - fim
		li $v0 30
		syscall
		
		sub $s5 $a0 $s5 #s5 = tempo final decorrido 
	
		li $v0 10 #carregando $v0 com 10, que encerra o programa
		syscall 
