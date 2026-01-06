#Cifra de César 

from math import log10

class ngram_score(object):
    def __init__(self,ngramfile,sep=' '):
        ''' load a file containing ngrams and counts, calculate log probabilities '''
        self.ngrams = {}
        for line in open(ngramfile).readlines():
            key,count = line.split(sep)
            self.ngrams[key] = int(count)
        self.L = len(key)
        self.N = sum(self.ngrams.values())
        #calculate log probabilities
        for key in self.ngrams.keys():
            self.ngrams[key] = log10(float(self.ngrams[key])/self.N)
        self.floor = log10(0.01/self.N)


    def score(self,text):
        ''' compute the score of text '''
        score = 0
        ngrams = self.ngrams.__getitem__
        for i in range(len(text)-self.L+1):
            if text[i:i+self.L] in self.ngrams: score += ngrams(text[i:i+self.L])
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


def decifra_cifra_de_cesar(cifra, deslocamento):
  
    decifrado = ""

    for char in cifra:
        if char.isalpha():  # Verifica se o caractere é uma letra
            char_decifrado = chr(((ord(char) - ord('A') - deslocamento) % 26) + ord('A'))
        else:
            char_decifrado = char  # Mantém caracteres não-alfabéticos inalterados

        decifrado += char_decifrado


    return decifrado


def calcula(cifra_unida):

    # Definindo o tamanho dos n-gramas
    tamanho_ngrama = ns.L

    # Lista para armazenar as pontuações de cada pedaço
    pontuacoes = []

    for i in range(0, len(cifra_unida) - tamanho_ngrama + 1):
        pedaco = cifra_unida[i:i + tamanho_ngrama]

        # Calcule a pontuação para o pedaço usando a função score
        pontuacao_pedaco = ns.score(pedaco)

        # Armazene a pontuação na lista
        pontuacoes.append(pontuacao_pedaco)

    
    # Calcule a média das pontuações
    media_pontuacoes = sum(pontuacoes) / len(pontuacoes)

    return media_pontuacoes


def possibilidades(cifra, deslocamento, aux2, desloc):
    if deslocamento < 26:
        decifrado = decifra_cifra_de_cesar(cifra, deslocamento)
        aux1 = calcula(decifrado)
        if abs(aux1) < abs(aux2):
            aux2 = aux1
            desloc = deslocamento
        print(f"Deslocamento {deslocamento}: {aux1}\n")
        return possibilidades(cifra, deslocamento + 1, aux2, desloc)

    return desloc

#Fim das funções


#Começo da "main"

arquivo = open("encoded_ces.txt", "r")

texto_cesar = arquivo.read()

arquivo.close()

ngramfile = "ngramas.txt"
ns = ngram_score(ngramfile)
deslocamento_inicial = 0


texto = binary_to_text(texto_cesar)
print(f"\n{texto}\n")


cifra_separada = texto.split()
cifra_unida = "".join(cifra_separada)


aux2_inicial = 100  # Valor grande o suficiente para garantir a primeira aceitação
deslocamento_correto = possibilidades(cifra_unida, deslocamento_inicial, aux2_inicial, deslocamento_inicial)
print(f"\n\nDeslocamento correto --> {deslocamento_correto}\n")


mensagem_decifrada = decifra_cifra_de_cesar(texto, deslocamento_correto)
print(f"{mensagem_decifrada}\n")