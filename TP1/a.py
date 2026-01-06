arquivo = open("encoded_sub.txt", "r")

texto_sub = arquivo.read()

arquivo.close()

def binary_to_text(binary_string):
  # Passo 1: Dividir a string binária em valores individuais, alocando em um vetor
  binary_values = binary_string.split()

  # Passo 2: Inicializar uma variável de texto vazia
  text = ""
  ''' Passo 3: Cada valor de "binary_values" é assumido por "binary_value" a cada 
    laço de repetição'''

  for binary_value in binary_values:
    # Passo 4: Converter o valor binário em um número decimal
    decimal_value = int(binary_value, 2)

    # Passo 5: Converter o número decimal em um caractere usando a função chr()
    character = chr(decimal_value)

    # Passo 6: Adicionar o caractere à variável de texto
    text += character

  # Passo 7: Retornar o texto resultante
  return text

texto = binary_to_text(texto_sub)
print(f"\n{texto}\n")