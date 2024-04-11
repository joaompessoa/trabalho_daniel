import re

def monolithic_search(csv_file):
    count = 0
    with open(csv_file, 'r') as file:
        next(file)  # Pula o cabeçalho
        for line in file:
            if re.search(r'Season 2$', line.strip()):
                count += 1
    return count

# Carregar dados e aplicar a função
result = monolithic_search('animes.csv')
print("Número de animes com 'Season 2':", result)

def iterative_search(csv_file):
    count = 0
    with open(csv_file, 'r') as file:
        next(file)  # Pula o cabeçalho
        for line in file:
            if re.search(r'Season 2$', line.strip()):
                count += 1
    return count

# Carregar dados e aplicar a função
result = iterative_search('animes.csv')
print("Número de animes com 'Season 2':", result)


def recursive_search(file, count=0):
    line = file.readline()
    if not line:
        return count
    if re.search(r'Season 2$', line.strip()):
        count += 1
    return recursive_search(file, count)

def main(csv_file):
    with open(csv_file, 'r') as file:
        next(file)  # Pula o cabeçalho
        result = recursive_search(file)
    return result

# Carregar dados e aplicar a função
if __name__ == "__main__":
    

