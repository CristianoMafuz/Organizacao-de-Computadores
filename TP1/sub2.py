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


def tenta_decifrar(alfa):
  mapeamento = criar_mapeamento(alfa, list(string.ascii_uppercase))
  decifred = substituir_caracteres(texto, mapeamento)

  print(f"\nTexto Decifrado:\n{decifred}\n")

  return decifred


def calcula_pont(united_cifra, tamanho_gram, ns):
  pont_total = 0
  k = 0

  for i in range(0, len(united_cifra) - tamanho_gram + 1):  #calcula scores
    pedac = united_cifra[i:i + tamanho_gram]

    # Calcule a pontuação para o pedaço usando a função score
    pontuacao_pedac = ns.score(pedac)

    pont_total += pontuacao_pedac

  k = pont_total / (len(united_cifra) - tamanho_gram + 1)

  return k


def troca(alf, quad, j):
  aux = alf[j]
  alf[j] = quad
  for k in range(26):
    if quad == alf[k] and k != j:
      alf[k] = aux


def encontrar_chave(cifra_unida,
                    ns,
                    quadgramas,
                    alfabeto,
                    texto_decifrado_unido=None):
  # Lista para armazenar as pontuações de cada pedaço
  pontuacoes = []

  y = 1000
  #Lista para armazenar letras com menor frequencia
  quad_mais_usado = None
  #quad_mais_usado = [None] * 1000

  maior_pontuacao = [0] * y
  melhor_da_rodada = [0] * y
  melhor_alfa_da_rodada = [0] * y
  melhor_alfa = None
  #sorted_pontuacoes = [0] * y

  n = 0
  tamanho_ngrama = 4

  for j in range(y):
    if j == 0:
      alfabeto = list(string.ascii_uppercase)
      pont1 = calcula_pont(cifra_unida, tamanho_ngrama, ns)

    for i in range(0, len(cifra_unida) - tamanho_ngrama + 1):  #calcula scores
      pedaco = cifra_unida[i:i + tamanho_ngrama]

      # Calcule a pontuação para o pedaço usando a função score
      pontuacao_pedaco = ns.score(pedaco)

      # Armazene a pontuação na lista
      pontuacoes.append(pontuacao_pedaco)
    """sorted_pontuacoes = sorted(pontuacoes, reverse=True)
        maior_pontuacao[count] = sorted_pontuacoes[count]"""
    maior_pontuacao[j] = max(pontuacoes)

    for i in range(0, len(cifra_unida) - tamanho_ngrama + 1):
      if pontuacoes[i] == maior_pontuacao[j]:
        quad_mais_usado = cifra_unida[i:i + tamanho_ngrama]

    quad_atual = quadgramas[j]

    if quad_mais_usado is not None:
      letras_separadas = list(quad_mais_usado)
      for i in range(4):
        for k in range(26):
          if letras_separadas[i] == alfabeto[k]:
            alfaaux = alfabeto
            troca(alfabeto, quad_atual[i], k)
            if (alfaaux == alfabeto):
              random.shuffle(alfabeto)
            texto_decifrado = tenta_decifrar(alfabeto)
            texto_decifrado_separado = texto_decifrado.split()
            texto_decifrado_unido = "".join(texto_decifrado_separado)
            pont2 = calcula_pont(texto_decifrado_unido, tamanho_ngrama, ns)
            print(f"{pont2}\n")
            if (pont1 > pont2):
              alfabeto = alfaaux
            else:
              pont1 = pont2
              melhor_alfa = alfabeto

    melhor_da_rodada[j] = pont1
    melhor_alfa_da_rodada[j] = melhor_alfa
  else:
    valor_maximo = max(melhor_da_rodada)
    indice = melhor_da_rodada.index(valor_maximo)
    melhor_texto = tenta_decifrar(melhor_alfa_da_rodada[indice])
    
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

encontrar_chave(cifra_unida, ns, quadgramas, alfabeto)
