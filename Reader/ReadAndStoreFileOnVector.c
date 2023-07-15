#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char** lines;
    int number;
    int capasity; 
} VectorSting;

VectorSting newVector(int);
void addElemntOnVector(VectorSting*, char*);
void printVectorContent(VectorSting*);

VectorSting newVector(int number)
{
    if(number <= 0)
    {
        printf("number must be positive");
        number = 1;
    }
    char** lines = malloc(sizeof(char*)*number+1);
    VectorSting vector = {lines, 0, number+1};
    return vector;
}

void addElemntOnVector(VectorSting* vector, char* newString)
{
    if(vector->number == vector->capasity)
    {
        vector->lines = realloc(vector->lines, sizeof(char*)*(2*(vector->capasity+1)));
        vector->capasity = 2*(vector->capasity+1);
        vector->lines[vector->number] = newString;
        vector->number += 1;
    }
    else
    {
        vector->lines[vector->number] = newString;
        vector->number += 1;
    }
}

void printVectorContent(VectorSting* vector)
{
    for (int i = 0; i < vector->number; i++)
    {
        printf("%i %s\n", i, vector->lines[i]);
    }
}

int main(int argc, char const *argv[])
{
    FILE *file;

    file = fopen("filename.txt", "r");

    if(file == NULL)
    {
        printf("\n Unable to open: filename.txt");
        return -1;
    }

    char myString[500];

    VectorSting vector = newVector(1);

    while (fgets(myString, sizeof(myString), file))
    {
        addElemntOnVector(&vector, myString);
    }

    printVectorContent(&vector);

    fclose(file);
    return 0;
}
