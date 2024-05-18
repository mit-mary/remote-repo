#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 1000
#define MAX_BUFFER_SIZE 100000

int count_characters(FILE *file) {
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
    	if(ch == ' '|| ch == '\t' || ch =='\n')
        count++; 
    }
    return count;
}

int count_words(FILE *file) {
    int count = 0;
    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        char *token = strtok(buffer, " ,\t\n");
        while (token != NULL) {
            count++;
            token = strtok(NULL, " ,\t\n");
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c | -w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char *parameter = argv[1];
    char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    int count;
    if (strcmp(parameter, "-c") == 0) {
        count = count_characters(file);
        printf("字符数：%d\n", count);
    } else if (strcmp(parameter, "-w") == 0) {
        count = count_words(file);
        printf("单词数：%d\n", count);
    } else {
        printf("Error: Invalid parameter\n");
        return 1;
    }

    fclose(file);
    return 0;
}

