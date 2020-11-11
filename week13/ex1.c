#include <stdio.h>
#include <stdlib.h>

#define ARRAY_INITIAL_CAPACITY 10

/*
    This is a structure for dynamic array.
*/
struct IntArray
{
    int *data;
    size_t size;
    size_t capacity;
};

// Create empty array with specified capacity
void IntArray_CreateEmpty(struct IntArray ** ppArray, size_t capacity)
{
    *ppArray = malloc(sizeof(struct IntArray));
    (**ppArray).data = malloc(sizeof(int) * capacity);
    (**ppArray).size = 0;
    (**ppArray).capacity = capacity;
}

// Create array of given size
void IntArray_CreateSized(struct IntArray ** ppArray, size_t size)
{
    *ppArray = malloc(sizeof(struct IntArray));
    (**ppArray).data = malloc(sizeof(int) * size);
    (**ppArray).size = size;
    (**ppArray).capacity = size;
}

// Delete array
void IntArray_Destroy(struct IntArray ** ppArray)
{
    free((**ppArray).data);
    (**ppArray).data = NULL;
    (**ppArray).size = 0;
    (**ppArray).capacity = 0;
    free(*ppArray);
    *ppArray = NULL;
}

size_t IntArray_Size(struct IntArray * pArray)
{
    return pArray->size;
}

int IntArray_GetElementByIndex(struct IntArray * pArray, size_t index)
{
    return pArray->data[index];
}

void IntArray_SetElementByIndex(struct IntArray * pArray, size_t index, int value)
{
    pArray->data[index] = value;
}

// Add element to the end of the array
void IntArray_PushBack(struct IntArray * pArray, int value)
{
    if (pArray->size == pArray->capacity)
    {
        pArray->capacity = 2 * pArray->capacity; // doucle the capacity
        pArray->data = realloc(pArray->data, sizeof(int) * pArray->capacity);
    }
    IntArray_SetElementByIndex(pArray, pArray->size, value);
    ++(pArray->size);
}

// Set all values of the array equal the given value
void IntArray_Fill(struct IntArray * pArray, int value)
{
    for (size_t i = 0; i < pArray->size; ++i)
    {
        IntArray_SetElementByIndex(pArray, i, value);
    }
}

// Read array form line in a file
void IntArray_ReadFromFile(FILE * p_file, struct IntArray * pArray)
{
    while (1)
    {
        const int nextChar = getc(p_file); // check if we are still on the same line
        if (nextChar != EOF)
        {
            ungetc(nextChar, p_file);
            if (nextChar != '\n')
            {
                int number;
                fscanf(p_file, "%i", &number);
                IntArray_PushBack(pArray, number);
                continue;
            }
        }
        break;
    }
    getc(p_file); // skip '\n' symbol
}

/*
    Structure for storing matrix
*/
struct IntMatrix
{
    int *data;
    size_t sizeWidth, sizeHeight;
};

// Create matrix of specified dimensions
void IntMatrix_Create(struct IntMatrix ** ppMatrix, size_t size_width, size_t size_height)
{
    *ppMatrix = malloc(sizeof(struct IntMatrix));
    (**ppMatrix).data = malloc(sizeof(int) * size_width * size_height);
    (**ppMatrix).sizeWidth = size_width;
    (**ppMatrix).sizeHeight = size_height;
}

// Delete matrix
void IntMatrix_Destroy(struct IntMatrix ** ppMatrix)
{
    free((**ppMatrix).data);
    (**ppMatrix).data = NULL;
    (**ppMatrix).sizeWidth = 0;
    (**ppMatrix).sizeHeight = 0;
    free(*ppMatrix);
    *ppMatrix = NULL;
}

int IntMatrix_GetElementByIndex(struct IntMatrix * pMatrix, size_t i, size_t j)
{
    return pMatrix->data[i * pMatrix->sizeWidth + j];
}

void IntMatrix_SetElementByIndex(struct IntMatrix * pMatrix, size_t i, size_t j, int value)
{
    pMatrix->data[i * pMatrix->sizeWidth + j] = value;
}

void IntMatrix_ReadFromFile(FILE * p_file, struct IntMatrix * pMatrix)
{
    for (size_t i = 0; i < pMatrix->sizeHeight; ++i)
    {
        for (size_t j = 0; j < pMatrix->sizeWidth; ++j)
        {
            int value;
            fscanf(p_file, "%i", &value);
            IntMatrix_SetElementByIndex(pMatrix, i, j, value);
        }
    }
}

