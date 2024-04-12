#include <stdio.h>
#include <string.h>

int contar_monolitico(FILE* csv_file, const char* coluna, const char* palavra) {
    int count = 0;
    char line[1024]; 

    
    fgets(line, sizeof(line), csv_file);

   
    int title_index = -1;
    char* token = strtok(line, ",");
    for (int i = 0; token != NULL; ++i) {
        if (strcmp(token, coluna) == 0) {
            title_index = i;
            break;
        }
        token = strtok(NULL, ",");
    }

    
    while (fgets(line, sizeof(line), csv_file) != NULL) {
        token = strtok(line, ",");
        for (int i = 0; token != NULL; ++i) {
            if (i == title_index) {
                
                if (strcasestr(token, palavra) != NULL) {
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
