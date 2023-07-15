#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    char** lines;
    int number;
    int capacity; 
} LinesVector;

void print_vector_content(LinesVector*);
LinesVector* get_lines(char*);

void print_vector_content(LinesVector* vector)
{
    printf("\n");
    for (int i = 0; i < vector->number; i++)
    {
        printf("%i %p %s\n", i, vector->lines[i], vector->lines[i]);
    }
    printf("\n");
}

LinesVector* get_lines(char* pathFile)
{
    FILE *file;

    file = fopen(pathFile, "r");

    if(file == NULL)
    {
        fprintf(stderr, "Unable to open: %s\n", pathFile);
    }
    
    char** lines = malloc(sizeof(char*)*2);
    LinesVector* vector = (LinesVector*)malloc(sizeof(LinesVector));
    vector->lines = lines;
    vector->number = 0;
    vector->capacity = 2;


    while (!feof(file) && !ferror(file))
    {   
        char* data = (char*)malloc(sizeof(char)*500);
        if(fgets(data, 500, file) != NULL)
        {
            if(vector->number == vector->capacity)
            {
                vector->lines = realloc(vector->lines, sizeof(char*)*(2*(vector->capacity+1)));
                vector->capacity = 2*(vector->capacity+1);
                vector->lines[vector->number] = data;
                vector->number += 1;
            }
            else
            {
                vector->lines[vector->number] = data;
                vector->number += 1;
            } 
        }
    }
    // print_vector_content(vector); only for testing
    fclose(file);
    return vector;
}

int main(int argc, char const *argv[])
{
    LinesVector* dummyVector = get_lines("filename.txt");
    return 0;
}