// Print matrix to stdout (for debug purposes)
void IntMatrix_Print(struct IntMatrix * pMatrix)
{
    for (size_t i = 0; i < pMatrix->sizeHeight; ++i)
    {
        for (size_t j = 0; j < pMatrix->sizeWidth; ++j)
        {
            printf("%i ", pMatrix->data[i * pMatrix->sizeWidth + j]);
        }
        printf("\n");
    }
}

// find a process which is 1 - unmarked, 2 - its ith row of R is less than or equal to A
int find(struct IntArray * pA, struct IntArray * pMarkedProcesses, struct IntMatrix * pR, size_t nProcesses, size_t nResourceTypes)
{
    for (size_t iProcess = 0; iProcess < nProcesses; ++iProcess)
    {
        if (IntArray_GetElementByIndex(pMarkedProcesses, iProcess) == 0) // process iProcess is unmarked
        {
            size_t checks = 0; // check comparison by element
            for (size_t iResType = 0; iResType < nResourceTypes; ++iResType)
            {
                if (IntMatrix_GetElementByIndex(pR, iProcess, iResType) <= IntArray_GetElementByIndex(pA, iResType))
                    ++checks;
            }
            if (checks == nResourceTypes)
            {
                return iProcess; // return index of process if found
            }
        }
    }
    return -1;
}

int main()
{
    struct IntArray * pE;
    struct IntArray * pA;
    struct IntMatrix * pC;
    struct IntMatrix * pR;

    IntArray_CreateEmpty(&pE, ARRAY_INITIAL_CAPACITY);
    IntArray_CreateEmpty(&pA, ARRAY_INITIAL_CAPACITY);

    FILE * pInputFile = fopen("input.txt", "r");

    IntArray_ReadFromFile(pInputFile, pE);
    IntArray_ReadFromFile(pInputFile, pA);

    size_t nResourceTypes = IntArray_Size(pE); // m
    size_t nProcesses = 5;                     // n
    /*
        Remark: the number of processes is not specified in the input file and will be used as a constant.
        However, the functionality is not tied to a constant and can be changed.
    */

    IntMatrix_Create(&pC, nResourceTypes, nProcesses);
    IntMatrix_Create(&pR, nResourceTypes, nProcesses);

    IntMatrix_ReadFromFile(pInputFile, pC);
    IntMatrix_ReadFromFile(pInputFile, pR);

    fclose(pInputFile);

    size_t nMarkedProcesses = 0;
    struct IntArray * pMarkedProcesses;
    IntArray_CreateSized(&pMarkedProcesses, nProcesses);
    IntArray_Fill(pMarkedProcesses, 0);

    int iProcess = find(pA, pMarkedProcesses, pR, nProcesses, nResourceTypes);
    while (iProcess >= 0)
    {
        for (size_t iResType = 0; iResType < nResourceTypes; ++iResType)
        {
            // add the ith row of C to A
            IntArray_SetElementByIndex(
                pA,
                iResType,
                IntArray_GetElementByIndex(pA, iResType) + IntMatrix_GetElementByIndex(pC, iProcess, iResType));
        }
        ++nMarkedProcesses;
        IntArray_SetElementByIndex(pMarkedProcesses, iProcess, 1); // mark the process
        iProcess = find(pA, pMarkedProcesses, pR, nProcesses, nResourceTypes);
    }

    // output results
    FILE * pOutputFile = fopen("output.txt", "w");
    if (nMarkedProcesses == nProcesses)
    {
        fprintf(pOutputFile, "No deadlock is detected.\n");
    }
    else
    {
        fprintf(pOutputFile, "Deadlock is detected for following processes:\n");
        for (size_t i = 0; i < nProcesses; ++i)
        {
            if (IntArray_GetElementByIndex(pMarkedProcesses, i) == 0)
            {
                fprintf(pOutputFile, "%zi ", i + 1);
            }
        }
        fprintf(pOutputFile, "\n");
    }
    fclose(pOutputFile);

    // release memory
    IntArray_Destroy(&pE);
    IntArray_Destroy(&pA);
    IntArray_Destroy(&pMarkedProcesses);
    IntMatrix_Destroy(&pC);
    IntMatrix_Destroy(&pR);
    return 0;
}