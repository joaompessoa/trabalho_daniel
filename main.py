import re

def monolithic_search(csv_file):
    count = 0
    with open(csv_file, 'r') as file:
        next(file)  # Pula o cabeçalho
        for line in file:
            if re.search(r'Season 2$', line.strip()):
                count += 1
    return count

def iterative_search(csv_file):
    count = 0
    with open(csv_file, 'r') as file:
        next(file)  # Pula o cabeçalho
        for line in file:
            if re.search(r'Season 2$', line.strip()):
                count += 1
    return count

def recursive_search(file, count=0):
    line = file.readline()
    if not line:
        return count
    if re.search(r'Season 2$', line.strip()):
        count += 1
    return recursive_search(file, count)


def count_season_2(csv_file):
    count = 0
    with open(csv_file, 'r') as file:
        headers = next(file).strip().split(',')
        title_index = headers.index('title')  # Encontra o índice da coluna 'title'
        
        for line in file:
            columns = line.strip().split(',')
            title = columns[title_index]
            if re.search(r'Season 2', title, re.IGNORECASE):  # Busca por 'Season 2' ignorando maiúsculas e minúsculas
                count += 1
    return count


# Carregar dados e aplicar a função
if __name__ == "__main__":
    number = count_season_2('main_Full_data.csv')

    print(number)
    

