#include <stdio.h>
#include <string.h>

int contar_monolitico(FILE* csv_file, const char* coluna, const char* palavra) {
    int count = 0;
    char line[1024]; // Assuming a maximum line length of 1024 characters

    // Read the header line (assuming it contains column names)
    fgets(line, sizeof(line), csv_file);

    // Find the index of the specified column
    int title_index = -1;
    char* token = strtok(line, ",");
    for (int i = 0; token != NULL; ++i) {
        if (strcmp(token, coluna) == 0) {
            title_index = i;
            break;
        }
        token = strtok(NULL, ",");
    }

    // Process each subsequent line
    while (fgets(line, sizeof(line), csv_file) != NULL) {
        token = strtok(line, ",");
        for (int i = 0; token != NULL; ++i) {
            if (i == title_index) {
                // Check if the title contains the specified word (case-insensitive)
                if (strcasestr(token, palavra) != NULL) {
                    count++;
                    break; // No need to continue checking this line
                }
            }
            token = strtok(NULL, ",");
        }
    }

    return count;
}

int main() {
    const char* csv_filename = "main_Full_data.csv"; // Replace with the actual CSV file name
    const char* target_coluna = "title"; // Replace with the desired column name
    const char* target_palavra = "Season 2"; // Replace with the word you're searching for

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
