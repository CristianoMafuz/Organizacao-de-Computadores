import random

# Cria uma lista com as letras do alfabeto
alfabeto = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")

#Embaralha a lista usando a função random.shuffle
random.shuffle(alfabeto)

tam = len(alfabeto) 

chave = []

#Concatena as letras da lista embaralhada na string da chave
for letra in alfabeto:
    chave += letra

for i in range(0, tam):
    print(f'{chave[i], {i}}')