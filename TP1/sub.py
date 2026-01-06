#Cifra de Substituição

from math import log10
import random
import string


class ngram_score(object):

  def __init__(self, ngramfile, sep=' '):
    ''' load a file containing ngrams and counts, calculate log probabilities '''
    self.ngrams = {}
    for line in open(ngramfile).readlines():
      key, count = line.split(sep)
      self.ngrams[key] = int(count)
    self.L = len(key)
    self.N = sum(self.ngrams.values())
    #calculate log probabilities
    for key in self.ngrams.keys():
      self.ngrams[key] = log10(float(self.ngrams[key]) / self.N)
    self.floor = log10(0.01 / self.N)

  def score(self, text):
    ''' compute the score of text '''
    score = 0
    ngrams = self.ngrams.__getitem__
    for i in range(len(text) - self.L + 1):
      if text[i:i + self.L] in self.ngrams: score += ngrams(text[i:i + self.L])
      else: score += self.floor
    return score


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


def criar_mapeamento(cifra, alfabeto):
  mapeamento = {}
  for i in range(len(cifra)):
    if cifra[i].isalpha():
      mapeamento[cifra[i].upper()] = alfabeto[i]
  return mapeamento


def substituir_caracteres(frase, mapeamento):
  resultado = ""
  for caractere in frase:
    if caractere.isalpha() and caractere.upper() in mapeamento:
      resultado += mapeamento[caractere.upper()]
    else:
      resultado += caractere
  return resultado


def ler_quadgramas(nome_arquivo):
  quad = []

  # Abra o arquivo que contém os quadgramas
  with open(nome_arquivo, "r") as arquivo:
    for linha in arquivo:
      # Divida cada linha em palavras usando espaço como separador
      palavras = linha.split()

      # Apenas pegue a primeira palavra (o quadgrama) e adicione-a ao vetor
      if len(palavras) > 0:
        quad.append(palavras[0])

  # Retorne o vetor de quadgramas
  return quad


def encontrar_chave(cifra_unida, count, ns, quadgramas, alfabeto):
  if count == 0:
    alfabeto = list(string.ascii_uppercase)

  if count < 20000:
    # Definindo o tamanho dos n-gramas
    tamanho_ngrama = 4

    # Lista para armazenar as pontuações de cada pedaço
    pontuacoes = []

    #Lista para armazenar letras com menor frequencia
    quad_mais_usado = None
    #quad_mais_usado = [None] * 1000
    
    maior_pontuacao = [0] * 300000
    sorted_pontuacoes = [0] * 300000

    for i in range(0, len(cifra_unida) - tamanho_ngrama + 1):  #calcula scores
      pedaco = cifra_unida[i:i + tamanho_ngrama]

      # Calcule a pontuação para o pedaço usando a função score
      pontuacao_pedaco = ns.score(pedaco)

      # Armazene a pontuação na lista
      pontuacoes.append(pontuacao_pedaco)

      media_pontuacoes = sum(pontuacoes) / len(pontuacoes)
      
    #maior_pontuacao[count] = max(pontuacoes)
    sorted_pontuacoes = sorted(pontuacoes, reverse=True)
    maior_pontuacao[count] = sorted_pontuacoes[count]
  #  print(f"{maior_pontuacao[count]}\n")

    for i in range(0, len(cifra_unida) - tamanho_ngrama + 1):
      if pontuacoes[i] == maior_pontuacao[count]:
        quad_mais_usado = cifra_unida[i:i + tamanho_ngrama]

   # print(f"{quad_mais_usado}\n")

    quad_atual = quadgramas[count]
   # print(f"{quad_atual}\n")

    if quad_mais_usado is not None:
      letras_separadas = list(quad_mais_usado)
      #print(f"{letras_separadas}\n")
      for i in range(4):
        for j in range(26):
          if letras_separadas[i] == alfabeto[j]:
            aux = alfabeto[j]
            alfabeto[j] = quad_atual[i]
            for k in range(26):
              if quad_atual[i] == alfabeto[k] and k != j:
                alfabeto[k] = aux

    count += 1
    #print(f"{alfabeto}\n")
    mapeamento = criar_mapeamento(alfabeto, list(string.ascii_uppercase))
    texto_decifrado = substituir_caracteres(texto, mapeamento)
    texto_decifrado_separado = texto_decifrado.split()
    texto_decifrado_unido = "".join(texto_decifrado_separado)
    print(f"\nTexto Decifrado:\n{texto_decifrado}\n")
    print(f'Média da métrica: {media_pontuacoes}')
    encontrar_chave(texto_decifrado_unido, count, ns, quadgramas, alfabeto)
    
  else:
    return


#Fim das funções

#Começo da "main"

arquivo = open("encoded_sub.txt", "r")

texto_sub = arquivo.read()

arquivo.close()

ngramfile = "ngramas.txt"
ns = ngram_score(ngramfile)
quadgramas = ler_quadgramas(ngramfile)

texto = binary_to_text(texto_sub)
print(f"\n{texto}\n")

cifra_separada = texto.split()
cifra_unida = "".join(cifra_separada)

count = 0
alfabeto = None

encontrar_chave(cifra_unida, count, ns, quadgramas, alfabeto)
