#include <stdio.h>
#include <string.h>

int contar_monolitico(FILE* csv_file, const char* coluna, const char* palavra) {

    /* A função contar_monolitico é responsável por contar quantas vezes 
    uma palavra aparece em uma coluna setada pelo usuario dentro de um arquivo CSV */

    int count = 0;
    char line[1024]; 

    
    fgets(line, sizeof(line), csv_file);

    /* A função fgets lê a primeira linha do arquivo, que contém os títulos das colunas.
    A função strtok é usada para dividir essa linha em palavras separados por vírgulas */
   
    int title_index = -1;
    char* token = strtok(line, ",");

    /* strtok quebra a funcao em partes (Token) baseado em um delimitador
    no caso ',' visto que estamos trabalhando com um CSV */

    for (int i = 0; token != NULL; ++i) {
        if (strcmp(token, coluna) == 0) {

            /* strcmp compara duas strings
            e retorna 0 se ela for igual */

            title_index = i;
            break;
        }
        token = strtok(NULL, ",");
    }

    /* Este loop percorre as palavras até encontrar a coluna desejava, salvando seu índice
    para se utilizado mais tarde */

    
    while (fgets(line, sizeof(line), csv_file) != NULL) {
        token = strtok(line, ",");
        for (int i = 0; token != NULL; ++i) {
            if (i == title_index) {
                
                if (strcasestr(token, palavra) != NULL) {
                /*  A strcasestr() localiza uma substring.
                    Ela retorna NULL se a substring nao for acha,
                    entao apenas entra nesse bloco se a palvra existir na coluna,
                    se sim add +1 no count
                */
                    count++;
                    break; 
                }
            }
            token = strtok(NULL, ",");
        }
    }

    return count;
}

int main() {
    const char* csv_filename = "main_Full_data.csv"; 
    const char* target_coluna = "title"; 
    const char* target_palavra = "Season 2"; 

    FILE* csv_file = fopen(csv_filename, "r");
    if (csv_file == NULL) {
        perror("Error opening CSV file");
        return 1;
    }

    int result = contar_monolitico(csv_file, target_coluna, target_palavra);
    printf("Pelo metodo Monolitico o resultado e: %d\n", result);

    fclose(csv_file);
    return 0;
}
