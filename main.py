import re


def contar_monolitico(csv_file, coluna, palavra):
    files = open(csv_file,'r')
    files.readline
    for file in files.readlines():
        print(file)
        headers = next(file).strip().split(',')
        title_index = headers.index(coluna)
        for line in file:
            columns = line.strip().split(',')
            title = columns[title_index]
            if re.search(fr'{palavra}', title, re.IGNORECASE):
                count += 1
    files.close()
    return count

def contar_interativo(csv_file,coluna,palavra):
    def definir_colunas(csv_file):
        hearders = next(csv_file).strip().split(',')
        return hearders
    def achar_index_coluna(headers,coluna):
        title_index = headers.index(coluna)
        return title_index 
    def contador(palavra,coluna):
        count = 0
        with open(csv_file, 'r') as file:
            headers = definir_colunas(file)
            title_index = achar_index_coluna(headers,coluna)
            for line in file:
                colums = line.strip().split(',')
                title = colums[title_index]
                if re.search(fr'{palavra}', title, re.IGNORECASE):  # Busca por 'Season 2' ignorando maiúsculas e minúsculas
                    count += 1
        return count
    return contador(palavra,coluna)

def contar_recursivo(csv_file, coluna, palavra):
    def definir_colunas(file):
        headers = next(file).strip().split(',')
        return headers
    
    def achar_index_coluna(headers, coluna):
        title_index = headers.index(coluna)
        return title_index
    
    def ler_linha(file, title_index, palavra, count=0):
        line = file.readline()
        if not line:
            return count
        columns = line.strip().split(',')
        title = columns[title_index]
        if re.search(fr'{palavra}', title, re.IGNORECASE):
            count += 1
        return ler_linha(file, title_index, palavra, count)
    
    with open(csv_file, 'r') as file:
        headers = definir_colunas(file)
        title_index = achar_index_coluna(headers, coluna)
        count = ler_linha(file, title_index, palavra)
        return count

# Carregar dados e aplicar a função
if __name__ == "__main__":
    dados = 'main_Full_data.csv'
    coluna = 'title'
    palavra = 'Season 2'
    total = contar_interativo(dados,coluna,palavra)
    total_recursivo = contar_recursivo(dados,coluna,palavra)

    print(f"Numero de entradas em {dados} que contem a palavra: {palavra} na coluna: {coluna} e: {total}")
    print(f"Numero de Entradas pelo metodo Recursivo: {total_recursivo}")
    

